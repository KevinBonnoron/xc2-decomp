#include "event/schedule_item.h"

#include "event/alpha_manager.h"
#include "event/alpha_obj.h"
#include "gf/game/gf_game_util.h"
#include "gf/object/gf_obj_util.h"
#include "mm_mtl/singleton.h"

namespace event {

const f32 ScheduleItem::FADE_SP = 0.1f;

ScheduleItem::ScheduleItem(gf::GF_OBJ_HANDLE *handle) : unknown08(handle), unknown10(nullptr), unknown20(1.0f) {}

void ScheduleItem::clear() {
  if (unknown10 && gf::GfObjUtil::getObj(unknown08) != nullptr) {
    // The original call passes attribute 3; its enumerator name is unknown.
    mm::mtl::Singleton<AlphaManager>::getPtr()->setAlpha(unknown08, static_cast<ALPHA_ATTR>(3), 1.0f, 1.0f);
  }
}

void ScheduleItem::fadeout() {
  if (hasItem()) {
    unknown20 = 1.0f;
    unknown10 = &ScheduleItem::func_fadeout;
  } else {
    unknown20 = 0.0f;
    unknown10 = nullptr;
  }
}

void ScheduleItem::func_fadeout(gf::GF_OBJ_HANDLE *handle) {
  unknown20 -= FADE_SP;
  if (unknown20 > 0.0f) {
    mm::mtl::Singleton<AlphaManager>::getPtr()->setAlpha(handle, static_cast<ALPHA_ATTR>(3), 1.0f, unknown20);
  } else {
    mm::mtl::Singleton<AlphaManager>::getPtr()->setAlpha(handle, static_cast<ALPHA_ATTR>(3), 1.0f, 0.0f);
    unknown20 = 0.0f;
    unknown10 = &ScheduleItem::func_fadewait;
  }
}

bool ScheduleItem::hasItem() {
  if (gf::GfObjUtil::getObj(unknown08) != nullptr) {
    if (gf::GfGameUtil::hasBelonging(unknown08, 2)) {
      return true;
    }
    if (gf::GfGameUtil::hasBelonging(unknown08, 1)) {
      return true;
    }
  }
  return false;
}

void ScheduleItem::fadein() {
  if (hasItem()) {
    unknown20 = 0.0f;
    unknown10 = &ScheduleItem::func_fadein;
  } else {
    unknown20 = 1.0f;
    unknown10 = nullptr;
  }
}

void ScheduleItem::func_fadein(gf::GF_OBJ_HANDLE *handle) {
  unknown20 += FADE_SP;
  if (unknown20 < 1.0f) {
    mm::mtl::Singleton<AlphaManager>::getPtr()->setAlpha(handle, static_cast<ALPHA_ATTR>(3), 1.0f, unknown20);
  } else {
    mm::mtl::Singleton<AlphaManager>::getPtr()->setAlpha(handle, static_cast<ALPHA_ATTR>(3), 1.0f, 1.0f);
    unknown20 = 0.0f;
    unknown10 = nullptr;
  }
}

void ScheduleItem::func_fadewait(gf::GF_OBJ_HANDLE *handle) {}

} // namespace event
