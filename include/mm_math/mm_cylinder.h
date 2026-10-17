#pragma once
#include "mm_math/mm_prim_base.h"
#include "types.h"

namespace mm {

class Cylinder : public PrimBase {
public:
  void getOBB(Obb &obb) const override;
  void getAABB(Aabb &aabb) const override;
  bool isCollide(const PrimBase &prim) const override;
  static f32 getBaseRadius();
  bool isCollideCylinder(const PrimBase &prim) const;
  bool isCollideCube(const PrimBase &prim) const;
  bool isCollideSphere(const PrimBase &prim) const;
};

} // namespace mm
