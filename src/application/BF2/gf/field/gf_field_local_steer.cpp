#include "gf/field/gf_field_local_steer.h"

#include <math.h>

#include "gf/object/gf_obj_handle.h"
#include "gmk/gmk_acc.h"
#include "gmk/gmk_route_navi.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_vec3.h"

namespace gf {

constexpr f32 COLLIDE_TIME_OUT = 5.0f;

void GfFieldLocalSteer::dispose() {
  unknown00 = INVALID_HANDLE;
  unknown08 = 2.0f;
  unknown0c = 1.0f;
  unknown10 = 0.5f;
  unknown14 = true;
  unknown18 = 0;
}

bool GfFieldLocalSteer::isTimeOutCollide() const {
  if (unknown00 != INVALID_HANDLE) {
    return COLLIDE_TIME_OUT < unknown24;
  }
  return false;
}

f32 GfFieldLocalSteer::getCurAngle() const {
  f32 angle = unknown34;
  if (unknown38 != 0.0f) {
    f32 rate = mm::max(mm::min(1.0f, unknown3c / unknown38), 0.0f);
    angle = unknown30 + (angle - unknown30) * rate;
  }
  return angle;
}

void validateGmkRouteNaviConsideringGfLocalSteer(gmk::GmkRouteNavi &navi, const GfFieldLocalSteer &steer, const mm::Vec3 &position) {
  if (navi.unknown00.isValid() && navi.unknown28.isValid() && navi.unknown80 && steer.unknown00 != INVALID_HANDLE && steer.unknown20) {
    f32 dx = navi.unknown90.x - position.x;
    f32 dy = navi.unknown90.y - position.y;
    f32 dz = navi.unknown90.z - position.z;
    if (sqrtf(dx * dx + dy * dy + dz * dz) < steer.unknown08) {
      navi.updateNextPos();
    }
  }
}

} // namespace gf
