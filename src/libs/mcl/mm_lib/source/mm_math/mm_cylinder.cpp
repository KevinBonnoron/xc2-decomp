#include "mm_math/mm_cylinder.h"

#include "mm_math/mm_mat44.h"
#include "mm_math/mm_obb.h"
#include "mm_math/mm_vec3.h"

namespace mm {

void Cylinder::getOBB(Obb &obb) const {
  Mat44 matrix;
  unknown001(matrix);
  Vec3 size;
  size.x = scale.x;
  size.y = scale.y;
  size.z = size.x;
  obb.setMat(matrix, size);
}

bool Cylinder::isCollide(const PrimBase &prim) const {
  switch (prim.type) {
  case PRIM_CYLINDER:
    return isCollideCylinder(prim);
  case PRIM_CUBE:
    return isCollideCube(prim);
  case PRIM_SPHERE:
    return isCollideSphere(prim);
  }
  return false;
}

f32 Cylinder::getBaseRadius() { return 1.0f; }

} // namespace mm
