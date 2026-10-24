#include "ui/timer/ui_timer.h"

#include "ui/ui_util.h"

namespace ui {

UITimer::UITimer() : unknown08(0), unknown10(0), unknown18(1.0f) {}

UITimer::~UITimer() { ; }

void UITimer::update(f32 sec) { unknown08 += UIUtil::timeSecToUITime(unknown18 * sec); }

void UITimer::start(u64 duration) {
  unknown08 = 0;
  this->unknown10 = duration;
  unknown18 = 1.0f;
}

void UITimer::restart() {
  if (unknown10 != 0) {
    unknown08 = 0;
  }
}

void UITimer::stop() { unknown10 = 0; }

bool UITimer::isActive() const { return unknown10 != 0; }

bool UITimer::isOver() const {
  if (unknown10 != 0) {
    return unknown08 >= unknown10;
  }
  return false;
}

} // namespace ui
