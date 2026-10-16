#include "event/fade_planner.h"

#include "event/fade_ctrl.h"
#include "event/skip_manager.h"
#include "mm_mtl/singleton.h"

namespace event {

FadePlanner::FadePlanner() : flags(0) {}

void FadePlanner::clear() {
  for (u32 i = 0; i < TYPE_COUNT; i++) {
    mPlans[i].clear();
  }
  flags = 0;
}

void FadePlanner::update(f32 delta) {
  for (u32 i = 0; i < TYPE_COUNT; i++) {
    Plan &plan = mPlans[i];
    if (plan.flags & Plan::FLAG_WAIT) {
      plan.waitTimer -= delta;
      if (plan.waitTimer < 0.0f) {
        play(static_cast<TYPE>(i));
        plan.flags &= ~Plan::FLAG_WAIT;
      }
    }
  }
}

void FadePlanner::play(TYPE type) {
  Plan &plan = mPlans[type];
  u32 frame = plan.frame;
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
    frame = 0;
  }
  if (type & 1) {
    mm::mtl::Singleton<FadeCtrl>::getPtr()->fadein(frame);
  } else {
    mm::mtl::Singleton<FadeCtrl>::getPtr()->fadeout(frame, plan.prio, &plan.color);
  }
}

void FadePlanner::plan(TYPE type, bool isEnable, u32 frame, u32 wait, FadeCtrl::PRIO prio, const mm::Col4 &color) {
  Plan &plan = mPlans[type];
  plan.clear();
  plan.flags = isEnable;
  plan.frame = frame;
  plan.wait = wait;
  plan.prio = prio;
  plan.color = color;
}

void FadePlanner::request(TYPE type) {
  Plan &plan = mPlans[type];
  if (plan.flags & Plan::FLAG_ENABLE) {
    u32 wait = plan.wait;
    plan.flags |= Plan::FLAG_REQUEST;
    if (wait != 0) {
      plan.flags |= Plan::FLAG_WAIT;
      plan.waitTimer = wait;
    } else {
      play(type);
    }
  }
}

} // namespace event
