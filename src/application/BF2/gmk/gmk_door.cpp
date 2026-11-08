#include "gmk/gmk_door.h"

#include "bdat.h"
#include "framework/sound/sound_manager.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_game_flag.h"
#include "gf/data/gf_object_type.h"
#include "gf/field/gf_field_lod.h"
#include "gf/field/gf_field_sound.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/quest/gf_quest_util.h"
#include "gf/gf_allocator.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_factory.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "gf/scom/gf_scom_obj.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep
#include "gmk/gmk_phantom.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/rtti.h"
#include "scn/scn_obj_acc.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace fw {
class SoundPack;
} // namespace fw

namespace gmk {

template bool TGmkList<GmkDoor, GmkDoor::BdatInfo, 1380929348u, 2u, GmkDoorGob>::initGmkBdatInfo(GmkDoor::BdatInfo &, int &, const AGmkBase &);

bool GmkDoor::BdatInfo::isGfObjMustExist() const {
  if (unknown06 == 0) {
    return false;
  }
  switch (unknown02) {
  case 1:
  case 2:
  case 5:
  case 6:
    return true;
  }
  return false;
}

void GmkDoor::setLodSwitch(LodSwitch lodSwitch) {
  if (!canCreateGameEntity()) {
    return;
  }
  u32 switchId;
  switch (lodSwitch) {
  case LOD_SWITCH_UNKNOWN_0:
    switchId = 2;
    break;
  case LOD_SWITCH_UNKNOWN_1:
    switchId = 2;
    break;
  case LOD_SWITCH_UNKNOWN_2:
    switchId = 1;
    break;
  default:
    switchId = 0;
    break;
  }
  gf::GfFieldLod *lod = gf::GfFieldLod::get();
  if (lod->unknown840.unknown00.unknown00 == nullptr || lod->unknown840.unknown00.unknown10 == nullptr) {
    return;
  }
  u16 lodId = lod->unknown08[getBdatInfo()->unknown06 - lod->unknown808];
  ml::ScnObjAccSeamPos seamPos(lod->unknown840.unknown00.unknown00);
  int num = seamPos.getMax();
  for (int i = 0; i < num; i++) {
    ml::ScnObjAccPartsPos partsPos = seamPos.getObj(i);
    if (lodId == partsPos.getID()) {
      partsPos.setSwitchID(switchId);
    }
  }
}

bool GmkDoor::BdatInfo::isLoadSaveData() const {
  if (isMapJumpingWithSaveData()) {
    return true;
  }
  if (unknown06 == 0) {
    return false;
  }
  switch (unknown02) {
  case 2:
  case 4:
  case 5:
    return true;
  }
  return false;
}

bool GmkDoor::BdatInfo::isPhantomMustExist() const {
  if (unknown06 == 0) {
    return false;
  }
  switch (unknown02) {
  case 3:
  case 4:
  case 6:
  case 7:
    return true;
  }
  return false;
}

bool GmkDoor::BdatInfo::isPopCondMatched() const {
  if (unknown00 != 0 && !gf::GfGameCond::isGameCond(unknown00)) {
    return false;
  }
  if (unknown3a.isEnable() && !unknown3a.isMatch()) {
    return false;
  }
  return true;
}

void GmkDoor::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  unknown00 = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
  unknown3a = BootedGmkCond(bdat, id, nullptr);
  unknown3e = BootedGmkCond(bdat, id, "OP_");
  unknown02 = bdat.getValCheck("response_type", id, BDAT_TYPE_U8);
  unknown03 = bdat.getValCheck("response_CHR", id, BDAT_TYPE_U8);
  unknown04 = bdat.getValCheck("nameRadius", id, BDAT_TYPE_U16);
  unknown06 = bdat.getValCheck("LODmodel", id, BDAT_TYPE_U16);
  unknown08 = bdat.getValCheck("missMSG_ID", id, BDAT_TYPE_U16);
  unknown0a = Bdat::getFlagVal(bdat.unknown00, "flag", id, "open_LODanime") != 0;
  unknown0b = Bdat::getFlagVal(bdat.unknown00, "flag", id, "open_SE_type") != 0;
  unknown0c = bdat.getValCheck("open_SE", id, BDAT_TYPE_U16);
  unknown0e = bdat.getValCheck("open_SE_size", id, BDAT_TYPE_U8);
  unknown10 = reinterpret_cast<const char *>(bdat.getValCheck("open_camGim_ID", id, BDAT_TYPE_STRING));
  unknown18 = bdat.getValCheck("open_camGim_ATR", id, BDAT_TYPE_U8);
  unknown19 = Bdat::getFlagVal(bdat.unknown00, "flag", id, "close_LODanime") != 0;
  unknown1a = Bdat::getFlagVal(bdat.unknown00, "flag", id, "close_SE_type") != 0;
  unknown1c = bdat.getValCheck("close_SE", id, BDAT_TYPE_U16);
  unknown1e = bdat.getValCheck("close_SE_size", id, BDAT_TYPE_U8);
  unknown20 = reinterpret_cast<const char *>(bdat.getValCheck("close_camGim_ID", id, BDAT_TYPE_STRING));
  unknown28 = bdat.getValCheck("close_camGim_ATR", id, BDAT_TYPE_U8);
  unknown2c = toBdatF32(bdat.getValCheck("door_nextwait", id, BDAT_TYPE_F32));
  unknown30 = reinterpret_cast<const char *>(bdat.getValCheck("sp_close_camGim_ID", id, BDAT_TYPE_STRING));
  unknown38 = bdat.getValCheck("sp_close_camGim_ATR", id, BDAT_TYPE_U8);
  unknown42 = BootedGmkCond(bdat, id, "SPOP_");
  unknown39 = Bdat::getFlagVal(bdat.unknown00, "flag", id, "gmkCamPos") != 0;
}

u32 GmkDoorPhantomTargetInfo::getTargetType() const {
  if (unknown00 == gf::INVALID_HANDLE) {
    return 0;
  }
  gf::GfObjAcc acc(unknown00);
  switch (acc.getType()) {
  case gf::OBJECT_TYPE_DRIVER:
  case gf::OBJECT_TYPE_BLADE:
    return 1;
  case gf::OBJECT_TYPE_ENEMY:
    return 2;
  default:
    return 0;
  }
}

GmkDoor::GmkDoor() : unknown60(nullptr), unknown2b0(false), unknown2b1(false), unknown2b8(gf::INVALID_HANDLE), unknown2c0(0.0f), unknown2c8(nullptr) {}

void GmkDoor::setProgress(Progress progress) {
  gf::GfGameFlag::setLocal(2, getGameFlagId(), progress);
  switch (progress) {
  case PROGRESS_UNKNOWN_0:
    unknown2c8 = &GmkDoor::seqDoor_BeforeBoot;
    break;
  case PROGRESS_UNKNOWN_1:
    unknown2c8 = &GmkDoor::seqDoor_Booted;
    break;
  case PROGRESS_UNKNOWN_2:
    unknown2c8 = &GmkDoor::seqDoor_Shutdowned;
    break;
  case PROGRESS_UNKNOWN_3:
    unknown2c8 = &GmkDoor::seqDoor_SpBooted;
    break;
  }
  validateLocSwitchState();
}

void GmkDoor::validateLocSwitchState() {
  LodSwitch lodSwitch = LOD_SWITCH_UNKNOWN_0;
  switch (getProgress()) {
  case PROGRESS_UNKNOWN_0:
  case PROGRESS_UNKNOWN_2:
    if (!isLocked()) {
      lodSwitch = LOD_SWITCH_UNKNOWN_2;
    }
    break;
  case PROGRESS_UNKNOWN_1:
    lodSwitch = isSpLocked() ? LOD_SWITCH_UNKNOWN_1 : LOD_SWITCH_UNKNOWN_2;
    break;
  case PROGRESS_UNKNOWN_3:
    lodSwitch = LOD_SWITCH_UNKNOWN_2;
    break;
  }
  setLodSwitch(lodSwitch);
}

void GmkDoor::create(const CreateInfo &info) {
  AGmkBase::create(info);
  if (!isValid()) {
    dispose();
    return;
  }
  const BdatInfo *bdatInfo = getBdatInfo();
  u32 progress = PROGRESS_UNKNOWN_0;
  if (bdatInfo->isLoadSaveData()) {
    progress = getProgress();
  }
  switch (progress) {
  case PROGRESS_UNKNOWN_0:
  case PROGRESS_UNKNOWN_2:
    if (gf::GfFieldLod::isAnimReverseOfInit(bdatInfo->unknown06)) {
      closeDoor(true);
    } else {
      openDoor(true);
    }
    setProgress(PROGRESS_UNKNOWN_0);
    break;
  case PROGRESS_UNKNOWN_1:
    bootGmk(true, false);
    setProgress(PROGRESS_UNKNOWN_1);
    break;
  case PROGRESS_UNKNOWN_3:
    spBootGmk(true, false);
    setProgress(PROGRESS_UNKNOWN_3);
    break;
  }
  validateLocSwitchState();
}

void GmkDoor::dispose() {
  disposeGmkPhantom();
  disposeGmkCamera();
  disposeGfObjHandle();
  unknown2e0.dispose();
  AGmkBase::dispose();
}

void GmkDoor::update(f32 deltaTime) {
  debugUpdateMmf();
  if (!isValid()) {
    return;
  }
  if (unknown2b1 != unknown2b0) {
    if (unknown2b1 && !unknown2b0 && (getBdatInfo()->unknown02 & 0xfe) == 6 && getProgress() != PROGRESS_UNKNOWN_2) {
      const BdatInfo *info = getBdatInfo();
      if (!info->unknown19) {
        openDoor(false);
      } else {
        closeDoor(false);
      }
      createGmkCamera(info->unknown20, info->unknown28, true);
      setProgress(PROGRESS_UNKNOWN_2);
    }
    unknown2b1 = unknown2b0;
  }
  const BdatInfo *info = getBdatInfo();
  unknown2b0 = false;
  if (info->isPopCondMatched()) {
    if (unknown2b8 == gf::INVALID_HANDLE && info->isGfObjMustExist()) {
      createGfObjHandle();
    }
    if (unknown1c0.unknown78 == nullptr && unknown250.unknown50 == nullptr && info->isPhantomMustExist()) {
      createGmkPhantom();
    }
  } else {
    disposeGfObjHandle();
    if (unknown1c0.unknown78 != nullptr || unknown250.unknown50 != nullptr) {
      disposeGmkPhantom();
    }
  }
  unknown60.update(deltaTime);
  if (unknown2c8) {
    (this->*unknown2c8)(deltaTime);
  }
}

bool GmkDoor::createGmkCamera(const char *name, u8 attribute, bool param3) {
  unknown60.dispose();
  GmkCamera::CreateInfo info;
  info.unknown00 = name;
  info.unknown104 = attribute;
  info.unknown106 = param3;
  if (getBdatInfo()->unknown39) {
    info.validateTransform(getBdatInfo()->unknown06);
  }
  if (info.unknown00.length() > 0) {
    unknown60.create(info);
    return true;
  }
  return false;
}

void GmkDoor::disposeGmkCamera() { unknown60.dispose(); }

void GmkDoor::createGmkPhantom() {
  if (!canCreateGameEntity()) {
    return;
  }
  switch (unknown08.unknown10->unknown0c) {
  case SHAPE_TYPE_SPHERE:
  case SHAPE_TYPE_BOX:
  case SHAPE_TYPE_CAPSULE:
    if ((getBdatInfo()->unknown03 & 2) == 0) {
      unknown1c0.create(*this, this, true);
    } else {
      GmkPhantomSimple::CreateInfo info;
      info.validateByAGmkBase(*this);
      unknown250.create(info);
      unknown250.unknown50->setColiUserData(this);
    }
    break;
  default:
    break;
  }
}

void GmkDoor::disposeGmkPhantom() {
  unknown250.dispose();
  unknown1c0.dispose();
}

void GmkDoor::disposeGfObjHandle() {
  if (unknown2b8 != gf::INVALID_HANDLE) {
    gf::GfObjAcc acc(unknown2b8);
    if (acc.isValid()) {
      acc.setUserData(gf::OBJ_USER_DATA_GMK, 0);
    }
    gf::GfObjUtil::destroy(unknown2b8);
    unknown2b8 = gf::INVALID_HANDLE;
  }
}

void GmkDoor::createGfObjHandle() {
  if (!canCreateGameEntity()) {
    return;
  }
  disposeGfObjHandle();
  CBdatWrapper bdat = {getBindedBdatFp()};
  unknown2b8 = gf::GfObjFactory::createGmkEvent(bdat, unknown20.unknown18);
  bindToGameObj(unknown2b8);
  gf::GfObjSetupGimmick *setup = mm::mtl::dynamicCast<gf::GfObjSetupGimmick>(gf::GfObjManager::getObjInfo(unknown2b8)->unknown30);
  unknown003(setup, unknown08.unknown08);
  bool isOpened = isDoorOpened();
  unknown002(unknown2b8, !isOpened);
}

bool GmkDoor::isSpLocked() const {
  if (getBdatInfo()->unknown42.isEnable()) {
    return !getBdatInfo()->unknown42.isMatch();
  }
  return false;
}

bool GmkDoor::isLocked() const {
  if (getBdatInfo()->unknown02 == 5) {
    return true;
  }
  if (getBdatInfo()->unknown3e.isEnable()) {
    return !getBdatInfo()->unknown3e.isMatch();
  }
  return false;
}

bool GmkDoor::isGmkFinished() const {
  u32 progress = getProgress();
  if (progress == 0) {
    return false;
  }
  const BdatInfo *info = getBdatInfo();
  if (unknown2c0 < info->unknown2c) {
    return false;
  }
  if (info->unknown42.isEnable()) {
    return progress == 3;
  }
  return progress == 1;
}

void GmkDoor::onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) {
  AGmkBase::onGobEvent(event, handle);
  if (event == gf::IGfObjListener::OBJEVT_DESTROY) {
    unknown2b8 = gf::INVALID_HANDLE;
  }
}

void GmkDoor::onEnterPhantom(const IGmkPhantomEventListener::OnEnterInfo &info) {
  if (&GmkDoor::seqDoor_BeforeBoot != unknown2c8 && &GmkDoor::seqDoor_Booted != unknown2c8 && &GmkDoor::seqDoor_Shutdowned != unknown2c8) {
    return;
  }
  pollBootGmk();
}

void GmkDoor::onLeavePhantom(const IGmkPhantomEventListener::OnLeaveInfo &info) {
  if ((getBdatInfo()->unknown02 & 0xfe) == 6 && getProgress() != PROGRESS_UNKNOWN_2) {
    const BdatInfo *bdatInfo = getBdatInfo();
    if (!bdatInfo->unknown19) {
      openDoor(false);
    } else {
      closeDoor(false);
    }
    createGmkCamera(bdatInfo->unknown20, bdatInfo->unknown28, true);
    setProgress(PROGRESS_UNKNOWN_2);
  }
}

GmkType GmkDoor::getGmkType() const { return GMK_TYPE; }

int GmkDoor::getGameFlagId() const { return unknown20.unknown18 + 0x94b6; }

const mm::mtl::RTTI *GmkDoor::getRTTI() const { return &m_rtti; }

u32 GmkDoor::getProgress() const { return gf::GfGameFlag::getLocal(2, getGameFlagId()); }

bool GmkDoor::isDoorOpened() const {
  const BdatInfo *info = getBdatInfo();
  gf::GfFieldLod *lod = gf::GfFieldLod::get();
  return !lod->isAnimReverse(info->unknown06);
}

void GmkDoor::createSe(bool isMapPack, u16 seId, u8 distance) {
  unknown2e0.dispose();
  GmkCtrlVolSe::CreateInfo info;
  if (isMapPack) {
    info.unknown00 = gf::GfFieldSound::get()->getMapPack();
  } else {
    info.unknown00 = gf::GfFieldSound::get()->getCommonPack();
  }
  if (seId == 0 || info.unknown00 == nullptr) {
    return;
  }
  info.unknown08 = seId;
  info.unknown10 = distance;
  info.unknown14 = distance;
  info.unknown20 = unknown08.unknown08->unknown00;
  unknown2e0.create(info);
}

bool GmkDoor::isSeLoop(bool isMapPack, u16 seId) const {
  fw::SoundPack *pack;
  if (isMapPack) {
    pack = gf::GfFieldSound::get()->getMapPack();
  } else {
    pack = gf::GfFieldSound::get()->getCommonPack();
  }
  return fw::SoundManager::get()->isLoop(seId, pack);
}

void GmkDoor::openDoor(bool isImmediate) {
  if (!canCreateGameEntity()) {
    return;
  }
  const BdatInfo *info = getBdatInfo();
  gf::GfFieldLod::get()->setAnimReverse(info->unknown06, false, isImmediate);
  if (unknown2b8 != gf::INVALID_HANDLE) {
    unknown002(unknown2b8, false);
  }
  if (info->unknown0c != 0) {
    if (isImmediate && !isSeLoop(info->unknown0b, info->unknown0c)) {
      return;
    }
    createSe(info->unknown0b, info->unknown0c, info->unknown0e);
  }
  if (!isImmediate) {
    u32 gimmick = unknown20.unknown18;
    f32 delay = 0.0f;
    if (gf::GfQuestUtil::getGimmickTaskEndCheck(GMK_TYPE, gimmick) == 1) {
      const BdatInfo *bdatInfo = getBdatInfo();
      delay = gf::GfFieldLod::get()->getAnimEndTime(bdatInfo->unknown06) + bdatInfo->unknown2c;
    }
    gf::SCOM_QUEST_GIMMICK::createDoor(gimmick, delay);
  }
}

void GmkDoor::closeDoor(bool isImmediate) {
  if (!canCreateGameEntity()) {
    return;
  }
  const BdatInfo *info = getBdatInfo();
  gf::GfFieldLod::get()->setAnimReverse(info->unknown06, true, isImmediate);
  if (unknown2b8 != gf::INVALID_HANDLE) {
    unknown002(unknown2b8, true);
  }
  if (info->unknown1c != 0) {
    if (isImmediate && !isSeLoop(info->unknown1a, info->unknown1c)) {
      return;
    }
    createSe(info->unknown1a, info->unknown1c, info->unknown1e);
  }
}

void GmkDoor::pollBootGmk() {
  if (unknown2b1 || unknown1c0.unknown83) {
    const BdatInfo *info = getBdatInfo();
    switch (info->unknown02) {
    case 3:
    case 4:
    case 7: {
      const BootedGmkCond &cond = info->unknown3e;
      if (!cond.isEnable() || cond.isMatch()) {
        bootGmk(false, true);
      }
      break;
    }
    }
  }
}

void GmkDoor::seqDoor_BeforeBoot(f32 deltaTime) { pollBootGmk(); }

void GmkDoor::seqDoor_Booted(f32 deltaTime) {
  if (unknown2c0 < getBdatInfo()->unknown2c) {
    unknown2c0 += deltaTime;
  }
  if (getBdatInfo()->unknown42.isEnable() && getBdatInfo()->unknown42.isMatch() && getProgress() != PROGRESS_UNKNOWN_3) {
    const BdatInfo *info = getBdatInfo();
    if (!info->unknown0a) {
      closeDoor(false);
    } else {
      openDoor(false);
    }
    createGmkCamera(info->unknown30, info->unknown38, false);
    unknown2c0 = 0.0f;
    setProgress(PROGRESS_UNKNOWN_3);
  }
  pollBootGmk();
}

void GmkDoor::bootGmk(bool isImmediate, bool isCamera) {
  if (getProgress() == PROGRESS_UNKNOWN_1) {
    return;
  }
  const BdatInfo *info = getBdatInfo();
  if (!info->unknown0a) {
    openDoor(isImmediate);
  } else {
    closeDoor(isImmediate);
  }
  u16 lodId = info->unknown06;
  const gf::GfFieldLod::BdatInfo *lodInfo = gf::GfFieldLod::get()->findBdatInfo(lodId);
  if (lodInfo != nullptr) {
    if (lodInfo->unknown04 > 0.0f) {
      gf::GfFieldLod::get()->setFade(lodId, true, isImmediate);
    } else if (lodInfo->unknown08 > 0.0f) {
      gf::GfFieldLod::get()->setFade(lodId, false, isImmediate);
    }
  }
  createGmkCamera(info->unknown10, info->unknown18, isCamera);
  if (!info->unknown42.isEnable()) {
    unknown2c0 = isImmediate ? info->unknown2c : 0.0f;
  }
  setProgress(PROGRESS_UNKNOWN_1);
}

void GmkDoor::spBootGmk(bool isImmediate, bool isCamera) {
  if (getProgress() == PROGRESS_UNKNOWN_3) {
    return;
  }
  const BdatInfo *info = getBdatInfo();
  if (!info->unknown0a) {
    closeDoor(isImmediate);
  } else {
    openDoor(isImmediate);
  }
  createGmkCamera(info->unknown30, info->unknown38, isCamera);
  unknown2c0 = isImmediate ? info->unknown2c : 0.0f;
  setProgress(PROGRESS_UNKNOWN_3);
}

void GmkDoor::shutdownGmk(bool isImmediate, bool isCamera) {
  if (getProgress() == PROGRESS_UNKNOWN_2) {
    return;
  }
  const BdatInfo *info = getBdatInfo();
  if (!info->unknown19) {
    openDoor(isImmediate);
  } else {
    closeDoor(isImmediate);
  }
  createGmkCamera(info->unknown20, info->unknown28, isCamera);
  setProgress(PROGRESS_UNKNOWN_2);
}

void GmkDoor::seqDoor_Shutdowned(f32 deltaTime) { seqDoor_Booted(deltaTime); }

void GmkDoor::seqDoor_SpBooted(f32 deltaTime) {
  if (unknown2c0 < getBdatInfo()->unknown2c) {
    unknown2c0 += deltaTime;
  }
}

void GmkDoor::onPlayerAccessed(gf::GF_OBJ_HANDLE *handle) {
  const BdatInfo *info = getBdatInfo();
  if (info->unknown02 == 5) {
    if (gf::GfGameManager::getControlMover() == gf::INVALID_HANDLE) {
      return;
    }
    const mm::Vec3 &position = gf::GfObjUtil::getObj(gf::GfGameManager::getControlMover())->getComponent<gf::GfComTransform>()->getPosition();
    const Xform *xform = unknown08.unknown08;
    mm::Vec3 diff = position - xform->unknown00;
    mm::Vec3 rotation = xform->unknown10;
    mm::Mat44 matrix;
    matrix.setRotXYZ(rotation);
    if (diff.x * matrix.rows[2][0] + diff.y * matrix.rows[2][1] + diff.z * matrix.rows[2][2] < 0.0f) {
      bootGmk(false, false);
      setLodSwitch(LOD_SWITCH_UNKNOWN_2);
      return;
    }
  } else if (!info->unknown3e.isEnable() || info->unknown3e.isMatch()) {
    bootGmk(false, false);
    return;
  }
  reqDrawCmnMsg(info->unknown08);
}

GmkDoorPhantomManager::GmkDoorPhantomManager() {
  gf::GfObjManager::addListener(this, OBJEVT_ALL);
  create();
}

GmkDoorPhantomManager::~GmkDoorPhantomManager() {
  dispose();
  gf::GfObjManager::removeListener(this);
}

void GmkDoorPhantomManager::create() {
  dispose();
  unknown08.setAllocator(gf::getAllocator(gf::ALLOCATOR_DEFAULT));
  int capacity = gf::GfObjManager::getGfObjCapacity(5);
  unknown08.reserve(capacity > 0 ? static_cast<u32>(capacity + 3) : 3);
}

void GmkDoorPhantomManager::dispose() { unknown08.destroy(); }

void GmkDoorPhantomManager::addTargetInfo(gf::GF_OBJ_HANDLE *handle) {
  if (unknown08.size() != unknown08.capacity()) {
    GmkDoorPhantomTargetInfo info;
    info.unknown00 = handle;
    unknown08.push_back(info);
  }
}

void GmkDoorPhantomManager::removeTargetInfo(gf::GF_OBJ_HANDLE *handle) {
  if (handle == gf::INVALID_HANDLE) {
    return;
  }
  for (GmkDoorPhantomTargetInfo *it = unknown08.begin(); it != unknown08.end(); it++) {
    if (it->unknown00 == handle) {
      unknown08.erase(it);
      return;
    }
  }
}

} // namespace gmk

template void mm::mtl::Vector<gmk::GmkDoor::BdatInfo>::expand(size_t, size_t);

template void mm::mtl::Vector<gmk::GmkDoor::BdatInfo>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkDoor::BdatInfo>::resize(size_t);
