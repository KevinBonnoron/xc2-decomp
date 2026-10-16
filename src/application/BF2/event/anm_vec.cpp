#include "event/anm_vec.h"

namespace event {

AnmVec::AnmVec() { clear(); }

void AnmVec::clear() {
  AnmBase::clear();
  values.clear();
  cvs.clear();
  value.x = 0.0f;
  value.y = 0.0f;
  value.z = 0.0f;
}

void AnmVec::replay() { AnmBase::replay(); }

void AnmVec::append(f32 frame, const mm::Vec3 &value, CV_TYPE cv) {
  AnmBase::append(frame);
  values.push_back(value);
  cvs.push_back(cv);
}

void AnmVec::insert(size_t index, const mm::Vec3 &value) {
  if (index < values.size()) {
    values[index] = value;
  }
}

size_t AnmVec::count() const { return AnmBase::count(); }

CV_TYPE AnmVec::getCv(size_t index) const {
  if (index < cvs.size()) {
    return cvs[index];
  }
  return CV_TYPE_LINEAR;
}

const mm::Vec3 &AnmVec::getValue(size_t index) const {
  if (index < values.size()) {
    return values[index];
  }
  return mm::Vec3::zero;
}

void AnmVec::setValue(size_t index, const mm::Vec3 &value) {
  if (index < values.size()) {
    values[index] = value;
  }
}

} // namespace event
