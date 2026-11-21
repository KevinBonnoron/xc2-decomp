// Original file name from the game string .../wndlib/src/wndlib/collision/wnd_sphere_box_agent.cpp.
#include <math.h>

#include "mm/mm_std_base.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_quat_impl_nx.h"
#include "mm_math/mm_vec3.h"
#include "types.h"
#include "wnd/wnd_dispatcher.h" // IWYU pragma: keep
#include "wnd/wnd_object.h"
#include "wnd/wnd_probe.h"
#include "wnd/wnd_shape.h"

namespace wnd {

void SphereBoxAgent::registerAgent(Dispatcher &dispatcher) { dispatcher.unknown18 = &SphereBoxAgent::processCollision; }

bool SphereBoxAgent::processCollision(const WindObject &wind0, const WindObject &wind1, f32 radius, HitCache *cache) {
  // The inverse and rotate must run before the shape asserts. The game loads the positions at
  // 0x710098add0-0x710098addc, and the rotate arithmetic sinks below the asserts when it moves after them.
  // Tried, none match: rotate after both asserts, rotate after the first assert, and `direction`
  // computed before the inverse.
  mm::Quat rotation = wind1.unknown30.unknown10;
  mm::Quat::inverse(rotation);
  mm::Vec3 direction = wind0.unknown30.unknown00 - wind1.unknown30.unknown00;
  mm::Vec3 local = rotation.rotate(direction);
  const SphereShape *pShape0 = wind0.m_pShape != nullptr && wind0.m_pShape->unknown0c == SHAPE_TYPE_UNKNOWN_0 ? static_cast<const SphereShape *>(wind0.m_pShape) : nullptr;
#line 51
  MM_ASSERT(pShape0);
  const BoxShape *pShape1 = wind1.m_pShape != nullptr && wind1.m_pShape->unknown0c == SHAPE_TYPE_UNKNOWN_1 ? static_cast<const BoxShape *>(wind1.m_pShape) : nullptr;
  MM_ASSERT(pShape1);
  f32 limitX = pShape0->unknown10 + pShape1->unknown10.x + radius;
  if (local.x < -limitX || local.x > limitX) {
    return false;
  }
  f32 limitY = pShape0->unknown10 + pShape1->unknown10.y + radius;
  if (local.y < -limitY || local.y > limitY) {
    return false;
  }
  f32 limitZ = pShape0->unknown10 + pShape1->unknown10.z + radius;
  if (local.z < -limitZ || local.z > limitZ) {
    return false;
  }
  // Repeats the tail of SphereSphereAgent::processCollision. This copy is at 0x710098afc4; the
  // original, in that function, is at 0x710098b18c. A shared helper breaks both functions. Tried by
  // value, by reference, and as a HitCache member.
  cache->unknown00 = &wind1;
  cache->unknown08 = sqrtf(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
  if (!direction.unknown003()) {
    direction.unknown001();
  }
  cache->unknown10 = direction;
  return true;
}

} // namespace wnd
