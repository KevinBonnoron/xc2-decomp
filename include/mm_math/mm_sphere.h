#pragma once
#include "mm/mm_std_base.h"
#include "mm_math/mm_prim_base.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace mm {

class Sphere : public PrimBase {
public:
  void getOBB(Obb &obb) const override;
  void getAABB(Aabb &aabb) const override;
  bool isCollide(const PrimBase &prim) const override;

  // __LINE__ must be 321 as in the original header: it is the line argument of the assert.
#line 319
  bool isCollideSphere(const PrimBase &prim) const {
    MM_ASSERT(prim.getType() == PRIM_SPHERE);
    const Vec3 &position = getPos();
    const Vec3 &otherPosition = prim.getPos();
    f32 dx = position.x - otherPosition.x;
    f32 dy = position.y - otherPosition.y;
    f32 dz = position.z - otherPosition.z;
    f32 distanceSq = dx * dx + dy * dy + dz * dz;
    f32 radius = scale.x + prim.scale.x;
    return distanceSq < radius * radius;
  }
#line 30
};

} // namespace mm
