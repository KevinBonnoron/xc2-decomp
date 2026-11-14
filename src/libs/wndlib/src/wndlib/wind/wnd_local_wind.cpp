// Original file name from the game string C:/Monolithsoft/BF2/prog/libs/wndlib/src/wndlib/wind/wnd_local_wind.cpp.
#include <math.h>

#include "mm/mm_std_base.h"
#include "mm_math/mm_vec3.h"
#include "types.h"
#include "wnd/wnd_object.h"
#include "wnd/wnd_probe.h" // IWYU pragma: keep
#include "wnd/wnd_shape.h"

namespace wnd {

LocalWind::LocalWind(const LocalWindCreateInfo &info) : WindObject(OBJECT_TYPE_UNKNOWN_0, info), unknown88(info.unknown14), unknown8c(info.unknown18), unknown90(info.unknown1c) {
  unknown98.unknown10 = this;
}

f32 LocalWind::calcDampingDistance(f32 distance) const {
  f32 ratio = (distance - unknown8c) / (unknown90 - unknown8c);
  f32 damping = 1.0f - ratio;
  return damping < 0.0f ? 0.0f : (damping > 1.0f ? 1.0f : damping);
}

void LocalWind::calcEffectiveWind(const mm::Vec3 &position, mm::Vec3 *wind) const {
  mm::Vec3 direction = mm::Vec3::zero;
  if (m_pShape != nullptr) {
    if (m_pShape->unknown0c == SHAPE_TYPE_UNKNOWN_0) {
      direction = position - unknown30.unknown00;
    } else {
      mm::MMStdBase::mmPrint("warning:");
      mm::MMStdBase::mmPrint("未対応な形状です");
#line 49
      MM_ASSERT(0);
    }
  }
  HitCache cache;
  cache.unknown08 = sqrtf(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
  if (!direction.unknown003()) {
    direction.unknown001();
  }
  cache.unknown10 = direction;
  calcEffectiveWindFormCache(cache, wind);
}

void LocalWind::calcEffectiveWindFormCache(const HitCache &cache, mm::Vec3 *wind) const {
  f32 damping = calcDampingDistance(cache.unknown08);
  *wind = cache.unknown10 * unknown88 * damping;
}

} // namespace wnd
