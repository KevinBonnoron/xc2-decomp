#include "mm_math/mm_sphere.h"

#include "mm_math/mm_aabb.h"

namespace mm {

void Sphere::getAABB(Aabb &aabb) const {
  const Vec3 &position = getPos();
  f32 radius = scale.x;
  Vec3 max;
  max.x = radius + position.x;
  max.y = radius + position.y;
  max.z = radius + position.z;
  const Vec3 &center = getPos();
  radius = scale.x;
  Vec3 min;
  min.x = center.x - radius;
  min.y = center.y - radius;
  min.z = center.z - radius;
  aabb.set(max, min);
}

bool Sphere::isCollide(const PrimBase &prim) const {
  switch (prim.getType()) {
  case PRIM_CUBE:
    return prim.isCollide(*this);
  case PRIM_CYLINDER:
    return prim.isCollide(*this);
  case PRIM_SPHERE:
    return isCollideSphere(*this);
  }
  return false;
}

} // namespace mm
