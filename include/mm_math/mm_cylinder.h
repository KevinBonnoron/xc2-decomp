#pragma once
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_prim_base.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace mm {

class Cylinder : public PrimBase {
public:
  Cylinder(const Mat44 &matrix) : PrimBase(PRIM_CYLINDER) {
    pos = Vec3(matrix.rows[3][0], matrix.rows[3][1], matrix.rows[3][2]);
    unknown004(rot, matrix);
    scale = Vec3(1.0f, 1.0f, 1.0f);
  }
  void getOBB(Obb &obb) const override;
  void getAABB(Aabb &aabb) const override;
  bool isCollide(const PrimBase &prim) const override;
  static f32 getBaseRadius();
  bool isCollideCylinder(const PrimBase &prim) const;
  bool isCollideCube(const PrimBase &prim) const;
  bool isCollideSphere(const PrimBase &prim) const;
};

} // namespace mm
