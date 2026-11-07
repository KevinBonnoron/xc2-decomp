#include "mm_math/mm_obb.h"

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
