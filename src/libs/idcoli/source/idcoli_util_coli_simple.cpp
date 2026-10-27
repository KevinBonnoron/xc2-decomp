#include "idcoli/idcoli_util_coli.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace idcoli {

bool IDColiUtilColiSimple::isSphereSphere(IDColiResult &result, const IDColiInput &input, const void *data) {
  const CLSphereWork *sphere = static_cast<const CLSphereWork *>(data);
  f32 x = input.sphere.unknown00.x - sphere->unknown00.x;
  f32 y = input.sphere.unknown00.y - sphere->unknown00.y;
  f32 z = input.sphere.unknown00.z - sphere->unknown00.z;
  f32 radius = input.sphere.unknown10 + sphere->unknown10;
  if (x * x + y * y + z * z > radius * radius) {
    return false;
  }

  return result.unknown001();
}

bool IDColiUtilColiSimple::isSphereBox(IDColiResult &result, const IDColiInput &input, const void *data) { return isSphereBox(result, &input.sphere, static_cast<const CLBoxWork *>(data)); }

bool IDColiUtilColiSimple::isSpherePoli(IDColiResult &result, const IDColiInput &input, const void *data) { return false; }

bool IDColiUtilColiSimple::isCapsuleBox(IDColiResult &result, const IDColiInput &input, const void *data) { return isCapsuleBox(result, &input.capsule, static_cast<const CLBoxWork *>(data)); }

bool IDColiUtilColiSimple::isCapsuleInBox(IDColiResult &result, const IDColiInput &input, const void *data) { return isCapsuleInBox(result, &input.capsule, static_cast<const CLBoxWork *>(data)); }

bool IDColiUtilColiSimple::isCapsulePoli(IDColiResult &result, const IDColiInput &input, const void *data) { return false; }

bool IDColiUtilColiSimple::isBoxSphere(IDColiResult &result, const IDColiInput &input, const void *data) { return isSphereBox(result, static_cast<const CLSphereWork *>(data), input.getBox()); }

bool IDColiUtilColiSimple::isBoxBox(IDColiResult &result, const IDColiInput &input, const void *data) { return false; }

bool IDColiUtilColiSimple::isBoxCapsule(IDColiResult &result, const IDColiInput &input, const void *data) { return isCapsuleBox(result, static_cast<const CLCapsuleWork *>(data), input.getBox()); }

bool IDColiUtilColiSimple::isBoxPoli(IDColiResult &result, const IDColiInput &input, const void *data) { return false; }

bool IDColiUtilColiSimple::isLineBox(IDColiResult &result, const IDColiInput &input, const void *data) { return isPartsLineBox(result, &input.line, data, false); }

bool IDColiUtilColiSimple::isLineCapsule(IDColiResult &result, const IDColiInput &input, const void *data) { return isPartsLineCapsule(result, &input.line, data, false); }

bool IDColiUtilColiSimple::isLinePoli(IDColiResult &result, const IDColiInput &input, const void *data) { return false; }

bool IDColiUtilColiSimple::isLineInBox(IDColiResult &result, const IDColiInput &input, const void *data) { return isPartsLineBox(result, &input.line, data, true); }

bool IDColiUtilColiSimple::isLineInCapsule(IDColiResult &result, const IDColiInput &input, const void *data) { return isPartsLineCapsule(result, &input.line, data, false); }

bool IDColiUtilColiSimple::isRayBox(IDColiResult &result, const IDColiInput &input, const void *data) {
  if (isPartsLineBox(result, &input.ray.unknown00[0], data, false)) {
    return true;
  }
  return isPartsLineBox(result, &input.ray.unknown00[1], data, false);
}

bool IDColiUtilColiSimple::isRayInBox(IDColiResult &result, const IDColiInput &input, const void *data) {
  if (isPartsLineBox(result, &input.ray.unknown00[0], data, true)) {
    return true;
  }
  return isPartsLineBox(result, &input.ray.unknown00[1], data, true);
}

bool IDColiUtilColiSimple::isRayCapsule(IDColiResult &result, const IDColiInput &input, const void *data) {
  if (isPartsLineCapsule(result, &input.ray.unknown00[0], data, false)) {
    return true;
  }
  return isPartsLineCapsule(result, &input.ray.unknown00[1], data, false);
}

bool IDColiUtilColiSimple::isRayInCapsule(IDColiResult &result, const IDColiInput &input, const void *data) {
  if (isPartsLineCapsule(result, &input.ray.unknown00[0], data, true)) {
    return true;
  }
  return isPartsLineCapsule(result, &input.ray.unknown00[1], data, true);
}

bool IDColiUtilColiSimple::isRayPoli(IDColiResult &result, const IDColiInput &input, const void *data) { return false; }

} // namespace idcoli
