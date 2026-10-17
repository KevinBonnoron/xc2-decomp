#pragma once
#include "mm_math/mm_prim_base.h"
#include "types.h"

namespace mm {

struct Line2;
struct Plane;
struct Vec3;

class Cube : public PrimBase {
public:
  static f32 m_fHalfLength;

  static f32 getHalfLength();
  static const Vec3 *getBaseVertices();
  static const Plane *getBasePlanes();
  static const Line2 *getBaseLines();
  void getOBB(Obb &obb) const override;
  void getAABB(Aabb &aabb) const override;
  bool isCollide(const PrimBase &prim) const override;
  bool isCollideCube(const PrimBase &prim) const;
  bool isCollideSphere(const PrimBase &prim) const;
};

} // namespace mm
