#include "mm_math/mm_obb.h"

namespace mm {

Obb::Obb() : matrix(Mat44::identity), size(1.0f, 1.0f, 1.0f) {}

Obb::Obb(const Mat44 &matrix, const Vec3 &size) : matrix(matrix), size(size) {}

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

Obb::Obb(const Obb &obb) : matrix(obb.matrix), size(obb.size) {}

Obb &Obb::operator=(const Obb &obb) {
  matrix = obb.matrix;
  size = obb.size;
  return *this;
}

void Obb::setMat(const Mat44 &matrix, const Vec3 &size) {
  this->matrix = matrix;
  this->size = size;
}

} // namespace mm
