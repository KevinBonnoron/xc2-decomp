#include <math.h>

#include "idcoli/idcoli_util_coli.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace idcoli {

s32 IDColiUtilColiResult::calcNearBoxPoint(mm::Vec3 &near, const CLBoxWork *box, const mm::Vec3 &point) {
  const f32 *halfSize = &box->unknown70.x;
  const f32 *value = &point.x;
  f32 *nearValue = &near.x;
  s32 count = 0;
  for (s32 i = 0; i < 3; i++) {
    if (halfSize[i] < value[i]) {
      nearValue[i] = halfSize[i];
    } else if (value[i] < -halfSize[i]) {
      nearValue[i] = -halfSize[i];
    } else {
      nearValue[i] = value[i];
      count++;
    }
  }
  return count;
}

void IDColiUtilColiResult::calcBoxInPoint(mm::Vec3 &normal, f32 &distance, const CLBoxWork *box, const mm::Vec3 &point, f32 radius) {
  const f32 *halfSize = &box->unknown70.x;
  const f32 *value = &point.x;
  f32 minDepth = 100000.0f;
  f32 sign = 1.0f;
  s32 index = 0;
  for (s32 i = 0; i < 3; i++) {
    f32 depth = halfSize[i] + (value[i] < 0.0f ? value[i] : -value[i]);
    if (minDepth > depth) {
      minDepth = depth;
      sign = value[i] < 0.0f ? -1.0f : 1.0f;
      index = i;
    }
  }
  normal = mm::Vec3(0.0f, 0.0f, 0.0f);
  (&normal.x)[index] = sign;
  distance = radius * 0.9f;
}

bool IDColiUtilColiResult::calcNearInBoxPoint(mm::Vec3 &near, const CLBoxWork *box, const mm::Vec3 &point, f32 range, f32 radius) {
  f32 margin = radius * 0.75f;
  const f32 *halfSize = &box->unknown70.x;
  const f32 *value = &point.x;
  f32 *nearValue = &near.x;
  for (s32 i = 0; i < 3; i++) {
    if (halfSize[i] + range < value[i] || -halfSize[i] - range > value[i]) {
      return false;
    }
    if (value[i] < 0.0f) {
      if (value[i] < -halfSize[i]) {
        nearValue[i] = value[i] - margin;
      } else {
        nearValue[i] = -halfSize[i];
      }
    } else if (halfSize[i] < value[i]) {
      nearValue[i] = value[i] + margin;
    } else {
      nearValue[i] = halfSize[i];
    }
  }
  return true;
}

bool IDColiUtilColiResult::isSpherePoli(IDColiResult &result, const IDColiInput &input, const void *data) { return false; }

bool IDColiUtilColiResult::isCapsulePoli(IDColiResult &result, const IDColiInput &input, const void *data) { return false; }

bool IDColiUtilColiResult::isPartsLineSphere(IDColiResult &result, const CLLineWork *line, const void *data, bool isBack) {
  const CLSphereWork *sphere = static_cast<const CLSphereWork *>(data);
  f32 x = line->unknown00.x - sphere->unknown00.x;
  f32 y = line->unknown00.y - sphere->unknown00.y;
  f32 z = line->unknown00.z - sphere->unknown00.z;
  f32 projection = x * line->unknown30.x + y * line->unknown30.y + z * line->unknown30.z;
  f32 distance = (x * x + y * y + z * z) - sphere->unknown10 * sphere->unknown10;
  if (0.0f <= projection && 0.0f <= distance) {
    return false;
  }
  f32 discriminant = projection * projection - distance;
  if (discriminant <= 0.0f) {
    return false;
  }
  f32 hit = -projection - sqrtf(discriminant);
  if (hit < 0.0f || line->unknown64 < hit) {
    return false;
  }

  IDColiCallArg arg;
  arg.unknown00 = line->unknown30 * hit;
  arg.unknown00 += line->unknown00;
  arg.unknown10.x = arg.unknown00.x - sphere->unknown00.x;
  arg.unknown10.y = arg.unknown00.y - sphere->unknown00.y;
  arg.unknown10.z = arg.unknown00.z - sphere->unknown00.z;
  f32 length = sqrtf(arg.unknown10.x * arg.unknown10.x + arg.unknown10.y * arg.unknown10.y + arg.unknown10.z * arg.unknown10.z);
  if (length <= 0.000001f) {
    arg.unknown10 = mm::Vec3::zero;
  } else {
    arg.unknown10 *= 1.0f / length;
  }
  setStockParms(result, arg, hit, isBack);
  return true;
}

bool IDColiUtilColiResult::isLineSphere(IDColiResult &result, const IDColiInput &input, const void *data) { return isPartsLineSphere(result, &input.line, data, false); }

bool IDColiUtilColiResult::isLineBox(IDColiResult &result, const IDColiInput &input, const void *data) { return isPartsLineBox(result, &input.line, data, false, false); }

bool IDColiUtilColiResult::isLineInBox(IDColiResult &result, const IDColiInput &input, const void *data) { return isPartsLineBox(result, &input.line, data, false, true); }

bool IDColiUtilColiResult::isLineCapsule(IDColiResult &result, const IDColiInput &input, const void *data) { return isPartsLineCapsule(result, &input.line, data, false, false); }

bool IDColiUtilColiResult::isLineInCapsule(IDColiResult &result, const IDColiInput &input, const void *data) { return isPartsLineCapsule(result, &input.line, data, false, true); }

bool IDColiUtilColiResult::isLinePoli(IDColiResult &result, const IDColiInput &input, const void *data) { return false; }

bool IDColiUtilColiResult::isRaySphere(IDColiResult &result, const IDColiInput &input, const void *data) {
  if (isPartsLineSphere(result, &input.ray.unknown00[0], data, false)) {
    return true;
  }
  return isPartsLineSphere(result, &input.ray.unknown00[1], data, true);
}

bool IDColiUtilColiResult::isRayBox(IDColiResult &result, const IDColiInput &input, const void *data) {
  if (isPartsLineBox(result, &input.ray.unknown00[0], data, false, false)) {
    return true;
  }
  return isPartsLineBox(result, &input.ray.unknown00[1], data, true, false);
}

bool IDColiUtilColiResult::isRayInBox(IDColiResult &result, const IDColiInput &input, const void *data) {
  if (isPartsLineBox(result, &input.ray.unknown00[0], data, false, true)) {
    return true;
  }
  return isPartsLineBox(result, &input.ray.unknown00[1], data, true, true);
}

bool IDColiUtilColiResult::isRayCapsule(IDColiResult &result, const IDColiInput &input, const void *data) {
  if (isPartsLineCapsule(result, &input.ray.unknown00[0], data, false, false)) {
    return true;
  }
  return isPartsLineCapsule(result, &input.ray.unknown00[1], data, true, false);
}

bool IDColiUtilColiResult::isRayInCapsule(IDColiResult &result, const IDColiInput &input, const void *data) {
  if (isPartsLineCapsule(result, &input.ray.unknown00[0], data, false, true)) {
    return true;
  }
  return isPartsLineCapsule(result, &input.ray.unknown00[1], data, true, true);
}

bool IDColiUtilColiResult::isRayPoli(IDColiResult &result, const IDColiInput &input, const void *data) { return false; }

} // namespace idcoli

// Same order as in the game executable.
// clang-format off
#include "idcoli_util_coli_simple.cpp"
#include "idcoli_primitive.cpp"
// clang-format on
