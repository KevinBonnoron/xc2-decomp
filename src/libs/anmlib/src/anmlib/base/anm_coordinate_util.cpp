#include "anm/anm_coordinate_util.h"

#include <math.h>

#include "mm/mm_std_base.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace anm {

void CoordinateUtil::convertRCSToSPC(mm::Vec3 *pVec) {
  MM_ASSERT(pVec);
  f32 radius = sqrtf(pVec->x * pVec->x + pVec->y * pVec->y + pVec->z * pVec->z);
  if (radius < 1.1920929e-07f) {
    *pVec = mm::Vec3::zero;
  } else {
    f32 theta = mm::asin(pVec->y / radius);
    f32 phi = atan2f(pVec->x, pVec->z);
    pVec->x = radius;
    pVec->y = theta;
    pVec->z = phi;
  }
}

void CoordinateUtil::convertSPCToRCS(mm::Vec3 *pVec) {
  MM_ASSERT(pVec);
  f32 theta = pVec->y;
  f32 sinTheta = sinf(theta);
  f32 cosTheta = cosf(theta);
  f32 phi = pVec->z;
  f32 sinPhi = sinf(phi);
  f32 cosPhi = cosf(phi);
  f32 radius = pVec->x;
  f32 projected = cosTheta * radius;
  f32 z = cosPhi * projected;
  f32 x = sinPhi * projected;
  pVec->x = x;
  pVec->y = sinTheta * radius;
  pVec->z = z;
}

} // namespace anm
