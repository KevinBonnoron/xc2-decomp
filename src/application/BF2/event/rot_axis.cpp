#include "event/rot_axis.h"

#include "event/data_manager.h"
#include "mm_mtl/singleton.h"

namespace event {

RotAxis::RotAxis() : mAxis(1), mRot(mm::Vec3::zero) {}

RotAxis::RotAxis(u32 axis, f32 x, f32 y, f32 z) : mAxis(axis), mRot(x, y, z) {}

RotAxis::RotAxis(u32 axis, const mm::Vec3 &rot) : mAxis(axis), mRot(rot) {}

void RotAxis::set(u32 axis, f32 x, f32 y, f32 z) {
  mAxis = axis;
  mRot.x = x;
  mRot.y = y;
  mRot.z = z;
}

void RotAxis::set(u32 axis, const mm::Vec3 &rot) {
  mAxis = axis;
  mRot = rot;
}

mm::Vec3 RotAxis::calcRot(const mm::Vec3 &pos) const {
  return mm::mtl::Singleton<DataManager>::getPtr()->axis2rot(mAxis, mRot.x, mRot.y, mRot.z, pos);
}

f32 RotAxis::calcOrigRot(const mm::Vec3 &pos) const { return mm::mtl::Singleton<DataManager>::getPtr()->getRotOfsY(mAxis, pos); }

const char *RotAxis::getOrigName() const { return mm::mtl::Singleton<DataManager>::getPtr()->getRotName(mAxis); }

} // namespace event
