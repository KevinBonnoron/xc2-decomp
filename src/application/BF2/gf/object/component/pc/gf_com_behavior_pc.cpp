#include "gf/object/component/pc/gf_com_behavior_pc.h"

#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "anm/anm_asm_listener.h"
#include "framework/coli/coli_charactor_proxy.h"
#include "framework/coli/coli_object.h"
#include "framework/ik/ik_placement_ground_solver.h"
#include "framework/ik/ik_slope_ground_solver.h"
#include "framework/ik/ik_two_chara_ground_solver.h"
#include "framework/memory/allocator.h"
#include "framework/object/updatable_object.h"
#include "framework/reference_frame.h"
#include "fw/fw_coli_check.h"
#include "fw/fw_param_manager.h"
#include "gf/field/gf_field_lod.h"
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
#include "gf/object/component/gf_com_ik.h"
#include "gf/object/component/gf_com_sound.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/component/gimmick/gf_com_behavior_gmk.h"
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
#include "gf/object/gf_obj_util.h"
#include "gf/request/gf_req_scom.h"
#include "idcoli/idcoli.h"
#include "idcoli/idcoli_util_coli.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_plane.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/delegate.h"
#include "mm_mtl/fixed_vector.h"
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

void GfComBehaviorPc::Listener::onWkStandbyLogout() { m_comBehaviorPc->unknown130 = nullptr; }

GfComBehaviorPc::GfComBehaviorPc() : m_hfsm(fw::Allocator::getProcAllocator()), unknown130(nullptr), m_listener(this) {}

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
  if (m_hfsm.m_pState != nullptr) {
    message.unknown08 = m_hfsm.m_pState->m_state;
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

bool GfComBehaviorPc::warpWall(GfComPropertyPc &property) {
  const pc::WarpParam *param = property.unknown006();
  EnviromentSensor::HorizonPacket packet;
  EnviromentSensor::unknown006 wall;
  packet.unknown00 = 0x40;
  mm::unknown011(property.unknown130.unknown10, mm::Vec3::unitZ, packet.unknown10);
  packet.unknown20 = 0.0f;
  packet.unknown24 = param->wallSearchDist;
  packet.unknown30 = property.getEnvSensor()->unknown290;
  packet.unknown38 = &wall;
  EnviromentSensor::searchHorizon(property.unknown130.unknown00, &packet);
  if (((packet.unknown34 >> 6) & 1) && wall.unknown60.unknown24_4) {
    GfComTransform *comTransform = mm::mtl::dynamicCast<GfComTransform>(unknown08->unknown38[GfComTransform::COMPONENT_INDEX]);
    fw::Transform &frameTransform = comTransform->unknown10->unknown003();
    frameTransform.unknown00 = property.unknown130.unknown00;
    frameTransform.unknown10 = property.unknown130.unknown10;
    property.m_propertyField.unknown130 = wall.unknown60;
    property.m_propertyField.unknown10_6 = true;
    fw::ColiObject *coli = unknown08->getComponent<GfComCollider>()->unknown001();
    if (coli != nullptr) {
      mm::Mat44 matrix;
      frameTransform.unknown001(matrix);
      coli->setInstantlyMatrix(matrix);
    }
    resetHeadColPosition(frameTransform);
    return true;
  }
  return false;
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

void GfComBehaviorPc::procMsgObjectNotifyDamage(fw::MessageObject *sender, MsgObjectNotifyDamage &message) {
  const MsgObjectDamage *damage = message.m_msgObjectDamage;
  if (damage != nullptr && damage->unknown10 == 0 && damage->unknown2a) {
    if (getProperty()->unknown111_1) {
      pc::StateUtilField::requestGetOffRider(*this);
    }
  }

  GfStateBase::unknown001 event;
  event.unknown00 = sender;
  event.unknown08 = &message;
  m_hfsm.execEvent(&event);
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
    m_hfsm.execEvent(&event);
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
    message.m_GF_OBJ_HANDLE = plugin->m_GF_OBJ_HANDLE;
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

// 1.0.0: 0x710056b96c; recieveMessage inlines it.
void GfComBehaviorPc::procMsgPcFieldWarp(fw::MessageObject *sender, MsgPcFieldWarp &message) {
  GfComPropertyPc *property = unknown08->getComponent<GfComPropertyPc>();
  if (property->unknown110_0) {
    if (!message.unknown30) {
      property->unknown003(message.m_transform, 0);
    } else {
      warpExternal(*property, message.m_transform);
      onWarpNormal(*property);
    }
    message.unknown31 = true;
  }
}

void GfComBehaviorPc::procMsgPcFieldChangeControlMode(fw::MessageObject *sender, MsgPcFieldChangeControlMode &message) {
  GfComPropertyPc *property = unknown08->getComponent<GfComPropertyPc>();
  GfComAsm *comAsm = unknown08->getComponent<GfComAsm>();
  u32 mode = getMode(*property);
  if (mode == message.unknown08) {
    return;
  }
  property->unknown113_2 = false;
  m_hfsm.clearState();
  switch (mode) {
  case 0:
    if (unknown98) {
      unknown98->cleanup(*property);
      unknown98.reset();
    }
    m_pluginManager.destroyPlugin<pc::DeadColCheckPlugin>();
    m_pluginManager.destroyPlugin<pc::TerrainDamagePlugin>();
    m_pluginManager.destroyPlugin<pc::AccessPlugin>();
    m_pluginManager.destroyPlugin<pc::FallIntoColiPlugin>();
    m_pluginManager.destroyPlugin<pc::FallDamagePlugin>();
    m_pluginManager.destroyPlugin<pc::FadePlugin>();
    m_pluginManager.destroyPlugin<pc::LurePlugin>();
    m_pluginManager.destroyPlugin<pc::FallDistanceAchievPlugin>();
    property->setPadControl(false);
    break;
  case 2: {
    fw::ColiObject *coli = unknown08->getComponent<GfComCollider>()->unknown001();
    if (coli != nullptr) {
      coli->setActivate(true);
    }
    property->unknown111_1 = false;
    pc::AttachPlugin *attach = unknown001<pc::AttachPlugin>(12);
    if (attach != nullptr) {
      attach->setActivate(true);
    }
    comAsm->setState("S_idle", ANIM_LAYER_UNKNOWN_0);
    break;
  }
  case 1:
    if (unknown98) {
      unknown98->cleanup(*property);
      unknown98.reset();
    }
    break;
  }
  switch (message.unknown08) {
  case 0:
// __LINE__ must be 2094 as in the original file: it is the line argument of operator new.
#line 2094 "gf/object/component/pc/gf_com_behavior_pc.cpp"
    unknown98.reset(new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) pc::PadAgent(0));
    unknown98->setup(*property);
    property->setPadControl(true);
    m_pluginManager.createPlugin<pc::AccessPlugin>();
    m_pluginManager.createPlugin<pc::FallIntoColiPlugin>();
    m_pluginManager.createPlugin<pc::FallDamagePlugin>();
    m_pluginManager.createPlugin<pc::FadePlugin>();
    m_pluginManager.createPlugin<pc::LurePlugin>();
    m_pluginManager.createPlugin<pc::TerrainDamagePlugin>();
    m_pluginManager.createPlugin<pc::DeadColCheckPlugin>();
    m_pluginManager.createPlugin<pc::FallDistanceAchievPlugin>();
    m_hfsm.setState(pc::STATE_ID_UNKNOWN_3);
    comAsm->setState("S_idle", ANIM_LAYER_UNKNOWN_0);
    unknown002(m_pluginManager, 16);
    unknown002(m_pluginManager, 19);
    return;
  case 2: {
    fw::ColiObject *coli = unknown08->getComponent<GfComCollider>()->unknown001();
    if (coli != nullptr) {
      coli->setActivate(false);
    }
    property->unknown111_1 = true;
    GfComIK *ik = unknown08->getComponent<GfComIK>();
    if (ik != nullptr) {
      fw::PlacementGroundSolver *placement = ik->unknown003<fw::PlacementGroundSolver>(unknown002_2);
      if (placement != nullptr) {
        placement->setEnablePlacement(false);
        placement->unknown65 = false;
      }
      fw::SlopeGroundSolver *slope = ik->unknown003<fw::SlopeGroundSolver>(unknown002_2);
      if (slope != nullptr) {
        slope->setEnablePlacement(false);
        slope->unknown88 = false;
      }
      fw::TwoCharaGroundSolver *twoChara = ik->unknown003<fw::TwoCharaGroundSolver>(unknown002_2);
      if (twoChara != nullptr) {
        twoChara->setEnablePlacement(false);
        twoChara->unknownb9 = false;
      }
    }
    pc::AttachPlugin *attach = unknown001<pc::AttachPlugin>(12);
    if (attach != nullptr) {
      attach->setActivate(false);
    }
    comAsm->setState("S_ride", ANIM_LAYER_UNKNOWN_0);
    m_hfsm.setState(pc::STATE_ID_UNKNOWN_57);
    return;
  }
  case 1:
// __LINE__ must be 2129 as in the original file: it is the line argument of operator new.
#line 2129 "gf/object/component/pc/gf_com_behavior_pc.cpp"
    unknown98.reset(new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) pc::AIAgent());
    unknown98->setup(*property);
    m_hfsm.setState(pc::STATE_ID_UNKNOWN_3);
    return;
  default:
    return;
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

// 1.0.0: 0x710056ca00. The game inlines it into procMsgPcFieldElvWarp (no call), so it is defined in this unit before its users.
bool isSameElv(GF_OBJ_HANDLE *handle, const MsgPcGetElvLift &lift) {
  if (handle != unknown020 && !lift.unknown08.empty()) {
    for (GF_OBJ_HANDLE *const *it = lift.unknown08.begin(); it != lift.unknown08.end(); it++) {
      if (*it == handle) {
        return true;
      }
    }
  }
  return false;
}

// 1.0.0: 0x710056ca58. The game inlines it into procMsgPcFieldChangeControlMode (0x710056bab8, no call) and keeps this copy after isSameElv, so it is defined in this unit and not in
// gf_com_property_pc.cpp.
u32 getMode(GfComPropertyPc &property) {
  if (property.unknown111_1) {
    return 2;
  }

  if (property.unknown111_2) {
    return 0;
  }

  return 1;
}

void GfComBehaviorPc::procMsgPcFieldElvWarp(fw::MessageObject *sender, MsgPcFieldElvWarp &message) {
  GfComPropertyPc *property = unknown08->getComponent<GfComPropertyPc>();
  if (property->unknown111_1) {
    return;
  }
  const MsgPcGetElvLift *lift = message.m_msgPcGetElvLift;
  pc::AttachPlugin *attach = unknown001<pc::AttachPlugin>(12);
  if (attach != nullptr && isSameElv(attach->m_GF_OBJ_HANDLE, *lift)) {
    return;
  }
  GfObj *elevator = GfObjUtil::getObj(message.m_GF_OBJ_HANDLE);
  if (elevator == nullptr) {
    return;
  }
  GfComTransform *comTransform = elevator->getComponent<GfComTransform>();
  const mm::Vec3 &position = comTransform->getPosition();
  const mm::Quat &rotation = comTransform->getRotation();
  const fw::ParamList *paramList = fw::ParamManager::get()->unknown408[6].operator->();
  // The local `param` places the load of unknown38 after the list lookup (0x710056c6f4); with the lookup written in the expression of `offset` the index is loaded first (first difference at
  // 0x710056c6f4). The null test of the ternary folds away, as the game's code has none.
  const FormationParam *param = paramList->unknown0c > 3 ? static_cast<const FormationParam *>(paramList->unknown10[3].param) : nullptr;
  const mm::Pnt<f32> &offset = param->offsets[property->unknown38 - 1];
  fw::Transform target;
  // Ruling 8: the statements of mm::unknown011 written out again (1.0.0: 0x710056c560, 296 instructions). Measured: the call form `mm::unknown011(rotation, vector, target.unknown00)`
  // matches this function but breaks gf::GfComBehaviorPc::warpWall (259 instructions, 30 differing lines: a second user of the helper changes how it is simplified); the statements
  // written out here keep both functions at 0 differing lines.
  mm::Vec3 vector(offset.x, 0.0f, offset.y);
  f32 tx = rotation.y * vector.z - rotation.z * vector.y + rotation.w * vector.x;
  f32 ty = rotation.z * vector.x - vector.z * rotation.x + vector.y * rotation.w;
  f32 tz = vector.y * rotation.x - rotation.y * vector.x + vector.z * rotation.w;
  f32 tw = -vector.x * rotation.x - rotation.y * vector.y - vector.z * rotation.z;
  target.unknown00.x = -(rotation.z * ty) + rotation.y * tz - rotation.x * tw + rotation.w * tx;
  target.unknown00.y = -(rotation.x * tz) + rotation.z * tx - rotation.y * tw + rotation.w * ty;
  target.unknown00.z = -(rotation.y * tx) + rotation.x * ty - rotation.z * tw + rotation.w * tz;
  target.unknown00 += position;
  target.unknown10 = rotation;
  // ColiCheckConfig block. A file-local helper taking the three differing values (`(config, flags, mask, mode)`) also matches (296 instructions, 0 differing lines), but this is its only
  // user in gf_com_behavior_pc.cpp and gf_com_property_pc.cpp, so the helper has no proof of existence (AGENTS.md, ruling 9). The same block is written out by the matching functions of
  // main (GfGamePlayerPicker::movePlayer in gf_game_player_picker.cpp, StateFieldIdle::checkSpace in gf_pc_state_field_idle.cpp, EnviromentSensor::searchHorizon in
  // gf_environment_sensor.cpp, and GfComEnvSensor::flushGroundSingle, GmkClimbing::updateIcon...), and no helper of the tree sets it.
  fw::ColiCheckConfig config;
  config.unknown08 = 0.0f;
  config.unknown0c = 0.0f;
  config.unknown14 = false;
  config.unknown15 = false;
  config.unknown10 = 1;
  config.unknown04 = 0x800000f6;
  config.unknown00 = 9;
  // `start` and `end` stay named locals: the same two sums as arguments of the call give other stack slots (first difference at 0x710056c6f8).
  mm::Vec3 start = target.unknown00 + mm::Vec3::unitY * 3.0f;
  mm::Vec3 end = target.unknown00 - mm::Vec3::unitY * 3.0f;
  fw::TColiCheckResult<256> result;
  fw::ColiCheck::testLine(result, start, end, config);
  bool isElevator = false;
  if (result.getCount() != 0) {
    fw::ColiUserData *userData = static_cast<fw::ColiUserData *>(result.unknown003(0));
    if (userData != nullptr) {
      GfFieldLodColiAnim::ColiUserData *lodUserData = mm::mtl::dynamicCast<GfFieldLodColiAnim::ColiUserData>(userData);
      isElevator = lodUserData != nullptr && isSameElv(lodUserData->m_GF_OBJ_HANDLE, *lift);
    }
  }
  if (isElevator) {
    target.unknown00 = result.getPosition(0);
  } else {
    GfGamePlayerFormation *formation = GfGamePlayerFormation::get();
    target = formation->unknowne0[formation->unknown1a0[property->unknown38].unknown00];
  }
  warpExternal(*property, target);
  onWarpNormal(*property);
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
    proxy.m_coliObject = coli;
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
    m_hfsm.setState(pc::STATE_ID_UNKNOWN_46);
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
    m_hfsm.execEvent(&event);
  }
}

void GfComBehaviorPc::procMsgGameChangeTarget(fw::MessageObject *sender, MsgGameChangeTarget &message) {
  pc::TargetIKPlugin *targetIK = unknown001<pc::TargetIKPlugin>(6);
  if (targetIK == nullptr) {
    return;
  }

  pc::LookAtPlugin *lookAt = unknown001<pc::LookAtPlugin>(5);
  GfComPropertyPc *property = unknown08->getComponent<GfComPropertyPc>();
  if (message.m_GF_OBJ_HANDLE == unknown020) {
    targetIK->setActivate(false);
    if (lookAt != nullptr && property->m_propertyField.unknown10_1) {
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
  m_pluginManager.beginSetup(*this, 0x16);
  m_pluginManager.unknown001<FootStepPlugin>(0, true);
  m_pluginManager.unknown001<EyeBlinkPlugin>(1, info.unknown04);
  m_pluginManager.unknown001<LipSyncPlugin>(2, true);
  m_pluginManager.unknown001<FootIkControllerPlugin>(3, true);
  m_pluginManager.unknown001<pc::AccessPlugin>(4, isPad);
  m_pluginManager.unknown001<pc::FallIntoColiPlugin>(9, isPad);
  m_pluginManager.unknown001<pc::FadePlugin>(11, isPad);
  m_pluginManager.unknown001<pc::LurePlugin>(15, isPad);
  m_pluginManager.unknown001<pc::LookAtPlugin>(5, true);
  m_pluginManager.unknown001<pc::TargetIKPlugin>(6, true);
  m_pluginManager.unknown001<pc::FallDamagePlugin>(7, isMainPc);
  m_pluginManager.unknown001<pc::TimerPlugin>(8, true);
  m_pluginManager.unknown001<pc::SlidePlugin>(10, true);
  m_pluginManager.unknown001<pc::AttachPlugin>(12, true);
  m_pluginManager.unknown001<pc::ColVelCalculatorPlugin>(13, true);
  m_pluginManager.unknown001<pc::TerrainDamagePlugin>(16, isMainPc);
  m_pluginManager.unknown001<pc::FallDistancePlugin>(17, true);
  m_pluginManager.unknown001<pc::WaterInPlugin>(18, true);
  m_pluginManager.unknown001<pc::DeadColCheckPlugin>(19, isMainPc);
  m_pluginManager.unknown001<pc::LookAxisPlugin>(20, true);
  m_pluginManager.unknown001<pc::FallDistanceAchievPlugin>(21, isMainPc);
  m_pluginManager.endSetup();
  unknown002(m_pluginManager, 13);
  unknown002(m_pluginManager, 16);
  unknown002(m_pluginManager, 2);
  unknown002(m_pluginManager, 3);
  unknown002(m_pluginManager, 19);
  unknown002(m_pluginManager, 20);
  m_hfsm.beginSetup(this, 0x52, 8);
  pc::registerFieldStates(m_hfsm);
  pc::registerBattleStates(m_hfsm);
  m_hfsm.endSetup();
  m_hfsm.setState(info.unknown00);
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
  m_hfsm.cleanup();
  m_pluginManager.cleanup();
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
