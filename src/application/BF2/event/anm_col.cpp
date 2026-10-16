#include "event/anm_col.h"

namespace event {

AnmCol::AnmCol() { clear(); }

void AnmCol::clear() {
  AnmBase::clear();
  values.clear();
  cvs.clear();
  value.r = 0.0f;
  value.g = 0.0f;
  value.b = 0.0f;
  value.a = 1.0f;
}

void AnmCol::update(f32 delta) {
  AnmBase::update(delta);
  if (state & STATE_PLAY) {
    value = calcEvalute(index, alpha);
  }
}

void AnmCol::replay() { AnmBase::replay(); }

void AnmCol::append(f32 frame, const mm::Col4 &value, CV_TYPE cv) {
  AnmBase::append(frame);
  values.push_back(value);
  cvs.push_back(cv);
}

size_t AnmCol::count() const { return AnmBase::count(); }

} // namespace event
