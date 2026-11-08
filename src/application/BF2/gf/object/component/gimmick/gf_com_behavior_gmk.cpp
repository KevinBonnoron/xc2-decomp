#include "gf/object/component/gimmick/gf_com_behavior_gmk.h"

#include "bdat.h"
#include "framework/coli/coli_object.h"
#include "framework/object/updatable_object.h"
#include "framework/reference_frame.h"
#include "fw/fw_transform.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_util.h"
#include "gf/game/sequential_play/gf_play_factory.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/object/gf_menu_obj_target_info.h"
#include "gf/object/component/gf_com_collider.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_jump.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_route_navi.h"
#include "gmk/gmk_salvage.h"
#include "gmk/gmk_warp.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/reference_object.h"
#include "mm_mtl/rtti.h"
#include "mm_mtl/vector.h"

namespace gf {

GfComBehaviorGmk::GfComBehaviorGmk() : unknown98(nullptr), unknowna0(nullptr), unknowna8(nullptr), unknownb0(nullptr), unknownc0(nullptr) {}

GfComBehaviorGmk::~GfComBehaviorGmk() {
  if (unknowna0 != nullptr) {
    delete unknowna0;
    unknowna0 = nullptr;
  }
}

const mm::mtl::RTTI *GfComBehaviorGmk::getRTTI() const { return &m_rtti; }

bool GfComBehaviorGmk::recieveMessage(fw::MessageObject *sender, fw::Message &message) {
  switch (message.unknown00) {
  case MSG_PC_GET_LOOK_POINT:
    procMsgPcGetLookPoint(sender, static_cast<MsgPcGetLookPoint &>(message));
    return true;
  case MSG_PC_FIELD_GET_ACCESS_TYPE:
    procMsgPcFieldGetAccessType(sender, static_cast<MsgPcFieldGetAccessType &>(message));
    return true;
  case MSG_PC_FIELD_NOTIFY_ACTION:
    procMsgPcFieldNotifyAction(sender, static_cast<MsgPcFieldNotifyAction &>(message));
    return true;
  case MSG_PC_FIELD_NOTIFY_SKILL_EVENT:
    procMsgPcFieldNotifySkillEvent(sender, static_cast<MsgPcFieldNotifySkillEvent &>(message));
    return true;
  case MSG_PC_GET_ELV_LIFT:
    procMsgPcGetElvLift(sender, static_cast<MsgPcGetElvLift &>(message));
    return true;
  default:
    return false;
  }
}

void GfComBehaviorGmk::procMsgPcFieldNotifyAction(fw::MessageObject *sender, MsgPcFieldNotifyAction &message) {
  if (message.unknown08 != 0 || (static_cast<GfObj *>(unknown08)->unknown110 & 1) == 0) {
    return;
  }

  gmk::AGmkBase *gmk = gmk::getBindedGmkInst(static_cast<GfObj *>(unknown08)->unknownf8);
  if (gmk == nullptr) {
    GfObjAcc acc(static_cast<GfObj *>(unknown08)->unknownf8);
    // The game calls both and drops the results, likely the arguments of a debug message removed from the release build.
    acc.isDestroy();
    acc.testFlag(OBJ_FLAG_UNKNOWN_E);
    return;
  }

  bool isAccess;
  switch (gmk->getGmkType()) {
  case gmk::GMK_TYPE_TBOX:
  case gmk::GMK_TYPE_SALVAGE_LOCATOR:
    isAccess = GfPlayFactory::createFieldTbox(static_cast<GfObj *>(unknown08)->unknownf8);
    break;
  case gmk::GMK_TYPE_EVENT:
  case gmk::GMK_TYPE_KIZUNA_TALK:
    isAccess = true;
    break;
  case gmk::GMK_TYPE_COLLECTION:
    isAccess = GfPlayFactory::createCollect(static_cast<GfObj *>(unknown08)->unknownf8);
    break;
  case gmk::GMK_TYPE_SALVAGE:
    isAccess = GfPlayFactory::createSalvage(static_cast<GfObj *>(unknown08)->unknownf8);
    break;
  case gmk::GMK_TYPE_MAP_GIMMICK:
    isAccess = GfPlayFactory::createMapGimmick(static_cast<GfObj *>(unknown08)->unknownf8);
    break;
  case gmk::GMK_TYPE_GRAVE:
    isAccess = GfPlayFactory::createGrave(static_cast<GfObj *>(unknown08)->unknownf8);
    break;
  case gmk::GMK_TYPE_JUMP:
    isAccess = GfPlayFactory::createJump(static_cast<GfObj *>(unknown08)->unknownf8);
    break;
  case gmk::GMK_TYPE_WARP:
    isAccess = GfPlayFactory::createWarp(static_cast<GfObj *>(unknown08)->unknownf8);
    break;
  case gmk::GMK_TYPE_DOOR:
  case gmk::GMK_TYPE_ELEVATOR:
    isAccess = GfGameManager::isEnableFieldAccess();
    break;
  default:
    return;
  }

  if (isAccess) {
    gmk->onPlayerAccessed(static_cast<GfObj *>(unknown08)->unknownf8);
  }
}

void GfComBehaviorGmk::procMsgPcFieldGetAccessType(fw::MessageObject *sender, MsgPcFieldGetAccessType &message) {
  gmk::AGmkBase *gmk = gmk::getBindedGmkInst(static_cast<GfObj *>(unknown08)->unknownf8);
  if (gmk == nullptr) {
    return;
  }

  switch (gmk->getGmkType()) {
  case gmk::GMK_TYPE_TBOX:
  case gmk::GMK_TYPE_COLLECTION:
    message.unknown08 = 1;
    break;
  default:
    message.unknown08 = 5;
    break;
  case gmk::GMK_TYPE_SALVAGE:
    message.unknown08 = 5;
    message.unknown0d = true;
    break;
  case gmk::GMK_TYPE_SALVAGE_LOCATOR:
    message.unknown08 = static_cast<gmk::GmkSalvageLocator *>(gmk)->getData()->unknown00 == 2 ? 1 : 5;
    break;
  case gmk::GMK_TYPE_JUMP:
    message.unknown08 = 3;
    break;
  case gmk::GMK_TYPE_WARP:
    message.unknown08 = 4;
    break;
  }
}

void GfComBehaviorGmk::procMsgPcGetLookPoint(fw::MessageObject *sender, MsgPcGetLookPoint &message) {
  message.unknown10 = unknownc0->getSyncedWorldTransform().unknown00;
  message.unknown20 = true;
}

void GfComBehaviorGmk::procMsgPcFieldNotifySkillEvent(fw::MessageObject *sender, MsgPcFieldNotifySkillEvent &message) {
  gmk::AGmkBase *gmk = gmk::getBindedGmkInst(static_cast<GfObj *>(unknown08)->unknownf8);
  if (gmk == nullptr) {
    return;
  }

  u32 event = message.unknown08;
  switch (gmk->getGmkType()) {
  case gmk::GMK_TYPE_JUMP:
    if (event == 0) {
      static_cast<gmk::GmkJump *>(gmk)->reqDeadIcon();
    } else {
      static_cast<gmk::GmkJump *>(gmk)->reqRecreateIcon();
      createMenuObj();
    }
    break;
  case gmk::GMK_TYPE_WARP:
    if (event == 0) {
      static_cast<gmk::GmkWarp *>(gmk)->reqDeadIcon();
    } else {
      static_cast<gmk::GmkWarp *>(gmk)->reqRecreateIcon();
      createMenuObj();
    }
    break;
  default:
    break;
  }
}

void GfComBehaviorGmk::createMenuObj() {
  disposeMenuObj();
  if (!mm::mtl::dynamicCast<GfObjSetupGimmick>(GfObjManager::getObjInfo(static_cast<GfObj *>(unknown08)->unknownf8)->unknown30)->unknowna1) {
    return;
  }
  GfMenuObjTargetInfo::OpenOtherParam param;
  param.unknown00 = static_cast<GfObj *>(unknown08)->unknownf8;
  param.unknown30 = GfDataBdat::getFP(BDAT_FLD_GMKNAME);
  if (!GfGameUtil::getNameMsId(param.unknown38, static_cast<GfObj *>(unknown08)->unknownf8)) {
    return;
  }
  gmk::AGmkBase *gmk = gmk::getBindedGmkInst(static_cast<GfObj *>(unknown08)->unknownf8);
  if (gmk == nullptr || !gmk->isValid()) {
    return;
  }
  u8 *bdat = gmk->getBindedBdatFp();
  int id = gmk->unknown20.unknown18;
  switch (gmk->getGmkType()) {
  case gmk::GMK_TYPE_COLLECTION:
    param.unknown3c = true;
    param.unknown40 = 2;
    break;
  case gmk::GMK_TYPE_SALVAGE:
    param.unknown40 = 0;
    param.unknown3c = true;
    param.unknown48 = GfDataBdat::getFP(BDAT_FLD_SALVAGEPOINT);
    param.unknown50 = static_cast<u16>(Bdat::getValCheck(bdat, "SalvagePointName", id, gmk::BDAT_TYPE_U16));
    break;
  case gmk::GMK_TYPE_KIZUNA_TALK:
    param.unknown3c = true;
    param.unknown40 = 1;
    break;
  default:
    break;
  }
  int offsetId = GfGameUtil::getUiOffsetId(param.unknown00);
  param.unknown10.unknown10 = nullptr;
  param.unknown10.unknown00 = mm::Vec3::zero.x;
  param.unknown10.unknown04 = mm::Vec3::zero.y;
  param.unknown10.unknown08 = mm::Vec3::zero.z;
  GfMenuBdat::getMenuOffset(offsetId, param.unknown10);
  unknowna8 = GfMenuCallContext::create();
  GfMenuObjTargetInfo::openOther(unknowna8, param);
}

void GfComBehaviorGmk::cleanup() {
  disposeMenuObj();
  unknownc0 = nullptr;
}

void GfComBehaviorGmk::disposeMenuObj() {
  if (unknowna8 != nullptr) {
    GfMenuObjTargetInfo::close(unknowna8);
    mm::mtl::safeRelease(unknowna8);
  }
}

void GfComBehaviorGmk::setActivateCollison(bool isActivate) {
  fw::ColiMoveObject *coli = getColiObject();
  if (coli != nullptr) {
    coli->setActivate(isActivate);
  }
}

fw::ColiMoveObject *GfComBehaviorGmk::getColiObject() const {
  GfComCollider *collider = unknown08->getComponent<GfComCollider>();
  if (collider != nullptr && !collider->unknown18.empty()) {
    fw::ColiObject *coli = collider->unknown18[0];
    if (coli != nullptr) {
      return mm::mtl::dynamicCast<fw::ColiMoveObject>(coli);
    }
  }

  return nullptr;
}

} // namespace gf
