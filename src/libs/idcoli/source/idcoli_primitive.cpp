#include <math.h>
#include <string.h>

#include "idcoli/idcoli.h"
#include "idcoli/idcoli_util_coli.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace idcoli {

void IDColiInputUtil::getLine(IDColiInput &input, const mm::Vec3 &start, const mm::Vec3 &end, bool isTree) {
  input.unknown70 = start;
  input.unknown80 = end;
  if (start.x > end.x) {
    input.unknown00.x = start.x;
    input.unknown10.x = end.x;
  } else {
    input.unknown00.x = end.x;
    input.unknown10.x = start.x;
  }
  if (start.y > end.y) {
    input.unknown00.y = start.y;
    input.unknown10.y = end.y;
  } else {
    input.unknown00.y = end.y;
    input.unknown10.y = start.y;
  }
  if (start.z > end.z) {
    input.unknown00.z = start.z;
    input.unknown10.z = end.z;
  } else {
    input.unknown00.z = end.z;
    input.unknown10.z = start.z;
  }
  input.unknown20 = start;
  input.unknown30.x = end.x - start.x;
  input.unknown30.y = end.y - start.y;
  input.unknown30.z = end.z - start.z;
  input.unknown98 = sqrtf(input.unknown30.x * input.unknown30.x + input.unknown30.y * input.unknown30.y + input.unknown30.z * input.unknown30.z);
  calcTreeAABB(input, input.unknown00, input.unknown10);
  input.unknown50 = input.unknown30 * 0.5f;
  input.unknown40.x = start.x + input.unknown50.x;
  input.unknown40.y = start.y + input.unknown50.y;
  input.unknown40.z = start.z + input.unknown50.z;
  input.unknown60.x = fabsf(input.unknown50.x) + 0.000001f;
  input.unknown60.y = fabsf(input.unknown50.y) + 0.000001f;
  input.unknown60.z = fabsf(input.unknown50.z) + 0.000001f;
  input.unknowna0 = 0.0f;
  IDColiPrimitive::createLine(input.line, input);
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

void IDColiInputUtil::getLine(IDColiInput &input, const IDColiInput &source, const IDCmfPosData *posData, bool isTree) {
  mm::Vec3 deltaStart = source.unknown70 - posData->unknown081();
  mm::Vec3 deltaEnd = source.unknown80 - posData->unknown081();
  mm::Vec3 start;
  mm::Vec3 end;
  posData->unknown080(start, deltaStart);
  posData->unknown080(end, deltaEnd);
  getLine(input, start, end, false);
  input.unknowna0 = source.unknowna0;
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
  mm::Vec3 center;
  posData->unknown011(center, source.unknown20);
  f32 scaledRadius = posData->unknown012() * IDColiObj::OBJ_CALC_RADIUS;
  getSphere(input, center, source.unknown90 * scaledRadius, false);
  input.unknowna0 = source.unknowna0;
}

void IDColiInputUtil::getRay(IDColiInput &input, const mm::Vec3 &start, const mm::Vec3 &direction, f32 length, f32 backLength, bool isTree) {
  input.unknown70 = start;
  input.unknown80 = direction;
  input.unknown90 = length;
  input.unknown94 = backLength;
  input.unknown98 = 1.0f;
  input.unknowna0 = 0.0f;
  mm::Vec3 front = direction * length + start;
  mm::Vec3 back = direction * backLength + start;
  if (front.x > back.x) {
    input.unknown00.x = front.x;
    input.unknown10.x = back.x;
  } else {
    input.unknown00.x = back.x;
    input.unknown10.x = front.x;
  }
  if (front.y > back.y) {
    input.unknown00.y = front.y;
    input.unknown10.y = back.y;
  } else {
    input.unknown00.y = back.y;
    input.unknown10.y = front.y;
  }
  if (front.z > back.z) {
    input.unknown00.z = front.z;
    input.unknown10.z = back.z;
  } else {
    input.unknown00.z = back.z;
    input.unknown10.z = front.z;
  }
  input.unknown20 = start;
  input.unknown30 = direction;
  calcTreeAABB(input, input.unknown00, input.unknown10);
  input.unknown50 = (front - back) * 0.5f;
  input.unknown40 = back + input.unknown50;
  input.unknown60.x = fabsf(input.unknown50.x) + 0.000001f;
  input.unknown60.y = fabsf(input.unknown50.y) + 0.000001f;
  input.unknown60.z = fabsf(input.unknown50.z) + 0.000001f;
  IDColiPrimitive::createRay(input.ray, start, direction, length, -backLength);
}

void IDColiPrimitive::createRay(CLRayWork &ray, const mm::Vec3 &start, const mm::Vec3 &direction, f32 length, f32 backLength) {
  ray.unknown00[0].unknown20.x = direction.x * length;
  ray.unknown00[0].unknown20.y = direction.y * length;
  ray.unknown00[0].unknown20.z = direction.z * length;
  ray.unknown00[1].unknown20.x = direction.x * -backLength;
  ray.unknown00[1].unknown20.y = direction.y * -backLength;
  ray.unknown00[1].unknown20.z = direction.z * -backLength;
  ray.unknown00[0].unknown30 = direction;
  ray.unknown00[1].unknown30 = mm::Vec3(-direction.x, -direction.y, -direction.z);
  ray.unknown00[0].unknown64 = length;
  ray.unknown00[1].unknown64 = backLength;
  for (s32 i = 0; i < 2; i++) {
    CLLineWork &line = ray.unknown00[i];
    line.unknown10.x = start.x + line.unknown20.x;
    line.unknown10.y = start.y + line.unknown20.y;
    line.unknown10.z = start.z + line.unknown20.z;
    line.unknown00 = start;
    line.unknown60 = line.unknown20.x * line.unknown20.x + line.unknown20.y * line.unknown20.y + line.unknown20.z * line.unknown20.z;
    if (line.unknown00.x > line.unknown10.x) {
      line.unknown40.x = line.unknown00.x;
      line.unknown50.x = line.unknown10.x;
    } else {
      line.unknown40.x = line.unknown10.x;
      line.unknown50.x = line.unknown00.x;
    }
    if (line.unknown00.y > line.unknown10.y) {
      line.unknown40.y = line.unknown00.y;
      line.unknown50.y = line.unknown10.y;
    } else {
      line.unknown40.y = line.unknown10.y;
      line.unknown50.y = line.unknown00.y;
    }
    if (line.unknown00.z > line.unknown10.z) {
      line.unknown40.z = line.unknown00.z;
      line.unknown50.z = line.unknown10.z;
    } else {
      line.unknown40.z = line.unknown10.z;
      line.unknown50.z = line.unknown00.z;
    }
  }
}

void IDColiInputUtil::getRay(IDColiInput &input, const IDColiInput &source, const IDCmfPosData *posData, bool isTree) {
  mm::Vec3 start;
  posData->unknown011(start, source.unknown70);
  mm::Vec3 direction;
  posData->unknown080(direction, source.unknown80);
  f32 length = sqrtf(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
  if (length <= 0.000001f) {
    direction = mm::Vec3::zero;
  } else {
    f32 inverse = 1.0f / length;
    direction.x = inverse * direction.x;
    direction.y = inverse * direction.y;
    direction.z = inverse * direction.z;
  }
  f32 scale = posData->unknown012() * IDColiObj::OBJ_CALC_RADIUS;
  getRay(input, start, direction, source.unknown90 * scale, scale * source.unknown94, false);
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

void IDColiInputUtil::getCapsule(IDColiInput &input, const IDColiInput &source, const IDCmfPosData *posData, bool isTree) {
  mm::Vec3 deltaStart = source.unknown70 - posData->unknown081();
  mm::Vec3 deltaEnd = source.unknown80 - posData->unknown081();
  mm::Vec3 start;
  mm::Vec3 end;
  posData->unknown080(start, deltaStart);
  posData->unknown080(end, deltaEnd);
  f32 scale = posData->unknown012() * IDColiObj::OBJ_CALC_RADIUS;
  getCapsule(input, start, end, source.unknown90 * scale, false);
  input.unknowna0 = source.unknowna0;
}

void IDColiInputUtil::getAaBb(IDColiInput &input, const mm::Vec3 &max, const mm::Vec3 &min) {
  input.unknown00 = max;
  input.unknown10 = min;
  input.unknowna0 = 0.0f;
  calcTreeAABB(input, input.unknown00, input.unknown10);
}

void IDColiInputUtil::getOBB(IDColiInput &input, const mm::Vec3 &max, const mm::Vec3 &min, const IDCmfPosData *posData) {
  input.unknown00 = max;
  input.unknown10 = min;
  mm::Vec3 corners[8] = {
      mm::Vec3(max.x, max.y, max.z),
      mm::Vec3(max.x, max.y, min.z),
      mm::Vec3(min.x, max.y, max.z),
      mm::Vec3(min.x, max.y, min.z),
      mm::Vec3(max.x, min.y, max.z),
      mm::Vec3(max.x, min.y, min.z),
      mm::Vec3(min.x, min.y, max.z),
      mm::Vec3(min.x, min.y, min.z),
  };
  mm::Vec3 localMax(-100000.0f, -100000.0f, -100000.0f);
  mm::Vec3 localMin(100000.0f, 100000.0f, 100000.0f);
  mm::Vec3 translation = posData->unknown081();
  for (s32 i = 0; i < 8; i++) {
    corners[i] -= translation;
    mm::Vec3 local;
    posData->unknown080(local, corners[i]);
    localMax.x = localMax.x > local.x ? localMax.x : local.x;
    localMax.y = localMax.y > local.y ? localMax.y : local.y;
    localMax.z = localMax.z > local.z ? localMax.z : local.z;
    localMin.x = localMin.x < local.x ? localMin.x : local.x;
    localMin.y = localMin.y < local.y ? localMin.y : local.y;
    localMin.z = localMin.z < local.z ? localMin.z : local.z;
  }
  calcTreeAABB(input, localMax, localMin);
  input.unknown40.x = posData->unknown00[0][0];
  input.unknown40.y = posData->unknown00[0][1];
  input.unknown40.z = posData->unknown00[0][2];
  input.unknown50.x = posData->unknown00[1][0];
  input.unknown50.y = posData->unknown00[1][1];
  input.unknown50.z = posData->unknown00[1][2];
  input.unknown60.x = posData->unknown00[2][0];
  input.unknown60.y = posData->unknown00[2][1];
  input.unknown60.z = posData->unknown00[2][2];
  input.unknown20 = translation;
  input.unknowna0 = 0.0f;
}

void IDColiInputUtil::getBox(IDColiInput &input, const CLBoxWork &box) {
  memcpy(&input.box, &box, sizeof(CLBoxWork));
  input.unknown00 = box.unknown80;
  input.unknown10 = box.unknown90;
  input.unknowna0 = 0.0f;
  calcTreeAABB(input, box.unknown80, box.unknown90);
}

void IDColiUtilMath::getNearLineToPoint(mm::Vec3 &near, const mm::Vec3 &start, const mm::Vec3 &end, const mm::Vec3 &point) {
  mm::Vec3 direction = end - start;
  f32 lengthSq = direction.x * direction.x + direction.y * direction.y + direction.z * direction.z;
  mm::Vec3 offset = point - start;
  f32 rate = (direction.x * offset.x + direction.y * offset.y + direction.z * offset.z) / lengthSq;
  if (rate < 0.0f) {
    rate = 0.0f;
  }
  if (rate > 1.0f) {
    rate = 1.0f;
  }
  near = direction * rate;
  near.x = start.x + near.x;
  near.y = start.y + near.y;
  near.z = start.z + near.z;
}

void IDColiPrimitive::calcBoxAaBb(CLBoxWork *box) {
  const mm::Vec3 &size = box->unknown70;
  mm::Vec3 corners[8] = {
      mm::Vec3(size.x, size.y, size.z),
      mm::Vec3(size.x, size.y, -size.z),
      mm::Vec3(-size.x, size.y, size.z),
      mm::Vec3(-size.x, size.y, -size.z),
      mm::Vec3(size.x, -size.y, size.z),
      mm::Vec3(size.x, -size.y, -size.z),
      mm::Vec3(-size.x, -size.y, size.z),
      mm::Vec3(-size.x, -size.y, -size.z),
  };
  box->unknown80.x = box->unknown80.y = box->unknown80.z = -100000.0f;
  box->unknown90.x = box->unknown90.y = box->unknown90.z = 100000.0f;
  for (s32 i = 0; i < 8; i++) {
    f32 x = corners[i].x * box->unknown00.x + corners[i].y * box->unknown00.y + corners[i].z * box->unknown00.z;
    f32 y = corners[i].x * box->unknown10.x + corners[i].y * box->unknown10.y + corners[i].z * box->unknown10.z;
    f32 z = corners[i].x * box->unknown20.x + corners[i].y * box->unknown20.y + corners[i].z * box->unknown20.z;
    if (box->unknown80.x < x) {
      box->unknown80.x = x;
    }
    if (box->unknown90.x > x) {
      box->unknown90.x = x;
    }
    if (box->unknown80.y < y) {
      box->unknown80.y = y;
    }
    if (box->unknown90.y > y) {
      box->unknown90.y = y;
    }
    if (box->unknown80.z < z) {
      box->unknown80.z = z;
    }
    if (box->unknown90.z > z) {
      box->unknown90.z = z;
    }
  }
  box->unknown80 += box->unknown60;
  box->unknown90 += box->unknown60;
}

// Inferred helper: grows a range by a value and a radius; original name unknown.
static void unknown082(f32 &max, f32 &min, f32 value, f32 radius) {
  if (max < value + radius) {
    max = value + radius;
  }
  if (min > value - radius) {
    min = value - radius;
  }
}

void IDColiPrimitive::calcCapsuleSetup(CLCapsuleWork *capsule) {
  capsule->unknown20.x = capsule->unknown10.x - capsule->unknown00.x;
  capsule->unknown20.y = capsule->unknown10.y - capsule->unknown00.y;
  capsule->unknown20.z = capsule->unknown10.z - capsule->unknown00.z;
  capsule->unknown54 = capsule->unknown20.x * capsule->unknown20.x + capsule->unknown20.y * capsule->unknown20.y + capsule->unknown20.z * capsule->unknown20.z;
  capsule->unknown58 = 1.0f / capsule->unknown54;
  capsule->unknown30.x = capsule->unknown30.y = capsule->unknown30.z = -100000.0f;
  capsule->unknown40.x = capsule->unknown40.y = capsule->unknown40.z = 100000.0f;
  unknown082(capsule->unknown30.x, capsule->unknown40.x, capsule->unknown00.x, capsule->unknown50);
  unknown082(capsule->unknown30.x, capsule->unknown40.x, capsule->unknown10.x, capsule->unknown50);
  unknown082(capsule->unknown30.y, capsule->unknown40.y, capsule->unknown00.y, capsule->unknown50);
  unknown082(capsule->unknown30.y, capsule->unknown40.y, capsule->unknown10.y, capsule->unknown50);
  unknown082(capsule->unknown30.z, capsule->unknown40.z, capsule->unknown00.z, capsule->unknown50);
  unknown082(capsule->unknown30.z, capsule->unknown40.z, capsule->unknown10.z, capsule->unknown50);
}

void IDColiPrimitive::calcBaseBoxSetup(CLBoxWork *box, const mm::Mat44 &matrix, const mm::Vec3 &size) {
  f32 scale = unknown123(matrix) * IDColiObj::OBJ_CALC_RADIUS;
  box->unknown70 = size;
  box->unknowna0 = scale;
  box->unknowna4 = 1.0f / scale;
  box->unknown60 = matrix.unknown004();
  box->unknown00.x = matrix.rows[0][0];
  box->unknown00.y = matrix.rows[1][0];
  box->unknown00.z = matrix.rows[2][0];
  box->unknown10.x = matrix.rows[0][1];
  box->unknown10.y = matrix.rows[1][1];
  box->unknown10.z = matrix.rows[2][1];
  box->unknown20.x = matrix.rows[0][2];
  box->unknown20.y = matrix.rows[1][2];
  box->unknown20.z = matrix.rows[2][2];
  mm::Mat44 rotation;
  rotation.unknown006(matrix);
  rotation.rows[3][0] = 0.0f;
  rotation.rows[3][1] = 0.0f;
  rotation.rows[3][2] = 0.0f;
  mm::Mat44 inverse = rotation.unknown003();
  box->unknown30 = mm::Vec3(inverse.rows[0][0], inverse.rows[1][0], inverse.rows[2][0]);
  box->unknown40 = mm::Vec3(inverse.rows[0][1], inverse.rows[1][1], inverse.rows[2][1]);
  box->unknown50 = mm::Vec3(inverse.rows[0][2], inverse.rows[1][2], inverse.rows[2][2]);
  calcBoxAaBb(box);
}

void IDColiPrimitive::calcPosDataSetup(IDCmfPosData *posData, const mm::Mat44 &matrix, const mm::Vec3 &max, const mm::Vec3 &min) {
  mm::Vec3 translation(matrix.rows[3][0], matrix.rows[3][1], matrix.rows[3][2]);
  for (s32 i = 0; i < 3; i++) {
    for (s32 j = 0; j < 3; j++) {
      posData->unknown00[i][j] = matrix.rows[j][i];
    }
  }
  posData->unknown00[0][3] = translation.x;
  posData->unknown00[1][3] = translation.y;
  posData->unknown00[2][3] = translation.z;
  mm::Mat44 rotation;
  rotation.unknown006(matrix);
  rotation.rows[3][0] = 0.0f;
  rotation.rows[3][1] = 0.0f;
  rotation.rows[3][2] = 0.0f;
  mm::Mat44 inverse = rotation.unknown003();
  posData->unknown40[0][0] = inverse.rows[0][0];
  posData->unknown40[0][1] = inverse.rows[1][0];
  posData->unknown40[0][2] = inverse.rows[2][0];
  posData->unknown40[1][0] = inverse.rows[0][1];
  posData->unknown40[1][1] = inverse.rows[1][1];
  posData->unknown40[1][2] = inverse.rows[2][1];
  posData->unknown40[2][0] = inverse.rows[0][2];
  posData->unknown40[2][1] = inverse.rows[1][2];
  posData->unknown40[2][2] = inverse.rows[2][2];
  mm::Vec3 corners[8] = {
      mm::Vec3(max.x, max.y, max.z),
      mm::Vec3(max.x, max.y, min.z),
      mm::Vec3(min.x, max.y, max.z),
      mm::Vec3(min.x, max.y, min.z),
      mm::Vec3(max.x, min.y, max.z),
      mm::Vec3(max.x, min.y, min.z),
      mm::Vec3(min.x, min.y, max.z),
      mm::Vec3(min.x, min.y, min.z),
  };
  posData->unknown80.x = posData->unknown80.y = posData->unknown80.z = -100000.0f;
  posData->unknown90.x = posData->unknown90.y = posData->unknown90.z = 100000.0f;
  for (s32 i = 0; i < 8; i++) {
    f32 x = corners[i].x * posData->unknown00[0][0] + corners[i].y * posData->unknown00[0][1] + corners[i].z * posData->unknown00[0][2];
    f32 y = corners[i].x * posData->unknown00[1][0] + corners[i].y * posData->unknown00[1][1] + corners[i].z * posData->unknown00[1][2];
    f32 z = corners[i].x * posData->unknown00[2][0] + corners[i].y * posData->unknown00[2][1] + corners[i].z * posData->unknown00[2][2];
    if (posData->unknown80.x < x) {
      posData->unknown80.x = x;
    }
    if (posData->unknown90.x > x) {
      posData->unknown90.x = x;
    }
    if (posData->unknown80.y < y) {
      posData->unknown80.y = y;
    }
    if (posData->unknown90.y > y) {
      posData->unknown90.y = y;
    }
    if (posData->unknown80.z < z) {
      posData->unknown80.z = z;
    }
    if (posData->unknown90.z > z) {
      posData->unknown90.z = z;
    }
  }
  posData->unknown80 += translation;
  posData->unknown90 += translation;
}

void IDColiPrimitive::createBaseSphere(void *data, IDColiBaseType &type, const mm::Mat44 &matrix, const mm::Vec3 &size) {
  CLSphereWork *sphere = static_cast<CLSphereWork *>(data);
  type = IDColiBaseType_UNKNOWN_0;
  f32 scale = unknown123(matrix);
  f32 radius = scale * IDColiObj::OBJ_CALC_RADIUS;
  sphere->unknown10 = size.x * radius;
  sphere->unknown00 = mm::Vec3(matrix.rows[3][0], matrix.rows[3][1], matrix.rows[3][2]);
}

void IDColiPrimitive::createBaseBox(void *data, IDColiBaseType &type, const mm::Mat44 &matrix, const mm::Vec3 &size) {
  calcBaseBoxSetup(static_cast<CLBoxWork *>(data), matrix, size);
  type = IDColiBaseType_UNKNOWN_1;
}

void IDColiPrimitive::createBaseCharacter(void *data, IDColiBaseType &type, const mm::Mat44 &matrix, const mm::Vec3 &size) {
  f32 scale = unknown123(matrix) * IDColiObj::OBJ_CALC_RADIUS;
  f32 radius = size.x * scale;
  f32 length = scale * size.y - radius * 2.0f;
  if (length <= 0.01f) {
    CLSphereWork *sphere = static_cast<CLSphereWork *>(data);
    sphere->unknown10 = radius;
    sphere->unknown00 = matrix.unknown004();
    sphere->unknown00.y += radius;
    type = IDColiBaseType_UNKNOWN_4;
  } else {
    CLCapsuleWork *capsule = static_cast<CLCapsuleWork *>(data);
    capsule->unknown50 = radius;
    capsule->unknown00 = matrix.unknown004();
    capsule->unknown00.y += radius;
    capsule->unknown10 = capsule->unknown00;
    capsule->unknown10.y += length;
    calcCapsuleSetup(capsule);
    type = IDColiBaseType_UNKNOWN_3;
  }
}

void IDColiPrimitive::createBasePoli(void *data, IDColiBaseType &type, const mm::Mat44 &matrix, const mm::Vec3 &size) {
  unknown085 *poli = static_cast<unknown010 *>(data)->unknown00;
  calcPosDataSetup(&poli->unknown00, matrix, poli->unknowna8[0], poli->unknowna8[1]);
  type = IDColiBaseType_UNKNOWN_5;
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
  const IDCmfPosData *poli = &static_cast<const unknown010 *>(data)->unknown00->unknown00;
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
