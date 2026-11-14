#include "ml/scn_util.h"

#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ml {

namespace {

// Inferred role: lifts a screen point to the z = 0 plane; original name unknown.
mm::Vec3 unknown001(const mm::Pnt<int> &point) { return mm::Vec3(point.x, point.y, 0.0f); }

} // namespace

bool ScnUtil::isCrossLine(const mm::Pnt<int> &a, const mm::Pnt<int> &b, const mm::Pnt<int> &c, const mm::Pnt<int> &d) {
  mm::Vec3 directionAB = unknown001(a) - unknown001(b);
  directionAB.unknown001();
  mm::Vec3 pointA = unknown001(a);
  mm::Vec3 directionCD = unknown001(c) - unknown001(d);
  directionCD.unknown001();
  mm::Vec3 pointC = unknown001(c);
  mm::Vec3 deltaC = pointC - pointA;
  f32 projectionC = directionAB.x * deltaC.x + directionAB.y * deltaC.y + directionAB.z * deltaC.z;
  mm::Vec3 sideC = pointC - (pointA + directionAB * projectionC);
  mm::Vec3 pointD = unknown001(d);
  mm::Vec3 deltaD = pointD - pointA;
  f32 projectionD = directionAB.x * deltaD.x + directionAB.y * deltaD.y + directionAB.z * deltaD.z;
  mm::Vec3 sideD = pointD - (pointA + directionAB * projectionD);
  if (sideC.x * sideD.x + sideC.y * sideD.y + sideC.z * sideD.z < 0.0f) {
    mm::Vec3 deltaA = unknown001(a) - pointC;
    f32 projectionA = directionCD.x * deltaA.x + directionCD.y * deltaA.y + directionCD.z * deltaA.z;
    mm::Vec3 sideA = unknown001(a) - (pointC + directionCD * projectionA);
    mm::Vec3 deltaB = unknown001(b) - pointC;
    f32 projectionB = directionCD.x * deltaB.x + directionCD.y * deltaB.y + directionCD.z * deltaB.z;
    mm::Vec3 sideB = unknown001(b) - (pointC + directionCD * projectionB);
    return sideA.x * sideB.x + sideA.y * sideB.y + sideA.z * sideB.z < 0.0f;
  }
  return false;
}

bool ScnUtil::checkLineRect(const mm::Vec3 &start, const mm::Vec3 &end, const mm::Rect<int> &rect) {
  mm::Pnt<int> startPos(start.x, start.y);
  mm::Pnt<int> endPos(end.x, end.y);
  if (startPos.x >= rect.x && startPos.x < rect.x + rect.width && startPos.y >= rect.y && startPos.y < rect.y + rect.height) {
    return true;
  }
  if (endPos.x >= rect.x && endPos.x < rect.x + rect.width && endPos.y >= rect.y && endPos.y < rect.y + rect.height) {
    return true;
  }
  if (isCrossLine(startPos, endPos, mm::Pnt<int>(rect.x, rect.y), mm::Pnt<int>(rect.x + rect.width, rect.y))) {
    return true;
  }
  if (isCrossLine(startPos, endPos, mm::Pnt<int>(rect.x + rect.width, rect.y), mm::Pnt<int>(rect.x + rect.width, rect.y + rect.height))) {
    return true;
  }
  if (isCrossLine(startPos, endPos, mm::Pnt<int>(rect.x, rect.y + rect.height), mm::Pnt<int>(rect.x + rect.width, rect.y + rect.height))) {
    return true;
  }
  return isCrossLine(startPos, endPos, mm::Pnt<int>(rect.x, rect.y), mm::Pnt<int>(rect.x, rect.y + rect.height));
}

} // namespace ml
