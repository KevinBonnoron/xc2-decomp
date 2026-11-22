#include "gf/object/component/behavior/gf_com_behavior_mob.h"

#include <math.h>

#include "ai/ai_state.h"
#include "bdat.h"
#include "framework/coli/coli_object.h"
#include "framework/memory/allocator.h"
#include "framework/message/message_object.h"
#include "framework/navi/navi_manager.h"
#include "framework/object/updatable_object.h"
#include "framework/reference_frame.h"
#include "fw/fw_transform.h"
#include "fw/fw_update_info.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/game/gf_game_manager.h"
#include "gf/object/component/behavior/mob/gf_mob_state_idle.h"
#include "gf/object/component/behavior/mob/gf_mob_state_move.h"
#include "gf/object/component/behavior/mob/gf_mob_state_squad_member.h"
#include "gf/object/component/behavior/npc/gf_npc_state_area_move.h"
#include "gf/object/component/behavior/npc/gf_npc_state_battle.h"
#include "gf/object/component/behavior/npc/gf_npc_state_reaction.h"
#include "gf/object/component/behavior/plugin/gf_eye_blink_plugin.h"
#include "gf/object/component/behavior/plugin/gf_foot_step_plugin.h"
#include "gf/object/component/behavior/plugin/gf_plugin_manager.h"
#include "gf/object/component/gf_com_collider.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/component/gf_component.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "gf/scom/gf_scom_obj.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_mob/gmk_mob.h"
#include "gmk/gmk_mob/gmk_routed_mob.h"
#include "mm_math/mm_math.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/rtti.h"
#include "mm_mtl/unique_ptr.h"
#include "mm_mtl/vector.h"
#include "navi/nvmsh_ac_obj.h"

namespace gf {
void GfComBehaviorMob::BdatInfo::create(const CBdatWrapper &bdat, int id) {
  u16 reactionRange = bdat.getValCheck("ReactionRange", id, gmk::BDAT_TYPE_UNKNOWN_2);
  unknown00 = static_cast<f32>(reactionRange * reactionRange);
  unknown04_0 = bdat.getValCheck("ReactionPercent", id, gmk::BDAT_TYPE_UNKNOWN_2);
  unknown06_0 = bdat.getValCheck("ReactionMot", id, gmk::BDAT_TYPE_UNKNOWN_2);
  unknown08 = bdat.getValCheck("BattleReaction", id, gmk::BDAT_TYPE_UNKNOWN_2);
  if (Bdat::getMember(bdat.unknown00, "BattleMot") != nullptr) {
    unknown0a = bdat.getValCheck("BattleMot", id, gmk::BDAT_TYPE_UNKNOWN_2);
  }
}

bool GfComBehaviorMob::recieveMessage(fw::MessageObject *sender, fw::Message &message) {
  switch (message.unknown00) {
  case MSG_UNKNOWN_16777219:
    procMsgActivateComponentDebugWindow(sender, static_cast<MsgDebugActivateComponentWindow &>(message));
    return true;
  case MSG_UNKNOWN_16777286:
    procMsgObjectGetVelocity(sender, static_cast<MsgObjectGetVelocity &>(message));
    return true;
  }
  return false;
}

void GfComBehaviorMob::procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message) {}

void GfComBehaviorMob::procMsgObjectGetVelocity(fw::MessageObject *sender, MsgObjectGetVelocity &message) { message.unknown10 = unknown100; }

GfComBehaviorMob::GfComBehaviorMob()
    : m_bdatInfo(), unknowna8(nullptr), unknownb0(0), unknownb8(nullptr), unknown100(mm::Vec3::zero), unknown110(mm::Vec3::zero), unknown120(mm::Quat::identity), m_gameStuckMeter(nullptr),
      m_gameDepopMeter(nullptr), m_fieldMoveSpeed(nullptr), m_fieldLookIk(unknown020), m_fieldLocalSteer(nullptr), m_hfsm(fw::Allocator::getProcAllocator()), unknown53b0(true), unknown53b8(nullptr),
      unknown53d0(1.0e12f), unknown53d4(1.0e12f), unknown53d8(false) {}

GfComBehaviorMob::~GfComBehaviorMob() { cleanup(); }

const mm::mtl::RTTI *GfComBehaviorMob::getRTTI() const { return &m_rtti; }

void GfComBehaviorMob::cleanup() {
  unknownb8 = nullptr;
  disposeNaviMeshObj();
  disposeFsm();
  m_pluginManager.cleanup();
}

const mm::Vec3 &GfComBehaviorMob::getPos() const { return unknown08->getComponent<GfComTransform>()->unknown001()->getSyncedWorldTransform().unknown00; }

const mm::Quat &GfComBehaviorMob::getRot() const { return unknown08->getComponent<GfComTransform>()->unknown001()->getSyncedWorldTransform().unknown10; }

fw::ColiMoveObject *GfComBehaviorMob::getColiObject() const {
  GfComCollider *collider = unknown08->getComponent<GfComCollider>();
  if (collider != nullptr) {
    fw::ColiObject *coli = collider->unknown18[0];
    if (coli != nullptr) {
      return mm::mtl::dynamicCast<fw::ColiMoveObject>(coli);
    }
  }

  return nullptr;
}

void GfComBehaviorMob::update(const fw::UpdateInfo &info) {
  unknown100.z = 0.0f;
  unknown100.x = 0.0f;
  fw::ColiMoveObject *coli = getColiObject();
  if (coli == nullptr || coli->testAttribute(fw::COLI_ATRR_UNKNOWN_0) || coli->unknown30 == 0) {
    unknown100.y = 0.0f;
  } else {
    unknown100.y += info.unknown04 * -9.8f;
  }
  if (gmk::isPlayerExist()) {
    GfObjAcc acc(static_cast<GfObj *>(unknown08));
    const mm::Vec3 &position = acc.getWorldTransform().unknown00;
    mm::Vec3 delta = gmk::getPlayerPos() - position;
    unknown53d4 = delta.y * delta.y;
    delta.y = 0.0f;
    unknown53d0 = delta.x * delta.x + delta.y * delta.y + delta.z * delta.z;
  }
  if (npc::StateBattle<GfComBehaviorMob>::isCondMatch(*this) && getStateId() != mob::STATE_ID_UNKNOWN_5) {
    m_hfsm.setState(mob::STATE_ID_UNKNOWN_5);
  }
  if (GfGameManager::isBattle() && m_bdatInfo.unknown08 == 1) {
    GfObjAcc acc(static_cast<GfObj *>(unknown08)->unknownf8);
    if (!acc.testFlag(OBJ_FLAG_UNKNOWN_17)) {
      SCOM_DESTROY_GAME_OBJ::create(static_cast<GfObj *>(unknown08)->unknownf8, 1.0f, false);
    }
  }
  m_hfsm.update(&info);
  coli = getColiObject();
  if (coli != nullptr) {
    coli->setDir(unknown100 * info.unknown04);
  }
  updateNaviMeshObj(info.unknown04);
  m_fieldLookIk.update(info.unknown04);
  m_fieldMoveSpeed.update(info.unknown04);
  m_gameStuckMeter.update(info.unknown04);
  unknown250.update(info.unknown04);
  m_pluginManager.update(info);
  GfFieldLocalSteer::UpdateInfo steerUpdate;
  steerUpdate.unknown00 = unknown110;
  steerUpdate.unknown10 = info.unknown04;
  m_fieldLocalSteer.castRay(unknown110);
  m_fieldLocalSteer.update(steerUpdate);
}

gmk::AGmkBase *GfComBehaviorMob::getBindedGmkInst() const { return gmk::getBindedGmkInst(static_cast<GfObj *>(unknown08)->unknownf8); }

bool GfComBehaviorMob::isSquadMember() const { return m_gmkSquadNavi.unknown001() && m_gmkSquadNavi.unknown28 != 0; }

f32 GfComBehaviorMob::getMoveSpeedMps() const {
  GfObjSetupMob *setup = mm::mtl::dynamicCast<GfObjSetupMob>(GfObjManager::getObjInfo(static_cast<GfObj *>(unknown08)->unknownf8)->unknown30);
  return m_fieldMoveSpeed.unknown10 * 0.2777778f * setup->getScaleX();
}

bool GfComBehaviorMob::isMove() const {
  if (unknown250.unknown00.unknown00 == unknown020 ||
      !(unknown250.unknown00.unknown0c >= 0.0f && unknown250.unknown00.unknown0c <= 3.1415927f && unknown250.unknown00.unknown10 >= 0.0f && unknown250.unknown00.unknown10 <= 3.1415927f &&
        unknown250.unknown00.unknown14 > 0.0f) ||
      unknown250.unknown6c) {
    fw::ColiMoveObject *coli = getColiObject();
    if (coli == nullptr) {
      return false;
    }
    if (coli->unknown30 != fw::COLI_TYPE_UNKNOWN_0) {
      gmk::AGmkBase *gmk = getBindedGmkInst();
      if (unknownb8 != nullptr) {
        return true;
      }
      if (isSquadMember()) {
        return true;
      }
      if (gmk == nullptr) {
        return false;
      }
      return gmk->m_createBaseInfo.unknown10->unknown0c != gmk::SHAPE_TYPE_UNKNOWN_1;
    }
  }

  return false;
}

void GfComBehaviorMob::init(bool param1) {
  fw::ColiMoveObject *coli = getColiObject();
  if (coli != nullptr) {
    coli->setState(fw::COLI_STATE_UNKNOWN_1);
    if (param1) {
      coli->setColiType(fw::COLI_TYPE_UNKNOWN_1);
      coli->setPriority(100);
      coli->setState(fw::COLI_STATE_UNKNOWN_0);
    } else {
      coli->setColiType(fw::COLI_TYPE_UNKNOWN_0);
      coli->setPriority(800);
      coli->clearState(fw::COLI_STATE_UNKNOWN_0);
    }
    const fw::unknown031 *shape = coli->unknowne8.get();
    if (shape != nullptr && shape->unknown00 == fw::unknown031::TYPE_UNKNOWN_5) {
      coli->setPriority(800);
    }
  }
  if (unknowna8 != nullptr) {
    if (param1) {
      unknowna8->unknown10 |= 2;
    } else {
      unknowna8->unknown10 &= ~2;
    }
  }
}

void GfComBehaviorMob::initMoveSpeed(f32 time) {
  GfObjSetupMob *setup = mm::mtl::dynamicCast<GfObjSetupMob>(GfObjManager::getObjInfo(static_cast<GfObj *>(unknown08)->unknownf8)->unknown30);
  f32 rate = setup->unknown90 * 0.01f;
  m_fieldMoveSpeed.setSpeedKmph(m_fieldMoveSpeed.unknown08 * rate, time);
}

void GfComBehaviorMob::setStateId(mob::STATE_ID stateId) {
  if (getStateId() != stateId) {
    m_hfsm.setState(stateId);
  }
}

void GfComBehaviorMob::setup() {
  cleanup();
  m_pluginManager.beginSetup(*this, 4);
  m_pluginManager.unknown001<FootStepPlugin>(0, true);
  m_pluginManager.unknown001<EyeBlinkPlugin>(1, true);
  m_pluginManager.endSetup();

  FootStepPlugin *footStep = unknown001<FootStepPlugin>(0);
  if (footStep != nullptr) {
    footStep->setActivate(true);
  }

  gmk::AGmkBase *gmkInst = getBindedGmkInst();
  if (gmkInst != nullptr && gmk::hasEyeBlink(*gmkInst)) {
    GfObjUtil::setEnableEyeBlink(static_cast<GfObj *>(unknown08)->unknownf8, true);
  }

  gmkInst = getBindedGmkInst();
  if (gmkInst != nullptr) {
    CBdatWrapper bdat{gmkInst->getBindedBdatFp()};
    m_bdatInfo.create(bdat, gmkInst->m_createInfo.unknown18);
  }

  createNaviMeshObj();
  createFsm();
  init(isMove());

  {
    GfFieldMoveSpeed::CreateInfo moveSpeedInfo;
    moveSpeedInfo.m_GF_OBJ_HANDLE = static_cast<GfObj *>(unknown08)->unknownf8;
    m_fieldMoveSpeed.create(moveSpeedInfo);
  }
  initMoveSpeed(0.0f);
  createSquadNavi();

  gmk::GmkRoutedMob *routedMob = nullptr;
  if (gmkInst != nullptr) {
    routedMob = gmkInst->getGmkType() == gmk::GMK_TYPE_ROUTED_MOB ? static_cast<gmk::GmkRoutedMob *>(gmkInst) : nullptr;
  }
  unknown08->getComponent<GfComTransform>();
  if (routedMob != nullptr) {
    unknownb8 = routedMob->findRouteNavi(static_cast<GfObj *>(unknown08)->unknownf8);
  }

  fw::ColiMoveObject *coli = getColiObject();
  if (coli != nullptr) {
    GfGameStuckMeter::CreateInfo stuckInfo;
    // The game really clears the value before setColiObj (1.0.0: str wzr, [sp, #16] right before the call), although it is set again below.
    stuckInfo.unknown10 = 0.0f;
    stuckInfo.setColiObj(coli);
    stuckInfo.unknown10 = stuckInfo.unknown00 * stuckInfo.unknown00;
    m_gameStuckMeter.create(stuckInfo);
  }

  {
    GfGameDepopMeter::CreateInfo depopInfo;
    depopInfo.unknown08 = true;
    depopInfo.m_GF_OBJ_HANDLE = static_cast<GfObj *>(unknown08)->unknownf8;
    m_gameDepopMeter.create(depopInfo);
  }

  if (gmkInst != nullptr) {
    CBdatWrapper bdat{gmkInst->getBindedBdatFp()};
    int id = gmkInst->m_createInfo.unknown18;
    m_fieldLookIk.create(static_cast<GfObj *>(unknown08)->unknownf8, bdat, id);
  }

  GfFieldLocalSteer::CreateInfo steerInfo;
  steerInfo.unknown08 = 2.0f;
  steerInfo.unknown0c = 1.0f;
  steerInfo.unknown10 = 0.5f;
  steerInfo.unknown14 = true;
  steerInfo.m_GF_OBJ_HANDLE = static_cast<GfObj *>(unknown08)->unknownf8;
  steerInfo.unknown18 = &unknown5320;
  m_fieldLocalSteer.create(steerInfo);

  mob::STATE_ID stateId = mob::STATE_ID_UNKNOWN_0;
  if (gmkInst != nullptr) {
    switch (gmkInst->getGmkType()) {
    case gmk::GMK_TYPE_MOB:
      stateId = mob::STATE_ID_UNKNOWN_0;
      break;
    case gmk::GMK_TYPE_ROUTED_MOB:
      stateId = mob::STATE_ID_UNKNOWN_1;
      break;
    default:
      break;
    }
  }
  setStateId(stateId);
}

void GfComBehaviorMob::disposeNaviMeshObj() {
  fw::NaviManager::get()->releaseObject(unknowna8);
  unknowna8 = nullptr;
}

void GfComBehaviorMob::disposeFsm() {
  if (!unknown53b0) {
    unknown53b0 = true;
    m_hfsm.cleanup();
  }
}

void GfComBehaviorMob::disposeSquadNavi() { m_gmkSquadNavi.dispose(); }

void GfComBehaviorMob::setActivateCollison(bool isActivate) {
  fw::ColiMoveObject *coli = getColiObject();
  if (coli != nullptr) {
    coli->setActivate(isActivate);
  }
}

u32 GfComBehaviorMob::getStateId() const {
  if (m_hfsm.m_pState != nullptr) {
    return m_hfsm.m_pState->m_state;
  }

  return ai::INVALID_STATE_ID;
}

void GfComBehaviorMob::updateNaviMeshObj(f32 deltaTime) {
  if (unknowna8 != nullptr && (unknowna8->unknown10 & 2) != 0 && m_fieldMoveSpeed.m_GF_OBJ_HANDLE != unknown020) {
    const mm::Vec3 &position = getPos();
    unknowna8->setBeginPos(position);
    unknowna8->setEndPos(unknown110);
    f32 speed = getMoveSpeedMps();
    unknowna8->setMoveSpd(speed * deltaTime);
    unknownb0++;
  }
}

void GfComBehaviorMob::moveToGoal(f32 deltaTime) {
  const mm::Vec3 &position = getPos();
  mm::Vec3 direction(0.0f, 0.0f, 0.0f);
  if (!getMoveVec(direction, unknowna8)) {
    direction = unknown110 - position;
    direction.y = 0.0f;
  }

  if (!direction.unknown003()) {
    direction.unknown001();
  }

  direction *= getMoveSpeedMps();
  unknown100.x = direction.x;
  unknown100.z = direction.z;
  if (m_fieldLocalSteer.m_createInfo.m_GF_OBJ_HANDLE != unknown020) {
    m_fieldLocalSteer.apply(unknown100, unknown100);
  }

  fw::Transform &transform = unknown08->getComponent<GfComTransform>()->unknown001()->unknown003();
  f32 goalAngle = atan2f(unknown100.x, unknown100.z);
  mm::Vec3 front = transform.unknown10.rotate(mm::Vec3::unitZ);
  f32 angle = atan2f(front.x, front.z);
  f32 half = (angle + mm::unknown003(goalAngle - angle) * 0.1f) * 0.5f;
  transform.unknown10.unknown001(half);
}

void GfComBehaviorMob::createNaviMeshObj() {
  disposeNaviMeshObj();
  unknowna8 = fw::NaviManager::get()->createObject();
  if (unknowna8 != nullptr) {
    unknowna8->setMeshNum(0);
    unknowna8->unknown10 |= 2;
  }
  unknownb0 = 0;
}

void GfComBehaviorMob::createFsm() {
  disposeFsm();
  m_hfsm.beginSetup(this, 6, 1);
  m_hfsm.registerState<mob::StateIdle>(mob::STATE_ID_UNKNOWN_0, -1);
  m_hfsm.registerState<mob::StateMove>(mob::STATE_ID_UNKNOWN_1, -1);
  m_hfsm.registerState<npc::StateAreaMove<GfComBehaviorMob>>(mob::STATE_ID_UNKNOWN_2, -1);
  m_hfsm.registerState<mob::StateSquadMember>(mob::STATE_ID_UNKNOWN_3, -1);
  m_hfsm.registerState<npc::StateReaction<GfComBehaviorMob>>(mob::STATE_ID_UNKNOWN_4, -1);
  m_hfsm.registerState<npc::StateBattle<GfComBehaviorMob>>(mob::STATE_ID_UNKNOWN_5, -1);
  m_hfsm.endSetup();
  unknown53b0 = false;
}

void GfComBehaviorMob::execTurnCmdToPos(const mm::Vec3 &position) {
  const mm::Vec3 &current = getPos();
  f32 angle = atan2f(position.x - current.x, position.z - current.z);
  angle += m_fieldLocalSteer.m_createInfo.m_GF_OBJ_HANDLE == unknown020 ? 0.0f : m_fieldLocalSteer.getCurAngle();
  unknown250.create(TFieldExecCmdTurn<GfComAsm>::CreateInfo(static_cast<GfObj *>(unknown08)->unknownf8, angle));
}

void GfComBehaviorMob::execTurnCmdToGoal() {
  mm::Vec3 goal;
  if (getMoveVec(goal, unknowna8)) {
    goal += getPos();
  } else {
    goal = unknown110;
  }
  execTurnCmdToPos(goal);
}

bool GfComBehaviorMob::isArrivedToGoal() const {
  if (m_fieldLocalSteer.isTimeOutCollide()) {
    return true;
  }
  fw::ColiMoveObject *coli = getColiObject();
  if (coli == nullptr) {
    return false;
  }
  f32 height;
  f32 radius;
  const fw::unknown031 *shape = coli->unknowne8.get();
  if (shape != nullptr && shape->unknown00 == fw::unknown031::TYPE_UNKNOWN_3) {
    const fw::unknown134 *character = static_cast<const fw::unknown134 *>(shape);
    height = character->unknown04;
    radius = character->unknown08;
  } else {
    mm::Vec3 min;
    mm::Vec3 max;
    // The game ignores the result of the call (0x710052d060) and reads min and max, which getAABB leaves unset when it returns false.
    coli->getAABB(min, max);
    f32 dx = max.x - min.x;
    f32 dz = max.z - min.z;
    radius = sqrtf(dx * dx + dz * dz) * 0.5f;
    height = max.y - min.y;
  }
  const mm::Vec3 &position = getPos();
  if (!(height < unknown110.y - position.y)) {
    mm::Vec3 diff(unknown110.x - position.x, 0.0f, unknown110.z - position.z);
    f32 distanceSq = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;
    return !(radius * radius < distanceSq);
  }

  return false;
}

void GfComBehaviorMob::createSquadNavi() {
  m_gmkSquadNavi.dispose();
  gmk::AGmkBase *gmk = getBindedGmkInst();
  if (gmk != nullptr) {
    gmk::GmkSquadNavi::CreateInfo info;
    bool isMob = gmk->getGmkType() == gmk::GMK_TYPE_MOB;
    gmk::GmkRoutedMob *routedMob = gmk->getGmkType() == gmk::GMK_TYPE_ROUTED_MOB ? static_cast<gmk::GmkRoutedMob *>(gmk) : nullptr;
    if (isMob) {
      info.m_gmkSquad = static_cast<gmk::GmkMob *>(gmk)->m_gmkMobInsts.m_gmkSquad;
    } else if (routedMob != nullptr) {
      info.m_gmkSquad = routedMob->m_gmkMobInsts.m_gmkSquad;
    }
    GfObjUtil::getObjSetup<GfObjSetupMob>(static_cast<GfObj *>(unknown08)->unknownf8);
    info.unknown08 = static_cast<GfObj *>(unknown08)->unknownf8;
    if (info.unknown08 != unknown020 && info.m_gmkSquad != nullptr) {
      m_gmkSquadNavi.create(info);
    }
  }
}

void GfComBehaviorMob::Listener::onWkStandbyLogout() { m_comBehaviorMob->unknown53b8 = nullptr; }

} // namespace gf
