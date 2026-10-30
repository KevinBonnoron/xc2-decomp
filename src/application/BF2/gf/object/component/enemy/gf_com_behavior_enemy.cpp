// Same order as in the game executable: the field behavior is defined before the enemy behavior component in the same unit.
// clang-format off
#include "gf/object/component/enemy/gf_behavior_enemy_field.cpp"
// clang-format on
#include "gf/object/component/enemy/gf_com_behavior_enemy.h"

#include <math.h>

#include "ai/ai_state.h"
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
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_enemy.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/field/gf_field_enemy_sensor.h"
#include "gf/field/gf_field_local_steer.h"
#include "gf/field/gf_field_move_speed.h"
#include "gf/field/gf_field_pitch_roll_controller.h"
#include "gf/game/gf_game_mount.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/object/gf_menu_obj_target_info.h"
#include "gf/object/component/animation/gf_com_asm.h"
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
#include "mm_mtl/reference_object.h"
#include "mm_mtl/rtti.h"
#include "mm_mtl/vector.h"

namespace gf {
struct GF_OBJ_HANDLE;

// Inferred helper: the enemy instances embedded in the gimmick; original name unknown.
static const gmk::GmkEnemyInsts &unknown002(const gmk::GmkEnemy &gmk) { return gmk.unknown48; }

// Inferred helper: the enemy instances embedded in the gimmick; original name unknown.
static const gmk::GmkEnemyInsts &unknown002(const gmk::GmkRoutedEnemy &gmk) { return gmk.unknown50; }

void GfComBehaviorEnemy::Listener::onWkStandbyLogout() { unknown08->unknown54e8 = nullptr; }

u32 GfComBehaviorEnemy::getStateId() const {
  if (unknowna0.m_pState != nullptr) {
    return unknowna0.m_pState->unknown08;
  }

  return ai::INVALID_STATE_ID;
}

void GfComBehaviorEnemy::callbackBattle(GfComAsm *comAsm, const CallBackCache &cache) {}

void GfComBehaviorEnemy::callbackField(GfComAsm *comAsm, const CallBackCache &cache) {}

void GfComBehaviorEnemy::procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message) {}

const mm::mtl::RTTI *GfComBehaviorEnemy::getRTTI() const { return &m_rtti; }

bool GfComBehaviorEnemy::recieveMessage(fw::MessageObject *sender, fw::Message &message) {
  switch (message.unknown00) {
  case MSG_OBJECT_NOTIFY_DAMAGE:
    procMsgObjectNotifyDamage(sender, static_cast<MsgObjectNotifyDamage &>(message));
    return true;
  case MSG_OBJECT_NOTIFY_DEAD:
    procMsgObjectNotifyDead(sender, static_cast<MsgObjectNotifyDead &>(message));
    return true;
  case MSG_OBJECT_LURE:
    procMsgObjectLure(sender, static_cast<MsgObjectLure &>(message));
    return true;
  case MSG_OBJECT_GET_VELOCITY:
    procMsgObjectGetVelocity(sender, static_cast<MsgObjectGetVelocity &>(message));
    return true;
  default:
    break;
  }

  if (message.unknown00 == MSG_DEBUG_ACTIVATE_COMPONENT_WINDOW) {
    procMsgActivateComponentDebugWindow(sender, static_cast<MsgDebugActivateComponentWindow &>(message));
    return true;
  }

  if (message.unknown00 == MSG_PC_GET_LOOK_POINT) {
    procMsgPcGetLookPoint(sender, static_cast<MsgPcGetLookPoint &>(message));
    return true;
  }

  return false;
}

GfComBehaviorEnemy::GfComBehaviorEnemy()
    : unknowna0(fw::Allocator::getProcAllocator()), unknown128(true), unknown130(nullptr), unknown54a0(nullptr), unknown54e0(false), unknown54e1(false), unknown54e2(false), unknown54e3(false),
      unknown54e4(false), unknown54e8(nullptr) {}

GfComBehaviorEnemy::~GfComBehaviorEnemy() {
  if (unknown54e0) {
    unknown54e0 = false;
    if (unknown140.unknownd0.unknownb0.isValid()) {
      static_cast<const gmk::GmkBattleLock *>(unknown140.unknownd0.unknownb0.unknown38)->unknownc4--;
    }
  }

  cleanup();
}

void GfComBehaviorEnemy::cleanup() {
  unknown140.dispose();
  disposeFsm();
  disposeMenuObj();
  unknown10.cleanup();
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

  param1 = gmkInst->unknown08.unknown00->getCreateInfo().unknown08->unknown10.unknown04;
  u8 *bdat = gmkInst->getBindedBdatFp();
  if (bdat == nullptr) {
    return false;
  }

  param2 = static_cast<u16>(Bdat::getValCheck(bdat, "battlelockname", gmkInst->unknown20.unknown18, 2)) - 1;
  return true;
}

f32 GfComBehaviorEnemy::getMoveSpeedDelta(GfBehaviorEnemyField::MoveSpeed moveSpeed) const {
  GfBehaviorEnemyField::MoveSpeed current = unknown140.getFieldMoveSpeedType(static_cast<enemy::STATE_ID>(getStateId()));
  if (current == moveSpeed) {
    return 0.0f;
  }

  return GfBehaviorEnemyField::unknown001(current, moveSpeed, *getEnemeyMoveParam(unknown140.unknown36));
}

void GfComBehaviorEnemy::reqChangeBattle() {
  if (getStateId() != enemy::STATE_ID_UNKNOWN_0) {
    unknown54e3 = true;
  }
}

void GfComBehaviorEnemy::disposeFsm() {
  if (!unknown128) {
    unknown128 = true;
    unknowna0.cleanup();
  }
}

void GfComBehaviorEnemy::setStateId(enemy::STATE_ID stateId) {
  if (stateId == enemy::STATE_ID_UNKNOWN_0) {
    unknown54e2 = false;
    unknown54e3 = false;
    unknown140.unknown5268.unknown30 = true;
    unknown140.unknown5268.unknown31 = true;
    static_cast<GfObj *>(unknown08)->unknown110 |= 4;
    GfObjUtil::setInvincible(static_cast<GfObj *>(unknown08)->unknownf8, false, false);
    if (unknown140.unknown37 != 0) {
      reqChangeBattleToOtherMember<gmk::GmkEnemy>();
      reqChangeBattleToOtherMember<gmk::GmkRoutedEnemy>();
    }
  }

  unknowna0.setState(stateId);
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
  unknowna0.execEvent(&event);
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

void GfComBehaviorEnemy::disposeMenuObj() {
  if (unknown130 != nullptr) {
    GfMenuObjTargetInfo::close(unknown130);
    mm::mtl::safeRelease(unknown130);
  }
}

void GfComBehaviorEnemy::validateBattleLock(bool isLock) {
  if ((unknown140.unknownd0.unknown10.unknown48 | unknown140.unknownd0.unknown10.unknown4c) < 0) {
    return;
  }

  if (!unknown140.unknownd0.unknownb0.isValid()) {
    if (unknown54e0) {
      unknown54e0 = false;
    }
    return;
  }

  const gmk::GmkBattleLock *lock = static_cast<const gmk::GmkBattleLock *>(unknown140.unknownd0.unknownb0.unknown38);
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

void GfComBehaviorEnemy::createFsm() {
  disposeFsm();
  unknowna0.beginSetup(this, 0x10, 3);
  unknowna0.registerState<enemy::StateBattle>(enemy::STATE_ID_UNKNOWN_0, -1);
  unknowna0.registerState<enemy::StateFieldIdle>(enemy::STATE_ID_UNKNOWN_1, -1);
  unknowna0.registerState<enemy::StateFieldIdle>(enemy::STATE_ID_UNKNOWN_2, -1);
  unknowna0.registerState<enemy::StateFieldIdle>(enemy::STATE_ID_UNKNOWN_3, -1);
  unknowna0.registerState<enemy::StateFieldIdle>(enemy::STATE_ID_UNKNOWN_4, -1);
  unknowna0.registerState<enemy::StateFieldIdle>(enemy::STATE_ID_UNKNOWN_5, -1);
  unknowna0.registerState<enemy::StateFieldSpawn>(enemy::STATE_ID_UNKNOWN_6, -1);
  unknowna0.registerState<enemy::StateFieldSpawn>(enemy::STATE_ID_UNKNOWN_7, -1);
  unknowna0.registerState<enemy::StateFieldAreaWalk>(enemy::STATE_ID_UNKNOWN_8, -1);
  unknowna0.registerState<enemy::StateFieldWalk>(enemy::STATE_ID_UNKNOWN_9, -1);
  unknowna0.registerState<enemy::StateFieldAreaWalk>(enemy::STATE_ID_UNKNOWN_10, -1);
  unknowna0.registerState<enemy::StateFieldWalk>(enemy::STATE_ID_UNKNOWN_11, -1);
  unknowna0.registerState<enemy::StateFieldHome>(enemy::STATE_ID_UNKNOWN_13, -1);
  unknowna0.registerState<enemy::StateFieldSquadMember>(enemy::STATE_ID_UNKNOWN_14, -1);
  unknowna0.registerState<enemy::StateFieldBlade>(enemy::STATE_ID_UNKNOWN_15, -1);
  unknowna0.endSetup();
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
  unknown140.update(info.unknown04);
  GfObjAcc acc(static_cast<GfObj *>(unknown08)->unknownf8);
  if (acc.isEnemyBlade()) {
    const btl::CharacterParameter *parameter = btl::CharacterManager::get()->GetCharacterConst(static_cast<GfObj *>(unknown08)->unknownf8)->GetCharacterParameterConst(true);
    GF_OBJ_HANDLE *driverHandle = parameter->unknown10;
    btl::BattleCharacter *driver = btl::CharacterManager::get()->GetCharacterConst(driverHandle);
    if (driver != nullptr && driver->IsBattle()) {
      setStateId(enemy::STATE_ID_UNKNOWN_0);
    }
  }

  if (getStateId() != enemy::STATE_ID_UNKNOWN_13 && unknown140.unknown52a9) {
    unknowna0.setState(enemy::STATE_ID_UNKNOWN_13);
  }

  GfMountManager::getHandle(static_cast<GfObj *>(unknown08)->unknownf8, GFATTACH_WEAPON, OPTMNT_UNKNOWN_1);
  GfMountManager::getHandle(static_cast<GfObj *>(unknown08)->unknownf8, GFATTACH_WEAPON, OPTMNT_BLADE);
}

template <typename T> void GfComBehaviorEnemy::reqChangeBattleToOtherMember() const {
  gmk::AGmkBase *gmkInst = getBindedGmkInst();
  if (gmkInst != nullptr && gmkInst->getGmkType() == T::GMK_TYPE) {
    const gmk::GmkEnemyInsts &insts = unknown002(*static_cast<T *>(gmkInst));
    GF_OBJ_HANDLE *handle = static_cast<GfObj *>(unknown08)->unknownf8;
    u32 num = insts.unknown98.getGobInstNum();
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
  if (unknown140.unknown37 == 0) {
    return false;
  }

  gmk::AGmkBase *gmkInst = getBindedGmkInst();
  if (gmkInst == nullptr || gmkInst->getGmkType() != T::GMK_TYPE) {
    return false;
  }

  const gmk::GmkEnemyInsts &insts = unknown002(*static_cast<T *>(gmkInst));
  GF_OBJ_HANDLE *handle = static_cast<GfObj *>(unknown08)->unknownf8;
  u32 num = insts.unknown98.getGobInstNum();
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
  if (unknown140.unknown37 != 0) {
    gmk::AGmkBase *gmkInst = getBindedGmkInst();
    if (gmkInst != nullptr && gmkInst->getGmkType() == T::GMK_TYPE) {
      const gmk::GmkEnemyInsts &insts = unknown002(*static_cast<T *>(gmkInst));
      GF_OBJ_HANDLE *handle = static_cast<GfObj *>(unknown08)->unknownf8;
      u32 num = insts.unknown98.getGobInstNum();
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
  info.unknown08 = unknown140.unknown200.getCurAngle() + angle;
  info.unknown0c = unknown140.unknown30;
  unknown53f0.create(info);
  if (!unknown53f0.unknown6c) {
    unknown140.unknown1d0.setSpeedKmph(unknown140.unknown1d0.unknown08, 0.0f);
  }
}

void GfComBehaviorEnemy::execTurnCmd(f32 angle, f32 param2, f32 param3, f32 param4) {
  TFieldExecCmdTurn<GfComAsm>::CreateInfo info;
  info.unknown00 = static_cast<GfObj *>(unknown08)->unknownf8;
  info.unknown08 = unknown140.unknown200.getCurAngle() + angle;
  info.unknown0c = param3;
  info.unknown14 = param2;
  info.unknown18 = param4;
  unknown53f0.create(info);
  if (!unknown53f0.unknown6c) {
    unknown140.unknown1d0.setSpeedKmph(unknown140.unknown1d0.unknown08, 0.0f);
  }
}

void GfComBehaviorEnemy::execTurnCmdAccurately(f32 angle) {
  getTransform();
  TFieldExecCmdTurn<GfComAsm>::CreateInfo info;
  info.unknown00 = static_cast<GfObj *>(unknown08)->unknownf8;
  info.unknown08 = unknown140.unknown200.getCurAngle() + angle;
  info.unknown0c = 0.0f;
  unknown53f0.create(info);
  if (!unknown53f0.unknown6c) {
    unknown140.unknown1d0.setSpeedKmph(unknown140.unknown1d0.unknown08, 0.0f);
  }
}

void GfComBehaviorEnemy::execTurnCmdToGoal() {
  mm::Vec3 direction;
  unknown140.getMoveDir(direction);
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
