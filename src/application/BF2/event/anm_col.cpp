#include "event/anm_col.h"

namespace event {

AnmCol::AnmCol() { clear(); }

void AnmCol::clear() {
  AnmBase::clear();
  unknown78.clear();
  unknown180.clear();
  unknown1c8.r = 0.0f;
  unknown1c8.g = 0.0f;
  unknown1c8.b = 0.0f;
  unknown1c8.a = 1.0f;
}

void AnmCol::update(f32 delta) {
  AnmBase::update(delta);
  if (unknown08 & STATE_PLAY) {
    unknown1c8 = calcEvalute(unknown68, unknown70);
  }
}

void AnmCol::replay() { AnmBase::replay(); }

void AnmCol::append(f32 frame, const mm::Col4 &value, CV_TYPE cv) {
  AnmBase::append(frame);
  unknown78.push_back(value);
  unknown180.push_back(cv);
}

size_t AnmCol::count() const { return AnmBase::count(); }

} // namespace event
