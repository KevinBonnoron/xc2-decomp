#pragma once
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_prim_base.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace mm {

struct Line2;

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

private:
  // Tests the 32 points of the top (or bottom) circle against the line segment (distance to the line <= radius and the foot between the
  // end points). Evidence: mm::Cylinder::chkCircleLine (1.0.0: 0x71009b29e4).
  static bool chkCircleLine(const Line2 &line, f32 radius, const Cylinder &cylinder, bool top);
};

} // namespace mm
