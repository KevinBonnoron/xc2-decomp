// Original file name from the game string .../wndlib/src/wndlib/collision/wnd_sphere_sphere_agent.cpp.
#include <math.h>

#include "mm/mm_std_base.h"
#include "mm_math/mm_vec3.h"
#include "types.h"
#include "wnd/wnd_dispatcher.h" // IWYU pragma: keep
#include "wnd/wnd_object.h"
#include "wnd/wnd_probe.h"
#include "wnd/wnd_shape.h"

namespace wnd {

void SphereSphereAgent::registerAgent(Dispatcher &dispatcher) { dispatcher.unknown10 = &SphereSphereAgent::processCollision; }

bool SphereSphereAgent::processCollision(const WindObject &wind0, const WindObject &wind1, f32 radius, HitCache *cache) {
  mm::Vec3 direction = wind0.unknown30.unknown00 - wind1.unknown30.unknown00;
  f32 distance = sqrtf(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
  const SphereShape *pShape0 = wind0.m_pShape != nullptr && wind0.m_pShape->unknown0c == SHAPE_TYPE_UNKNOWN_0 ? static_cast<const SphereShape *>(wind0.m_pShape) : nullptr;
#line 47
  MM_ASSERT(pShape0);
  const SphereShape *pShape1 = wind1.m_pShape != nullptr && wind1.m_pShape->unknown0c == SHAPE_TYPE_UNKNOWN_0 ? static_cast<const SphereShape *>(wind1.m_pShape) : nullptr;
  MM_ASSERT(pShape1);
  if (distance < pShape0->unknown10 + pShape1->unknown10 + radius) {
    cache->unknown00 = &wind1;
    cache->unknown08 = distance;
    if (!direction.unknown003()) {
      direction.unknown001();
    }
    cache->unknown10 = direction;
    return true;
  }
  return false;
}

} // namespace wnd
