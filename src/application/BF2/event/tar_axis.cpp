#include "event/tar_axis.h"

#include "event/data_manager.h"
#include "mm_mtl/singleton.h"

namespace event {

TarAxis::TarAxis() : mAxis(1), mTar(mm::Vec3::zero) {}

TarAxis::TarAxis(u32 axis, f32 x, f32 y, f32 z) : mAxis(axis), mTar(x, y, z) {}

TarAxis::TarAxis(u32 axis, const mm::Vec3 &tar) : mAxis(axis), mTar(tar) {}

void TarAxis::set(u32 axis, f32 x, f32 y, f32 z) {
  mAxis = axis;
  mTar.x = x;
  mTar.y = y;
  mTar.z = z;
}

void TarAxis::set(u32 axis, const mm::Vec3 &tar) {
  mAxis = axis;
  mTar = tar;
}

mm::Vec3 TarAxis::calcTar(const mm::Vec3 &pos) const {
  return mm::mtl::Singleton<DataManager>::getPtr()->axis2tar(mAxis, mTar.x, mTar.y, mTar.z, pos);
}

mm::Mat44 TarAxis::calcOrigMat() const { return mm::mtl::Singleton<DataManager>::getPtr()->getTarAxis(mAxis); }

const char *TarAxis::getOrigName() const { return mm::mtl::Singleton<DataManager>::getPtr()->getTarName(mAxis); }

} // namespace event
