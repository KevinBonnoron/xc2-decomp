#include "gf/object/component/effect/gf_com_effect_caster.h"

#include "gf/game/gf_game_util.h"
#include "gf/object/gf_obj.h"

namespace fw {
class MessageObject;
} // namespace fw

namespace gf {

void GfComEffectCaster::procMsgFxRimBloomEnd(fw::MessageObject *object, MsgFxRimBloomEnd &message) {
  unknown14 = false;
  if (unknown20 == -1.0f) {
    unknown20 = unknown1c;
  }
}

void GfComEffectCaster::procMsgFxRimBloomTarget(fw::MessageObject *object, MsgFxRimBloomTarget &message) {
  unknown18 = 10;
  unknown14 = false;
  unknown1c = 0.0f;
  unknown20 = -1.0f;
}

fw::EffectPoint *GfComEffectCaster::getEffectPoint() { return unknown390; }

bool GfComEffectCaster::getValidEffectName(const char *name) const { return true; }

bool GfComEffectCaster::isDynamicAnnotationEffect(u8 type) const { return type != 0 && type != 0xe; }

GfComEffectCaster::Param *GfComEffectCaster::findEffectCasterParam(u32 effect) {
  for (Param *param = unknown3a0.begin(); param != unknown3a0.end(); param++) {
    if (param->unknown58 == effect) {
      return param;
    }
  }
  return nullptr;
}

GF_OBJ_HANDLE *GfComEffectCaster::getWeaponHandle(u16 weapon) {
  if (weapon == 3 || weapon == 4) {
    return GfGameUtil::getDriverWeaponRight(static_cast<GfObj *>(unknown08)->unknownf8);
  }
  if (weapon == 5 || weapon == 6) {
    return GfGameUtil::getDriverWeaponLeft(static_cast<GfObj *>(unknown08)->unknownf8);
  }
  return reinterpret_cast<GF_OBJ_HANDLE *>(-1);
}

void GfComEffectCaster::getWpnMatOld1(mm::Mat44 &matrix) { matrix = unknown113d0; }

void GfComEffectCaster::getWpnMatOld2(mm::Mat44 &matrix) { matrix = unknown11410; }

} // namespace gf
