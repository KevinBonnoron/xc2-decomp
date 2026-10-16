#include "event/alpha_obj.h"

#include "gf/game/gf_game_util.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_util.h"

namespace event {

AlphaObj::AlphaObj(gf::GF_OBJ_HANDLE *handle) : handle(handle), alpha(1.0f), belongingAlpha(1.0f), opaqueFrames(0) {
  flags = FLAG_ACTIVE;
  for (u32 i = 0; i < ALPHA_ATTR_COUNT; i++) {
    alphas[i] = 1.0f;
  }
  for (u32 i = 0; i < ALPHA_ATTR_COUNT; i++) {
    belongingAlphas[i] = 1.0f;
  }
}

void AlphaObj::update() {
  if (gf::GfObjUtil::getObj(handle) != nullptr) {
    if (!(alpha >= 1.0f) || !(belongingAlpha >= 1.0f)) {
      opaqueFrames = 0;
      return;
    }
    if (opaqueFrames++ < 4) {
      return;
    }
  }
  flags &= ~FLAG_ACTIVE;
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
