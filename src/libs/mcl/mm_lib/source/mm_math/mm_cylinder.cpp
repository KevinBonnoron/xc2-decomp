#include "mm_math/mm_cylinder.h"

#include <math.h>

#include "mm_math/mm_line2.h"
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

void Cylinder::getAABB(Aabb &aabb) const {
  Obb obb;
  getOBB(obb);
  obb.getAABB(aabb);
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

namespace {

// Inferred role: distance along the direction of line from its start to the start of other; original name unknown.
// Internal linkage with reference parameters: the promotion of the arguments to scalars (before the function is inlined) makes the caller load
// the components of line.direction again at the call; the loads are then not merged with the loads of the entry (Reassociate puts the difference
// of the starts left of the direction in the products). A member of Vec3 or a function of external linkage merges them and swaps the operands.
// Forms tried for the same function: Vec3::unknown005 on a temporary difference (3 operand swaps), a helper returning the foot point, a helper
// taking the three vectors apart (different load order, register differences).
f32 unknown101(const Line2 &line, const Line2 &other) { return (other.start - line.start).unknown005(line.direction); }

// Inferred role: true when the point is within radius of the line and its foot lies between the end points; original name unknown.
// Evidence: inlined in mm::Cylinder::chkCircleLine (1.0.0: 0x71009b29e4). Internal linkage, like unknown101.
bool unknown102(const Line2 &line, const Vec3 &point, f32 radius) {
  Vec3 toPoint = point - line.start;
  Vec3 cross;
  cross.unknown004(line.direction, toPoint);
  if (sqrtf(cross.unknown005(cross)) <= radius) {
    f32 along = toPoint.unknown005(line.direction);
    Vec3 foot = line.direction * along + line.start;
    if ((line.start - foot).unknown005(line.end - foot) < 0.0f) {
      return true;
    }
  }
  return false;
}

} // namespace

u32 Line2::getNearest(const Line2 &line, const Line2 &other, f32 &length, Vec3 *position, Vec3 *otherPosition) {
  f32 dot = line.direction.unknown005(other.direction);
  if (fabsf(dot * dot - 1.0f) < 0.000001f) {
    f32 along = unknown101(line, other);
    Vec3 nearest = line.start + line.direction * along;
    if (position != nullptr) {
      position->x = nearest.x;
      position->y = nearest.y;
      position->z = nearest.z;
    }
    if (otherPosition != nullptr) {
      otherPosition->x = other.start.x;
      otherPosition->y = other.start.y;
      otherPosition->z = other.start.z;
    }
    Vec3 difference = other.start - nearest;
    length = sqrtf(difference.unknown005(difference));
    return 2;
  }
  f32 scale = 1.0f / (1.0f - dot * dot);
  f32 along = line.direction.unknown005(other.end - line.end);
  f32 otherAlong = other.direction.unknown005(line.end - other.end);
  f32 first = scale * (along + dot * otherAlong);
  f32 second = scale * (otherAlong + dot * along);
  Vec3 nearest = line.end + line.direction * first;
  Vec3 otherNearest = other.end + other.direction * second;
  Vec3 difference = nearest - otherNearest;
  length = sqrtf(difference.unknown005(difference));
  if (position != nullptr) {
    position->x = nearest.x;
    position->y = nearest.y;
    position->z = nearest.z;
  }
  if (otherPosition != nullptr) {
    otherPosition->x = otherNearest.x;
    otherPosition->y = otherNearest.y;
    otherPosition->z = otherNearest.z;
  }
  if ((nearest - line.start).unknown005(nearest - line.end) > 0.0f || (otherNearest - other.start).unknown005(otherNearest - other.end) > 0.0f) {
    return 1;
  }
  return 0;
}

// The 32 points of the circle are (sin, +-1, cos) of the multiples of 2 * pi / 32, tested after the transform by the matrix of the cylinder.
// The loop condition keeps the hit flag as its second operand: the IR then has the shared exit block (phi of the result) before the loop and the
// latch compares `icmp ugt i, 31` towards it, which gives the game's `cmp #31; b.ls`. With `return true` in the body the exit block follows the
// latch (IR-next), ISel inverts the branch and canonicalises it to `cmp #32; b.lo`; ~35 spellings of a `return` loop gave that.
bool Cylinder::chkCircleLine(const Line2 &line, f32 radius, const Cylinder &cylinder, bool top) {
  Mat44 matrix;
  cylinder.getMat(matrix);
  f32 height = top ? 1.0f : -1.0f;
  bool hit = false;
  for (u32 i = 0; i < 32 && !hit; i++) {
    f32 angle = i * 0.19634955f;
    f32 x = sinf(angle);
    f32 z = cosf(angle);
    if (unknown102(line, matrix.unknown023(Vec3(x, height, z)), radius)) {
      hit = true;
    }
  }
  return hit;
}

} // namespace mm
