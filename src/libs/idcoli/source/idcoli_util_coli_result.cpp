#include "idcoli/idcoli_util_coli.h"

namespace idcoli {
class IDColiResult;

bool IDColiUtilColiResult::isSpherePoli(IDColiResult &result, const IDColiInput &input, const void *data) { return false; }

bool IDColiUtilColiResult::isCapsulePoli(IDColiResult &result, const IDColiInput &input, const void *data) { return false; }

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
