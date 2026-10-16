#include "ui/timer/ui_timer.h"

#include "ui/ui_util.h"

namespace ui {

UITimer::UITimer() : elapsed(0), duration(0), speedFactor(1.0f) {}

UITimer::~UITimer() { ; }

void UITimer::update(f32 sec) { elapsed += UIUtil::timeSecToUITime(speedFactor * sec); }

void UITimer::start(u64 duration) {
  elapsed = 0;
  this->duration = duration;
  speedFactor = 1.0f;
}

void UITimer::restart() {
  if (duration != 0) {
    elapsed = 0;
  }
}

void UITimer::stop() { duration = 0; }

bool UITimer::isActive() const { return duration != 0; }

bool UITimer::isOver() const {
  if (duration != 0) {
    return elapsed >= duration;
  }
  return false;
}

} // namespace ui
