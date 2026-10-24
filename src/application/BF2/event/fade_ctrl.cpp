#include "event/fade_ctrl.h"

#include "mm_math/mm_col4.h"

namespace event {

namespace {

mm::Col4 s_eventSkipFadeColor(0.0f, 0.0f, 0.0f, 1.0f);

} // namespace

FadeCtrl::FadeCtrl() : unknown68(0) {
  for (u32 i = 0; i < PRIO_COUNT; i++) {
    unknown08[i].setup(i);
  }
}

void FadeCtrl::clear() {
  for (u32 i = 0; i < PRIO_COUNT; i++) {
    unknown08[i].clear();
  }
  unknown68 = 0;
}

void FadeCtrl::update() {
  for (u32 i = 0; i < PRIO_COUNT; i++) {
    unknown08[i].update();
  }
}

void FadeCtrl::fadeout(int frame, PRIO prio, const mm::Col4 *color) { unknown08[prio].reserve(true, frame, color); }

void FadeCtrl::fadein(int frame) {
  unknown08[PRIO_LOW].reserve(false, frame, nullptr);
  unknown08[PRIO_MIDDLE].reserve(false, frame, nullptr);
  if (!(unknown68 & FLAG_EVENT_SKIP)) {
    unknown08[PRIO_HIGH].reserve(false, frame, nullptr);
  }
}

void FadeCtrl::fadeoutEventSkip(int frame) {
  unknown08[PRIO_HIGH].reserve(true, frame, &s_eventSkipFadeColor);
  unknown68 |= FLAG_EVENT_SKIP;
}

void FadeCtrl::fadeinEventSkip(int frame) {
  unknown08[PRIO_HIGH].reserve(false, frame, &s_eventSkipFadeColor);
  unknown68 &= ~FLAG_EVENT_SKIP;
}

} // namespace event
