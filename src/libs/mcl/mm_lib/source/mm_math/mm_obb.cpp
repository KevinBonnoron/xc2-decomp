#include "mm_math/mm_obb.h"

#include <math.h>

#include "mm_math/mm_line.h"
#include "mm_math/mm_line2.h"
#include "mm_math/mm_plane.h"
#include "mm_math/mm_sphere.h"

namespace mm {

bool Sphere::isCross(const Line2 &line) const {
  Vec3 toStart = getPos() - line.start;
  f32 normalX = toStart.y * line.direction.z - toStart.z * line.direction.y;
  f32 normalY = toStart.z * line.direction.x - toStart.x * line.direction.z;
  f32 normalZ = toStart.x * line.direction.y - toStart.y * line.direction.x;
  if (sqrtf(normalX * normalX + normalY * normalY + normalZ * normalZ) > scale.x + 0.000001f) {
    return false;
  }
  Vec3 toEnd = getPos() - line.end;
  // getPos() is virtual and the game calls it twice for the end delta (blr at 0x71009b589c, the deltas kept in registers, then at 0x71009b58c8 for
  // the dot product); with one shared delta vector the same lines of getCross give 224 instructions against the game's 239.
  Vec3 toEnd2 = getPos() - line.end;
  f32 along = toEnd2.x * line.direction.x + toEnd2.y * line.direction.y + toEnd2.z * line.direction.z;
  f32 distance = sqrtf(toEnd.x * toEnd.x + toEnd.y * toEnd.y + toEnd.z * toEnd.z);
  if (distance - along < 0.000001f) {
    return false;
  }
  f32 height = sqrtf(distance * distance - along * along);
  if (scale.x - height < 0.000001f) {
    return false;
  }
  f32 half = sqrtf(scale.x * scale.x - height * height);
  Vec3 point = line.direction * (along - half) + line.end;
  Vec3 startOffset = line.start - getPos();
  f32 startDistance = startOffset.x * startOffset.x + startOffset.y * startOffset.y + startOffset.z * startOffset.z;
  bool startInner = startDistance < scale.x * scale.x;
  Vec3 endOffset = line.end - getPos();
  f32 endDistance = endOffset.x * endOffset.x + endOffset.y * endOffset.y + endOffset.z * endOffset.z;
  bool endInner = endDistance < scale.x * scale.x;
  if (startInner && endInner) {
    return false;
  }
  if (startInner != endInner) {
    return true;
  }
  Vec3 pointStart = line.start - point;
  Vec3 pointEnd = line.end - point;
  return pointEnd.x * pointStart.x + pointEnd.y * pointStart.y + pointEnd.z * pointStart.z <= 0.0f;
}

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

u32 Sphere::getCross(Vec3 &first, Vec3 &second, const Line2 &line) const {
  Vec3 toStart = getPos() - line.start;
  f32 normalX = toStart.y * line.direction.z - toStart.z * line.direction.y;
  f32 normalY = toStart.z * line.direction.x - toStart.x * line.direction.z;
  f32 normalZ = toStart.x * line.direction.y - toStart.y * line.direction.x;
  if (sqrtf(normalX * normalX + normalY * normalY + normalZ * normalZ) > scale.x + 0.000001f) {
    return 0;
  }
  Vec3 toEnd = getPos() - line.end;
  // Second getPos() call of the game (0x71009b7f08), see isCross.
  Vec3 toEnd2 = getPos() - line.end;
  f32 along = toEnd2.x * line.direction.x + toEnd2.y * line.direction.y + toEnd2.z * line.direction.z;
  f32 distance = sqrtf(toEnd.x * toEnd.x + toEnd.y * toEnd.y + toEnd.z * toEnd.z);
  if (distance - along < 0.000001f) {
    return 0;
  }
  f32 height = sqrtf(distance * distance - along * along);
  if (scale.x - height < 0.000001f) {
    return 0;
  }
  f32 half = sqrtf(scale.x * scale.x - height * height);
  f32 nearStep = along - half;
  first.x = line.direction.x * nearStep;
  first.y = line.direction.y * nearStep;
  first.z = line.direction.z * nearStep;
  first += line.end;
  f32 farStep = along + half;
  second.x = line.direction.x * farStep;
  second.y = line.direction.y * farStep;
  second.z = line.direction.z * farStep;
  second += line.end;
  Vec3 startOffset = line.start - getPos();
  f32 startDistance = startOffset.x * startOffset.x + startOffset.y * startOffset.y + startOffset.z * startOffset.z;
  bool startInner = startDistance < scale.x * scale.x;
  Vec3 endOffset = line.end - getPos();
  f32 endDistance = endOffset.x * endOffset.x + endOffset.y * endOffset.y + endOffset.z * endOffset.z;
  bool endInner = endDistance < scale.x * scale.x;
  if (startInner && endInner) {
    return 0;
  }
  if (startInner && !endInner) {
    return 1;
  }
  if (!startInner && endInner) {
    first = second;
    return 1;
  }
  Vec3 firstStart = line.start - first;
  Vec3 firstEnd = line.end - first;
  return firstStart.x * firstEnd.x + firstStart.y * firstEnd.y + firstStart.z * firstEnd.z > 0.0f ? 0 : 2;
}

} // namespace mm
