#include "gf/object/component/pc/gf_com_behavior_pc.h"

#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "anm/anm_asm_listener.h"
#include "framework/coli/coli_charactor_proxy.h"
#include "framework/coli/coli_object.h"
#include "framework/memory/allocator.h"
#include "framework/object/updatable_object.h"
#include "framework/reference_frame.h"
#include "fw/fw_param_manager.h"
#include "gf/game/gf_game_player_formation.h"
#include "gf/gf_allocator.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/behavior/plugin/gf_eye_blink_plugin.h"
#include "gf/object/component/behavior/plugin/gf_foot_ik_controller_plugin.h"
#include "gf/object/component/behavior/plugin/gf_foot_step_plugin.h"
#include "gf/object/component/behavior/plugin/gf_lip_sync_plugin.h"
#include "gf/object/component/behavior/plugin/gf_plugin.h"
#include "gf/object/component/behavior/plugin/gf_plugin_manager.h"
#include "gf/object/component/effect/gf_com_effect_caster.h"
#include "gf/object/component/enemy/gf_enemy_state_battle.h"
#include "gf/object/component/env_sensor/gf_com_env_sensor.h"
#include "gf/object/component/gf_com_collider.h"
#include "gf/object/component/gf_com_dynamics.h"
#include "gf/object/component/gf_com_sound.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/component/model/gf_com_model.h"
#include "gf/object/component/pc/battle/gf_pc_battle_states.h"
#include "gf/object/component/pc/field/gf_pc_field_states.h"
#include "gf/object/component/pc/gf_pc_agent.h"
#include "gf/object/component/pc/gf_pc_ai_agent.h"
#include "gf/object/component/pc/gf_pc_pad_agent.h"
#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "gf/object/component/pc/param/gf_pc_param.h"
#include "gf/object/component/pc/plugin/gf_pc_access_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_attach_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_col_velocity_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_dead_col_check_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_fade_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_fall_damage_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_fall_distance_achiev_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_fall_distance_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_fall_into_coli_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_look_at_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_look_axis_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_lure_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_slide_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_target_ik_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_terrain_damage_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_timer_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_water_in_plugin.h"
#include "gf/object/component/property/gf_com_property.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/request/gf_req_scom.h"
#include "idcoli/idcoli.h"
#include "idcoli/idcoli_util_coli.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_plane.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/delegate.h"
#include "mm_mtl/vector.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

bool isAttenuationPack(const char *name) {
  return strcmp(name, "se_mov_pc_default") == 0 || strcmp(name, "se_fld_move_nopon") == 0 || strcmp(name, "se_fld_move_large") == 0 || strcmp(name, "se_fld_move_hana") == 0 ||
         strcmp(name, "se_fld_move_beast") == 0 || strcmp(name, "se_fld_move_float") == 0 || strcmp(name, "se_fld_allmap") == 0;
}

// Inferred helper: activates the plugin at an index when it exists, repeated by GfComBehaviorPc::setup (0x71005646e4) for six plugins; original name unknown. The game reloads the plugin table for
// each one: a loop over an index table does not match (1231 instructions instead of 1323), so the six calls are written out.
static void unknown002(PluginManager &manager, u32 index) {
  Plugin *plugin = manager.unknown28[index];
  if (plugin != nullptr) {
    plugin->setActivate(true);
  }
}

namespace pc {

// Named as the game's global symbols gf::pc::ASM_CB_NAME_FIELD and gf::pc::ASM_CB_NAME_BATTLE.
const char *ASM_CB_NAME_FIELD = "field";
const char *ASM_CB_NAME_BATTLE = "battle";

Plugin *AccessPlugin::create() {
  // __LINE__ must be 31 as in the original header: it is the line argument of operator new.
#line 31 "gf/object/component/pc/plugin/gf_pc_access_plugin.h"
  return new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) AccessPlugin();
}

Plugin *AttachPlugin::create() {
  // __LINE__ must be 26 as in the original header: it is the line argument of operator new.
#line 26 "gf/object/component/pc/plugin/gf_pc_attach_plugin.h"
  return new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) AttachPlugin();
}

Plugin *ColVelCalculatorPlugin::create() {
  // __LINE__ must be 27 as in the original header: it is the line argument of operator new.
#line 27 "gf/object/component/pc/plugin/gf_pc_col_velocity_plugin.h"
  return new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ColVelCalculatorPlugin();
}

Plugin *DeadColCheckPlugin::create() {
  // __LINE__ must be 27 as in the original header: it is the line argument of operator new.
#line 27 "gf/object/component/pc/plugin/gf_pc_dead_col_check_plugin.h"
  return new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) DeadColCheckPlugin();
}

Plugin *FadePlugin::create() {
  // __LINE__ must be 34 as in the original header: it is the line argument of operator new.
#line 34 "gf/object/component/pc/plugin/gf_pc_fade_plugin.h"
  return new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) FadePlugin();
}

Plugin *FallDamagePlugin::create() {
  // __LINE__ must be 27 as in the original header: it is the line argument of operator new.
#line 27 "gf/object/component/pc/plugin/gf_pc_fall_damage_plugin.h"
  return new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) FallDamagePlugin();
}

Plugin *FallDistanceAchievPlugin::create() {
  // __LINE__ must be 26 as in the original header: it is the line argument of operator new.
#line 26 "gf/object/component/pc/plugin/gf_pc_fall_distance_achiev_plugin.h"
  return new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) FallDistanceAchievPlugin();
}

Plugin *FallDistancePlugin::create() {
  // __LINE__ must be 26 as in the original header: it is the line argument of operator new.
#line 26 "gf/object/component/pc/plugin/gf_pc_fall_distance_plugin.h"
  return new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) FallDistancePlugin();
}

Plugin *FallIntoColiPlugin::create() {
  // __LINE__ must be 25 as in the original header: it is the line argument of operator new.
#line 25 "gf/object/component/pc/plugin/gf_pc_fall_into_coli_plugin.h"
  return new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) FallIntoColiPlugin();
}

Plugin *LookAxisPlugin::create() {
  // __LINE__ must be 27 as in the original header: it is the line argument of operator new.
#line 27 "gf/object/component/pc/plugin/gf_pc_look_axis_plugin.h"
  return new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) LookAxisPlugin();
}

Plugin *LurePlugin::create() {
  // __LINE__ must be 29 as in the original header: it is the line argument of operator new.
#line 29 "gf/object/component/pc/plugin/gf_pc_lure_plugin.h"
  return new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) LurePlugin();
}

Plugin *LookAtPlugin::create() {
  // __LINE__ must be 39 as in the original header: it is the line argument of operator new.
#line 39 "gf/object/component/pc/plugin/gf_pc_lookat_plugin.h"
  return new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) LookAtPlugin();
}

Plugin *SlidePlugin::create() {
  // __LINE__ must be 26 as in the original header: it is the line argument of operator new.
#line 26 "gf/object/component/pc/plugin/gf_pc_slide_plugin.h"
  return new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SlidePlugin();
}

Plugin *TargetIKPlugin::create() {
  // __LINE__ must be 33 as in the original header: it is the line argument of operator new.
#line 33 "gf/object/component/pc/plugin/gf_pc_target_ik_plugin.h"
  return new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) TargetIKPlugin();
}

Plugin *TerrainDamagePlugin::create() {
  // __LINE__ must be 26 as in the original header: it is the line argument of operator new.
#line 26 "gf/object/component/pc/plugin/gf_pc_terrain_damage_plugin.h"
  return new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) TerrainDamagePlugin();
}

Plugin *TimerPlugin::create() {
  // __LINE__ must be 25 as in the original header: it is the line argument of operator new.
#line 25 "gf/object/component/pc/plugin/gf_pc_timer_plugin.h"
  return new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) TimerPlugin();
}

Plugin *WaterInPlugin::create() {
  // __LINE__ must be 25 as in the original header: it is the line argument of operator new.
#line 25 "gf/object/component/pc/plugin/gf_pc_water_in_plugin.h"
  return new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) WaterInPlugin();
}

} // namespace pc

void GfComBehaviorPc::Listener::onWkStandbyLogout() { unknown08->unknown130 = nullptr; }

GfComBehaviorPc::GfComBehaviorPc() : unknowna0(fw::Allocator::getProcAllocator()), unknown130(nullptr), unknown138(this) {}

GfComBehaviorPc::~GfComBehaviorPc() {}

void GfComBehaviorPc::callbackBattle(GfComAsm *comAsm, const CallBackCache &cache) {}

void GfComBehaviorPc::callbackField(GfComAsm *comAsm, const CallBackCache &cache) {}

void GfComBehaviorPc::callbackSound(const fw::ResSoundData &data, fw::SoundResSourceManager::CustomInfo *info) {
  u32 playerId = getProperty()->unknown38;
  if (playerId - 1 < 5 && isAttenuationPack(data.unknown00)) {
    info->unknown00 = static_cast<const f32 *>(fw::ParamManager::get()->unknown408[18].get()->unknown10[0].param)[playerId - 1];
  }
}

void GfComBehaviorPc::procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message) {}

const mm::mtl::RTTI *GfComBehaviorPc::getRTTI() const { return &m_rtti; }

void GfComBehaviorPc::procMsgPcApplyFieldDamage(fw::MessageObject *sender, MsgPcApplyFieldDamage &message) { pc::StateUtil::applyDamage(*this, message.unknown08, true); }

void GfComBehaviorPc::procMsgPcGetState(fw::MessageObject *sender, MsgPcGetState &message) {
  if (unknowna0.m_pState != nullptr) {
    message.unknown08 = unknowna0.m_pState->unknown08;
  }
}

void GfComBehaviorPc::procMsgPcGetLookPoint(fw::MessageObject *sender, MsgPcGetLookPoint &message) {
  if (unknown128.get() != nullptr) {
    message.unknown10 = unknown128->getSyncedWorldTransform().unknown00;
    message.unknown20 = true;
  }
}

void GfComBehaviorPc::procMsgPcResetState(fw::MessageObject *sender, MsgPcResetState &message) {
  GfComPropertyPc *property = getProperty();
  if (!property->unknown111_1) {
    property->flush();
    onWarpNormal(*property);
  }
}

void GfComBehaviorPc::procMsgObjectGetVelocity(fw::MessageObject *sender, MsgObjectGetVelocity &message) {
  GfComPropertyPc *property = unknown08->getComponent<GfComPropertyPc>();
  if (property != nullptr) {
    GfObj *object = static_cast<GfObj *>(unknown08);
    property->recieveMessage(object, message);
  }
}

// 1.0.0: 0x7100567b5c, 151 instructions; the game keeps the null test of the collider component (cbz x20 at 0x7100567c08, joining at the vector read), see GfComCollider::unknown001 and
// UpdatableObject::getComponent. warpExternal reads the collider the same way.
bool GfComBehaviorPc::warpBattle(GfComPropertyPc &property) {
  GfComTransform *comTransform = mm::mtl::dynamicCast<GfComTransform>(unknown08->unknown38[GfComTransform::COMPONENT_INDEX]);
  fw::Transform &frameTransform = comTransform->unknown10->unknown003();
  frameTransform.unknown00 = property.unknown130.unknown00;
  frameTransform.unknown10 = property.unknown130.unknown10;
  fw::ColiObject *coli = unknown08->getComponent<GfComCollider>()->unknown001();
  if (coli != nullptr) {
    mm::Mat44 matrix;
    frameTransform.unknown001(matrix);
    coli->setInstantlyMatrix(matrix);
  }
  resetHeadColPosition(frameTransform);
  return true;
}

bool GfComBehaviorPc::warpFallDead(GfComPropertyPc &property) { return warpNormal(property); }

bool GfComBehaviorPc::warpExternal(GfComPropertyPc &property, const fw::Transform &transform) {
  onWarpBeforeTransform(property);
  GfComTransform *comTransform = mm::mtl::dynamicCast<GfComTransform>(unknown08->unknown38[GfComTransform::COMPONENT_INDEX]);
  comTransform->unknown10->unknown003() = transform;
  fw::ColiObject *coli = unknown08->getComponent<GfComCollider>()->unknown001();
  if (coli != nullptr) {
    mm::Mat44 matrix;
    transform.unknown001(matrix);
    coli->setInstantlyMatrix(matrix);
  }
  resetHeadColPosition(transform);
  onWarpAfterTransform(property);
  return true;
}

void GfComBehaviorPc::onWarpFallDead(GfComPropertyPc &property) {
  onWarpNormal(property);
  property.unknown111_3 = false;
}

void GfComBehaviorPc::onWarp(GfComPropertyPc &property) {
  switch (property.unknown150) {
  case 0:
    onWarpNormal(property);
    break;
  case 1:
    onWarpWall(property);
    break;
  case 2:
    onWarpBattle(property);
    break;
  case 3:
    onWarpFallDead(property);
    break;
  }
}

void GfComBehaviorPc::onWarpBeforeTransform(GfComPropertyPc &property) {
  pc::AttachPlugin *plugin = unknown001<pc::AttachPlugin>(12);
  if (plugin != nullptr) {
    plugin->setActivate(false);
  }
}

void GfComBehaviorPc::onWarpAfterTransform(GfComPropertyPc &property) {
  pc::AttachPlugin *plugin = unknown001<pc::AttachPlugin>(12);
  if (plugin != nullptr) {
    plugin->setActivate(true);
  }
}

void GfComBehaviorPc::procMsgObjectNotifyDamage(fw::MessageObject *sender, MsgObjectNotifyDamage &message) {
  const MsgObjectDamage *damage = message.unknown08;
  if (damage != nullptr && damage->unknown10 == 0 && damage->unknown2a) {
    if (getProperty()->unknown111_1) {
      pc::StateUtilField::requestGetOffRider(*this);
    }
  }

  GfStateBase::unknown001 event;
  event.unknown00 = sender;
  event.unknown08 = &message;
  unknowna0.execEvent(&event);
}

void GfComBehaviorPc::procMsgObjectNotifyDead(fw::MessageObject *sender, MsgObjectNotifyDead &message) {
  if (pc::StateUtilField::testVechile(*this)) {
    pc::StateUtilField::requestGetOffRider(*this);
    pc::StateUtil::sendMessageToBuddy(*this, message);
    return;
  }

  GfComPropertyPc *property = unknown08->getComponent<GfComPropertyPc>();
  if (property->unknown111_1) {
    pc::StateUtilField::requestGetOffRider(*this);
  }
  if (!property->unknown111_3 || message.unknown08 == DEAD_TYPE_UNKNOWN_4) {
    GfStateBase::unknown001 event;
    event.unknown00 = sender;
    event.unknown08 = &message;
    unknowna0.execEvent(&event);
  }
}

void GfComBehaviorPc::procMsgDebugNotifyReloadLookAtBdat(fw::MessageObject *sender, MsgDebugNotifyReloadLookAtBdat &message) {
  pc::LookAtPlugin *plugin = unknown001<pc::LookAtPlugin>(5);
  if (plugin != nullptr) {
    plugin->onReloadBdat();
  }
}

void GfComBehaviorPc::procMsgPcFieldGetFallMaxHeight(fw::MessageObject *sender, MsgPcFieldGetFallMaxHeight &message) {
  pc::FallDamagePlugin *plugin = unknown001<pc::FallDamagePlugin>(7);
  if (plugin != nullptr) {
    plugin->procMsgPcFieldGetFallMaxHeight(sender, message);
  }
}

void GfComBehaviorPc::procMsgPcFieldSetFallMaxHeight(fw::MessageObject *sender, MsgPcFieldSetFallMaxHeight &message) {
  pc::FallDamagePlugin *plugin = unknown001<pc::FallDamagePlugin>(7);
  if (plugin != nullptr) {
    plugin->setActivate(true);
    plugin->procMsgPcFieldSetFallMaxHeight(sender, message);
  }
}

void GfComBehaviorPc::procMsgPcFieldGetAccessTarget(fw::MessageObject *sender, MsgPcFieldGetAccessTarget &message) {
  pc::AccessPlugin *plugin = unknown001<pc::AccessPlugin>(4);
  if (plugin != nullptr) {
    message.unknown08 = plugin->unknown10;
  }
}

void GfComBehaviorPc::procMsgPcFieldNotifyWall(fw::MessageObject *sender, MsgPcFieldNotifyWall &message) {
  if (unknown98) {
    GfComPropertyPc *property = unknown08->getComponent<GfComPropertyPc>();
    unknown98->recieveMessage(*property, sender, message);
  }
}

void GfComBehaviorPc::procMsgPcFieldNotifyHighJump(fw::MessageObject *sender, MsgPcFieldNotifyHighJump &message) {
  if (unknown98) {
    GfComPropertyPc *property = unknown08->getComponent<GfComPropertyPc>();
    unknown98->recieveMessage(*property, sender, message);
  }
}

void GfComBehaviorPc::procMsgPcFieldNotifyWallJumpStart(fw::MessageObject *sender, MsgPcFieldNotifyWallJumpStart &message) {
  if (unknown98) {
    GfComPropertyPc *property = unknown08->getComponent<GfComPropertyPc>();
    unknown98->recieveMessage(*property, sender, message);
  }
}

void GfComBehaviorPc::procMsgPcFieldNotifyWaterWarp(fw::MessageObject *sender, MsgPcFieldNotifyWaterWarp &message) {
  if (unknown98) {
    GfComPropertyPc *property = unknown08->getComponent<GfComPropertyPc>();
    unknown98->recieveMessage(*property, sender, message);
  }
}

void GfComBehaviorPc::procMsgPcFieldNotifyWaterWarpBuddy(fw::MessageObject *sender, MsgPcFieldNotifyWaterWarpBuddy &message) {
  if (unknown98) {
    GfComPropertyPc *property = unknown08->getComponent<GfComPropertyPc>();
    unknown98->recieveMessage(*property, sender, message);
  }
}

void GfComBehaviorPc::procMsgPcFieldReqFallDeadMotion(fw::MessageObject *sender, MsgPcFieldReqFallDeadMotion &message) {
  GfComPropertyPc *property = unknown08->getComponent<GfComPropertyPc>();
  GfComAsm *comAsm = unknown08->getComponent<GfComAsm>();
  if (strcmp(comAsm->getStateName(ANIM_LAYER_UNKNOWN_0), "S_fall") != 0) {
    comAsm->setState("S_fall", ANIM_LAYER_UNKNOWN_0);
  }
  comAsm->execCmd("C_falldead", ANIM_LAYER_UNKNOWN_0);
}

bool GfComBehaviorPc::warp() {
  GfComPropertyPc *property = unknown08->getComponent<GfComPropertyPc>();
  switch (property->unknown150) {
  case 0:
  case 3:
    return warpNormal(*property);
  case 1:
    return warpWall(*property);
  case 2:
    warpBattle(*property);
    return true;
  default:
    return false;
  }
}

void GfComBehaviorPc::resetHeadColiPos(GfComPropertyPc &property) {
  if (property.unknown40 > FLT_EPSILON) {
    mm::Vec3 position;
    calcHeadColiPos(property.unknown40, property.unknown160, &position);
    property.unknown50 = position;
  }
}

void GfComBehaviorPc::resetHeadColPosition(const fw::Transform &transform) {
  GfComPropertyPc *property = unknown08->getComponent<GfComPropertyPc>();
  if (property->unknown40 > FLT_EPSILON) {
    mm::Vec3 position;
    calcHeadColiPos(property->unknown40, transform, &position);
    property->unknown50 = position;
  }
}

void GfComBehaviorPc::calcHeadColiPos(f32 height, const fw::Transform &transform, mm::Vec3 *position) {
  mm::Vec3 axis = transform.unknown10.rotate(mm::Vec3::unitX);
  mm::Vec3 normal = mm::Vec3::unitY;
  EnviromentSensor::GroundInfo *ground = pc::StateUtil::getGroundInfo(*this);
  if (ground != nullptr) {
    normal = ground->unknown10.normal;
  }
  mm::Vec3 direction(axis.y * normal.z - axis.z * normal.y, axis.z * normal.x - axis.x * normal.z, axis.x * normal.y - axis.y * normal.x);
  if (!(fabsf(direction.x) <= 0.000001f) || !(fabsf(direction.y) <= 0.000001f) || !(fabsf(direction.z) <= 0.000001f)) {
    direction.unknown001();
  } else {
    direction = transform.unknown10.rotate(mm::Vec3::unitZ);
  }
  direction *= height;
  *position = direction + transform.unknown00;
}

void GfComBehaviorPc::detectHead(GfComPropertyPc &property, fw::ColiObject *coli, const mm::Vec3 &move, fw::Transform *transform) {
  if ((coli != nullptr && !coli->isActivate()) || !property.unknown111_6) {
    return;
  }
  f32 height = property.unknown40;
  if (height > FLT_EPSILON && coli->unknowne8.get() != nullptr && coli->unknowne8.get()->unknown00 == fw::unknown031::TYPE_UNKNOWN_3) {
    const fw::unknown134 *shape = static_cast<const fw::unknown134 *>(coli->unknowne8.get());
    idcoli::IDColiMove coliMove;
    coliMove.setShapeParms(shape->unknown08, shape->unknown04);
    coliMove.unknown00 = true;
    coliMove.unknown01 = true;
    coliMove.unknown02 = true;
    coliMove.unknown10.unknowne8 = 0x1000d;
    coliMove.setAccuracy(true);
    mm::Vec3 headPosition;
    calcHeadColiPos(height, *transform, &headPosition);
    mm::Vec3 delta = headPosition - property.unknown50;
    coliMove.moveColi(property.unknown50, delta + move);
    mm::Vec3 horizontal(coliMove.unknown130.x - delta.x, 0.0f, coliMove.unknown130.z - delta.z);
    fw::ColiCharactorProxy proxy;
    mm::Mat44 matrix;
    transform->unknown001(matrix);
    coli->setInstantlyMatrix(matrix);
    proxy.unknown00 = coli;
    if (!(fabsf(horizontal.x) <= 0.000001f) || !(fabsf(horizontal.z) <= 0.000001f)) {
      mm::Vec3 down = move;
      if (fabsf(down.x) <= 0.000001f && fabsf(down.y) <= 0.000001f && fabsf(down.z) <= 0.000001f) {
        down = mm::Vec3::unitY * -0.001f;
      }
      f32 adsorption = coli->getAdsorption();
      if (coli->testAttribute(fw::COLI_ATRR_UNKNOWN_0)) {
        coli->setAdsorption(0.1f);
      }
      mm::Vec3 result;
      proxy.integrate(horizontal, down, &result);
      coli->setAdsorption(adsorption);
      transform->unknown00 += result;
    }
    mm::Vec3 position;
    calcHeadColiPos(height, *transform, &position);
    property.unknown50 = position;
  }
}

void GfComBehaviorPc::integrateMove(const fw::UpdateInfo &info) {
  pc::StateUtil::reflectionAdsorption(*this);
  GfComPropertyPc *property = unknown08->getComponent<GfComPropertyPc>();
  if (!property->unknown112_0) {
    switch (property->unknown120) {
    case 0:
      integrateMoveNormal(info, *property);
      break;
    case 1:
      integrateMoveChildHeight(info, *property);
      break;
    case 2:
      integrateMoveWall(info, *property);
      break;
    }
  }
}

void GfComBehaviorPc::onWarpWall(GfComPropertyPc &property) {
  GfComTransform *transform = unknown08->getComponent<GfComTransform>();
  const fw::Transform &world = transform->unknown10->getSyncedWorldTransform();
  unknown08->getComponent<GfComEnvSensor>()->flushEnv(world);
  property.flush();
  GfComAsm *comAsm = unknown08->getComponent<GfComAsm>();
  if (comAsm != nullptr && comAsm->setState("S_climbidle_base", ANIM_LAYER_UNKNOWN_0)) {
    unknowna0.setState(pc::STATE_ID_UNKNOWN_46);
  }
  GfComDynamics *dynamics = unknown08->getComponent<GfComDynamics>();
  if (dynamics != nullptr) {
    dynamics->resetMovement();
  }
  const pc::WarpParam *param = property.unknown006();
  SCOM_OBJ_ALPHA::create(static_cast<GfObj *>(unknown08)->unknownf8, 0.0f, 0.0f);
  SCOM_OBJ_ALPHA::create(static_cast<GfObj *>(unknown08)->unknownf8, param->fadeTime, 1.0f);
}

void GfComBehaviorPc::onWarpBattle(GfComPropertyPc &property) {
  GfComTransform *transform = unknown08->getComponent<GfComTransform>();
  const fw::Transform &world = transform->unknown10->getSyncedWorldTransform();
  unknown08->getComponent<GfComEnvSensor>()->flushEnv(world);
  property.flush();
  property.unknownc0 = 0.0f;
  property.unknown110_7 = false;
  GfComDynamics *dynamics = unknown08->getComponent<GfComDynamics>();
  if (dynamics != nullptr) {
    dynamics->resetMovement();
  }
  pc::FallDamagePlugin *fallDamage = unknown001<pc::FallDamagePlugin>(7);
  if (fallDamage != nullptr) {
    fallDamage->cacheMaxHeight(true);
  }
  pc::FallDistancePlugin *fallDistance = unknown001<pc::FallDistancePlugin>(17);
  if (fallDistance != nullptr) {
    fallDistance->cacheMaxHeight(true);
  }
}

void GfComBehaviorPc::procAnimCallback(GfComAsm *comAsm, const CallBackCache &cache) {
  const anm::AsmAnnotetion *annotation = cache.unknown08;
  if (strcmp(annotation->unknown00, "look") == 0) {
    pc::StateUtil::setEnableLookIK(*this, annotation->unknown10_int != 0);
  } else if (strcmp(annotation->unknown00, "changeLookAxis") == 0) {
    pc::LookAxisPlugin *plugin = unknown001<pc::LookAxisPlugin>(20);
    if (plugin != nullptr) {
      plugin->changeAxisYaw(atof(cache.unknown08->unknown10));
    }
  } else {
    MsgObjectNotifyAsmCallback message(comAsm, annotation);
    GfStateBase::unknown001 event;
    event.unknown00 = static_cast<GfObj *>(unknown08);
    event.unknown08 = &message;
    unknowna0.execEvent(&event);
  }
}

void GfComBehaviorPc::procMsgGameChangeTarget(fw::MessageObject *sender, MsgGameChangeTarget &message) {
  pc::TargetIKPlugin *targetIK = unknown001<pc::TargetIKPlugin>(6);
  if (targetIK == nullptr) {
    return;
  }

  pc::LookAtPlugin *lookAt = unknown001<pc::LookAtPlugin>(5);
  GfComPropertyPc *property = unknown08->getComponent<GfComPropertyPc>();
  if (message.unknown08 == unknown020) {
    targetIK->setActivate(false);
    if (lookAt != nullptr && property->unknown310.unknown10_1) {
      lookAt->setActivate(true);
    }
  } else {
    if (lookAt != nullptr) {
      lookAt->setActivate(false);
    }
    if (property->unknown111_0) {
      targetIK->setActivate(true);
    }
  }
  targetIK->procMsgGameChangeTarget(sender, message);
}

void GfComBehaviorPc::setup(const SetupInfo &info) {
  static_cast<GfObj *>(unknown08)->unknown110 |= 2;
  GfComAsm *comAsm = unknown08->getComponent<GfComAsm>();
  if (comAsm != nullptr) {
    unknown014(comAsm);
    comAsm->unknown70[1].unknown00 = pc::ASM_CB_NAME_FIELD;
    comAsm->unknown70[1].unknown08.bind<GfComBehaviorPc>(this, &GfComBehaviorPc::callbackField);
    comAsm->unknown70[2].unknown00 = pc::ASM_CB_NAME_BATTLE;
    comAsm->unknown70[2].unknown08.bind<GfComBehaviorPc>(this, &GfComBehaviorPc::callbackBattle);
  }
  GfComSound *comSound = unknown08->getComponent<GfComSound>();
  if (comSound != nullptr) {
    comSound->unknown130.bind<GfComBehaviorPc>(this, &GfComBehaviorPc::callbackSound);
  }
  GfComPropertyPc *property = unknown08->getComponent<GfComPropertyPc>();
  bool isPad = property->unknown111_2;
  if (isPad) {
// __LINE__ must be 156 as in the original file: it is the line argument of operator new.
#line 156 "gf/object/component/pc/gf_com_behavior_pc.cpp"
    unknown98.reset(new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) pc::PadAgent(0));
  } else {
// __LINE__ must be 161 as in the original file: it is the line argument of operator new.
#line 161 "gf/object/component/pc/gf_com_behavior_pc.cpp"
    unknown98.reset(new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) pc::AIAgent());
  }
  unknown98->setup(*property);
  GfGamePlayerFormation *formation = GfGamePlayerFormation::get();
  bool isMainPc = false;
  if (formation != nullptr && property->unknown38 != PLAYER_ID_UNKNOWN_4294967295) {
    isMainPc = formation->unknown1a0[property->unknown38].unknown10;
  }
  unknown10.beginSetup(*this, 0x16);
  unknown10.unknown001<FootStepPlugin>(0, true);
  unknown10.unknown001<EyeBlinkPlugin>(1, info.unknown04);
  unknown10.unknown001<LipSyncPlugin>(2, true);
  unknown10.unknown001<FootIkControllerPlugin>(3, true);
  unknown10.unknown001<pc::AccessPlugin>(4, isPad);
  unknown10.unknown001<pc::FallIntoColiPlugin>(9, isPad);
  unknown10.unknown001<pc::FadePlugin>(11, isPad);
  unknown10.unknown001<pc::LurePlugin>(15, isPad);
  unknown10.unknown001<pc::LookAtPlugin>(5, true);
  unknown10.unknown001<pc::TargetIKPlugin>(6, true);
  unknown10.unknown001<pc::FallDamagePlugin>(7, isMainPc);
  unknown10.unknown001<pc::TimerPlugin>(8, true);
  unknown10.unknown001<pc::SlidePlugin>(10, true);
  unknown10.unknown001<pc::AttachPlugin>(12, true);
  unknown10.unknown001<pc::ColVelCalculatorPlugin>(13, true);
  unknown10.unknown001<pc::TerrainDamagePlugin>(16, isMainPc);
  unknown10.unknown001<pc::FallDistancePlugin>(17, true);
  unknown10.unknown001<pc::WaterInPlugin>(18, true);
  unknown10.unknown001<pc::DeadColCheckPlugin>(19, isMainPc);
  unknown10.unknown001<pc::LookAxisPlugin>(20, true);
  unknown10.unknown001<pc::FallDistanceAchievPlugin>(21, isMainPc);
  unknown10.endSetup();
  unknown002(unknown10, 13);
  unknown002(unknown10, 16);
  unknown002(unknown10, 2);
  unknown002(unknown10, 3);
  unknown002(unknown10, 19);
  unknown002(unknown10, 20);
  unknowna0.beginSetup(this, 0x52, 8);
  pc::registerFieldStates(unknowna0);
  pc::registerBattleStates(unknowna0);
  unknowna0.endSetup();
  unknowna0.setState(info.unknown00);
  GfComModel *model = unknown08->getComponent<GfComModel>();
  unknown128 = model->createBoneReferenceFrame("JU_neck");
  if (unknown128.get() == nullptr) {
    unknown128 = model->createBoneReferenceFrame("JU_spA");
    if (unknown128.get() == nullptr) {
      GfComTransform *transform = unknown08->getComponent<GfComTransform>();
      unknown128 = transform->unknown18.get() == nullptr ? transform->unknown10 : transform->unknown18;
    }
  }
  GfComEffectCaster *effectCaster = unknown08->getComponent<GfComEffectCaster>();
  if (effectCaster != nullptr) {
    effectCaster->unknown28 = property->unknown2f0;
  }
}

void GfComBehaviorPc::cleanup() {
  if (unknown128.get() != nullptr) {
    GfComModel *model = unknown08->getComponent<GfComModel>();
    if (model->getBoneReferenceFrame("JU_neck").get() != nullptr) {
      model->destroyBoneReferenceFrame("JU_neck");
    } else if (model->getBoneReferenceFrame("JU_spA").get() != nullptr) {
      model->destroyBoneReferenceFrame("JU_spA");
    }
    unknown128 = nullptr;
  }
  unknowna0.cleanup();
  unknown10.cleanup();
  if (unknown98) {
    GfComPropertyPc *property = unknown08->getComponent<GfComPropertyPc>();
    unknown98->cleanup(*property);
    unknown98.reset();
  }
}

void GfComBehaviorPc::setEnableAgentField(bool isEnable) {
  GfComPropertyPc *property = unknown08->getComponent<GfComPropertyPc>();
  if (unknown98 && property != nullptr) {
    unknown98->setFieldAI(*property, isEnable);
  }
}

void GfComBehaviorPc::setEnableAgentBattle(bool isEnable) {
  GfComPropertyPc *property = unknown08->getComponent<GfComPropertyPc>();
  if (unknown98 && property != nullptr) {
    unknown98->setBattleAI(*property, isEnable);
  }
}

} // namespace gf

template void gf::PluginManager::createPlugin<gf::pc::AccessPlugin>();
template void gf::PluginManager::createPlugin<gf::pc::FallIntoColiPlugin>();
template void gf::PluginManager::createPlugin<gf::pc::FallDamagePlugin>();
template void gf::PluginManager::createPlugin<gf::pc::FadePlugin>();
template void gf::PluginManager::createPlugin<gf::pc::LurePlugin>();
template void gf::PluginManager::createPlugin<gf::pc::TerrainDamagePlugin>();
template void gf::PluginManager::createPlugin<gf::pc::DeadColCheckPlugin>();
template void gf::PluginManager::createPlugin<gf::pc::FallDistanceAchievPlugin>();
template void gf::PluginManager::destroyPlugin<gf::pc::DeadColCheckPlugin>();
template void gf::PluginManager::destroyPlugin<gf::pc::TerrainDamagePlugin>();
template void gf::PluginManager::destroyPlugin<gf::pc::AccessPlugin>();
template void gf::PluginManager::destroyPlugin<gf::pc::FallIntoColiPlugin>();
template void gf::PluginManager::destroyPlugin<gf::pc::FallDamagePlugin>();
template void gf::PluginManager::destroyPlugin<gf::pc::FadePlugin>();
template void gf::PluginManager::destroyPlugin<gf::pc::LurePlugin>();
template void gf::PluginManager::destroyPlugin<gf::pc::FallDistanceAchievPlugin>();

template void mm::mtl::Delegate<void(gf::GfComAsm *, const gf::CallBackCache &)>::memberFuncInvoker<gf::GfComBehaviorPc>(const mm::mtl::Delegate<void(gf::GfComAsm *, const gf::CallBackCache &)> *,
                                                                                                                         gf::GfComAsm *, const gf::CallBackCache &);
template void mm::mtl::Delegate<void(const fw::ResSoundData &, fw::SoundResSourceManager::CustomInfo *)>::memberFuncInvoker<gf::GfComBehaviorPc>(
    const mm::mtl::Delegate<void(const fw::ResSoundData &, fw::SoundResSourceManager::CustomInfo *)> *, const fw::ResSoundData &, fw::SoundResSourceManager::CustomInfo *);
