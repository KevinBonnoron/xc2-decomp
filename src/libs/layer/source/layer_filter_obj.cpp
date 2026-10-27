#include "layer/layer_filter_obj.h"

#include <math.h>

#include "layer/layer_manager.h"
#include "layer/layer_obj.h"
#include "layer/layer_obj_util.h"
#include "mm_math/mm_vec3.h"

namespace layer {

void LayerFilterObj::render() {}

void LayerFilterObj::releaseCall() { unknown08 |= 1 << LayerManager::s_nStkIdx; }

u32 LayerFilterObj::isReleaseCall() const { return unknown08 & (1 << LayerManager::s_nDebIdx); }

void LayerFilterObj::calcMatInvert(f32 *param, const LayerResMatrix &matrix) {
  mm::Vec3 pos;
  mm::Vec3 scl;
  LayerObjUtil::calcLayerInvertMatrix(pos, scl, matrix);
  param[0] = pos.x;
  param[1] = pos.y;
  param[3] = pos.z;
  param[4] = scl.x;
  param[5] = scl.y;
  param[7] = scl.z;
  param[6] = 0.0f;
  param[2] = 0.0f;
}

void LayerFilterObj::calcMatRotParam(f32 *param, const LayerResMatrix &matrix) {
  f32 invX = 1.0f / sqrtf(matrix.unknown08 * matrix.unknown08 + matrix.unknown14 * matrix.unknown14);
  f32 invY = 1.0f / sqrtf(matrix.unknown10 * matrix.unknown10 + matrix.unknown0c * matrix.unknown0c);
  param[0] = invX * matrix.unknown08;
  param[1] = invX * matrix.unknown14;
  param[2] = invY * matrix.unknown10;
  param[3] = invY * matrix.unknown0c;
}

f32 LayerFilterObj::gaussianDistribution(f32 x, f32 y, f32 rho) const {
  f32 g = 1.0f / sqrtf(rho * 6.2831855f * rho);
  g *= expf((x * x + y * y) / (rho * -2.0f * rho));
  return g;
}

} // namespace layer
