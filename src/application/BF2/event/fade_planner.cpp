#include "event/fade_planner.h"

#include "event/fade_ctrl.h"
#include "event/skip_manager.h"
#include "mm_mtl/singleton.h"

namespace event {

FadePlanner::FadePlanner() : unknown08(0) {}

void FadePlanner::clear() {
  for (u32 i = 0; i < TYPE_COUNT; i++) {
    unknown0c[i].clear();
  }
  unknown08 = 0;
}

void FadePlanner::update(f32 delta) {
  for (u32 i = 0; i < TYPE_COUNT; i++) {
    Plan &plan = unknown0c[i];
    if (plan.unknown00 & Plan::FLAG_WAIT) {
      plan.unknown20 -= delta;
      if (plan.unknown20 < 0.0f) {
        play(static_cast<TYPE>(i));
        plan.unknown00 &= ~Plan::FLAG_WAIT;
      }
    }
  }
}

void FadePlanner::play(TYPE type) {
  Plan &plan = unknown0c[type];
  u32 frame = plan.unknown04;
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
    frame = 0;
  }
  if (type & 1) {
    mm::mtl::Singleton<FadeCtrl>::getPtr()->fadein(frame);
  } else {
    mm::mtl::Singleton<FadeCtrl>::getPtr()->fadeout(frame, plan.unknown0c, &plan.unknown10);
  }
}

void FadePlanner::plan(TYPE type, bool isEnable, u32 frame, u32 wait, FadeCtrl::PRIO prio, const mm::Col4 &color) {
  Plan &plan = unknown0c[type];
  plan.clear();
  plan.unknown00 = isEnable;
  plan.unknown04 = frame;
  plan.unknown08 = wait;
  plan.unknown0c = prio;
  plan.unknown10 = color;
}

void FadePlanner::request(TYPE type) {
  Plan &plan = unknown0c[type];
  if (plan.unknown00 & Plan::FLAG_ENABLE) {
    u32 wait = plan.unknown08;
    plan.unknown00 |= Plan::FLAG_REQUEST;
    if (wait != 0) {
      plan.unknown00 |= Plan::FLAG_WAIT;
      plan.unknown20 = wait;
    } else {
      play(type);
    }
  }
}

} // namespace event
