#include "event/anm_f32.h"

namespace event {

AnmF32::AnmF32() { clear(); }

void AnmF32::clear() {
  AnmBase::clear();
  unknown78.clear();
  unknownc0.clear();
  unknown108 = 0.0f;
}

void AnmF32::update(f32 delta) {
  AnmBase::update(delta);
  if (unknown08 & STATE_PLAY) {
    unknown108 = calcEvalute(unknown68, unknown70);
  }
}

void AnmF32::replay() { AnmBase::replay(); }

void AnmF32::append(f32 frame, f32 value, CV_TYPE cv) {
  AnmBase::append(frame);
  unknown78.push_back(value);
  unknownc0.push_back(cv);
}

size_t AnmF32::count() const { return AnmBase::count(); }

CV_TYPE AnmF32::getCv(size_t index) const {
  if (index < unknownc0.size()) {
    return unknownc0[index];
  }
  return CV_TYPE_LINEAR;
}

f32 AnmF32::getValue(size_t index) const {
  if (index < unknown78.size()) {
    return unknown78[index];
  }
  return 0.0f;
}

void AnmF32::setValue(size_t index, f32 value) {
  if (index < unknown78.size()) {
    unknown78[index] = value;
  }
}

} // namespace event
