// Same order as in the game executable: the field behavior is defined before the enemy behavior component in the same unit.
// clang-format off
#include "gf/object/component/enemy/gf_behavior_enemy_field.cpp"
// clang-format on
#include "gf/object/component/enemy/gf_com_behavior_enemy.h"

#include <math.h>

#include "ai/ai_state.h"
#include "anm/anm_qs_transform.h"
#include "battle/character/battle_character.h"
#include "battle/character/character_manager_battle.h"
#include "battle/character/character_parameter_battle.h"
#include "bdat.h"
#include "framework/coli/coli_object.h"
#include "framework/memory/allocator.h"
#include "framework/reference_frame.h"
#include "fw/fw_transform.h"
#include "fw/fw_update_info.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_rsc.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_enemy.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/field/gf_field_enemy_sensor.h"
#include "gf/field/gf_field_local_steer.h"
#include "gf/field/gf_field_move_speed.h"
#include "gf/field/gf_field_pitch_roll_controller.h"
#include "gf/game/gf_game_mount.h"
#include "gf/game/gf_game_util.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/object/gf_menu_obj_target_info.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/behavior/plugin/gf_foot_step_plugin.h"
#include "gf/object/component/behavior/plugin/gf_plugin_manager.h"
#include "gf/object/component/enemy/gf_enemy_state_battle.h"
#include "gf/object/component/enemy/gf_enemy_state_field_area_walk.h"
#include "gf/object/component/enemy/gf_enemy_state_field_blade.h"
#include "gf/object/component/enemy/gf_enemy_state_field_home.h"
#include "gf/object/component/enemy/gf_enemy_state_field_idle.h"
#include "gf/object/component/enemy/gf_enemy_state_field_spawn.h"
#include "gf/object/component/enemy/gf_enemy_state_field_squad_member.h"
#include "gf/object/component/enemy/gf_enemy_state_field_walk.h"
#include "gf/object/component/gf_com_collider.h"
#include "gf/object/component/gf_component.h"
#include "gf/object/component/model/gf_com_model.h"
#include "gf/object/component/property/gf_com_property.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "gf/param/enemy/gf_param_enemy.h"
#include "gmk/gmk_acc.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_battle_lock.h"
#include "gmk/gmk_enemy/gmk_enemy.h"
#include "gmk/gmk_enemy/gmk_routed_enemy.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_set.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec4.h"
#include "mm_mtl/reference_object.h"
#include "mm_mtl/rtti.h"
#include "mm_mtl/vector.h"

namespace gf {
struct GF_OBJ_HANDLE;

// Inferred helper: the enemy instances embedded in the gimmick; original name unknown.
static const gmk::GmkEnemyInsts &unknown002(const gmk::GmkEnemy &gmk) { return gmk.m_gmkEnemyInsts; }

// Inferred helper: the enemy instances embedded in the gimmick; original name unknown.
static const gmk::GmkEnemyInsts &unknown002(const gmk::GmkRoutedEnemy &gmk) { return gmk.m_gmkEnemyInsts; }

namespace enemy {

// Named as the game's global symbols gf::enemy::ASM_CB_NAME_FIELD_ENEMY and gf::enemy::ASM_CB_NAME_BATTLE_ENEMY.
const char *ASM_CB_NAME_FIELD_ENEMY = "field_en";
const char *ASM_CB_NAME_BATTLE_ENEMY = "battle_en";

} // namespace enemy

void GfComBehaviorEnemy::Listener::onWkStandbyLogout() { m_comBehaviorEnemy->unknown54e8 = nullptr; }

u32 GfComBehaviorEnemy::getStateId() const {
  if (m_hfsm.m_pState != nullptr) {
    return m_hfsm.m_pState->m_state;
  }

  return ai::INVALID_STATE_ID;
}

void GfComBehaviorEnemy::callbackBattle(GfComAsm *comAsm, const CallBackCache &cache) {}

void GfComBehaviorEnemy::callbackField(GfComAsm *comAsm, const CallBackCache &cache) {}

void GfComBehaviorEnemy::procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message) {}

const mm::mtl::RTTI *GfComBehaviorEnemy::getRTTI() const { return &m_rtti; }

bool GfComBehaviorEnemy::recieveMessage(fw::MessageObject *sender, fw::Message &message) {
  switch (message.unknown00) {
  case MSG_OBJECT_UNKNOWN_16777271:
    procMsgObjectNotifyDamage(sender, static_cast<MsgObjectNotifyDamage &>(message));
    return true;
  case MSG_OBJECT_UNKNOWN_16777272:
    procMsgObjectNotifyDead(sender, static_cast<MsgObjectNotifyDead &>(message));
    return true;
  case MSG_UNKNOWN_16777281:
    procMsgObjectLure(sender, static_cast<MsgObjectLure &>(message));
    return true;
  case MSG_UNKNOWN_16777286:
    procMsgObjectGetVelocity(sender, static_cast<MsgObjectGetVelocity &>(message));
    return true;
  default:
    break;
  }

  if (message.unknown00 == MSG_UNKNOWN_16777219) {
    procMsgActivateComponentDebugWindow(sender, static_cast<MsgDebugActivateComponentWindow &>(message));
    return true;
  }

  if (message.unknown00 == MSG_UNKNOWN_16777224) {
    procMsgPcGetLookPoint(sender, static_cast<MsgPcGetLookPoint &>(message));
    return true;
  }

  return false;
}

GfComBehaviorEnemy::GfComBehaviorEnemy()
    : m_hfsm(fw::Allocator::getProcAllocator()), unknown128(true), m_menuCallContext(nullptr), m_fieldDmg(nullptr), unknown54e0(false), unknown54e1(false), unknown54e2(false), unknown54e3(false),
      unknown54e4(false), unknown54e8(nullptr) {}

GfComBehaviorEnemy::~GfComBehaviorEnemy() {
  if (unknown54e0) {
    unknown54e0 = false;
    if (m_behaviorEnemyField.m_fieldEnemySensor.m_gmkAcc.isValid()) {
      static_cast<const gmk::GmkBattleLock *>(m_behaviorEnemyField.m_fieldEnemySensor.m_gmkAcc.m_aGmkBase)->unknownc4--;
    }
  }

  cleanup();
}

void GfComBehaviorEnemy::cleanup() {
  m_behaviorEnemyField.dispose();
  disposeFsm();
  disposeMenuObj();
  m_pluginManager.cleanup();
  unknown138 = nullptr;
}

void GfComBehaviorEnemy::procMsgObjectLure(fw::MessageObject *sender, MsgObjectLure &message) {
  if (sender != nullptr) {
    unknown54e4 = true;
    MsgObjectDamage damage(1, 0);
    damage.unknown2e = true;
    sender->sendMessage(static_cast<GfObj *>(unknown08), damage);
  }
}

gmk::AGmkBase *GfComBehaviorEnemy::getBindedGmkInst() const { return gmk::getBindedGmkInst(static_cast<GfObj *>(unknown08)->unknownf8); }

bool GfComBehaviorEnemy::isFly() const {
  DataParamAcc dataParam(static_cast<GfObj *>(unknown08)->unknownf8);
  return dataParam.getSDataEnemy()->unknown9a == 3;
}

bool GfComBehaviorEnemy::isWater() const {
  DataParamAcc dataParam(static_cast<GfObj *>(unknown08)->unknownf8);
  return dataParam.getSDataEnemy()->unknown9a == 1;
}

bool GfComBehaviorEnemy::isFlyInsect() const {
  if (isFly()) {
    u8 *bdat = GfDataBdat::getFP(BDAT_FLD_ENACT_MOVE);
    GfObjSetupEnemy *setup = mm::mtl::dynamicCast<GfObjSetupEnemy>(GfObjManager::getObjInfo(static_cast<GfObj *>(unknown08)->unknownf8)->unknown30);
    if (setup->unknowna8 != 0) {
      return Bdat::getValCheck(bdat, "actMove_Atr", setup->unknowna8, 1) & 1;
    }
  }

  return false;
}

bool GfComBehaviorEnemy::isFlyCircle() const {
  if (isFly()) {
    u8 *bdat = GfDataBdat::getFP(BDAT_FLD_ENACT_MOVE);
    GfObjSetupEnemy *setup = mm::mtl::dynamicCast<GfObjSetupEnemy>(GfObjManager::getObjInfo(static_cast<GfObj *>(unknown08)->unknownf8)->unknown30);
    if (setup->unknowna8 != 0) {
      return (Bdat::getValCheck(bdat, "actMove_Atr", setup->unknowna8, 1) >> 1) & 1;
    }
  }

  return false;
}

u32 GfComBehaviorEnemy::getBdatId_CHR_EnArrange() const {
  return mm::mtl::dynamicCast<GfObjSetupEnemy>(GfObjManager::getObjInfo(static_cast<GfObj *>(unknown08)->unknownf8)->unknown30)->m_enArrangeID;
}

const fw::Transform &GfComBehaviorEnemy::getTransform() const { return unknown001()->getSyncedWorldTransform(); }

const fw::Transform &GfComBehaviorEnemy::getTransformToSearchPlayer() const {
  if (unknown138.get() != nullptr) {
    return unknown138->getSyncedWorldTransform();
  }

  return getTransform();
}

bool GfComBehaviorEnemy::getGmkBattleLockInfo(int &param1, int &param2) const {
  gmk::AGmkBase *gmkInst = gmk::getBindedGmkInst(static_cast<GfObj *>(unknown08)->unknownf8);
  if (gmkInst == nullptr) {
    return false;
  }

  param1 = gmkInst->m_createBaseInfo.m_ownerGmkEnemyList->getCreateInfo().m_gmkSet->m_createInfo.unknown04;
  u8 *bdat = gmkInst->getBindedBdatFp();
  if (bdat == nullptr) {
    return false;
  }

  param2 = static_cast<u16>(Bdat::getValCheck(bdat, "battlelockname", gmkInst->m_createInfo.unknown18, 2)) - 1;
  return true;
}

f32 GfComBehaviorEnemy::getMoveSpeedDelta(GfBehaviorEnemyField::MoveSpeed moveSpeed) const {
  GfBehaviorEnemyField::MoveSpeed current = m_behaviorEnemyField.getFieldMoveSpeedType(static_cast<enemy::STATE_ID>(getStateId()));
  if (current == moveSpeed) {
    return 0.0f;
  }

  return GfBehaviorEnemyField::unknown001(current, moveSpeed, *getEnemeyMoveParam(m_behaviorEnemyField.unknown36));
}

void GfComBehaviorEnemy::reqChangeBattle() {
  if (getStateId() != enemy::STATE_ID_UNKNOWN_0) {
    unknown54e3 = true;
  }
}

void GfComBehaviorEnemy::disposeFsm() {
  if (!unknown128) {
    unknown128 = true;
    m_hfsm.cleanup();
  }
}

void GfComBehaviorEnemy::setStateId(enemy::STATE_ID stateId) {
  if (stateId == enemy::STATE_ID_UNKNOWN_0) {
    unknown54e2 = false;
    unknown54e3 = false;
    m_behaviorEnemyField.m_fieldPitchRollController.unknown30 = true;
    m_behaviorEnemyField.m_fieldPitchRollController.unknown31 = true;
    static_cast<GfObj *>(unknown08)->unknown110 |= 4;
    GfObjUtil::setInvincible(static_cast<GfObj *>(unknown08)->unknownf8, false, false);
    if (m_behaviorEnemyField.unknown37 != 0) {
      reqChangeBattleToOtherMember<gmk::GmkEnemy>();
      reqChangeBattleToOtherMember<gmk::GmkRoutedEnemy>();
    }
  }

  m_hfsm.setState(stateId);
}

fw::ColiMoveObject *GfComBehaviorEnemy::getColiObject() const {
  GfComCollider *collider = unknown08->getComponent<GfComCollider>();
  if (collider != nullptr) {
    fw::ColiObject *coli = collider->unknown18[0];
    if (coli != nullptr) {
      return mm::mtl::dynamicCast<fw::ColiMoveObject>(coli);
    }
  }

  return nullptr;
}

void GfComBehaviorEnemy::setActivateCollison(bool isActivate) {
  fw::ColiMoveObject *coli = getColiObject();
  if (coli != nullptr) {
    coli->setActivate(isActivate);
  }
}

void GfComBehaviorEnemy::moveProc(mm::Vec3 &velocity) {
  GfComCollider *collider = unknown08->getComponent<GfComCollider>();
  if (collider != nullptr) {
    fw::ColiObject *coli = collider->unknown18[0];
    if (coli != nullptr) {
      coli->setDir(velocity);
    }
  }
}

void GfComBehaviorEnemy::procMsgPcGetLookPoint(fw::MessageObject *sender, MsgPcGetLookPoint &message) {
  if (unknown138.get() != nullptr) {
    message.unknown10 = unknown138->getSyncedWorldTransform().unknown00;
    message.unknown20 = true;
  }
}

void GfComBehaviorEnemy::procMsgObjectGetVelocity(fw::MessageObject *sender, MsgObjectGetVelocity &message) { message.unknown10 = unknown54d0; }

void GfComBehaviorEnemy::procAnimCallback(GfComAsm *comAsm, const CallBackCache &cache) {
  MsgObjectNotifyAsmCallback message(comAsm, cache.unknown08);
  GfStateBase::unknown001 event;
  event.unknown00 = static_cast<GfObj *>(unknown08);
  event.unknown08 = &message;
  m_hfsm.execEvent(&event);
}

void GfComBehaviorEnemy::setupWeapon() {
  unknown5500 = 0;
  unknown5501 = 0;
  GfObjAcc acc(static_cast<GfObj *>(unknown08)->unknownf8);
  if (acc.getBdatId() == 0xef) {
    unknown5500 |= 2;
  }

  updateWeapon();
}

void GfComBehaviorEnemy::updateInvincible() {
  bool isInvincible;
  bool isTargetable;
  {
    DataParamAcc dataParam(static_cast<GfObj *>(unknown08)->unknownf8);
    if (!dataParam.isEnbaleTarget()) {
      isTargetable = false;
      isInvincible = true;
    } else {
      switch (getStateId()) {
      case enemy::STATE_ID_UNKNOWN_6:
      case enemy::STATE_ID_UNKNOWN_7:
      case enemy::STATE_ID_UNKNOWN_13:
        isTargetable = false;
        isInvincible = true;
        break;
      default:
        gmk::AGmkBase *gmkInst = getBindedGmkInst();
        if (gmkInst == nullptr) {
          isTargetable = true;
          isInvincible = false;
        } else {
          gmk::GmkType type = gmkInst->getGmkType();
          if (type == gmk::GmkEnemy::GMK_TYPE) {
            if ((m_behaviorEnemyField.m_fieldEnemySensor.m_createInfo.unknown48 | m_behaviorEnemyField.m_fieldEnemySensor.m_createInfo.unknown4c) >= 0) {
              isInvincible = true;
              isTargetable = true;
            } else {
              isInvincible = unknown002(*static_cast<gmk::GmkEnemy *>(gmkInst)).m_bdatInfo.isInvincibleCondMatched();
              isTargetable = !isInvincible;
            }
          } else if (type == gmk::GmkRoutedEnemy::GMK_TYPE) {
            isInvincible = unknown002(*static_cast<gmk::GmkRoutedEnemy *>(gmkInst)).m_bdatInfo.isInvincibleCondMatched();
            isTargetable = !isInvincible;
          } else {
            isTargetable = true;
            isInvincible = false;
          }
        }
        break;
      }
    }
  }
  if (isTargetable) {
    static_cast<GfObj *>(unknown08)->unknown110 |= 4;
  } else {
    static_cast<GfObj *>(unknown08)->unknown110 &= ~4u;
  }
  m_behaviorEnemyField.unknown52a8 = isTargetable;
  GfObjUtil::setInvincible(static_cast<GfObj *>(unknown08)->unknownf8, isInvincible, false);
}

void GfComBehaviorEnemy::disposeMenuObj() {
  if (m_menuCallContext != nullptr) {
    GfMenuObjTargetInfo::close(m_menuCallContext);
    mm::mtl::safeRelease(m_menuCallContext);
  }
}

void GfComBehaviorEnemy::setup() {
  GfObjSetupEnemy *setup = GfObjUtil::getObjSetup<GfObjSetupEnemy>(static_cast<GfObj *>(unknown08)->unknownf8);
  GfComAsm *comAsm = unknown08->getComponent<GfComAsm>();
  if (comAsm != nullptr) {
    unknown014(comAsm);
    comAsm->unknown70[1].unknown00 = enemy::ASM_CB_NAME_FIELD_ENEMY;
    comAsm->unknown70[1].unknown08.bind<GfComBehaviorEnemy>(this, &GfComBehaviorEnemy::callbackField);
    comAsm->unknown70[2].unknown00 = enemy::ASM_CB_NAME_BATTLE_ENEMY;
    comAsm->unknown70[2].unknown08.bind<GfComBehaviorEnemy>(this, &GfComBehaviorEnemy::callbackBattle);
  }

  u8 *bdat = GfDataBdat::getFP(BDAT_RSC_EN);
  GfObjSetupEnemy *searchSetup = mm::mtl::dynamicCast<GfObjSetupEnemy>(GfObjManager::getObjInfo(static_cast<GfObj *>(unknown08)->unknownf8)->unknown30);
  const char *searchBone = reinterpret_cast<const char *>(Bdat::getValCheck(bdat, "SearchBaseBone", searchSetup->unknown10, 7));
  const char *boneName = "JU_spA";
  if (searchBone != nullptr && *searchBone != '\0') {
    boneName = searchBone;
  }

  GfComModel *model = unknown08->getComponent<GfComModel>();
  unknown138 = model->createBoneReferenceFrame(boneName);
  if (unknown138.get() == nullptr) {
    GfComTransform *transform = unknown08->getComponent<GfComTransform>();
    unknown138 = transform->unknown18.get() == nullptr ? transform->unknown10 : transform->unknown18;
  }

  m_pluginManager.beginSetup(*this, 4);
  m_pluginManager.unknown001<FootStepPlugin>(0, true);
  m_pluginManager.endSetup();
  FootStepPlugin *footStep = GfComBehavior::unknown001<FootStepPlugin>(0);
  if (footStep != nullptr) {
    footStep->setActivate(true);
  }

  {
    DataParamAcc dataParam(static_cast<GfObj *>(unknown08)->unknownf8);
    if (dataParam.isEnbaleTarget()) {
      createMenuObj();
    }
  }

  createFsm();
  {
    f32 radius = getCollisionRadius();
    GfFieldUndulator::CreateInfo undulatorInfo;
    undulatorInfo.unknown00 = setup->m_enArrangeID;
    undulatorInfo.unknown04 = radius + radius;
    m_fieldUndulator.create(undulatorInfo);
  }

  GfComTransform *transform = unknown08->getComponent<GfComTransform>();
  m_fieldUndulator.update(transform->unknown18.get() == nullptr ? transform->unknown10 : transform->unknown18, false);
  createBehField();
  GfObjAcc acc(static_cast<GfObj *>(unknown08)->unknownf8);
  if (acc.isEnemyBlade()) {
    m_hfsm.setState(enemy::STATE_ID_UNKNOWN_15);
  }

  {
    DataParamAcc dataParam(static_cast<GfObj *>(unknown08)->unknownf8);
    const SDataEnemy *dataEnemy = dataParam.getSDataEnemy();
    if (dataEnemy != nullptr && dataEnemy->m_fieldDamage) {
      GfFieldDmg::CreateInfo dmgInfo;
      dmgInfo.unknown00 = true;
      m_fieldDmg.create(dmgInfo);
    }
  }

  updateInvincible();
  setupWeapon();
}

void GfComBehaviorEnemy::createMenuObj() {
  disposeMenuObj();
  m_menuCallContext = GfMenuCallContext::create();
  GfMenuObjTargetInfo::OpenEnemyParam param;
  param.m_GF_OBJ_HANDLE = static_cast<GfObj *>(unknown08)->unknownf8;
  int offsetId = GfGameUtil::getUiOffsetId(param.m_GF_OBJ_HANDLE);
  param.m_menuOffset.unknown10 = nullptr;
  param.m_menuOffset.unknown00 = mm::Vec3::zero;
  GfMenuBdat::getMenuOffset(offsetId, param.m_menuOffset);
  GfMenuObjTargetInfo::openEnemy(m_menuCallContext, param);
}

void GfComBehaviorEnemy::validateBattleLock(bool isLock) {
  if ((m_behaviorEnemyField.m_fieldEnemySensor.m_createInfo.unknown48 | m_behaviorEnemyField.m_fieldEnemySensor.m_createInfo.unknown4c) < 0) {
    return;
  }

  if (!m_behaviorEnemyField.m_fieldEnemySensor.m_gmkAcc.isValid()) {
    if (unknown54e0) {
      unknown54e0 = false;
    }
    return;
  }

  const gmk::GmkBattleLock *lock = static_cast<const gmk::GmkBattleLock *>(m_behaviorEnemyField.m_fieldEnemySensor.m_gmkAcc.m_aGmkBase);
  bool isFree = true;
  if (unknown54e0) {
    if (lock->unknownc4 != 0) {
      isFree = false;
    } else {
      unknown54e0 = false;
    }
  }

  if (isLock) {
    if (isFree) {
      unknown54e0 = true;
      lock->unknownc4++;
    }
  } else if (!isFree) {
    unknown54e0 = false;
    lock->unknownc4--;
  }
}

bool GfComBehaviorEnemy::extractLoco() {
  GfObj *obj;
  {
    GfObjAcc acc(static_cast<GfObj *>(unknown08)->unknownf8);
    obj = acc.getObj();
  }

  if (obj != nullptr) {
    GfComTransform *transform = obj->getComponent<GfComTransform>();
    GfComAsm *comAsm = obj->getComponent<GfComAsm>();
    if (transform != nullptr && comAsm != nullptr) {
      const anm::QsTransform &locomotion = comAsm->getLocomotion();
      mm::Quat rotation = mm::Quat::mul(locomotion.unknown10, transform->getRotation());
      transform->setRotation(rotation);
      f32 speed = comAsm->getSpeed(ANIM_LAYER_UNKNOWN_0);
      mm::Vec3 offset = transform->getRotation().rotate(mm::Vec3(locomotion.unknown00.x, locomotion.unknown00.y, locomotion.unknown00.z)) * speed;
      transform->setPosition(transform->getPosition() + offset);
      return true;
    }
  }

  return false;
}

f32 GfComBehaviorEnemy::getCollisionRadius() const {
  GfComCollider *collider = unknown08->getComponent<GfComCollider>();
  mm::Vec3 min;
  mm::Vec3 max;
  if (!collider->unknown18[0]->getAABB(min, max)) {
    return 0.0f;
  }

  f32 dx = max.x - min.x;
  f32 dy = max.y - min.y;
  f32 dz = max.z - min.z;
  return sqrtf(dx * dx + dy * dy + dz * dz) * 0.5f;
}

void GfComBehaviorEnemy::createBehField() {
  m_behaviorEnemyField.dispose();
  GfObjSetupEnemy *setup = GfObjUtil::getObjSetup<GfObjSetupEnemy>(static_cast<GfObj *>(unknown08)->unknownf8);
  GfBehaviorEnemyField::CreateInfo info;
  info.m_iGfBehFieldOwner = this;
  info.m_GF_OBJ_HANDLE = static_cast<GfObj *>(unknown08)->unknownf8;
  {
    f32 radius;
    f32 height;
    GfComCollider *collider = unknown08->getComponent<GfComCollider>();
    mm::Vec3 min;
    mm::Vec3 max;
    if (collider->unknown18[0]->getAABB(min, max)) {
      f32 dx = max.x - min.x;
      f32 dz = max.z - min.z;
      radius = sqrtf(dx * dx + dz * dz) * 0.5f;
      height = max.y - min.y;
    } else {
      radius = GfBdatRsc::get()->getRscEnCharColli(setup->unknown10);
      height = radius + radius;
    }

    info.unknown10 = radius;
    info.unknown14 = height;
  }

  if (info.unknown10 < 1.0f) {
    info.unknown10 = 1.0f;
  }

  if (info.unknown14 < 2.0f) {
    info.unknown14 = 2.0f;
  }

  {
    DataParamAcc dataParam(static_cast<GfObj *>(unknown08)->unknownf8);
    info.unknown18 = dataParam.getSDataEnemy()->unknown9a;
  }

  m_behaviorEnemyField.create(info);
  m_behaviorEnemyField.unknown52a0 = setup->unknownac;
  m_behaviorEnemyField.unknown52a4 = 0.0f;
}

void GfComBehaviorEnemy::createFsm() {
  disposeFsm();
  m_hfsm.beginSetup(this, 0x10, 3);
  m_hfsm.registerState<enemy::StateBattle>(enemy::STATE_ID_UNKNOWN_0, -1);
  m_hfsm.registerState<enemy::StateFieldIdle>(enemy::STATE_ID_UNKNOWN_1, -1);
  m_hfsm.registerState<enemy::StateFieldIdle>(enemy::STATE_ID_UNKNOWN_2, -1);
  m_hfsm.registerState<enemy::StateFieldIdle>(enemy::STATE_ID_UNKNOWN_3, -1);
  m_hfsm.registerState<enemy::StateFieldIdle>(enemy::STATE_ID_UNKNOWN_4, -1);
  m_hfsm.registerState<enemy::StateFieldIdle>(enemy::STATE_ID_UNKNOWN_5, -1);
  m_hfsm.registerState<enemy::StateFieldSpawn>(enemy::STATE_ID_UNKNOWN_6, -1);
  m_hfsm.registerState<enemy::StateFieldSpawn>(enemy::STATE_ID_UNKNOWN_7, -1);
  m_hfsm.registerState<enemy::StateFieldAreaWalk>(enemy::STATE_ID_UNKNOWN_8, -1);
  m_hfsm.registerState<enemy::StateFieldWalk>(enemy::STATE_ID_UNKNOWN_9, -1);
  m_hfsm.registerState<enemy::StateFieldAreaWalk>(enemy::STATE_ID_UNKNOWN_10, -1);
  m_hfsm.registerState<enemy::StateFieldWalk>(enemy::STATE_ID_UNKNOWN_11, -1);
  m_hfsm.registerState<enemy::StateFieldHome>(enemy::STATE_ID_UNKNOWN_13, -1);
  m_hfsm.registerState<enemy::StateFieldSquadMember>(enemy::STATE_ID_UNKNOWN_14, -1);
  m_hfsm.registerState<enemy::StateFieldBlade>(enemy::STATE_ID_UNKNOWN_15, -1);
  m_hfsm.endSetup();
  unknown128 = false;
}

bool GfComBehaviorEnemy::isStateCondMatch(enemy::STATE_ID stateId) const {
  switch (stateId) {
  case enemy::STATE_ID_UNKNOWN_0:
  case enemy::STATE_ID_UNKNOWN_1:
  case enemy::STATE_ID_UNKNOWN_2:
  case enemy::STATE_ID_UNKNOWN_3:
  case enemy::STATE_ID_UNKNOWN_4:
  case enemy::STATE_ID_UNKNOWN_5:
    return true;
  case enemy::STATE_ID_UNKNOWN_15:
    return false;
  default:
    return false;
  case enemy::STATE_ID_UNKNOWN_8:
    return enemy::StateFieldAreaWalk::isCondMatch(*this);
  case enemy::STATE_ID_UNKNOWN_9:
    return enemy::StateFieldWalk::isCondMatch(*this);
  case enemy::STATE_ID_UNKNOWN_10:
    return enemy::StateFieldAreaWalk::isCondMatch(*this);
  case enemy::STATE_ID_UNKNOWN_11:
    return enemy::StateFieldWalk::isCondMatch(*this);
  case enemy::STATE_ID_UNKNOWN_13:
    return enemy::StateFieldHome::isCondMatch(*this);
  case enemy::STATE_ID_UNKNOWN_14:
    return enemy::StateFieldSquadMember::isCondMatch(*this);
  }
}

void GfComBehaviorEnemy::updateField(const fw::UpdateInfo &info) {
  m_behaviorEnemyField.update(info.unknown04);
  GfObjAcc acc(static_cast<GfObj *>(unknown08)->unknownf8);
  if (acc.isEnemyBlade()) {
    const btl::CharacterParameter *parameter = btl::CharacterManager::get()->GetCharacterConst(static_cast<GfObj *>(unknown08)->unknownf8)->GetCharacterParameterConst(true);
    GF_OBJ_HANDLE *driverHandle = parameter->unknown10;
    btl::BattleCharacter *driver = btl::CharacterManager::get()->GetCharacterConst(driverHandle);
    if (driver != nullptr && driver->IsBattle()) {
      setStateId(enemy::STATE_ID_UNKNOWN_0);
    }
  }

  if (getStateId() != enemy::STATE_ID_UNKNOWN_13 && m_behaviorEnemyField.unknown52a9) {
    m_hfsm.setState(enemy::STATE_ID_UNKNOWN_13);
  }

  GfMountManager::getHandle(static_cast<GfObj *>(unknown08)->unknownf8, GFATTACH_UNKNOWN_0, OPTMNT_UNKNOWN_1);
  GfMountManager::getHandle(static_cast<GfObj *>(unknown08)->unknownf8, GFATTACH_UNKNOWN_0, OPTMNT_UNKNOWN_3);
}

template <typename T> void GfComBehaviorEnemy::reqChangeBattleToOtherMember() const {
  gmk::AGmkBase *gmkInst = getBindedGmkInst();
  if (gmkInst != nullptr && gmkInst->getGmkType() == T::GMK_TYPE) {
    const gmk::GmkEnemyInsts &insts = unknown002(*static_cast<T *>(gmkInst));
    GF_OBJ_HANDLE *handle = static_cast<GfObj *>(unknown08)->unknownf8;
    u32 num = insts.m_popInfo.getGobInstNum();
    for (u32 i = 0; i < num; i++) {
      GF_OBJ_HANDLE *gobHandle = insts.getGobInst(i);
      if (handle != gobHandle) {
        GfObjAcc acc(gobHandle);
        GfObj *obj = acc.getObj();
        if (obj != nullptr && !acc.isBattle()) {
          GfComBehaviorEnemy *behavior = obj->getComponent<GfComBehaviorEnemy>();
          if (behavior != nullptr) {
            u32 stateId = behavior->getStateId();
            if (stateId != enemy::STATE_ID_UNKNOWN_0 && stateId != enemy::STATE_ID_UNKNOWN_13) {
              behavior->unknown54e3 = true;
            }
          }
        }
      }
    }
  }
}

template <typename T> bool GfComBehaviorEnemy::isOtherMemberBattle() const {
  if (m_behaviorEnemyField.unknown37 == 0) {
    return false;
  }

  gmk::AGmkBase *gmkInst = getBindedGmkInst();
  if (gmkInst == nullptr || gmkInst->getGmkType() != T::GMK_TYPE) {
    return false;
  }

  const gmk::GmkEnemyInsts &insts = unknown002(*static_cast<T *>(gmkInst));
  GF_OBJ_HANDLE *handle = static_cast<GfObj *>(unknown08)->unknownf8;
  u32 num = insts.m_popInfo.getGobInstNum();
  for (u32 i = 0; i < num; i++) {
    GF_OBJ_HANDLE *gobHandle = insts.getGobInst(i);
    if (handle != gobHandle) {
      GfObjAcc acc(gobHandle);
      if (acc.getObj() != nullptr && acc.isBattle()) {
        return true;
      }
    }
  }

  return false;
}

bool GfComBehaviorEnemy::isOtherMemberBattle() const {
  if (isOtherMemberBattle<gmk::GmkEnemy>()) {
    return true;
  }

  return isOtherMemberBattle<gmk::GmkRoutedEnemy>();
}

template <typename T> bool GfComBehaviorEnemy::isOtherMemberHome() const {
  if (m_behaviorEnemyField.unknown37 != 0) {
    gmk::AGmkBase *gmkInst = getBindedGmkInst();
    if (gmkInst != nullptr && gmkInst->getGmkType() == T::GMK_TYPE) {
      const gmk::GmkEnemyInsts &insts = unknown002(*static_cast<T *>(gmkInst));
      GF_OBJ_HANDLE *handle = static_cast<GfObj *>(unknown08)->unknownf8;
      u32 num = insts.m_popInfo.getGobInstNum();
      for (u32 i = 0; i < num; i++) {
        GF_OBJ_HANDLE *gobHandle = insts.getGobInst(i);
        if (handle != gobHandle) {
          GfObjAcc acc(gobHandle);
          GfObj *obj = acc.getObj();
          if (obj != nullptr) {
            GfComBehaviorEnemy *behavior = obj->getComponent<GfComBehaviorEnemy>();
            if (behavior != nullptr && behavior->getStateId() == enemy::STATE_ID_UNKNOWN_13) {
              return true;
            }
          }
        }
      }
    }
  }

  return false;
}

bool GfComBehaviorEnemy::isOtherMemberHome() const {
  if (isOtherMemberHome<gmk::GmkEnemy>()) {
    return true;
  }

  return isOtherMemberHome<gmk::GmkRoutedEnemy>();
}

void GfComBehaviorEnemy::execTurnCmd(f32 angle) {
  getTransform();
  TFieldExecCmdTurn<GfComAsm>::CreateInfo info;
  info.unknown00 = static_cast<GfObj *>(unknown08)->unknownf8;
  info.unknown08 = m_behaviorEnemyField.m_fieldLocalSteer.getCurAngle() + angle;
  info.unknown0c = m_behaviorEnemyField.unknown30;
  unknown53f0.create(info);
  if (!unknown53f0.unknown6c) {
    m_behaviorEnemyField.m_enemyFieldMoveSpeed.setSpeedKmph(m_behaviorEnemyField.m_enemyFieldMoveSpeed.unknown08, 0.0f);
  }
}

void GfComBehaviorEnemy::execTurnCmd(f32 angle, f32 param2, f32 param3, f32 param4) {
  TFieldExecCmdTurn<GfComAsm>::CreateInfo info;
  info.unknown00 = static_cast<GfObj *>(unknown08)->unknownf8;
  info.unknown08 = m_behaviorEnemyField.m_fieldLocalSteer.getCurAngle() + angle;
  info.unknown0c = param3;
  info.unknown14 = param2;
  info.unknown18 = param4;
  unknown53f0.create(info);
  if (!unknown53f0.unknown6c) {
    m_behaviorEnemyField.m_enemyFieldMoveSpeed.setSpeedKmph(m_behaviorEnemyField.m_enemyFieldMoveSpeed.unknown08, 0.0f);
  }
}

void GfComBehaviorEnemy::execTurnCmdAccurately(f32 angle) {
  getTransform();
  TFieldExecCmdTurn<GfComAsm>::CreateInfo info;
  info.unknown00 = static_cast<GfObj *>(unknown08)->unknownf8;
  info.unknown08 = m_behaviorEnemyField.m_fieldLocalSteer.getCurAngle() + angle;
  info.unknown0c = 0.0f;
  unknown53f0.create(info);
  if (!unknown53f0.unknown6c) {
    m_behaviorEnemyField.m_enemyFieldMoveSpeed.setSpeedKmph(m_behaviorEnemyField.m_enemyFieldMoveSpeed.unknown08, 0.0f);
  }
}

void GfComBehaviorEnemy::execTurnCmdToGoal() {
  mm::Vec3 direction;
  m_behaviorEnemyField.getMoveDir(direction);
  direction.y = 0.0f;
  if (!(fabsf(direction.x) <= 0.000001f) || !(fabsf(direction.z) <= 0.000001f)) {
    f32 length = sqrtf(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
    if (length <= 0.000001f) {
      direction = mm::Vec3::zero;
    } else {
      f32 inverse = 1.0f / length;
      direction.x = inverse * direction.x;
      direction.y = inverse * direction.y;
      direction.z = inverse * direction.z;
    }
  }

  execTurnCmd(atan2f(direction.x, direction.z));
}

template void GfComBehaviorEnemy::reqChangeBattleToOtherMember<gmk::GmkEnemy>() const;
template void GfComBehaviorEnemy::reqChangeBattleToOtherMember<gmk::GmkRoutedEnemy>() const;
template bool GfComBehaviorEnemy::isOtherMemberBattle<gmk::GmkEnemy>() const;
template bool GfComBehaviorEnemy::isOtherMemberBattle<gmk::GmkRoutedEnemy>() const;
template bool GfComBehaviorEnemy::isOtherMemberHome<gmk::GmkEnemy>() const;
template bool GfComBehaviorEnemy::isOtherMemberHome<gmk::GmkRoutedEnemy>() const;

} // namespace gf

template void mm::mtl::Delegate<void(gf::GfComAsm *, const gf::CallBackCache &)>::memberFuncInvoker<gf::GfComBehaviorEnemy>(const mm::mtl::Delegate<void(gf::GfComAsm *, const gf::CallBackCache &)> *,
                                                                                                                            gf::GfComAsm *, const gf::CallBackCache &);
