#include <math.h>

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

bool IDColiUtilColiSimple::isSphereInBox(IDColiResult &result, const IDColiInput &input, const void *data) {
  const CLBoxWork *box = static_cast<const CLBoxWork *>(data);
  const CLSphereWork &sphere = input.sphere;
  if (box->unknown80.x + sphere.unknown10 < sphere.unknown00.x || box->unknown90.x - sphere.unknown10 > sphere.unknown00.x) {
    return false;
  }
  if (box->unknown80.z + sphere.unknown10 < sphere.unknown00.z || box->unknown90.z - sphere.unknown10 > sphere.unknown00.z) {
    return false;
  }
  if (box->unknown80.y + sphere.unknown10 < sphere.unknown00.y || box->unknown90.y - sphere.unknown10 > sphere.unknown00.y) {
    return false;
  }

  mm::Vec3 delta = sphere.unknown00 - box->unknown60;
  mm::Vec3 local(delta.x * box->unknown30.x + delta.y * box->unknown30.y + delta.z * box->unknown30.z,
                 delta.x * box->unknown40.x + delta.y * box->unknown40.y + delta.z * box->unknown40.z,
                 delta.x * box->unknown50.x + delta.y * box->unknown50.y + delta.z * box->unknown50.z);
  const f32 *halfSize = &box->unknown70.x;
  const f32 *value = &local.x;
  mm::Vec3 near;
  f32 *nearValue = &near.x;
  for (s32 i = 0; i < 3; i++) {
    if (halfSize[i] < value[i] || -halfSize[i] > value[i]) {
      return false;
    }
    nearValue[i] = value[i] < 0.0f ? -halfSize[i] : halfSize[i];
  }

  f32 radius = sphere.unknown10 * box->unknowna4;
  f32 radiusSq = radius * radius;
  bool isHit = false;
  mm::Vec3 normal;
  mm::Vec3 point;
  for (s32 i = 0; i < 3; i++) {
    point = local;
    (&point.x)[i] = nearValue[i];
    normal = local - point;
    f32 lengthSq = normal.x * normal.x + normal.y * normal.y + normal.z * normal.z;
    if (radiusSq < lengthSq) {
      continue;
    }
    if (lengthSq > 0.000001f) {
      isHit = true;
      break;
    }
  }
  if (!isHit) {
    return false;
  }

  return result.unknown001();
}

bool IDColiUtilColiSimple::isSphereCapsule(IDColiResult &result, const IDColiInput &input, const void *data) {
  const CLCapsuleWork *capsule = static_cast<const CLCapsuleWork *>(data);
  const CLSphereWork &sphere = input.sphere;
  if (capsule->unknown30.x + sphere.unknown10 < sphere.unknown00.x || capsule->unknown40.x - sphere.unknown10 > sphere.unknown00.x) {
    return false;
  }
  if (capsule->unknown30.z + sphere.unknown10 < sphere.unknown00.z || capsule->unknown40.z - sphere.unknown10 > sphere.unknown00.z) {
    return false;
  }
  if (capsule->unknown30.y + sphere.unknown10 < sphere.unknown00.y || capsule->unknown40.y - sphere.unknown10 > sphere.unknown00.y) {
    return false;
  }

  mm::Vec3 delta = sphere.unknown00 - capsule->unknown00;
  f32 rate = (delta.x * capsule->unknown20.x + delta.y * capsule->unknown20.y + delta.z * capsule->unknown20.z) * capsule->unknown58;
  if (rate < 0.0f) {
    rate = 0.0f;
  }
  if (rate > 1.0f) {
    rate = 1.0f;
  }
  mm::Vec3 normal = delta - capsule->unknown20 * rate;
  f32 range = sphere.unknown10 + capsule->unknown50;
  if (normal.x * normal.x + normal.y * normal.y + normal.z * normal.z > range * range) {
    return false;
  }

  return result.unknown001();
}

bool IDColiUtilColiSimple::isSphereInCapsule(IDColiResult &result, const IDColiInput &input, const void *data) {
  const CLCapsuleWork *capsule = static_cast<const CLCapsuleWork *>(data);
  const mm::Vec3 &center = input.sphere.unknown00;
  const f32 &radius = input.sphere.unknown10;
  if (capsule->unknown30.x + radius < center.x || capsule->unknown40.x - radius > center.x) {
    return false;
  }
  if (capsule->unknown30.z + radius < center.z || capsule->unknown40.z - radius > center.z) {
    return false;
  }
  if (capsule->unknown30.y + radius < center.y || capsule->unknown40.y - radius > center.y) {
    return false;
  }

  mm::Vec3 delta = center - capsule->unknown00;
  f32 rate = (delta.x * capsule->unknown20.x + delta.y * capsule->unknown20.y + delta.z * capsule->unknown20.z) * capsule->unknown58;
  if (rate < 0.0f) {
    rate = 0.0f;
  }
  if (rate > 1.0f) {
    rate = 1.0f;
  }
  mm::Vec3 offset = capsule->unknown20 * rate;
  mm::Vec3 normal = delta - offset;
  f32 lengthSq = normal.x * normal.x + normal.y * normal.y + normal.z * normal.z;
  if (lengthSq > capsule->unknown50 * capsule->unknown50 || lengthSq <= 0.000001f) {
    return false;
  }

  f32 inverse = 1.0f / sqrtf(lengthSq);
  mm::Vec3 surface = offset + normal * inverse * capsule->unknown50 + capsule->unknown00;
  mm::Vec3 distance = center - surface;
  f32 distanceSq = distance.x * distance.x + distance.y * distance.y + distance.z * distance.z;
  f32 radiusSq = radius * radius;
  if (distanceSq <= 0.000001f || distanceSq > radiusSq) {
    return false;
  }

  return result.unknown001();
}

bool IDColiUtilColiSimple::isSpherePoli(IDColiResult &result, const IDColiInput &input, const void *data) { return false; }

bool IDColiUtilColiSimple::isCapsuleSphere(IDColiResult &result, const IDColiInput &input, const void *data) {
  const CLSphereWork *sphere = static_cast<const CLSphereWork *>(data);
  const CLCapsuleWork &capsule = input.capsule;
  if (capsule.unknown30.x + sphere->unknown10 < sphere->unknown00.x || capsule.unknown40.x - sphere->unknown10 > sphere->unknown00.x) {
    return false;
  }
  if (capsule.unknown30.z + sphere->unknown10 < sphere->unknown00.z || capsule.unknown40.z - sphere->unknown10 > sphere->unknown00.z) {
    return false;
  }
  if (capsule.unknown30.y + sphere->unknown10 < sphere->unknown00.y || capsule.unknown40.y - sphere->unknown10 > sphere->unknown00.y) {
    return false;
  }

  mm::Vec3 delta = sphere->unknown00 - capsule.unknown00;
  f32 rate = (delta.x * capsule.unknown20.x + delta.y * capsule.unknown20.y + delta.z * capsule.unknown20.z) * capsule.unknown58;
  if (rate < 0.0f) {
    rate = 0.0f;
  }
  if (rate > 1.0f) {
    rate = 1.0f;
  }
  mm::Vec3 normal = delta - capsule.unknown20 * rate;
  f32 range = sphere->unknown10 + capsule.unknown50;
  if (normal.x * normal.x + normal.y * normal.y + normal.z * normal.z > range * range) {
    return false;
  }

  return result.unknown001();
}

bool IDColiUtilColiSimple::isCapsuleBox(IDColiResult &result, const IDColiInput &input, const void *data) { return isCapsuleBox(result, &input.capsule, static_cast<const CLBoxWork *>(data)); }

bool IDColiUtilColiSimple::isCapsuleInBox(IDColiResult &result, const CLCapsuleWork *capsule, const CLBoxWork *box) {
  const f32 &radius = capsule->unknown50;
  const mm::Vec3 &center = capsule->unknown00.y > capsule->unknown10.y ? capsule->unknown10 : capsule->unknown00;
  if (box->unknown80.x + radius < center.x || box->unknown90.x - radius > center.x) {
    return false;
  }
  if (box->unknown80.z + radius < center.z || box->unknown90.z - radius > center.z) {
    return false;
  }
  if (box->unknown80.y + radius < center.y || box->unknown90.y - radius > center.y) {
    return false;
  }

  mm::Vec3 delta = center - box->unknown60;
  mm::Vec3 local(delta.x * box->unknown30.x + delta.y * box->unknown30.y + delta.z * box->unknown30.z,
                 delta.x * box->unknown40.x + delta.y * box->unknown40.y + delta.z * box->unknown40.z,
                 delta.x * box->unknown50.x + delta.y * box->unknown50.y + delta.z * box->unknown50.z);
  const f32 *halfSize = &box->unknown70.x;
  const f32 *value = &local.x;
  mm::Vec3 near;
  f32 *nearValue = &near.x;
  for (s32 i = 0; i < 3; i++) {
    if (halfSize[i] < value[i] || -halfSize[i] > value[i]) {
      return false;
    }
    nearValue[i] = value[i] < 0.0f ? -halfSize[i] : halfSize[i];
  }

  f32 scaledRadius = radius * box->unknowna4;
  f32 radiusSq = scaledRadius * scaledRadius;
  bool isHit = false;
  mm::Vec3 normal;
  mm::Vec3 point;
  for (s32 i = 0; i < 3; i++) {
    point = local;
    (&point.x)[i] = nearValue[i];
    normal = local - point;
    f32 lengthSq = normal.x * normal.x + normal.y * normal.y + normal.z * normal.z;
    if (radiusSq < lengthSq) {
      continue;
    }
    if (lengthSq > 0.000001f) {
      isHit = true;
      break;
    }
  }
  if (!isHit) {
    return false;
  }

  return result.unknown001();
}

bool IDColiUtilColiSimple::isCapsuleInBox(IDColiResult &result, const IDColiInput &input, const void *data) { return isCapsuleInBox(result, &input.capsule, static_cast<const CLBoxWork *>(data)); }

bool IDColiUtilColiSimple::isCapsuleCapsule(IDColiResult &result, const IDColiInput &input, const void *data) {
  const CLCapsuleWork *capsule = static_cast<const CLCapsuleWork *>(data);
  if (input.capsule.unknown30.x < capsule->unknown40.x || input.capsule.unknown40.x > capsule->unknown30.x) {
    return false;
  }
  if (input.capsule.unknown30.z < capsule->unknown40.z || input.capsule.unknown40.z > capsule->unknown30.z) {
    return false;
  }
  if (input.capsule.unknown30.y < capsule->unknown40.y || input.capsule.unknown40.y > capsule->unknown30.y) {
    return false;
  }

  mm::Vec3 near1;
  mm::Vec3 near2;
  IDColiUtilMath::getNearLineToLine(near1, near2, input.capsule.unknown00, input.capsule.unknown10, capsule->unknown00, capsule->unknown10);
  mm::Vec3 delta = near1 - near2;
  f32 range = input.capsule.unknown50 + capsule->unknown50;
  if (delta.x * delta.x + delta.y * delta.y + delta.z * delta.z > range * range) {
    return false;
  }

  return result.unknown001();
}

bool IDColiUtilColiSimple::isCapsuleInCapsule(IDColiResult &result, const IDColiInput &input, const void *data) {
  const CLCapsuleWork *capsule = static_cast<const CLCapsuleWork *>(data);
  const f32 &radius = input.capsule.unknown50;
  const mm::Vec3 &center = input.capsule.unknown00.y > input.capsule.unknown10.y ? input.capsule.unknown10 : input.capsule.unknown00;
  if (capsule->unknown30.x + radius < center.x || capsule->unknown40.x - radius > center.x) {
    return false;
  }
  if (capsule->unknown30.z + radius < center.z || capsule->unknown40.z - radius > center.z) {
    return false;
  }
  if (capsule->unknown30.y + radius < center.y || capsule->unknown40.y - radius > center.y) {
    return false;
  }

  mm::Vec3 delta = center - capsule->unknown00;
  f32 rate = (delta.x * capsule->unknown20.x + delta.y * capsule->unknown20.y + delta.z * capsule->unknown20.z) * capsule->unknown58;
  if (rate < 0.0f) {
    rate = 0.0f;
  }
  if (rate > 1.0f) {
    rate = 1.0f;
  }
  mm::Vec3 offset = capsule->unknown20 * rate;
  mm::Vec3 normal = delta - offset;
  f32 lengthSq = normal.x * normal.x + normal.y * normal.y + normal.z * normal.z;
  if (lengthSq > capsule->unknown50 * capsule->unknown50 || lengthSq <= 0.000001f) {
    return false;
  }

  f32 inverse = 1.0f / sqrtf(lengthSq);
  mm::Vec3 surface = offset + normal * inverse * capsule->unknown50 + capsule->unknown00;
  mm::Vec3 distance = center - surface;
  f32 distanceSq = distance.x * distance.x + distance.y * distance.y + distance.z * distance.z;
  f32 radiusSq = radius * radius;
  if (distanceSq <= 0.000001f || distanceSq > radiusSq) {
    return false;
  }

  return result.unknown001();
}

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

bool IDColiUtilColiSimple::isPartsLineSphere(IDColiResult &result, const CLLineWork *line, const void *data) {
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

  return result.unknown001();
}

bool IDColiUtilColiSimple::isLineSphere(IDColiResult &result, const IDColiInput &input, const void *data) { return isPartsLineSphere(result, &input.line, data); }

bool IDColiUtilColiSimple::isRaySphere(IDColiResult &result, const IDColiInput &input, const void *data) {
  if (isPartsLineSphere(result, &input.ray.unknown00[0], data)) {
    return true;
  }
  return isPartsLineSphere(result, &input.ray.unknown00[1], data);
}

} // namespace idcoli
