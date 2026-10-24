#include "event/cam_base.h"

#include <math.h>

namespace event {

CamBase::CamBase(bool isFocal) : mIsFocal(isFocal), mPos(0.0f, 1.0f, 2.0f), mTarget(0.0f, 1.0f, 1.0f), mFov(40.0f), mRoll(0.0f), mNear(0.5f), mFar(40000.0f) {}

mm::Vec3 CamBase::getRot() const {
  f32 dx = mTarget.x - mPos.x;
  f32 dy = mTarget.y - mPos.y;
  f32 dz = mTarget.z - mPos.z;
  mm::Vec3 rot;
  rot.y = -atan2f(dx, -dz);
  rot.x = atan2f(dy, sqrtf(dx * dx + dz * dz));
  rot.z = mRoll;
  return rot;
}

} // namespace event
