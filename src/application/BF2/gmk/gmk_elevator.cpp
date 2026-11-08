#include "gmk/gmk_elevator.h"

#include "bdat.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_util.h"
#include "gf/data/gf_game_flag.h"
#include "gf/data/gf_object_type.h"
#include "gf/field/gf_field_lod.h"
#include "gf/field/gf_field_sound.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_obj.h"
#include "gf/game/quest/gf_quest_util.h"
#include "gf/game/sequential_play/gf_play_factory.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_factory.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "gf/request/gf_req_command.h"
#include "gf/scom/gf_scom_obj.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep
#include "gmk/gmk_set.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/rtti.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace gmk {

template bool TGmkList<GmkElevator, GmkElevator::BdatInfo, 1414941765u, 2u, GmkElevatorGobCustom>::initGmkBdatInfo(GmkElevator::BdatInfo &, int &, const AGmkBase &);
template bool TGmkList<GmkElevatorLocator, GmkElevatorLocator::BdatInfo, 1129073733u, 2u, GmkElevatorLocatorGob>::initGmkBdatInfo(GmkElevatorLocator::BdatInfo &, int &, const AGmkBase &);

void GmkElevator::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  unknown00 = bdat.getValCheck("OP_Condition", id, BDAT_TYPE_U16);
  unknown02 = bdat.getValCheck("callnameRadius", id, BDAT_TYPE_U16);
  unknown04 = bdat.getValCheck("liftnameRadius", id, BDAT_TYPE_U16);
  unknown06 = bdat.getValCheck("LIFTLOD", id, BDAT_TYPE_U16);
  unknown08 = bdat.getValCheck("shtALOD", id, BDAT_TYPE_U16);
  unknown0a = bdat.getValCheck("shtBLOD", id, BDAT_TYPE_U16);
  unknown0c = bdat.getValCheck("switchALOD", id, BDAT_TYPE_U16);
  unknown0e = bdat.getValCheck("switchBLOD", id, BDAT_TYPE_U16);
  unknown10 = bdat.getValCheck("switchSE", id, BDAT_TYPE_U16);
  unknown12 = bdat.getValCheck("shutterSE", id, BDAT_TYPE_U16);
  unknown14 = bdat.getValCheck("LiftStartSE", id, BDAT_TYPE_U16);
  unknown16 = bdat.getValCheck("LiftLoopSE", id, BDAT_TYPE_U16);
  unknown18 = bdat.getValCheck("LiftStopSE", id, BDAT_TYPE_U16);
  unknown1a = bdat.getValCheck("LiftMinVolDist", id, BDAT_TYPE_U8);
  unknown1b = bdat.getValCheck("LiftMaxVolDist", id, BDAT_TYPE_U8);
  unknown1c = Bdat::getFlagVal(bdat.unknown00, "flag", id, "lift_reverse") != 0;
  unknown20 = toBdatF32(bdat.getValCheck("call_liftspeed", id, BDAT_TYPE_F32));
  unknown24 = bdat.getValCheck("missMSG_ID", id, BDAT_TYPE_U16);
  unknown28 = static_cast<s16>(bdat.getValCheck("elevator_nextwait", id, BDAT_TYPE_S16));
  unknown2c = bdat.getValCheck("liftAMapJumpId", id, BDAT_TYPE_U16);
  unknown2e = bdat.getValCheck("liftBMapJumpId", id, BDAT_TYPE_U16);
}

GmkType GmkElevatorLocator::getGmkType() const { return GMK_TYPE; }

bool GmkElevatorLocator::isValid() const { return unknown08.unknown00 != nullptr && unknown20.unknown08 != nullptr; }

GmkElevator::GmkElevator() : unknown4b0(gf::INVALID_HANDLE), unknown4b8(nullptr), unknown4c8(false), unknown4c9(false), unknown4ca(false), unknown4cb(false), unknown4cc(0.0f) {
  for (u32 i = 0; i < 4; i++) {
    unknown290[i] = gf::INVALID_HANDLE;
  }
}

GmkType GmkElevator::getGmkType() const { return GMK_TYPE; }

int GmkElevator::getGameFlagId() const { return unknown20.unknown18 + 0xb248; }

void GmkElevator::create(const CreateInfo &info) {
  AGmkBase::create(info);
  if (isValid() && static_cast<s16>(getData()->unknown02 - getData()->unknown00) == 3) {
    unknown4cc = getBdatInfo()->unknown28;
    unknown4b8 = canCreateGameEntity() ? &GmkElevator::seqWaitToValidate_GfFieldLod : &GmkElevator::seqInit;
  } else {
    dispose();
  }
}

void GmkElevator::seqWaitToValidate_GfFieldLod(f32 deltaTime) {
  gf::GfFieldLod *lod = gf::GfFieldLod::get();
  if (lod == nullptr || !lod->unknown80c || lod->unknown840.unknown00.unknown00 == nullptr || lod->unknown840.unknown00.unknown10 == nullptr) {
    return;
  }
  const BdatInfo *info = getBdatInfo();
  const gf::GfFieldLod::BdatInfo *lodInfo = lod->findBdatInfo(info->unknown06);
  if (lodInfo != nullptr) {
    u16 lodId = lodInfo->unknown00;
    for (gf::GF_OBJ_HANDLE *const &handle : *gf::GfGameObj::getList(gf::OBJECT_TYPE_UNKNOWN_2)) {
      gf::GfObjSetupMapLodAnim *setup = mm::mtl::dynamicCast<gf::GfObjSetupMapLodAnim>(gf::GfObjManager::getObjInfo(handle)->unknown30);
      if (setup->unknown6c == lodId) {
        unknown4b0 = handle;
      }
    }
  }
  bool isDown = isLiftStateDown();
  gf::GfFieldLod::get()->setAnimReverse(info->unknown06, isDown, true);
  gf::GfFieldLod::get()->setPlaySpeed(info->unknown06, 1.0f);
  if (info->unknown08 != 0) {
    gf::GfFieldLod::get()->setAnimReverse(info->unknown08, !isDown, true);
  }
  if (info->unknown0a != 0) {
    gf::GfFieldLod::get()->setAnimReverse(info->unknown0a, isDown, true);
  }
  unknown4b8 = &GmkElevator::seqInit;
}

void GmkElevator::seqInit(f32 deltaTime) {
  if (!unknown08.unknown00->getCreateInfo().unknown08->unknown1b8[GMK_TYPE_ELEVATOR_LOCATOR]->isValid()) {
    return;
  }
  if (canCreateGameEntity()) {
    for (int i = 0; i < 4; i++) {
      const AGmkBase *gmk = getGmkBaseByItemType(static_cast<ItemType>(i));
      switch (gmk->unknown08.unknown10->unknown0c) {
      case SHAPE_TYPE_SPHERE:
      case SHAPE_TYPE_BOX:
      case SHAPE_TYPE_CAPSULE:
        unknown50[i].create(*gmk, this, false);
        break;
      default: {
        gf::GF_OBJ_HANDLE *handle = gf::GfObjFactory::createGmkEvent(CBdatWrapper{getBindedBdatFp()}, unknown20.unknown18);
        bindToGameObj(handle);
        unknown003(gf::GfObjUtil::getObjSetup<gf::GfObjSetupGimmick>(handle), gmk->unknown08.unknown08);
        unknown002(handle, true);
        unknown290[i] = handle;
        break;
      }
      }
    }
  }
  if (isLiftStateDown()) {
    initDownFloorState();
  } else {
    initUpFloorState();
  }
}

void GmkElevator::onLeavePhantom(const IGmkPhantomEventListener::OnLeaveInfo &info) {}

void GmkElevator::clearRequests() {
  unknown4c8 = false;
  unknown4c9 = false;
  unknown4ca = false;
  unknown4cb = false;
}

bool GmkElevator::isCallSwitch(gf::GF_OBJ_HANDLE *handle) const {
  for (int i = 0; i < 4; i++) {
    if (unknown290[i] == handle) {
      return i % 2 == 0;
    }
  }
  return false;
}

bool GmkElevator::isLiftSwitch(gf::GF_OBJ_HANDLE *handle) const {
  for (int i = 0; i < 4; i++) {
    if (unknown290[i] == handle) {
      return i % 2 == 1;
    }
  }
  return false;
}

bool GmkElevator::isElevatorMoveOK() const {
  if (!isValid()) {
    return false;
  }
  return gf::GfGameManager::isElevatorMoveOK(getBdatInfo()->unknown06);
}

bool GmkElevator::isGmkFinished() const {
  if (unknown4cc < getBdatInfo()->unknown28) {
    return false;
  }
  return gf::GfGameFlag::getLocal(1, getGameFlagId()) != 0;
}

const GmkElevatorLocator *GmkElevator::getBindedGmkElevatorLocator(u32 index) const {
  const IGmkList *list = unknown08.unknown00->getCreateInfo().unknown08->unknown1b8[GMK_TYPE_ELEVATOR_LOCATOR];
  if (!list->isValid()) {
    return nullptr;
  }
  const Data *data = getData();
  return static_cast<const GmkElevatorLocator *>(list->getInst(data->unknown00 + index));
}

const AGmkBase *GmkElevator::getGmkBaseByItemType(ItemType type) const {
  switch (type) {
  case ITEM_TYPE_UNKNOWN_0:
    return this;
  case ITEM_TYPE_UNKNOWN_1:
    return getBindedGmkElevatorLocator(0);
  case ITEM_TYPE_UNKNOWN_2:
    return getBindedGmkElevatorLocator(1);
  case ITEM_TYPE_UNKNOWN_3:
    return getBindedGmkElevatorLocator(2);
  }
  return nullptr;
}

bool GmkElevator::getLiftPos(mm::Vec3 &position) const {
  gf::GfFieldLod *lod = gf::GfFieldLod::get();
  if (lod == nullptr) {
    return false;
  }
  mm::Mat44 matrix;
  if (!lod->unknown80c || !lod->findTransform(matrix, getBdatInfo()->unknown06)) {
    return false;
  }
  position = matrix.unknown004();
  return true;
}

bool GmkElevator::getDownShutterPos(mm::Vec3 &position) const {
  gf::GfFieldLod *lod = gf::GfFieldLod::get();
  if (lod == nullptr) {
    return false;
  }
  mm::Mat44 matrix;
  if (!lod->unknown80c || !lod->findTransform(matrix, getBdatInfo()->unknown08)) {
    return false;
  }
  position = matrix.unknown004();
  return true;
}

bool GmkElevator::getUpShutterPos(mm::Vec3 &position) const {
  gf::GfFieldLod *lod = gf::GfFieldLod::get();
  if (lod == nullptr) {
    return false;
  }
  mm::Mat44 matrix;
  if (!lod->unknown80c || !lod->findTransform(matrix, getBdatInfo()->unknown0a)) {
    return false;
  }
  position = matrix.unknown004();
  return true;
}

const Xform *GmkElevator::getDownLiftSwitchPos() const {
  const IGmkList *list = unknown08.unknown00->getCreateInfo().unknown08->unknown1b8[GMK_TYPE_ELEVATOR_LOCATOR];
  list->isValid();
  const Data *data = getData();
  return list->getInst(data->unknown00)->unknown08.unknown08;
}

const Xform *GmkElevator::getUpLiftSwitchPos() const {
  const IGmkList *list = unknown08.unknown00->getCreateInfo().unknown08->unknown1b8[GMK_TYPE_ELEVATOR_LOCATOR];
  list->isValid();
  const Data *data = getData();
  return list->getInst(data->unknown00 + 2)->unknown08.unknown08;
}

bool GmkElevator::getPosForCompass(mm::Vec3 &position) const {
  const BdatInfo *info = getBdatInfo();
  if (info->unknown2c != 0) {
    if (&GmkElevator::seqDownIdle == unknown4b8) {
      const GmkElevatorLocator *locator = getBindedGmkElevatorLocator(1);
      if (locator == nullptr) {
        return false;
      }
      position = locator->unknown08.unknown08->unknown00;
      return true;
    }
    if (&GmkElevator::seqUpIdle == unknown4b8) {
      const GmkElevatorLocator *locator = getBindedGmkElevatorLocator(2);
      if (locator == nullptr) {
        return false;
      }
      position = locator->unknown08.unknown08->unknown00;
      return true;
    }
    if (&GmkElevator::seqWaitToArriveDownFloor == unknown4b8) {
      position = getDownLiftSwitchPos()->unknown00;
      return true;
    }
    return false;
  }
  if (info->unknown2e != 0) {
    if (&GmkElevator::seqUpIdle == unknown4b8) {
      position = unknown08.unknown08->unknown00;
      return true;
    }
    if (&GmkElevator::seqDownIdle == unknown4b8) {
      const GmkElevatorLocator *locator = getBindedGmkElevatorLocator(0);
      if (locator == nullptr) {
        return false;
      }
      position = locator->unknown08.unknown08->unknown00;
      return true;
    }
    if (&GmkElevator::seqWaitToArriveUpFloor == unknown4b8) {
      position = getUpLiftSwitchPos()->unknown00;
      return true;
    }
    return false;
  }
  if (info->unknown1c) {
    position = getUpLiftSwitchPos()->unknown00;
  } else {
    position = getDownLiftSwitchPos()->unknown00;
  }
  return true;
}

void GmkElevator::clearSe() {
  unknown2b0[0].dispose();
  unknown2b0[1].dispose();
  unknown2b0[2].dispose();
  unknown2b0[3].dispose();
}

void GmkElevator::disposeSe(SeType type) { unknown2b0[type].dispose(); }

void GmkElevator::createSe(SeType type, const mm::Vec3 &position) {
  disposeSe(type);
  const BdatInfo *bdatInfo = getBdatInfo();
  GmkCtrlVolSe::CreateInfo info;
  info.unknown00 = gf::GfFieldSound::get()->getCommonPack();
  switch (type) {
  case SE_TYPE_UNKNOWN_0:
    info.unknown08 = bdatInfo->unknown10;
    break;
  case SE_TYPE_UNKNOWN_1:
    info.unknown08 = bdatInfo->unknown12;
    break;
  case SE_TYPE_UNKNOWN_2:
    info.unknown08 = bdatInfo->unknown14;
    break;
  case SE_TYPE_UNKNOWN_3:
    info.unknown08 = bdatInfo->unknown16;
    info.unknown10 = bdatInfo->unknown1a;
    info.unknown14 = bdatInfo->unknown1b;
    info.unknown30 = unknown4b0;
    break;
  }
  info.unknown20 = position;
  if (info.unknown00 == nullptr || info.unknown08 == 0) {
    return;
  }
  unknown2b0[type].create(info);
}

void GmkElevator::startLiftSe() {
  mm::Vec3 position;
  if (getLiftPos(position)) {
    createSe(SE_TYPE_UNKNOWN_2, position);
    createSe(SE_TYPE_UNKNOWN_3, position);
  }
}

void GmkElevator::stopLiftSe() {
  mm::Vec3 position;
  if (getLiftPos(position)) {
    createSe(SE_TYPE_UNKNOWN_2, position);
  }
  disposeSe(SE_TYPE_UNKNOWN_3);
}

void GmkElevator::sendGfComQuest() const {
  u32 gimmick = unknown20.unknown18;
  f32 delay = 0.0f;
  if (gf::GfQuestUtil::getGimmickTaskEndCheck(GMK_TYPE, gimmick) == 1) {
    delay = getBdatInfo()->unknown28;
  }
  gf::SCOM_QUEST_GIMMICK::createElevator(gimmick, delay);
}

bool GmkElevator::isPlayEnd(u16 lodId) {
  gf::GfFieldLod *lod = gf::GfFieldLod::get();
  if (lod->unknown840.unknown00.unknown00 != nullptr && lod->unknown840.unknown00.unknown10 != nullptr) {
    return lod->isPlayAnimEnd(lodId);
  }
  return false;
}

void GmkElevator::setTargetableByItemType(ItemType type, bool isTargetable) {
  if (unknown290[type] == gf::INVALID_HANDLE) {
    return;
  }
  if (canCreateGameEntity()) {
    u32 switchId = 2;
    if (getBdatInfo()->unknown00 == 0 || gf::GfGameCond::isGameCond(getBdatInfo()->unknown00)) {
      switchId = isTargetable ? 1 : 2;
    }
    const BdatInfo *info = getBdatInfo();
    if (type == ITEM_TYPE_UNKNOWN_0) {
      if (info->unknown0c != 0) {
        gf::GfFieldLod::get()->setLodSwitchId(info->unknown0c, switchId);
      }
    } else if (type == ITEM_TYPE_UNKNOWN_2) {
      if (info->unknown0e != 0) {
        gf::GfFieldLod::get()->setLodSwitchId(info->unknown0e, switchId);
      }
    }
  }
  unknown002(unknown290[type], isTargetable);
}

void GmkElevator::setUntargetableOfAllItem() {
  setTargetableByItemType(ITEM_TYPE_UNKNOWN_0, false);
  setTargetableByItemType(ITEM_TYPE_UNKNOWN_1, false);
  setTargetableByItemType(ITEM_TYPE_UNKNOWN_2, false);
  setTargetableByItemType(ITEM_TYPE_UNKNOWN_3, false);
}

void GmkElevator::initDownFloorState() {
  setTargetableByItemType(ITEM_TYPE_UNKNOWN_0, false);
  setTargetableByItemType(ITEM_TYPE_UNKNOWN_1, true);
  setTargetableByItemType(ITEM_TYPE_UNKNOWN_2, true);
  setTargetableByItemType(ITEM_TYPE_UNKNOWN_3, false);
  clearRequests();
  unknown4b8 = &GmkElevator::seqDownIdle;
}

void GmkElevator::initUpFloorState() {
  setTargetableByItemType(ITEM_TYPE_UNKNOWN_0, true);
  setTargetableByItemType(ITEM_TYPE_UNKNOWN_1, false);
  setTargetableByItemType(ITEM_TYPE_UNKNOWN_2, false);
  setTargetableByItemType(ITEM_TYPE_UNKNOWN_3, true);
  clearRequests();
  unknown4b8 = &GmkElevator::seqUpIdle;
}

void GmkElevator::seqDownIdle(f32 deltaTime) {
  if (!unknown4c9 && !(unknown4cb && isElevatorMoveOK())) {
    return;
  }
  const BdatInfo *info = getBdatInfo();
  if (unknown4c9) {
    gf::GfFieldLod::get()->setPlaySpeed(info->unknown06, info->unknown20);
    unknown4c9 = false;
  }
  if (unknown4cb) {
    unknown4cb = false;
  }
  setUntargetableOfAllItem();
  if (info->unknown08 != 0) {
    gf::GfFieldLod::get()->setAnimReverse(info->unknown08, true, false);
    mm::Vec3 position;
    if (getDownShutterPos(position)) {
      createSe(SE_TYPE_UNKNOWN_1, position);
    }
    unknown4b8 = &GmkElevator::seqWaitToCloseDownShutter;
  } else {
    gf::GfFieldLod::get()->setAnimReverse(info->unknown06, false, false);
    unknown4b8 = &GmkElevator::seqWaitToArriveUpFloor;
    startLiftSe();
  }
}

void GmkElevator::seqUpIdle(f32 deltaTime) {
  if (!unknown4c8 && !(unknown4ca && isElevatorMoveOK())) {
    return;
  }
  const BdatInfo *info = getBdatInfo();
  if (unknown4c8) {
    gf::GfFieldLod::get()->setPlaySpeed(info->unknown06, info->unknown20);
    unknown4c8 = false;
  }
  if (unknown4ca) {
    unknown4ca = false;
  }
  setUntargetableOfAllItem();
  if (info->unknown0a != 0) {
    gf::GfFieldLod::get()->setAnimReverse(info->unknown0a, true, false);
    mm::Vec3 position;
    if (getUpShutterPos(position)) {
      createSe(SE_TYPE_UNKNOWN_1, position);
    }
    unknown4b8 = &GmkElevator::seqWaitToCloseUpShutter;
  } else {
    gf::GfFieldLod::get()->setAnimReverse(info->unknown06, true, false);
    unknown4b8 = &GmkElevator::seqWaitToArriveDownFloor;
    startLiftSe();
  }
}

void GmkElevator::seqWaitToArriveDownFloor(f32 deltaTime) {
  if (gf::GfFieldLod::get()->unknown840.unknown00.unknown00 != nullptr && gf::GfFieldLod::get()->unknown840.unknown00.unknown10 != nullptr) {
    const BdatInfo *info = getBdatInfo();
    if (gf::GfFieldLod::get()->isPlayAnimEnd(info->unknown06)) {
      stopLiftSe();
      gf::GfFieldLod::get()->setPlaySpeed(info->unknown06, 1.0f);
      if (info->unknown08 != 0) {
        gf::GfFieldLod::get()->setAnimReverse(info->unknown08, false, false);
        mm::Vec3 position;
        if (getDownShutterPos(position)) {
          createSe(SE_TYPE_UNKNOWN_1, position);
        }
      }
      initDownFloorState();
      if (info->unknown2e == 0) {
        sendGfComQuest();
      }
    }
  }
}

void GmkElevator::seqWaitToArriveUpFloor(f32 deltaTime) {
  if (gf::GfFieldLod::get()->unknown840.unknown00.unknown00 != nullptr && gf::GfFieldLod::get()->unknown840.unknown00.unknown10 != nullptr) {
    const BdatInfo *info = getBdatInfo();
    if (gf::GfFieldLod::get()->isPlayAnimEnd(info->unknown06)) {
      stopLiftSe();
      gf::GfFieldLod::get()->setPlaySpeed(info->unknown06, 1.0f);
      if (info->unknown0a != 0) {
        gf::GfFieldLod::get()->setAnimReverse(info->unknown0a, false, false);
        mm::Vec3 position;
        if (getUpShutterPos(position)) {
          createSe(SE_TYPE_UNKNOWN_1, position);
        }
      }
      initUpFloorState();
      // The game tests the lift b map jump id here too, like seqWaitToArriveDownFloor.
      if (info->unknown2e == 0) {
        sendGfComQuest();
      }
    }
  }
}

void GmkElevator::seqWaitToCloseDownShutter(f32 deltaTime) {
  if (gf::GfFieldLod::get()->unknown840.unknown00.unknown00 != nullptr && gf::GfFieldLod::get()->unknown840.unknown00.unknown10 != nullptr) {
    const BdatInfo *info = getBdatInfo();
    if (gf::GfFieldLod::get()->isPlayAnimEnd(info->unknown08)) {
      gf::GfFieldLod::get()->setAnimReverse(info->unknown06, false, false);
      unknown4b8 = &GmkElevator::seqWaitToArriveUpFloor;
      startLiftSe();
    }
  }
}

void GmkElevator::seqWaitToCloseUpShutter(f32 deltaTime) {
  if (gf::GfFieldLod::get()->unknown840.unknown00.unknown00 != nullptr && gf::GfFieldLod::get()->unknown840.unknown00.unknown10 != nullptr) {
    const BdatInfo *info = getBdatInfo();
    if (gf::GfFieldLod::get()->isPlayAnimEnd(info->unknown0a)) {
      gf::GfFieldLod::get()->setAnimReverse(info->unknown06, true, false);
      unknown4b8 = &GmkElevator::seqWaitToArriveDownFloor;
      startLiftSe();
    }
  }
}

void GmkElevator::clearGobInsts() {
  for (int i = 0; i < 4; i++) {
    if (unknown290[i] != gf::INVALID_HANDLE) {
      gf::GfObjAcc acc(unknown290[i]);
      if (acc.isValid()) {
        acc.setUserData(gf::OBJ_USER_DATA_GMK, 0);
      }
      gf::GfObjUtil::destroy(unknown290[i]);
      unknown290[i] = gf::INVALID_HANDLE;
    }
  }
}

void GmkElevator::dispose() {
  clearRequests();
  unknown4b0 = gf::INVALID_HANDLE;
  unknown4b8 = nullptr;
  clearGobInsts();
  clearSe();
  bool isGmkValid = isValid();
  gf::GfFieldLod *lod = gf::GfFieldLod::get();
  if (lod != nullptr && isGmkValid && !isMapJumpingWithSaveData()) {
    const BdatInfo *info = getBdatInfo();
    if (info->unknown2c != 0) {
      lod->setAnimReverse(info->unknown06, true, true);
    } else if (info->unknown2e != 0) {
      lod->setAnimReverse(info->unknown06, false, true);
    }
  }
  AGmkBase::dispose();
}

void GmkElevator::update(f32 deltaTime) {
  debugUpdateMmf();
  if (!isValid()) {
    return;
  }
  if (unknown4b8) {
    (this->*unknown4b8)(deltaTime);
  }
}

bool GmkElevator::isLiftStateDown() const {
  const u16 unknown001 = 8030; // Inferred role: scenario flag checked for the elevator ma18a_elv_01; original name unknown.
  const BdatInfo *info = getBdatInfo();
  bool isDown;
  if (isMapJumpingWithSaveData()) {
    isDown = gf::GfFieldLod::get()->isAnimReverse(info->unknown06);
  } else {
    isDown = info->unknown1c == 0;
  }
  if (gf::GfDataUtil::getScenarioFlag() == unknown001) {
    const char *name = unknown08.unknown10->unknown00;
    if (name != nullptr) {
      isDown |= __builtin_strcmp("ma18a_elv_01", name) == 0;
    }
  }
  return isDown;
}

void GmkElevator::onPlayerAccessed(gf::GF_OBJ_HANDLE *handle) {
  const BdatInfo *info = getBdatInfo();
  if (info->unknown00 != 0 && !gf::GfGameCond::isGameCond(info->unknown00)) {
    reqDrawCmnMsg(info->unknown24);
    return;
  }
  ItemType type;
  if (unknown290[ITEM_TYPE_UNKNOWN_0] == handle) {
    type = ITEM_TYPE_UNKNOWN_0;
    unknown4c8 = true;
  } else if (unknown290[ITEM_TYPE_UNKNOWN_1] == handle) {
    type = ITEM_TYPE_UNKNOWN_1;
    unknown4cb = true;
  } else if (unknown290[ITEM_TYPE_UNKNOWN_2] == handle) {
    type = ITEM_TYPE_UNKNOWN_2;
    unknown4c9 = true;
  } else if (unknown290[ITEM_TYPE_UNKNOWN_3] == handle) {
    type = ITEM_TYPE_UNKNOWN_3;
    unknown4ca = true;
  } else {
    return;
  }
  const AGmkBase *gmk = getGmkBaseByItemType(type);
  if (gmk != nullptr) {
    createSe(SE_TYPE_UNKNOWN_0, gmk->unknown08.unknown08->unknown00);
  }
}

void GmkElevator::onEnterPhantom(const IGmkPhantomEventListener::OnEnterInfo &info) {
  const BdatInfo *bdatInfo = getBdatInfo();
  if (bdatInfo->unknown00 != 0 && !gf::GfGameCond::isGameCond(bdatInfo->unknown00)) {
    reqDrawCmnMsg(bdatInfo->unknown24);
    return;
  }
  if (&unknown50[ITEM_TYPE_UNKNOWN_0] == info.phantom) {
    unknown4c8 = true;
  } else if (&unknown50[ITEM_TYPE_UNKNOWN_1] == info.phantom) {
    if (bdatInfo->unknown2c != 0 && &GmkElevator::seqWaitToArriveDownFloor == unknown4b8) {
      sendGfComQuest();
      gf::GfMapjumpInfo mapjumpInfo(bdatInfo->unknown2c);
      gf::GfPlayFactory::createMapjump(mapjumpInfo);
    } else {
      unknown4cb = true;
    }
  } else if (&unknown50[ITEM_TYPE_UNKNOWN_2] == info.phantom) {
    unknown4c9 = true;
  } else if (&unknown50[ITEM_TYPE_UNKNOWN_3] == info.phantom) {
    if (bdatInfo->unknown2e != 0 && &GmkElevator::seqWaitToArriveUpFloor == unknown4b8) {
      sendGfComQuest();
      gf::GfMapjumpInfo mapjumpInfo(bdatInfo->unknown2e);
      gf::GfPlayFactory::createMapjump(mapjumpInfo);
    } else {
      unknown4ca = true;
    }
  }
}

} // namespace gmk

template void mm::mtl::Vector<gmk::GmkElevator::BdatInfo>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkElevatorLocator::BdatInfo>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkElevatorLocator::BdatInfo>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkElevatorLocator::BdatInfo>::resize(size_t);
template void mm::mtl::Vector<gmk::GmkElevatorLocator>::expand(size_t, size_t);

template void mm::mtl::Vector<gmk::GmkElevator::BdatInfo>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkElevator::BdatInfo>::resize(size_t);
template void mm::mtl::Vector<gmk::GmkElevatorLocator>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkElevatorLocator>::resize(size_t);
template void mm::mtl::Vector<gmk::GmkElevator>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkElevator>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkElevator>::resize(size_t);
