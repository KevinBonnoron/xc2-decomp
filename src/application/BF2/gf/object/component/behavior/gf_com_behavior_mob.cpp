#include "gf/object/component/behavior/gf_com_behavior_mob.h"

#include <math.h>

#include "ai/ai_state.h"
#include "framework/coli/coli_object.h"
#include "framework/navi/navi_manager.h"
#include "framework/object/updatable_object.h"
#include "framework/reference_frame.h"
#include "fw/fw_transform.h"
#include "gf/object/component/behavior/mob/gf_mob_state_idle.h"
#include "gf/object/component/behavior/mob/gf_mob_state_move.h"
#include "gf/object/component/behavior/mob/gf_mob_state_squad_member.h"
#include "gf/object/component/behavior/npc/gf_npc_state_area_move.h"
#include "gf/object/component/behavior/npc/gf_npc_state_battle.h"
#include "gf/object/component/behavior/npc/gf_npc_state_reaction.h"
#include "gf/object/component/behavior/plugin/gf_plugin_manager.h"
#include "gf/object/component/gf_com_collider.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_mob/gmk_mob.h"
#include "gmk/gmk_mob/gmk_routed_mob.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/rtti.h"
#include "mm_mtl/unique_ptr.h"
#include "mm_mtl/vector.h"
#include "navi/nvmsh_ac_obj.h"

namespace gf {

void GfComBehaviorMob::procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message) {}

void GfComBehaviorMob::procMsgObjectGetVelocity(fw::MessageObject *sender, MsgObjectGetVelocity &message) { message.unknown10 = unknown100; }

GfComBehaviorMob::~GfComBehaviorMob() { cleanup(); }

const mm::mtl::RTTI *GfComBehaviorMob::getRTTI() const { return &m_rtti; }

void GfComBehaviorMob::cleanup() {
  unknownb8 = nullptr;
  disposeNaviMeshObj();
  disposeFsm();
  unknown10.cleanup();
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

gmk::AGmkBase *GfComBehaviorMob::getBindedGmkInst() const { return gmk::getBindedGmkInst(static_cast<GfObj *>(unknown08)->unknownf8); }

bool GfComBehaviorMob::isSquadMember() const { return unknownc0.unknown001() && unknownc0.unknown28 != 0; }

bool GfComBehaviorMob::isMove() const {
  if (unknown250.unknown00.unknown00 == INVALID_HANDLE ||
      !(unknown250.unknown00.unknown0c >= 0.0f && unknown250.unknown00.unknown0c <= 3.1415927f && unknown250.unknown00.unknown10 >= 0.0f && unknown250.unknown00.unknown10 <= 3.1415927f &&
        unknown250.unknown00.unknown14 > 0.0f) ||
      unknown250.unknown6c) {
    fw::ColiMoveObject *coli = getColiObject();
    if (coli == nullptr) {
      return false;
    }
    if (coli->unknown30 != fw::COLI_TYPE_STATIC) {
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
      return gmk->unknown08.unknown10->unknown0c != gmk::SHAPE_TYPE_POINT;
    }
  }

  return false;
}

void GfComBehaviorMob::init(bool param1) {
  fw::ColiMoveObject *coli = getColiObject();
  if (coli != nullptr) {
    coli->setState(fw::COLI_STATE_ENABLE);
    if (param1) {
      coli->setColiType(fw::COLI_TYPE_UNKNOWN_1);
      coli->setPriority(100);
      coli->setState(fw::COLI_STATE_UNKNOWN_0);
    } else {
      coli->setColiType(fw::COLI_TYPE_STATIC);
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
  unknown1e0.setSpeedKmph(unknown1e0.unknown08 * rate, time);
}

void GfComBehaviorMob::setStateId(mob::STATE_ID stateId) {
  if (getStateId() != stateId) {
    unknown5328.setState(stateId);
  }
}

void GfComBehaviorMob::disposeNaviMeshObj() {
  fw::NaviManager::get()->releaseObject(unknowna8);
  unknowna8 = nullptr;
}

void GfComBehaviorMob::disposeFsm() {
  if (!unknown53b0) {
    unknown53b0 = true;
    unknown5328.cleanup();
  }
}

void GfComBehaviorMob::disposeSquadNavi() { unknownc0.dispose(); }

void GfComBehaviorMob::setActivateCollison(bool isActivate) {
  fw::ColiMoveObject *coli = getColiObject();
  if (coli != nullptr) {
    coli->setActivate(isActivate);
  }
}

u32 GfComBehaviorMob::getStateId() const {
  if (unknown5328.m_pState != nullptr) {
    return unknown5328.m_pState->unknown08;
  }

  return ai::INVALID_STATE_ID;
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
  unknown5328.beginSetup(this, 6, 1);
  unknown5328.registerState<mob::StateIdle>(mob::STATE_ID_UNKNOWN_0, -1);
  unknown5328.registerState<mob::StateMove>(mob::STATE_ID_UNKNOWN_1, -1);
  unknown5328.registerState<npc::StateAreaMove<GfComBehaviorMob>>(mob::STATE_ID_UNKNOWN_2, -1);
  unknown5328.registerState<mob::StateSquadMember>(mob::STATE_ID_UNKNOWN_3, -1);
  unknown5328.registerState<npc::StateReaction<GfComBehaviorMob>>(mob::STATE_ID_UNKNOWN_4, -1);
  unknown5328.registerState<npc::StateBattle<GfComBehaviorMob>>(mob::STATE_ID_UNKNOWN_5, -1);
  unknown5328.endSetup();
  unknown53b0 = false;
}

void GfComBehaviorMob::execTurnCmdToPos(const mm::Vec3 &position) {
  const mm::Vec3 &current = getPos();
  f32 angle = atan2f(position.x - current.x, position.z - current.z);
  angle += unknown2c0.unknown00.unknown00 == INVALID_HANDLE ? 0.0f : unknown2c0.getCurAngle();
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
  if (unknown2c0.isTimeOutCollide()) {
    return true;
  }
  fw::ColiMoveObject *coli = getColiObject();
  if (coli == nullptr) {
    return false;
  }
  f32 height;
  f32 radius;
  const fw::unknown031 *shape = coli->unknowne8.get();
  if (shape != nullptr && shape->unknown00 == fw::unknown031::TYPE_CHARACTER) {
    const fw::unknown134 *character = static_cast<const fw::unknown134 *>(shape);
    height = character->unknown04;
    radius = character->unknown08;
  } else {
    mm::Vec3 min;
    mm::Vec3 max;
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
  unknownc0.dispose();
  gmk::AGmkBase *gmk = getBindedGmkInst();
  if (gmk != nullptr) {
    gmk::GmkSquadNavi::CreateInfo info;
    bool isMob = gmk->getGmkType() == gmk::GMK_TYPE_MOB;
    gmk::GmkRoutedMob *routedMob = gmk->getGmkType() == gmk::GMK_TYPE_ROUTED_MOB ? static_cast<gmk::GmkRoutedMob *>(gmk) : nullptr;
    if (isMob) {
      info.unknown00 = static_cast<gmk::GmkMob *>(gmk)->unknown48.unknownb0;
    } else if (routedMob != nullptr) {
      info.unknown00 = routedMob->unknown50.unknownb0;
    }
    GfObjUtil::getObjSetup<GfObjSetupMob>(static_cast<GfObj *>(unknown08)->unknownf8);
    info.unknown08 = static_cast<GfObj *>(unknown08)->unknownf8;
    if (info.unknown08 != INVALID_HANDLE && info.unknown00 != nullptr) {
      unknownc0.create(info);
    }
  }
}

void GfComBehaviorMob::Listener::onWkStandbyLogout() { unknown08->unknown53b8 = nullptr; }

} // namespace gf
