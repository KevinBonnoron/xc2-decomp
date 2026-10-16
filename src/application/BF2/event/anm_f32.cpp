#include "event/anm_f32.h"

namespace event {

AnmF32::AnmF32() { clear(); }

void AnmF32::clear() {
  AnmBase::clear();
  values.clear();
  cvs.clear();
  value = 0.0f;
}

void AnmF32::update(f32 delta) {
  AnmBase::update(delta);
  if (state & STATE_PLAY) {
    value = calcEvalute(index, alpha);
  }
}

void AnmF32::replay() { AnmBase::replay(); }

void AnmF32::append(f32 frame, f32 value, CV_TYPE cv) {
  AnmBase::append(frame);
  values.push_back(value);
  cvs.push_back(cv);
}

size_t AnmF32::count() const { return AnmBase::count(); }

CV_TYPE AnmF32::getCv(size_t index) const {
  if (index < cvs.size()) {
    return cvs[index];
  }
  return CV_TYPE_LINEAR;
}

f32 AnmF32::getValue(size_t index) const {
  if (index < values.size()) {
    return values[index];
  }
  return 0.0f;
}

void AnmF32::setValue(size_t index, f32 value) {
  if (index < values.size()) {
    values[index] = value;
  }
}

} // namespace event
