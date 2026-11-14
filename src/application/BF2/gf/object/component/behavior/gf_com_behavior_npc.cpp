#include "gf/object/component/behavior/gf_com_behavior_npc.h"

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
#include "gf/asset/gf_asset_def.h"
#include "gf/asset/gf_asset_manager.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_game_flag.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_message.h"
#include "gf/gf_tween.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/object/gf_menu_obj_target_info.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/behavior/npc/gf_npc_state_approach_pc.h"
#include "gf/object/component/behavior/npc/gf_npc_state_area_move.h"
#include "gf/object/component/behavior/npc/gf_npc_state_battle.h"
#include "gf/object/component/behavior/npc/gf_npc_state_idle.h"
#include "gf/object/component/behavior/npc/gf_npc_state_reaction.h"
#include "gf/object/component/behavior/npc/gf_npc_state_talk.h"
#include "gf/object/component/behavior/npc/gf_npc_state_walk.h"
#include "gf/object/component/behavior/plugin/gf_eye_blink_plugin.h"
#include "gf/object/component/behavior/plugin/gf_lip_sync_plugin.h"
#include "gf/object/component/behavior/plugin/gf_plugin.h"
#include "gf/object/component/behavior/plugin/gf_plugin_manager.h"
#include "gf/object/component/gf_com_collider.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/component/gf_component.h"
#include "gf/object/component/model/gf_com_model.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "gf/scom/gf_scom_obj.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_blade.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_npc/gmk_npc.h"
#include "gmk/gmk_npc/gmk_routed_npc.h"
#include "mm/mm_std_base.h"
#include "mm_mtl/reference_object.h"
#include "mm_mtl/rtti.h"
#include "mm_mtl/unique_ptr.h"
#include "mm_mtl/vector.h"
#include "navi/nvmsh_ac_obj.h"

namespace gf {

constexpr int unknown001 = 0xa396; // Inferred role: first game flag of the talk bonus states; original name unknown.

// Inferred role: talk state of each MsgGameTalkAction action; original name unknown.
static const char *const unknown009[] = {"S_talkA_00", "S_talkA_01", "S_talkA_02", "S_idle"};
// Inferred role: talk command of each MsgGameTalkAction action, none for the actions that only set the state; original name unknown.
static const char *const unknown010[] = {"C_talkA_00", nullptr, "C_talkA_02", nullptr};

void GfComBehaviorNpc::BdatInfo::create(const CBdatWrapper &bdat, int id, const GfComBehaviorNpc &npc) {
  unknown00 = bdat.getValCheck("ShopID", id, gmk::BDAT_TYPE_UNKNOWN_2);
  u16 closeRange = bdat.getValCheck("CloseRange", id, gmk::BDAT_TYPE_UNKNOWN_2);
  unknown04 = static_cast<f32>(closeRange * closeRange);
  unknown08 = static_cast<f32>(static_cast<u16>(bdat.getValCheck("MoveSpeed", id, gmk::BDAT_TYPE_UNKNOWN_2)));
  u16 reactionRange = bdat.getValCheck("ReactionRange", id, gmk::BDAT_TYPE_UNKNOWN_2);
  unknown0c = static_cast<f32>(reactionRange * reactionRange);
  unknown10 = bdat.getValCheck("ReactionPercent", id, gmk::BDAT_TYPE_UNKNOWN_2);
  unknown12 = bdat.getValCheck("ReactionMot", id, gmk::BDAT_TYPE_UNKNOWN_2);
  unknown14 = bdat.getValCheck("BattleReaction", id, gmk::BDAT_TYPE_UNKNOWN_2);
  unknown16 = bdat.getValCheck("BattleMot", id, gmk::BDAT_TYPE_UNKNOWN_2);

  gmk::AGmkBase *gmk = npc.getBindedGmkInst();
  switch (gmk->getGmkType()) {
  case gmk::GMK_TYPE_NPC:
  case gmk::GMK_TYPE_ROUTED_NPC:
    unknown18 = bdat.getValCheck("EventID", id, gmk::BDAT_TYPE_UNKNOWN_2);
    break;
  case gmk::GMK_TYPE_BLADE:
    if (static_cast<gmk::GmkBlade *>(gmk)->unknown50 != 0) {
      unknown18 = GfDataBlade::getNormalTalk(static_cast<gmk::GmkBlade *>(gmk)->unknown50);
    }
    break;
  default:
    break;
  }

  if (unknown18 != 0) {
    u8 *talk = GfDataBdat::getFP(BDAT_EVT_LIST_TLK01);
    if (Bdat::getIdTop(talk) <= unknown18 && unknown18 < Bdat::getIdTop(talk) + Bdat::getIdCount(talk) && unknown00 == 0) {
      unknown1a = true;
    }
  }
}

int GfComBehaviorNpc::BdatInfo::getTalkBonusFlagId() const {
  u8 *talk = GfDataBdat::getFP(BDAT_EVT_LIST_TLK01);
  u16 event = unknown18;
  return event + gf::unknown001 - Bdat::getIdTop(talk);
}

bool GfComBehaviorNpc::BdatInfo::isIconTalkBonus() const {
  if (!unknown1a) {
    return false;
  }
  return GfGameFlag::getLocal(1, getTalkBonusFlagId()) == 0;
}

void GfComBehaviorNpc::BdatInfo::setTalkBonusFlag() const { GfGameFlag::setLocal(1, getTalkBonusFlagId(), 1); }

f32 GfComBehaviorNpc::BdatInfo::getDistYThreshold() { return 2.0f; }

bool GfComBehaviorNpc::LocalSteerIsTargetNotPlayer::operator()(const GfFieldLocalSteer &steer, GF_OBJ_HANDLE *handle) const { return GfGameManager::getPartyLeader() != handle; }

void GfComBehaviorNpc::procMsgPcFieldNotifyAction(fw::MessageObject *sender, MsgPcFieldNotifyAction &message) {
  switch (message.unknown08) {
  case 0:
    if (!unknown100 && GfGameManager::isTalkOK() && getStateId() != npc::STATE_ID_UNKNOWN_6) {
      unknown100 = true;
      unknown220.unknown20 = false;
      setStateId(npc::STATE_ID_UNKNOWN_6);
    }
    break;
  case 1:
    if (unknown100) {
      unknown100 = false;
      unknown220.unknown20 = true;
    }
    break;
  }
}

void GfComBehaviorNpc::procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message) {}

void GfComBehaviorNpc::procMsgPcFieldGetAccessType(fw::MessageObject *sender, MsgPcFieldGetAccessType &message) {
  message.unknown08 = 2;
  message.unknown0c = false;
  if (unknown100 || !GfGameManager::isTalkOK() || getStateId() == npc::STATE_ID_UNKNOWN_6) {
    return;
  }

  gmk::AGmkBase *gmk = getBindedGmkInst();
  if (gmk == nullptr) {
    return;
  }

  gmk::GmkType type = gmk->getGmkType();
  if (type == gmk::GMK_TYPE_NPC) {
    message.unknown0c = static_cast<gmk::GmkNpc *>(gmk)->isPopCondMatchedExceptDist();
  } else if (type == gmk::GMK_TYPE_ROUTED_NPC) {
    message.unknown0c = static_cast<gmk::GmkRoutedNpc *>(gmk)->isPopCondMatchedExceptDist();
  } else if (type == gmk::GMK_TYPE_BLADE) {
    message.unknown0c = gmk->isValid() && static_cast<gmk::GmkBlade *>(gmk)->getBdatInfo()->isPopCommonCondMatched();
  }
}

void GfComBehaviorNpc::procMsgPcGetLookPoint(fw::MessageObject *sender, MsgPcGetLookPoint &message) {
  if (unknown1b8.get() != nullptr) {
    message.unknown10 = unknown1b8->getSyncedWorldTransform().unknown00;
    message.unknown20 = true;
  }
}

void GfComBehaviorNpc::procMsgGameTalkAction(fw::MessageObject *sender, MsgGameTalkAction &message) {
  GfComAsm *comAsm = unknown08->getComponent<GfComAsm>();
  if (comAsm == nullptr) {
    return;
  }

  if (message.isDirect) {
    message.isSuccess = comAsm->setState(unknown009[message.action], ANIM_LAYER_UNKNOWN_0);
  } else {
    if (unknown010[message.action] != nullptr) {
      message.isSuccess = comAsm->execCmd(unknown010[message.action], ANIM_LAYER_UNKNOWN_0);
    }
    if (!message.isSuccess) {
      // The game computes the state name and drops it, likely the argument of a debug message removed from the release build.
      MM_VERIFY(comAsm->getStateName(ANIM_LAYER_UNKNOWN_0) != nullptr ? comAsm->getStateName(ANIM_LAYER_UNKNOWN_0) : "");
      if (unknown010[message.action] != nullptr) {
        message.isSuccess = comAsm->setState(unknown009[message.action], ANIM_LAYER_UNKNOWN_0);
      }
    }
  }
}

void GfComBehaviorNpc::procMsgGameLipAction(fw::MessageObject *sender, MsgGameLipAction &message) {
  switch (message.action) {
  case 0: {
    LipSyncPlugin *plugin = unknown001<LipSyncPlugin>(2);
    if (plugin != nullptr) {
      plugin->unknown21 = true;
    }
    break;
  }
  case 1: {
    LipSyncPlugin *plugin = unknown001<LipSyncPlugin>(2);
    if (plugin != nullptr) {
      plugin->unknown21 = false;
    }
    break;
  }
  }
}

void GfComBehaviorNpc::procMsgGameSetLipWeight(fw::MessageObject *sender, MsgGameSetLipWeight &message) {
  LipSyncPlugin *plugin = unknown001<LipSyncPlugin>(2);
  if (plugin != nullptr) {
    plugin->setWeight(message.unknown08);
  }
}

void GfComBehaviorNpc::procMsgObjectGetVelocity(fw::MessageObject *sender, MsgObjectGetVelocity &message) { message.unknown10 = unknownf0; }

gmk::GmkRouteNavi *GfComBehaviorNpc::getGmkRouteNavi() const {
  gmk::AGmkBase *gmk = getBindedGmkInst();
  if (gmk != nullptr && gmk->getGmkType() == gmk::GMK_TYPE_ROUTED_NPC) {
    return static_cast<gmk::GmkRoutedNpc *>(gmk)->unknown70;
  }

  return nullptr;
}

const mm::Vec3 &GfComBehaviorNpc::getPos() const { return unknown08->getComponent<GfComTransform>()->unknown001()->getSyncedWorldTransform().unknown00; }

const mm::Quat &GfComBehaviorNpc::getRot() const { return unknown08->getComponent<GfComTransform>()->unknown001()->getSyncedWorldTransform().unknown10; }

void GfComBehaviorNpc::disposeNaviMeshObj() {
  fw::NaviManager::get()->releaseObject(unknownb8);
  unknownb8 = nullptr;
}

gmk::AGmkBase *GfComBehaviorNpc::getBindedGmkInst() const { return gmk::getBindedGmkInst(static_cast<GfObj *>(unknown08)->unknownf8); }

void GfComBehaviorNpc::setGoalPos(const mm::Vec3 &position) { unknownc0 = position; }

const mm::mtl::RTTI *GfComBehaviorNpc::getRTTI() const { return &m_rtti; }

GfComAsm *GfComBehaviorNpc::getComAsm() const { return unknown08->getComponent<GfComAsm>(); }

bool GfComBehaviorNpc::isNullNpc() const { return !GfAssetManager::isExist(GfObjUtil::getAssetHandle(static_cast<GfObj *>(unknown08)->unknownf8), static_cast<GfFileIdx>(6)); }

fw::ColiMoveObject *GfComBehaviorNpc::getColiObject() const {
  GfComCollider *collider = unknown08->getComponent<GfComCollider>();
  if (collider != nullptr) {
    fw::ColiObject *coli = collider->unknown18[0];
    if (coli != nullptr) {
      return mm::mtl::dynamicCast<fw::ColiMoveObject>(coli);
    }
  }

  return nullptr;
}

void GfComBehaviorNpc::disposeFsm() {
  if (!unknown190) {
    unknown190 = true;
    unknown108.cleanup();
  }
}

u32 GfComBehaviorNpc::getStateId() const {
  if (unknown108.m_pState != nullptr) {
    return unknown108.m_pState->unknown08;
  }

  return ai::INVALID_STATE_ID;
}

void GfComBehaviorNpc::setStateId(npc::STATE_ID stateId) {
  if (getStateId() != stateId) {
    initStateId(stateId);
  }
}

void GfComBehaviorNpc::initStateId(npc::STATE_ID stateId) {
  unknown108.setState(stateId);
  validateLocalSteer(stateId);
}

void GfComBehaviorNpc::validateLocalSteer(npc::STATE_ID stateId) {
  GfFieldLocalSteer::CreateInfo info;
  info.unknown08 = 2.0f;
  info.unknown0c = 1.0f;
  info.unknown10 = 0.5f;
  info.unknown14 = true;
  info.unknown00 = static_cast<GfObj *>(unknown08)->unknownf8;
  info.unknown18 = stateId == npc::STATE_ID_UNKNOWN_3 ? &unknown53b0 : nullptr;
  unknown350.create(info);
}

void GfComBehaviorNpc::disposeMenuObj() {
  if (unknown1b0 != nullptr) {
    GfMenuObjTargetInfo::close(unknown1b0);
    mm::mtl::safeRelease(unknown1b0);
  }
}

void GfComBehaviorNpc::setActivateCollison(bool isActivate) {
  fw::ColiMoveObject *coli = getColiObject();
  if (coli != nullptr) {
    coli->setActivate(isActivate);
  }
}

void GfComBehaviorNpc::createFsm() {
  disposeFsm();
  unknown108.beginSetup(this, 7, 1);
  unknown108.registerState<npc::StateIdle>(npc::STATE_ID_UNKNOWN_0, -1);
  unknown108.registerState<npc::StateWalk>(npc::STATE_ID_UNKNOWN_1, -1);
  unknown108.registerState<npc::StateAreaMove<GfComBehaviorNpc>>(npc::STATE_ID_UNKNOWN_2, -1);
  unknown108.registerState<npc::StateApproachPc>(npc::STATE_ID_UNKNOWN_3, -1);
  unknown108.registerState<npc::StateReaction<GfComBehaviorNpc>>(npc::STATE_ID_UNKNOWN_4, -1);
  unknown108.registerState<npc::StateBattle<GfComBehaviorNpc>>(npc::STATE_ID_UNKNOWN_5, -1);
  unknown108.registerState<npc::StateTalk>(npc::STATE_ID_UNKNOWN_6, -1);
  unknown108.endSetup();
  unknown190 = false;
}

void GfComBehaviorNpc::createNaviMeshObj() {
  disposeNaviMeshObj();
  unknownb8 = fw::NaviManager::get()->createObject();
  if (unknownb8 != nullptr) {
    unknownb8->setMeshNum(0);
    unknownb8->unknown10 |= 2;
  }
}

GfComBehaviorNpc::GfComBehaviorNpc()
    : unknown98(), unknownb8(nullptr), unknownc0(mm::Vec3::zero), unknownd0(mm::Quat::identity), unknowne0(1.0e12f), unknowne4(1.0e12f), unknownf0(mm::Vec3::zero), unknown100(false),
      unknown101(false), unknown108(fw::Allocator::getProcAllocator()), unknown190(true), unknown198(nullptr), unknown1a0(), unknown1b0(nullptr), unknown1b8(), unknown1c0(nullptr),
      unknown220(nullptr), unknown270(nullptr), unknown2a0(unknown020) {
  createNaviMeshObj();
}

void GfComBehaviorNpc::cleanup() {
  disposeFsm();
  disposeMenuObj();
  if (unknown1b8.get() != nullptr) {
    GfComModel *model = unknown08->getComponent<GfComModel>();
    if (model != nullptr) {
      const char *bone = nullptr;
      if (model->getBoneReferenceFrame("JU_neck").get() != nullptr) {
        bone = "JU_neck";
      } else if (model->getBoneReferenceFrame("JU_spA").get() != nullptr) {
        bone = "JU_spA";
      }
      if (bone != nullptr) {
        model->destroyBoneReferenceFrame(bone);
      }
    }
    unknown1b8 = nullptr;
  }
  unknown10.cleanup();
}

bool GfComBehaviorNpc::recieveMessage(fw::MessageObject *sender, fw::Message &message) {
  bool isHandled = false;
  switch (message.unknown00) {
  case MSG_UNKNOWN_16777219:
    isHandled = true;
    break;
  case MSG_UNKNOWN_16777224:
    procMsgPcGetLookPoint(sender, static_cast<MsgPcGetLookPoint &>(message));
    isHandled = true;
    break;
  case MSG_UNKNOWN_16777228:
    procMsgPcFieldGetAccessType(sender, static_cast<MsgPcFieldGetAccessType &>(message));
    isHandled = true;
    break;
  case MSG_UNKNOWN_16777229:
    procMsgPcFieldNotifyAction(sender, static_cast<MsgPcFieldNotifyAction &>(message));
    isHandled = true;
    break;
  case MSG_GAME_UNKNOWN_16777261:
    procMsgGameTalkAction(sender, static_cast<MsgGameTalkAction &>(message));
    isHandled = true;
    break;
  case MSG_GAME_UNKNOWN_16777262:
    procMsgGameLipAction(sender, static_cast<MsgGameLipAction &>(message));
    isHandled = true;
    break;
  case MSG_GAME_UNKNOWN_16777263:
    procMsgGameSetLipWeight(sender, static_cast<MsgGameSetLipWeight &>(message));
    isHandled = true;
    break;
  case MSG_UNKNOWN_16777286:
    procMsgObjectGetVelocity(sender, static_cast<MsgObjectGetVelocity &>(message));
    isHandled = true;
    break;
  }
  return isHandled;
}

void GfComBehaviorNpc::setup() {
  cleanup();
  unknown10.beginSetup(*this, 4);
  unknown10.unknown001<EyeBlinkPlugin>(1, true);
  unknown10.unknown001<LipSyncPlugin>(2, true);
  unknown10.endSetup();
  Plugin *plugin = unknown10.unknown28[2];
  if (plugin != nullptr) {
    plugin->setActivate(true);
  }
  gmk::AGmkBase *gmk = getBindedGmkInst();
  if (gmk != nullptr && gmk::hasEyeBlink(*gmk)) {
    GfObjUtil::setEnableEyeBlink(static_cast<GfObj *>(unknown08)->unknownf8, true);
  }
  init(false);
  createFsm();
  {
    GfFieldMoveSpeed::CreateInfo moveSpeedInfo;
    moveSpeedInfo.unknown00 = static_cast<GfObj *>(unknown08)->unknownf8;
    unknown270.create(moveSpeedInfo);
  }
  validateBindedGmkInstInfo(false);
  fw::ColiMoveObject *coli = getColiObject();
  if (coli != nullptr) {
    GfGameStuckMeter::CreateInfo stuckInfo;
    // The game really clears the value before setColiObj (1.0.0: str wzr, [sp, #24] at 0x7100534b74, right before the call), although it is set again below.
    stuckInfo.unknown10 = 0.0f;
    stuckInfo.setColiObj(coli);
    stuckInfo.unknown10 = stuckInfo.unknown00 * stuckInfo.unknown00;
    unknown1c0.create(stuckInfo);
  }
  GfGameDepopMeter::CreateInfo depopInfo;
  depopInfo.unknown08 = true;
  depopInfo.unknown00 = static_cast<GfObj *>(unknown08)->unknownf8;
  unknown220.create(depopInfo);
}

void GfComBehaviorNpc::update(const fw::UpdateInfo &info) {
  if (!unknown100) {
    unknown2a0.update(info.unknown04);
  }
  unknownf0.z = 0.0f;
  unknownf0.x = 0.0f;
  fw::ColiMoveObject *coli = getColiObject();
  if (coli == nullptr || coli->testAttribute(fw::COLI_ATRR_UNKNOWN_0) || coli->unknown30 == 0) {
    unknownf0.y = 0.0f;
  } else {
    unknownf0.y += info.unknown04 * -9.8f;
  }
  if (gmk::isPlayerExist()) {
    GfObjAcc acc(static_cast<GfObj *>(unknown08));
    const mm::Vec3 &position = acc.getWorldTransform().unknown00;
    mm::Vec3 delta = gmk::getPlayerPos() - position;
    unknowne4 = delta.y * delta.y;
    delta.y = 0.0f;
    unknowne0 = delta.x * delta.x + delta.y * delta.y + delta.z * delta.z;
  }
  if (npc::StateBattle<GfComBehaviorNpc>::isCondMatch(*this) && (unknown108.m_pState == nullptr || unknown108.m_pState->unknown08 != npc::STATE_ID_UNKNOWN_5)) {
    unknown108.setState(npc::STATE_ID_UNKNOWN_5);
    GfFieldLocalSteer::CreateInfo steerInfo;
    steerInfo.unknown08 = 2.0f;
    steerInfo.unknown0c = 1.0f;
    steerInfo.unknown10 = 0.5f;
    steerInfo.unknown14 = true;
    steerInfo.unknown00 = static_cast<GfObj *>(unknown08)->unknownf8;
    steerInfo.unknown18 = nullptr;
    unknown350.create(steerInfo);
  }
  if (GfGameManager::isBattle() && unknown98.unknown14 == 1) {
    GfObjAcc acc(static_cast<GfObj *>(unknown08)->unknownf8);
    if (!acc.testFlag(OBJ_FLAG_UNKNOWN_17)) {
      SCOM_DESTROY_GAME_OBJ::create(static_cast<GfObj *>(unknown08)->unknownf8, 1.0f, false);
    }
  }
  unknown108.update(&info);
  coli = getColiObject();
  if (coli != nullptr) {
    coli->setDir(mm::Vec3(info.unknown04 * unknownf0.x, info.unknown04 * unknownf0.y, info.unknown04 * unknownf0.z));
  }
  unknown1c0.update(info.unknown04);
  unknown2e0.update(info.unknown04);
  unknown10.update(info);
  if (unknownf0.x != 0.0f && unknownf0.z != 0.0f) {
    GfFieldLocalSteer::UpdateInfo steerUpdate;
    steerUpdate.unknown00 = unknownc0;
    steerUpdate.unknown10 = info.unknown04;
    unknown350.castRay(unknownc0);
    unknown350.update(steerUpdate);
  } else {
    unknown350.unknown28.unknown10 = 0.0f;
    unknown350.unknown28.unknown14 = 0.0f;
    unknown350.unknown28.unknown08 = 0.0f;
    unknown350.unknown28.unknown0c = 0.0f;
  }
  updateNaviMeshObj(info.unknown04);
}

GfComBehaviorNpc::~GfComBehaviorNpc() {
  cleanup();
  disposeNaviMeshObj();
}

void GfComBehaviorNpc::updateNaviMeshObj(f32 deltaTime) {
  if (unknownb8 != nullptr && (unknownb8->unknown10 & 2) != 0) {
    const mm::Vec3 &position = getPos();
    unknownb8->setBeginPos(position);
    unknownb8->setEndPos(unknownc0);
    unknownb8->setMoveSpd(unknown98.unknown08 * deltaTime);
  }
}

void GfComBehaviorNpc::init(bool param1) {
  fw::ColiMoveObject *coli = getColiObject();
  if (coli != nullptr) {
    coli->setState(fw::COLI_STATE_UNKNOWN_1);
    if (param1) {
      coli->setColiType(fw::COLI_TYPE_UNKNOWN_1);
      coli->setPriority(200);
      coli->setState(fw::COLI_STATE_UNKNOWN_0);
    } else {
      coli->setColiType(fw::COLI_TYPE_UNKNOWN_0);
      coli->setPriority(900);
      coli->clearState(fw::COLI_STATE_UNKNOWN_0);
    }

    if (coli->unknowne8.get() != nullptr && coli->unknowne8.get()->unknown00 == fw::unknown031::TYPE_UNKNOWN_5) {
      coli->setPriority(900);
    }
  }

  if (unknownb8 != nullptr) {
    if (param1) {
      unknownb8->unknown10 |= 2;
    } else {
      unknownb8->unknown10 &= ~2;
    }
  }
}

void GfComBehaviorNpc::execTurnCmd(f32 angle) {
  angle += unknown350.unknown00.unknown00 == unknown020 ? 0.0f : unknown350.getCurAngle();
  unknown2e0.create(TFieldExecCmdTurn<GfComAsm>::CreateInfo(static_cast<GfObj *>(unknown08)->unknownf8, angle));
}

void GfComBehaviorNpc::execTurnCmd(f32 angle, f32 param2, f32 param3, f32 param4) {
  TFieldExecCmdTurn<GfComAsm>::CreateInfo info;
  info.unknown00 = static_cast<GfObj *>(unknown08)->unknownf8;
  info.unknown08 = (unknown350.unknown00.unknown00 == unknown020 ? 0.0f : unknown350.getCurAngle()) + angle;
  info.unknown0c = param3;
  info.unknown14 = param2;
  info.unknown18 = param4;
  unknown2e0.create(info);
}

void GfComBehaviorNpc::execTurnCmdToPos(const mm::Vec3 &position) {
  const mm::Vec3 &current = getPos();
  f32 angle = atan2f(position.x - current.x, position.z - current.z);
  angle += unknown350.unknown00.unknown00 == unknown020 ? 0.0f : unknown350.getCurAngle();
  unknown2e0.create(TFieldExecCmdTurn<GfComAsm>::CreateInfo(static_cast<GfObj *>(unknown08)->unknownf8, angle));
}

void GfComBehaviorNpc::execTurnCmdToGoal() {
  mm::Vec3 position;
  if (getMoveVec(position, unknownb8)) {
    position += getPos();
  } else {
    position = unknownc0;
  }

  execTurnCmdToPos(position);
}

void GfComBehaviorNpc::Listener::onWkStandbyLogout() { unknown08->unknown198 = nullptr; }

} // namespace gf
