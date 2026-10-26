#include "gmk/gmk_door.h"

#include "bdat.h"
#include "framework/sound/sound_manager.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_game_flag.h"
#include "gf/data/gf_object_type.h"
#include "gf/field/gf_field_lod.h"
#include "gf/field/gf_field_sound.h"
#include "gf/game/gf_game_cond.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_phantom.h"
#include "mm_mtl/fixstr.h"

namespace fw {
class SoundPack;
} // namespace fw

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gmk {

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

void GmkDoor::seqDoor_Shutdowned(f32 deltaTime) { seqDoor_Booted(deltaTime); }

void GmkDoor::seqDoor_SpBooted(f32 deltaTime) {
  if (unknown2C0 < getBdatInfo()->unknown2c) {
    unknown2C0 += deltaTime;
  }
}

} // namespace gmk
