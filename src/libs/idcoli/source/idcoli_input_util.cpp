#include <math.h>
#include <string.h>

#include "idcoli/idcoli_util_coli.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace idcoli {

void IDColiInputUtil::calcTreeAABB(IDColiInput &input, const mm::Vec3 &max, const mm::Vec3 &min) {
  input.unknowna4[0] = static_cast<s16>(ceilf(max.x));
  input.unknowna4[1] = static_cast<s16>(ceilf(max.y));
  input.unknowna4[2] = static_cast<s16>(ceilf(max.z));
  input.unknowna4[3] = static_cast<s16>(floorf(min.x));
  input.unknowna4[4] = static_cast<s16>(floorf(min.y));
  input.unknowna4[5] = static_cast<s16>(floorf(min.z));
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

} // namespace idcoli
