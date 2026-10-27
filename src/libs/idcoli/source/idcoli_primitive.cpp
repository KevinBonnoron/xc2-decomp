#include <math.h>
#include <string.h>

#include "idcoli/idcoli.h"
#include "idcoli/idcoli_util_coli.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace idcoli {

// Inferred helper: length of the sum of the matrix axes; original name unknown.
static f32 unknown001(const mm::Mat44 &matrix) {
  f32 x = matrix.rows[0][0] + matrix.rows[1][0] + matrix.rows[2][0];
  f32 y = matrix.rows[0][1] + matrix.rows[1][1] + matrix.rows[2][1];
  f32 z = matrix.rows[0][2] + matrix.rows[1][2] + matrix.rows[2][2];
  return sqrtf(x * x + y * y + z * z);
}

void IDColiInputUtil::calcTreeAABB(IDColiInput &input, const mm::Vec3 &max, const mm::Vec3 &min) {
  input.unknowna4[0] = static_cast<s16>(ceilf(max.x));
  input.unknowna4[1] = static_cast<s16>(ceilf(max.y));
  input.unknowna4[2] = static_cast<s16>(ceilf(max.z));
  input.unknowna4[3] = static_cast<s16>(floorf(min.x));
  input.unknowna4[4] = static_cast<s16>(floorf(min.y));
  input.unknowna4[5] = static_cast<s16>(floorf(min.z));
}

void IDColiPrimitive::createLine(CLLineWork &line, const IDColiInput &input) {
  line.unknown00 = input.unknown70;
  line.unknown10 = input.unknown80;
  line.unknown20 = input.unknown30;
  line.unknown40 = input.unknown00;
  line.unknown50 = input.unknown10;
  line.unknown64 = input.unknown98;
  if (input.unknown98 > 0.0001f) {
    f32 inverse = 1.0f / line.unknown64;
    line.unknown30 = line.unknown20 * inverse;
  } else {
    line.unknown30.y = 1.0f;
    line.unknown30.x = 0.0f;
  }
  line.unknown60 = line.unknown20.x * line.unknown20.x + line.unknown20.y * line.unknown20.y + line.unknown20.z * line.unknown20.z;
}

void IDColiInputUtil::getSphere(IDColiInput &input, const mm::Vec3 &center, f32 radius, bool isTree) {
  input.unknown20 = center;
  input.unknown90 = radius;
  input.unknown94 = radius * radius;
  input.unknowna0 = 0.0f;
  input.unknown00.x = center.x + radius;
  input.unknown00.y = center.y + radius;
  input.unknown00.z = center.z + radius;
  input.unknown10.x = center.x - radius;
  input.unknown10.y = center.y - radius;
  input.unknown10.z = center.z - radius;
  calcTreeAABB(input, input.unknown00, input.unknown10);
  input.sphere.unknown00 = input.unknown20;
  input.sphere.unknown10 = radius;
}

void IDColiPrimitive::createSphere(CLSphereWork &sphere, const IDColiInput &input) {
  sphere.unknown00 = input.unknown20;
  sphere.unknown10 = input.unknown90;
}

void IDColiInputUtil::getSphere(IDColiInput &input, const IDColiInput &source, const IDCmfPosData *posData, bool isTree) {
  mm::Vec3 center = posData->unknown011(source.unknown20);
  f32 scaledRadius = posData->unknown012() * IDColiObj::OBJ_CALC_RADIUS;
  getSphere(input, center, source.unknown90 * scaledRadius, false);
  input.unknowna0 = source.unknowna0;
}

void IDColiPrimitive::createCapsule(CLCapsuleWork &capsule, const IDColiInput &input) {
  capsule.unknown00 = input.unknown70;
  capsule.unknown10 = input.unknown80;
  capsule.unknown20 = input.unknown30;
  capsule.unknown50 = input.unknown90;
  f32 lengthSq = capsule.unknown20.x * capsule.unknown20.x + capsule.unknown20.y * capsule.unknown20.y + capsule.unknown20.z * capsule.unknown20.z;
  capsule.unknown54 = lengthSq;
  capsule.unknown58 = 1.0f / lengthSq;
  capsule.unknown30 = input.unknown00;
  capsule.unknown40 = input.unknown10;
}

void IDColiInputUtil::getAaBb(IDColiInput &input, const mm::Vec3 &max, const mm::Vec3 &min) {
  input.unknown00 = max;
  input.unknown10 = min;
  input.unknowna0 = 0.0f;
  calcTreeAABB(input, input.unknown00, input.unknown10);
}

void IDColiInputUtil::getBox(IDColiInput &input, const CLBoxWork &box) {
  memcpy(&input.box, &box, sizeof(CLBoxWork));
  input.unknown00 = box.unknown80;
  input.unknown10 = box.unknown90;
  input.unknowna0 = 0.0f;
  calcTreeAABB(input, box.unknown80, box.unknown90);
}

void IDColiPrimitive::createBaseSphere(void *data, IDColiBaseType &type, const mm::Mat44 &matrix, const mm::Vec3 &size) {
  CLSphereWork *sphere = static_cast<CLSphereWork *>(data);
  type = IDColiBaseType_UNKNOWN_0;
  f32 scale = unknown001(matrix);
  f32 radius = scale * IDColiObj::OBJ_CALC_RADIUS;
  sphere->unknown10 = size.x * radius;
  sphere->unknown00 = mm::Vec3(matrix.rows[3][0], matrix.rows[3][1], matrix.rows[3][2]);
}

void IDColiPrimitive::createBaseBox(void *data, IDColiBaseType &type, const mm::Mat44 &matrix, const mm::Vec3 &size) {
  calcBaseBoxSetup(static_cast<CLBoxWork *>(data), matrix, size);
  type = IDColiBaseType_UNKNOWN_1;
}

void IDColiPrimitive::createAaBbBox(mm::Vec3 &max, mm::Vec3 &min, const void *data) {
  const CLBoxWork *box = static_cast<const CLBoxWork *>(data);
  if (max.x < box->unknown80.x) {
    max.x = box->unknown80.x;
  }
  if (min.x > box->unknown90.x) {
    min.x = box->unknown90.x;
  }
  if (max.y < box->unknown80.y) {
    max.y = box->unknown80.y;
  }
  if (min.y > box->unknown90.y) {
    min.y = box->unknown90.y;
  }
  if (max.z < box->unknown80.z) {
    max.z = box->unknown80.z;
  }
  if (min.z > box->unknown90.z) {
    min.z = box->unknown90.z;
  }
}

void IDColiPrimitive::createAaBbCapsule(mm::Vec3 &max, mm::Vec3 &min, const void *data) {
  const CLCapsuleWork *capsule = static_cast<const CLCapsuleWork *>(data);
  if (max.x < capsule->unknown30.x) {
    max.x = capsule->unknown30.x;
  }
  if (min.x > capsule->unknown40.x) {
    min.x = capsule->unknown40.x;
  }
  if (max.y < capsule->unknown30.y) {
    max.y = capsule->unknown30.y;
  }
  if (min.y > capsule->unknown40.y) {
    min.y = capsule->unknown40.y;
  }
  if (max.z < capsule->unknown30.z) {
    max.z = capsule->unknown30.z;
  }
  if (min.z > capsule->unknown40.z) {
    min.z = capsule->unknown40.z;
  }
}

void IDColiPrimitive::createAaBbPoli(mm::Vec3 &max, mm::Vec3 &min, const void *data) {}

void IDColiPrimitive::createBaPosSphere(mm::Vec3 &position, mm::Vec3 &unknown, bool &isRotate, f32 &radius, f32 &length, const void *data) {
  const CLSphereWork *sphere = static_cast<const CLSphereWork *>(data);
  position = sphere->unknown00;
  radius = sphere->unknown10;
  length = sphere->unknown10 + sphere->unknown10;
  isRotate = false;
  unknown = mm::Vec3(0.0f, 0.0f, 0.0f);
}

void IDColiPrimitive::createBaPosBox(mm::Vec3 &position, mm::Vec3 &unknown, bool &isRotate, f32 &radius, f32 &length, const void *data) {
  const CLBoxWork *box = static_cast<const CLBoxWork *>(data);
  position = box->unknown60;
  radius = box->unknown70.x;
  length = box->unknown70.y;
  isRotate = false;
  unknown = mm::Vec3(0.0f, 0.0f, 0.0f);
}

void IDColiPrimitive::createBaPosCapsule(mm::Vec3 &position, mm::Vec3 &unknown, bool &isRotate, f32 &radius, f32 &length, const void *data) {
  const CLCapsuleWork *capsule = static_cast<const CLCapsuleWork *>(data);
  position = capsule->unknown00;
  radius = capsule->unknown50;
  length = sqrtf(capsule->unknown54) + (radius + radius);
  isRotate = true;
  unknown = capsule->unknown20;
}

void IDColiPrimitive::createBaPosPoli(mm::Vec3 &position, mm::Vec3 &unknown, bool &isRotate, f32 &radius, f32 &length, const void *data) {
  const IDCmfPosData *poli = static_cast<const unknown010 *>(data)->unknown00;
  position = mm::Vec3(poli->unknown00[0][3], poli->unknown00[1][3], poli->unknown00[2][3]);
  radius = (poli->unknown80.x - poli->unknown90.x) * 0.5f;
  length = radius + radius;
  isRotate = false;
  unknown = mm::Vec3(0.0f, 0.0f, 0.0f);
}

void IDColiPrimitive::createLine(CLLineWork &line, const mm::Vec3 &start, const mm::Vec3 &end) {
  line.unknown00 = start;
  line.unknown10 = end;
  if (start.x > end.x) {
    line.unknown40.x = start.x;
    line.unknown50.x = end.x;
  } else {
    line.unknown40.x = end.x;
    line.unknown50.x = start.x;
  }
  if (start.y > end.y) {
    line.unknown40.y = start.y;
    line.unknown50.y = end.y;
  } else {
    line.unknown40.y = end.y;
    line.unknown50.y = start.y;
  }
  if (start.z > end.z) {
    line.unknown40.z = start.z;
    line.unknown50.z = end.z;
  } else {
    line.unknown40.z = end.z;
    line.unknown50.z = start.z;
  }
  line.unknown20.x = end.x - start.x;
  line.unknown20.y = end.y - start.y;
  line.unknown20.z = end.z - start.z;
  f32 length = sqrtf(line.unknown20.x * line.unknown20.x + line.unknown20.y * line.unknown20.y + line.unknown20.z * line.unknown20.z);
  line.unknown60 = line.unknown20.x * line.unknown20.x + line.unknown20.y * line.unknown20.y + line.unknown20.z * line.unknown20.z;
  line.unknown64 = length;
  f32 inverse = 1.0f / length;
  line.unknown30.x = inverse * line.unknown20.x;
  line.unknown30.y = inverse * line.unknown20.y;
  line.unknown30.z = inverse * line.unknown20.z;
}

void IDColiPrimitive::createSphere(CLSphereWork &sphere, const mm::Vec3 &center, f32 radius) {
  sphere.unknown00 = center;
  sphere.unknown10 = radius;
}

} // namespace idcoli
