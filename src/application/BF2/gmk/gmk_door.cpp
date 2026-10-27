#include "gmk/gmk_door.h"

#include "bdat.h"
#include "framework/sound/sound_manager.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_game_flag.h"
#include "gf/data/gf_object_type.h"
#include "gf/field/gf_field_lod.h"
#include "gf/field/gf_field_sound.h"
#include "gf/game/gf_game_cond.h"
#include "gf/gf_allocator.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep
#include "gmk/gmk_phantom.h"
#include "mm_mtl/fixstr.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace fw {
class SoundPack;
} // namespace fw

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

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
    if (unknown238 == nullptr && unknown2a0 == nullptr && info->isPhantomMustExist()) {
      createGmkPhantom();
    }
  } else {
    disposeGfObjHandle();
    if (unknown238 != nullptr || unknown2a0 != nullptr) {
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
  if (unknown2C0 < info->unknown2c) {
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

GmkType GmkDoor::getGmkType() const { return GMK_TYPE; }

int GmkDoor::getGameFlagId() const { return unknown20.unknown18 + 0x94b6; }

const mm::mtl::RTTI *GmkDoor::getRTTI() const { return &m_rtti; }

u32 GmkDoor::getProgress() const { return gf::GfGameFlag::getLocal(2, getGameFlagId()); }

bool GmkDoor::isDoorOpened() const {
  const BdatInfo *info = getBdatInfo();
  gf::GfFieldLod *lod = gf::GfFieldLod::get();
  return !lod->isAnimReverse(info->unknown06);
}

void GmkDoor::isSeLoop(bool isMapPack, u16 seId) const {
  fw::SoundPack *pack;
  if (isMapPack) {
    pack = gf::GfFieldSound::get()->getMapPack();
  } else {
    pack = gf::GfFieldSound::get()->getCommonPack();
  }
  fw::SoundManager::get()->isLoop(seId, pack);
}

void GmkDoor::pollBootGmk() {
  if (unknown2b1 || unknown243) {
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
  if (unknown2C0 < getBdatInfo()->unknown2c) {
    unknown2C0 += deltaTime;
  }
  if (getBdatInfo()->unknown42.isEnable() && getBdatInfo()->unknown42.isMatch() && getProgress() != PROGRESS_UNKNOWN_3) {
    const BdatInfo *info = getBdatInfo();
    if (!info->unknown0a) {
      closeDoor(false);
    } else {
      openDoor(false);
    }
    createGmkCamera(info->unknown30, info->unknown38, false);
    unknown2C0 = 0.0f;
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
  const gf::GfFieldLod::unknown001 *lodInfo = gf::GfFieldLod::get()->findBdatInfo(lodId);
  if (lodInfo != nullptr) {
    if (lodInfo->unknown04 > 0.0f) {
      gf::GfFieldLod::get()->setFade(lodId, true, isImmediate);
    } else if (lodInfo->unknown08 > 0.0f) {
      gf::GfFieldLod::get()->setFade(lodId, false, isImmediate);
    }
  }
  createGmkCamera(info->unknown10, info->unknown18, isCamera);
  if (!info->unknown42.isEnable()) {
    unknown2C0 = isImmediate ? info->unknown2c : 0.0f;
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
  unknown2C0 = isImmediate ? info->unknown2c : 0.0f;
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
  if (unknown2C0 < getBdatInfo()->unknown2c) {
    unknown2C0 += deltaTime;
  }
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
