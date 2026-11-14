#include "mm_math/mm_obb.h"

#include "mm_math/mm_line.h"
#include "mm_math/mm_line2.h"
#include "mm_math/mm_plane.h"
#include "mm_math/mm_sphere.h"

namespace mm {

Obb::Obb() : matrix(Mat44::identity), size(1.0f, 1.0f, 1.0f) {}

Obb::Obb(const Mat44 &matrix, const Vec3 &size) { setMat(matrix, size); }

Obb::Obb(const Vec3 &position, const Vec3 &axisX, const Vec3 &axisY, const Vec3 &axisZ, const Vec3 &size) {
  Vec3 trans = position;
  matrix.setTrans(trans);
  matrix.rows[0][0] = axisX.x;
  matrix.rows[0][1] = axisX.y;
  matrix.rows[0][2] = axisX.z;
  matrix.rows[1][0] = axisY.x;
  matrix.rows[1][1] = axisY.y;
  matrix.rows[1][2] = axisY.z;
  matrix.rows[2][0] = axisZ.x;
  matrix.rows[2][1] = axisZ.y;
  matrix.rows[2][2] = axisZ.z;
  this->size = size;
}

Obb::Obb(const Vec3 *vertices, u32 count) { setVertices(vertices, count); }

Obb::Obb(const Obb &obb) { *this = obb; }

Obb &Obb::operator=(const Obb &obb) {
  matrix = obb.matrix;
  size = obb.size;
  return *this;
}

void Obb::setMat(const Mat44 &matrix, const Vec3 &size) {
  this->matrix = matrix;
  this->size = size;
}

u32 Obb::getCross(Vec3 &first, Vec3 &second, const Line2 &line) const {
  Line infinite;
  infinite.unknown00 = line.direction;
  infinite.unknown00.unknown001();
  infinite.unknown10 = line.end;
  if (!getCross(first, second, infinite)) {
    return 0;
  }
  Vec3 firstStart = line.start - first;
  Vec3 firstEnd = line.end - first;
  bool firstInner = firstStart.x * firstEnd.x + firstStart.y * firstEnd.y + firstStart.z * firstEnd.z < 0.0f;
  Vec3 secondStart = line.start - second;
  Vec3 secondEnd = line.end - second;
  bool secondInner = secondStart.x * secondEnd.x + secondStart.y * secondEnd.y + secondStart.z * secondEnd.z < 0.0f;
  if (!firstInner && secondInner) {
    first = second;
    return 1;
  }
  if (firstInner && !secondInner) {
    return 1;
  }
  return firstInner && secondInner ? 2 : 0;
}

bool Obb::isInner(const Vec3 &point) const {
  Plane planes[6];
  getPlane(planes);
  for (u32 i = 0; i < 6; i++) {
    if ((point.x * planes[i].normal.x + point.y * planes[i].normal.y + point.z * planes[i].normal.z) + planes[i].distance > 0.000001f) {
      return false;
    }
  }
  return true;
}

bool Obb::isInner(const Sphere &sphere) const {
  Plane planes[6];
  getPlane(planes);
  for (u32 i = 0; i < 6; i++) {
    const Vec3 &position = sphere.getPos();
    if ((position.x * planes[i].normal.x + position.y * planes[i].normal.y + position.z * planes[i].normal.z) + planes[i].distance > -sphere.scale.x) {
      return false;
    }
  }
  return true;
}

} // namespace mm
