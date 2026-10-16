#include "event/schedule_item.h"

#include "gf/game/gf_game_util.h"
#include "gf/object/gf_obj_util.h"

namespace event {

const f32 ScheduleItem::FADE_SP = 0.1f;

ScheduleItem::ScheduleItem(gf::GF_OBJ_HANDLE *handle) : handle(handle), mFunc(nullptr), alpha(1.0f) {}

void ScheduleItem::fadeout() {
  if (hasItem()) {
    alpha = 1.0f;
    mFunc = &ScheduleItem::func_fadeout;
  } else {
    alpha = 0.0f;
    mFunc = nullptr;
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

void ScheduleItem::func_fadewait(gf::GF_OBJ_HANDLE *handle) {}

} // namespace event
