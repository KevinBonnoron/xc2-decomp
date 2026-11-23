#include "event/fade_ctrl.h"

#include "mm_math/mm_col4.h"

namespace event {

namespace {

mm::Col4 s_eventSkipFadeColor(0.0f, 0.0f, 0.0f, 1.0f);

} // namespace

FadeCtrl::FadeCtrl() : unknown68(0) {
  for (u32 i = 0; i < PRIO_COUNT; i++) {
    m_fadeUpdater[i].setup(i);
  }
}

void FadeCtrl::clear() {
  for (u32 i = 0; i < PRIO_COUNT; i++) {
    m_fadeUpdater[i].clear();
  }
  unknown68 = 0;
}

void FadeCtrl::update() {
  for (u32 i = 0; i < PRIO_COUNT; i++) {
    m_fadeUpdater[i].update();
  }
}

void FadeCtrl::fadeout(int frame, PRIO prio, const mm::Col4 *color) { m_fadeUpdater[prio].reserve(true, frame, color); }

void FadeCtrl::fadein(int frame) {
  m_fadeUpdater[PRIO_LOW].reserve(false, frame, nullptr);
  m_fadeUpdater[PRIO_MIDDLE].reserve(false, frame, nullptr);
  if (!(unknown68 & FLAG_UNKNOWN_0)) {
    m_fadeUpdater[PRIO_UNKNOWN_2].reserve(false, frame, nullptr);
  }
}

void FadeCtrl::fadeoutEventSkip(int frame) {
  m_fadeUpdater[PRIO_UNKNOWN_2].reserve(true, frame, &s_eventSkipFadeColor);
  unknown68 |= FLAG_UNKNOWN_0;
}

void FadeCtrl::fadeinEventSkip(int frame) {
  m_fadeUpdater[PRIO_UNKNOWN_2].reserve(false, frame, &s_eventSkipFadeColor);
  unknown68 &= ~FLAG_UNKNOWN_0;
}

} // namespace event
