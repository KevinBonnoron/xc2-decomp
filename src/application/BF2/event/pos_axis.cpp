#include "event/pos_axis.h"

#include "event/data_manager.h"
#include "mm_mtl/singleton.h"

namespace event {

PosAxis::PosAxis() : mAxis(1), mPos(mm::Vec3::zero) {}

PosAxis::PosAxis(u32 axis, f32 x, f32 y, f32 z) : mAxis(axis), mPos(x, y, z) {}

PosAxis::PosAxis(u32 axis, const mm::Vec3 &pos) : mAxis(axis), mPos(pos) {}

void PosAxis::set(u32 axis, f32 x, f32 y, f32 z) {
  mAxis = axis;
  mPos.x = x;
  mPos.y = y;
  mPos.z = z;
}

void PosAxis::set(u32 axis, const mm::Vec3 &pos) {
  mAxis = axis;
  mPos = pos;
}

mm::Vec3 PosAxis::calcPos() const { return mm::mtl::Singleton<DataManager>::getPtr()->axis2pos(mAxis, mPos.x, mPos.y, mPos.z); }

mm::Mat44 PosAxis::calcOrigMat() const { return mm::mtl::Singleton<DataManager>::getPtr()->getPosAxis(mAxis); }

const char *PosAxis::getOrigName() const { return mm::mtl::Singleton<DataManager>::getPtr()->getPosName(mAxis); }

} // namespace event
