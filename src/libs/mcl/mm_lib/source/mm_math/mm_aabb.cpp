#include "mm_math/mm_aabb.h"

#include "mm_mtl/fixed_array.h"

namespace mm {

Aabb::Aabb(const Vec3 &a, const Vec3 &b) { set(a, b); }

void Aabb::set(const Vec3 &a, const Vec3 &b) {
  min.x = a.x < b.x ? a.x : b.x;
  min.y = a.y < b.y ? a.y : b.y;
  min.z = a.z < b.z ? a.z : b.z;
  max.x = a.x > b.x ? a.x : b.x;
  max.y = a.y > b.y ? a.y : b.y;
  max.z = a.z > b.z ? a.z : b.z;
}

void Aabb::setExtend(const Vec3 &center, const Vec3 &corner) {
  Vec3 opposite(center.x + center.x - corner.x, center.y + center.y - corner.y, center.z + center.z - corner.z);
  set(opposite, corner);
}

void Aabb::apply(const Vec3 &point) {
  min.x = min.x < point.x ? min.x : point.x;
  min.y = min.y < point.y ? min.y : point.y;
  min.z = min.z < point.z ? min.z : point.z;
  max.x = max.x > point.x ? max.x : point.x;
  max.y = max.y > point.y ? max.y : point.y;
  max.z = max.z > point.z ? max.z : point.z;
}

void Aabb::add(const Vec3 &offset) {
  min += offset;
  max += offset;
}

void Aabb::sub(const Vec3 &offset) {
  min -= offset;
  max -= offset;
}

void Aabb::getVertices(mtl::FixedArray<Vec3, 8> &vertices) const {
  vertices[0] = Vec3(min.x, min.y, min.z);
  vertices[1] = Vec3(max.x, min.y, min.z);
  vertices[2] = Vec3(min.x, max.y, min.z);
  vertices[3] = Vec3(max.x, max.y, min.z);
  vertices[4] = Vec3(min.x, min.y, max.z);
  vertices[5] = Vec3(max.x, min.y, max.z);
  vertices[6] = Vec3(min.x, max.y, max.z);
  vertices[7] = Vec3(max.x, max.y, max.z);
}

Aabb &Aabb::operator+=(const Vec3 &offset) {
  add(offset);
  return *this;
}

Aabb &Aabb::operator-=(const Vec3 &offset) {
  sub(offset);
  return *this;
}

void Aabb::getCenter(Vec3 &center) const {
  center.x = min.x + max.x;
  center.y = min.y + max.y;
  center.z = min.z + max.z;
  center *= 0.5f;
}

} // namespace mm
