#include "event/fade_ctrl.h"

#include "mm_math/mm_col4.h"

namespace event {

namespace {

mm::Col4 s_eventSkipFadeColor(0.0f, 0.0f, 0.0f, 1.0f);

} // namespace

FadeCtrl::FadeCtrl() : flags(0) {
  for (u32 i = 0; i < PRIO_COUNT; i++) {
    mUpdaters[i].setup(i);
  }
}

void FadeCtrl::clear() {
  for (u32 i = 0; i < PRIO_COUNT; i++) {
    mUpdaters[i].clear();
  }
  flags = 0;
}

void FadeCtrl::update() {
  for (u32 i = 0; i < PRIO_COUNT; i++) {
    mUpdaters[i].update();
  }
}

void FadeCtrl::fadeout(int frame, PRIO prio, const mm::Col4 *color) { mUpdaters[prio].reserve(true, frame, color); }

void FadeCtrl::fadein(int frame) {
  mUpdaters[PRIO_LOW].reserve(false, frame, nullptr);
  mUpdaters[PRIO_MIDDLE].reserve(false, frame, nullptr);
  if (!(flags & FLAG_EVENT_SKIP)) {
    mUpdaters[PRIO_HIGH].reserve(false, frame, nullptr);
  }
}

void FadeCtrl::fadeoutEventSkip(int frame) {
  mUpdaters[PRIO_HIGH].reserve(true, frame, &s_eventSkipFadeColor);
  flags |= FLAG_EVENT_SKIP;
}

void FadeCtrl::fadeinEventSkip(int frame) {
  mUpdaters[PRIO_HIGH].reserve(false, frame, &s_eventSkipFadeColor);
  flags &= ~FLAG_EVENT_SKIP;
}

} // namespace event
