#include "gmk/gmk_dmg_gimmick.h"

#include "framework/sound/sound_manager.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/game/gf_game_cond.h"
#include "gmk/gmk_bdat.h"

namespace fw {
enum SoundCategory : int;
} // namespace fw
namespace mm {
struct Vec3;
} // namespace mm

namespace gmk {

const fw::SoundCategory DMG_SE_CATEGORY = static_cast<fw::SoundCategory>(7);

void GmkDmgGimmick::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  unknown00 = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
  unknown1c = BootedGmkCond(bdat, id, "DEPOP_");
  unknown02 = bdat.getValCheck("DEPOP_Condition", id, BDAT_TYPE_U16);
  unknown04 = toBdatF32(bdat.getValCheck("DMG_interval", id, BDAT_TYPE_F32));
  unknown08 = bdat.getValCheck("Pc_dmg", id, BDAT_TYPE_U8);
  unknown09 = bdat.getValCheck("EN_dmg", id, BDAT_TYPE_U8);
  unknown10 = reinterpret_cast<const char *>(bdat.getValCheck("effect_name", id, BDAT_TYPE_STRING));
  unknown18 = bdat.getValCheck("SE_name", id, BDAT_TYPE_U8);
  unknown19 = bdat.getValCheck("volumeMAX", id, BDAT_TYPE_U8);
  unknown1a = bdat.getValCheck("volumeMIN", id, BDAT_TYPE_U8);
  u16 effectDispRadius = bdat.getValCheck("effect_disp_r", id, BDAT_TYPE_U16);
  unknown20.unknown00 = static_cast<f32>(effectDispRadius) * static_cast<f32>(effectDispRadius);
  u8 effectReleaseRadius = bdat.getValCheck("effect_release_r", id, BDAT_TYPE_U8);
  f32 effectReleaseDistance = effectDispRadius + effectReleaseRadius;
  unknown24.unknown00 = effectReleaseDistance * effectReleaseDistance;
}

bool GmkDmgGimmick::BdatInfo::isCondMatched() const {
  if (unknown00 != 0 && !gf::GfGameCond::isGameCond(unknown00)) {
    return false;
  }
  if (unknown1c.isEnable() && unknown1c.isMatch()) {
    return false;
  }
  if (unknown02 != 0 && gf::GfGameCond::isGameCond(unknown02)) {
    return false;
  }
  return true;
}

void GmkDmgSe::createGmkPhantom() const {
  if (!canCreateGameEntity()) {
    return;
  }
  switch (unknown08.unknown10->unknown0c) {
  case SHAPE_TYPE_SPHERE:
  case SHAPE_TYPE_BOX:
  case SHAPE_TYPE_CAPSULE:
    unknown50.create(*this, nullptr, false);
    break;
  default:
    break;
  }
}

void GmkDmgSe::createSeInst(fw::SoundPack *pack, u32 id) const {
  if (!canCreateGameEntity()) {
    return;
  }
  disposeSeInst(false);
  unknowne4 = fw::SoundManager::get()->playSe(id, pack, 1.0f, DMG_SE_CATEGORY);
  if (unknowne4 != 0) {
    const mm::Vec3 &position = unknown08.unknown08->unknown00;
    fw::SoundManager::get()->setPos(unknowne4, position);
  }
}

void GmkDmgSe::disposeSeInst(bool isFadeOut) const {
  if (unknowne4 == 0) {
    return;
  }
  fw::SoundManager::get()->stopSe(unknowne4, isFadeOut ? 1.0f : 0.0f);
  unknowne4 = 0;
}

void GmkDmgSe::setSeVolume(f32 volume, f32 time) const {
  unknowne8 = volume;
  fw::SoundManager::get()->setVolume(unknowne4, volume, time);
}

void GmkDmgSe::dispose() {
  disposeSeInst(false);
  AGmkBase::dispose();
}

void GmkDmgSe::validateMute() const {
  if (unknowne4 == 0) {
    return;
  }
  fw::SoundManager::get()->setVolume(unknowne4, unknowne0 ? 0.0f : unknowne8, 0.0f);
}

} // namespace gmk
