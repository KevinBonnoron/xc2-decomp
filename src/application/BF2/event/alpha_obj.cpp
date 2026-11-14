#include "event/alpha_obj.h"

#include "gf/game/gf_game_util.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_util.h"

namespace event {

AlphaObj::AlphaObj(gf::GF_OBJ_HANDLE *handle) : unknown10(handle), unknown38(1.0f), unknown3c(1.0f), unknown40(0) {
  unknown08 = FLAG_UNKNOWN_0;
  for (u32 i = 0; i < ALPHA_ATTR_UNKNOWN_4; i++) {
    unknown18[i] = 1.0f;
  }
  for (u32 i = 0; i < ALPHA_ATTR_UNKNOWN_4; i++) {
    unknown28[i] = 1.0f;
  }
}

void AlphaObj::update() {
  if (gf::GfObjUtil::getObj(unknown10) != nullptr) {
    if (!(unknown38 >= 1.0f) || !(unknown3c >= 1.0f)) {
      unknown40 = 0;
      return;
    }
    if (unknown40++ < 4) {
      return;
    }
  }
  unknown08 &= ~FLAG_UNKNOWN_0;
}

void AlphaObj::setAlpha(ALPHA_ATTR attr, f32 alpha, f32 belongingAlpha) {
  if (gf::GfObjUtil::getObj(unknown10) != nullptr) {
    f32 oldAlpha = unknown38;
    if (unknown18[attr] != alpha) {
      unknown18[attr] = alpha;
      unknown38 = 1.0f;
      for (u32 i = 0; i < ALPHA_ATTR_UNKNOWN_4; i++) {
        unknown38 = unknown18[i] * unknown38;
      }
    }
    f32 oldBelongingAlpha = unknown3c;
    if (unknown28[attr] != belongingAlpha) {
      unknown28[attr] = belongingAlpha;
      unknown3c = 1.0f;
      for (u32 i = 0; i < ALPHA_ATTR_UNKNOWN_4; i++) {
        unknown3c = unknown28[i] * unknown3c;
      }
    }
    if (oldAlpha != unknown38 || oldBelongingAlpha != unknown3c) {
      setEventAlpha(unknown10, unknown38, unknown38 * unknown3c);
    }
    unknown40 = 0;
  }
}

void AlphaObj::setEventAlpha(gf::GF_OBJ_HANDLE *handle, f32 alpha, f32 belongingAlpha) {
  gf::GfObjAcc acc(handle);
  acc.setAlphaEvent(alpha);
  if (gf::GfGameUtil::hasBelonging(handle, 2)) {
    gf::GfGameUtil::changeAlphaBelonging(handle, 2, belongingAlpha, 0.0f);
  }
  if (gf::GfGameUtil::hasBelonging(handle, 1)) {
    gf::GfGameUtil::changeAlphaBelonging(handle, 1, belongingAlpha, 0.0f);
  }
}

} // namespace event
