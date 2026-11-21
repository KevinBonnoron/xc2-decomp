#include "gf/object/component/gimmick/gf_com_behavior_gmk.h"

#include <math.h>

#include "bdat.h"
#include "framework/coli/coli_object.h"
#include "framework/object/updatable_object.h"
#include "framework/reference_frame.h"
#include "fw/fw_transform.h"
#include "fw/fw_update_info.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_object_type.h"
#include "gf/field/gf_big_obj_unique.h"
#include "gf/field/gf_field_lod.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_obj.h"
#include "gf/game/gf_game_util.h"
#include "gf/game/sequential_play/gf_play_factory.h"
#include "gf/gf_allocator.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/object/gf_menu_obj_target_info.h"
#include "gf/object/component/gf_com_collider.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_elevator.h"
#include "gmk/gmk_jump.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_map_obj.h"
#include "gmk/gmk_route_navi.h"
#include "gmk/gmk_salvage.h"
#include "gmk/gmk_warp.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_list.h"
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
  case MSG_UNKNOWN_16777224:
    procMsgPcGetLookPoint(sender, static_cast<MsgPcGetLookPoint &>(message));
    return true;
  case MSG_UNKNOWN_16777228:
    procMsgPcFieldGetAccessType(sender, static_cast<MsgPcFieldGetAccessType &>(message));
    return true;
  case MSG_UNKNOWN_16777229:
    procMsgPcFieldNotifyAction(sender, static_cast<MsgPcFieldNotifyAction &>(message));
    return true;
  case MSG_PC_UNKNOWN_16777245:
    procMsgPcFieldNotifySkillEvent(sender, static_cast<MsgPcFieldNotifySkillEvent &>(message));
    return true;
  case MSG_PC_UNKNOWN_16777254:
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
    acc.testFlag(OBJ_FLAG_UNKNOWN_14);
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

void GfComBehaviorGmk::procMsgPcGetElvLift(fw::MessageObject *sender, MsgPcGetElvLift &message) {
  message.unknown08.clear();
  gmk::AGmkBase *gmk = gmk::getBindedGmkInst(static_cast<GfObj *>(unknown08)->unknownf8);
  if (gmk != nullptr && gmk->getGmkType() == gmk::GMK_TYPE_ELEVATOR) {
    gmk::GmkElevator *elevator = static_cast<gmk::GmkElevator *>(gmk);
    u16 liftLod = elevator->getBdatInfo()->unknown06;
    const GfFieldLod::BdatInfo *lodInfo = GfFieldLod::get()->findBdatInfo(liftLod);
    if (lodInfo != nullptr) {
      u16 lodId = lodInfo->unknown00;
      for (GF_OBJ_HANDLE *const &handle : *GfGameObj::getList(OBJECT_TYPE_MAP_LOD)) {
        GfObjSetupMapLodAnim *setup = mm::mtl::dynamicCast<GfObjSetupMapLodAnim>(GfObjManager::getObjInfo(handle)->unknown30);
        if (setup->unknown6c == lodId) {
          if (message.unknown08.size() == message.unknown08.capacity()) {
            // Ruling 5 (P3): the game (0x710052a4a0) calls GfFieldLod::findBdatInfo again with the lift lod id when the
            // list of riding objects is full and drops the result; the original expression cannot be checked.
            GfFieldLod::get()->findBdatInfo(liftLod);
          } else {
            // Ruling 1/2 (P2): the game loads the handle (0x710052a5c0) before the size assertion of push_back.
            GF_OBJ_HANDLE *rider = handle;
            message.unknown08.push_back(rider);
          }
        }
      }
    }
    message.unknown90 = elevator->isLiftSwitch(static_cast<GfObj *>(unknown08)->unknownf8);
  }
}

void GfComBehaviorGmk::setup() {
  unknownc0 = unknown08->getComponent<GfComTransform>()->unknown001();
  createMenuObj();
  gmk::AGmkBase *gmk = gmk::getBindedGmkInst(static_cast<GfObj *>(unknown08)->unknownf8);
  if (gmk != nullptr) {
    gmk::GmkType type = gmk->getGmkType();
    if (type == gmk::GMK_TYPE_MAP_OBJ || type == gmk::GMK_TYPE_ROUTED_MAP_OBJ) {
      u8 *bdat = GfDataBdat::getFP(BDAT_RSC_MAP_OBJ_LIST);
      GfObjSetupGimmick *setup = mm::mtl::dynamicCast<GfObjSetupGimmick>(GfObjManager::getObjInfo(static_cast<GfObj *>(unknown08)->unknownf8)->unknown30);
      int id = 0;
      if (setup->unknown08 == OBJECT_TYPE_MOB) {
        id = setup->unknown10;
      } else if (setup->unknown08 == OBJECT_TYPE_GIMMICK) {
        id = setup->unknown10;
      }
      if (Bdat::getFlagVal(bdat, "flag", id, "BigObj") != 0) {
        GfBigObjUnique::CreateInfo bigObjInfo;
        bigObjInfo.unknown00 = static_cast<GfObj *>(unknown08)->unknownf8;
        unknownb0.create(bigObjInfo);
      }
    }
  }
  {
    // The game calls the GfObjAcc constructor here (0x710052a920) and its stack slot is reused by the later locals, so its lifetime ends here.
    GfObjAcc acc(static_cast<GfObj *>(unknown08));
  }
  gmk::AGmkBase *routeGmk = gmk::getBindedGmkInst(static_cast<GfObj *>(unknown08)->unknownf8);
  if (routeGmk != nullptr && routeGmk->getGmkType() == gmk::GMK_TYPE_ROUTED_MAP_OBJ) {
    gmk::GmkRouteNavi::CreateInfo naviInfo(static_cast<gmk::GmkRoutedMapObj *>(routeGmk));
    naviInfo.unknown10 = 0.5f;
    naviInfo.unknown14 = 1.0f;
#line 131
    unknowna0 = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) gmk::GmkRouteNavi(&naviInfo);
    GfComCollider *collider = unknown08->getComponent<GfComCollider>();
    fw::unknown133 shape(mm::Vec3(5.5f, 0.1f, 5.5f));
    shape.unknown10.unknown10 = false;
    fw::ColiCharacterInfo coliInfo;
    coliInfo.unknown80 = &shape;
    coliInfo.unknown04 = fw::COLI_TYPE_UNKNOWN_1;
    coliInfo.unknown0c = 2;
    coliInfo.unknown08 = 1000;
    collider->createColiMoveCharacter(0, coliInfo, mm::mtl::IntrusivePtr<fw::ReferenceFrame>());
    // The game reads the first collision through the const operator[] of the vector (0x710052aaa8: asserts at vector.h lines 345 and 346).
    const mm::mtl::Vector<fw::ColiObject *> &colis = collider->unknown18;
    unknown98 = colis[0];
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
    param.unknown50 = static_cast<u16>(Bdat::getValCheck(bdat, "SalvagePointName", id, gmk::BDAT_TYPE_UNKNOWN_2));
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
  param.unknown10.unknown00 = mm::Vec3::zero;
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

void GfComBehaviorGmk::update(const fw::UpdateInfo &info) {
  mm::Vec3 direction;
  if (unknowna0 == nullptr) {
    direction = mm::Vec3(0.0f, 0.0f, 0.0f);
  } else {
    fw::ReferenceFrame *frame = unknown08->getComponent<GfComTransform>()->unknown001().operator->();
    const mm::Vec3 &position = frame->getSyncedWorldTransform().unknown00;
    gmk::GmkRouteNavi::UpdateInfo naviInfo;
    naviInfo.position = position;
    unknowna0->update(naviInfo);
    direction = unknowna0->unknown90 - position;
    if (!direction.unknown003()) {
      direction.unknown001();
    }
    direction *= 2.0f;
  }
  if (unknown98 != nullptr) {
    unknown98->setDir(direction * info.unknown04);
    if (unknowna0 != nullptr) {
      // The game calls atan2f here and drops the result (errno keeps the call). It loads the owner (ldr x21, [x20, #8], 0x710052b148) before the
      // call (0x710052b154); without this local the load comes after it (167 instructions either way, one load out of place).
      fw::UpdatableObject *owner = unknown08;
      atan2f(direction.x, direction.z);
      owner->getComponent<GfComTransform>()->unknown001()->invalidateLocal();
    }
  }
  unknownb0.update(info.unknown04);
}

} // namespace gf
