#include "event/anm_vec.h"

namespace event {

AnmVec::AnmVec() { clear(); }

void AnmVec::clear() {
  AnmBase::clear();
  unknown80.clear();
  unknown190.clear();
  unknown1e0.x = 0.0f;
  unknown1e0.y = 0.0f;
  unknown1e0.z = 0.0f;
}

void AnmVec::update(f32 delta) {
  AnmBase::update(delta);
  if (unknown08 & STATE_PLAY) {
    unknown1e0 = calcEvalute(unknown68, unknown70);
  }
}

void AnmVec::replay() { AnmBase::replay(); }

void AnmVec::append(f32 frame, const mm::Vec3 &value, CV_TYPE cv) {
  AnmBase::append(frame);
  unknown80.push_back(value);
  unknown190.push_back(cv);
}

void AnmVec::insert(size_t index, const mm::Vec3 &value) {
  if (index < unknown80.size()) {
    unknown80[index] = value;
  }
}

size_t AnmVec::count() const { return AnmBase::count(); }

CV_TYPE AnmVec::getCv(size_t index) const {
  if (index < unknown190.size()) {
    return unknown190[index];
  }
  return CV_TYPE_LINEAR;
}

const mm::Vec3 &AnmVec::getValue(size_t index) const {
  if (index < unknown80.size()) {
    return unknown80[index];
  }
  return mm::Vec3::zero;
}

void AnmVec::setValue(size_t index, const mm::Vec3 &value) {
  if (index < unknown80.size()) {
    unknown80[index] = value;
  }
}

} // namespace event
