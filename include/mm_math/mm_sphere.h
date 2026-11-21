#pragma once
#include "mm/mm_std_base.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_prim_base.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace mm {

struct Line2;

class Sphere : public PrimBase {
public:
  Sphere(const Mat44 &matrix) : PrimBase(PRIM_SPHERE) {
    pos = Vec3(matrix.rows[3][0], matrix.rows[3][1], matrix.rows[3][2]);
    unknown004(rot, matrix);
    scale = Vec3(1.0f, 1.0f, 1.0f);
  }
  void getOBB(Obb &obb) const override;
  void getAABB(Aabb &aabb) const override;
  bool isCross(const Line2 &line) const;
  u32 getCross(Vec3 &first, Vec3 &second, const Line2 &line) const;
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
