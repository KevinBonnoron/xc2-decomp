#include "event/cam_base.h"

#include <math.h>

namespace event {

CamBase::CamBase(bool isFocal) : unknown08(isFocal), unknown10(0.0f, 1.0f, 2.0f), unknown20(0.0f, 1.0f, 1.0f), unknown30(40.0f), unknown34(0.0f), unknown38(0.5f), unknown3c(40000.0f) {}

mm::Vec3 CamBase::getRot() const {
  f32 dx = unknown20.x - unknown10.x;
  f32 dy = unknown20.y - unknown10.y;
  f32 dz = unknown20.z - unknown10.z;
  mm::Vec3 rot;
  rot.y = -atan2f(dx, -dz);
  rot.x = atan2f(dy, sqrtf(dx * dx + dz * dz));
  rot.z = unknown34;
  return rot;
}

} // namespace event
