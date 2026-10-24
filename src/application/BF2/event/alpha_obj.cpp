#include "event/alpha_obj.h"

#include "gf/game/gf_game_util.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_util.h"

namespace event {

AlphaObj::AlphaObj(gf::GF_OBJ_HANDLE *handle) : unknown10(handle), unknown38(1.0f), unknown3c(1.0f), unknown40(0) {
  unknown08 = FLAG_ACTIVE;
  for (u32 i = 0; i < ALPHA_ATTR_COUNT; i++) {
    unknown18[i] = 1.0f;
  }
  for (u32 i = 0; i < ALPHA_ATTR_COUNT; i++) {
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
  unknown08 &= ~FLAG_ACTIVE;
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
