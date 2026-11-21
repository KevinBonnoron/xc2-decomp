#pragma once
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_prim_base.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_array.h"
#include "types.h"

namespace mm {

struct Line2;
struct Plane;

class Cube : public PrimBase {
public:
  // Evidence: Cube, Cylinder and Sphere (const Mat44 &) 0x710070b918, 0x710070bc28, 0x710070be8c are identical but for the type and the vtable and are
  // not inlined into DRPRIM::flush: type, position from row 3 (ldr x/ldr w, lsr, stp, str), the quaternion of unknown004, unit scale.
  Cube(const Mat44 &matrix) : PrimBase(PRIM_CUBE) {
    pos = Vec3(matrix.rows[3][0], matrix.rows[3][1], matrix.rows[3][2]);
    unknown004(rot, matrix);
    scale = Vec3(1.0f, 1.0f, 1.0f);
  }

  static f32 m_fHalfLength;

  static f32 getHalfLength();
  static const Vec3 *getBaseVertices();
  static const Plane *getBasePlanes();
  static const Line2 *getBaseLines();
  void getVertices(mtl::FixedArray<Vec3, 8> &vertices) const;
  void getOBB(Obb &obb) const override;
  void getAABB(Aabb &aabb) const override;
  bool isCollide(const PrimBase &prim) const override;
  bool isCollideCube(const PrimBase &prim) const;
  bool isCollideSphere(const PrimBase &prim) const;
};

} // namespace mm
