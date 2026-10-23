#include "event/schedule_item.h"

#include "event/alpha_manager.h"
#include "event/alpha_obj.h"
#include "gf/game/gf_game_util.h"
#include "gf/object/gf_obj_util.h"
#include "mm_mtl/singleton.h"

namespace event {

const f32 ScheduleItem::FADE_SP = 0.1f;

ScheduleItem::ScheduleItem(gf::GF_OBJ_HANDLE *handle) : handle(handle), mFunc(nullptr), alpha(1.0f) {}

void ScheduleItem::clear() {
  if (mFunc && gf::GfObjUtil::getObj(handle) != nullptr) {
    // The original call passes attribute 3; its enumerator name is unknown.
    mm::mtl::Singleton<AlphaManager>::getPtr()->setAlpha(handle, static_cast<ALPHA_ATTR>(3), 1.0f, 1.0f);
  }
}

void ScheduleItem::fadeout() {
  if (hasItem()) {
    alpha = 1.0f;
    mFunc = &ScheduleItem::func_fadeout;
  } else {
    alpha = 0.0f;
    mFunc = nullptr;
  }
}

void ScheduleItem::func_fadeout(gf::GF_OBJ_HANDLE *handle) {
  alpha -= FADE_SP;
  if (alpha > 0.0f) {
    mm::mtl::Singleton<AlphaManager>::getPtr()->setAlpha(handle, static_cast<ALPHA_ATTR>(3), 1.0f, alpha);
  } else {
    mm::mtl::Singleton<AlphaManager>::getPtr()->setAlpha(handle, static_cast<ALPHA_ATTR>(3), 1.0f, 0.0f);
    alpha = 0.0f;
    mFunc = &ScheduleItem::func_fadewait;
  }
}

bool ScheduleItem::hasItem() {
  if (gf::GfObjUtil::getObj(handle) != nullptr) {
    if (gf::GfGameUtil::hasBelonging(handle, 2)) {
      return true;
    }
    if (gf::GfGameUtil::hasBelonging(handle, 1)) {
      return true;
    }
  }
  return false;
}

void ScheduleItem::fadein() {
  if (hasItem()) {
    alpha = 0.0f;
    mFunc = &ScheduleItem::func_fadein;
  } else {
    alpha = 1.0f;
    mFunc = nullptr;
  }
}

void ScheduleItem::func_fadein(gf::GF_OBJ_HANDLE *handle) {
  alpha += FADE_SP;
  if (alpha < 1.0f) {
    mm::mtl::Singleton<AlphaManager>::getPtr()->setAlpha(handle, static_cast<ALPHA_ATTR>(3), 1.0f, alpha);
  } else {
    mm::mtl::Singleton<AlphaManager>::getPtr()->setAlpha(handle, static_cast<ALPHA_ATTR>(3), 1.0f, 1.0f);
    alpha = 0.0f;
    mFunc = nullptr;
  }
}

void ScheduleItem::func_fadewait(gf::GF_OBJ_HANDLE *handle) {}

} // namespace event
