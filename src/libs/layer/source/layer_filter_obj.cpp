#include "layer/layer_filter_obj.h"

#include <math.h>

#include "layer/layer_manager.h"
#include "layer/layer_obj.h"
#include "layer/layer_obj_util.h"
#include "layer/layer_render_view.h"
#include "layer/layer_res_view_port_info.h"
#include "layer/layer_shd_manager.h"
#include "mm_math/mm_rect.h"
#include "mm_math/mm_vec3.h"

namespace layer {

void LayerFilterObj::render() {}

void LayerFilterObj::releaseCall() { unknown08 |= 1 << LayerManager::s_nStkIdx; }

u32 LayerFilterObj::isReleaseCall() const { return unknown08 & (1 << LayerManager::s_nDebIdx); }

void LayerFilterObj::calcFilterUvParam(f32 *param, const LayerRenderView *view) {
  const LayerResViewPortInfo *viewPort = view->unknown08;
  if (viewPort != nullptr && viewPort->unknown10 != nullptr) {
    f32 x = viewPort->unknown00.x;
    LayerShdManager *shader = LayerManager::get()->unknown58;
    f32 scale = shader->unknown558;
    f32 screenWidth = shader->unknown530;
    f32 scaledX = x * scale;
    f32 scaledY = scale * viewPort->unknown00.y;
    f32 scaledWidth = scale * viewPort->unknown00.width;
    f32 scaledHeight = scale * viewPort->unknown00.height;
    f32 screenHeight = shader->unknown534;
    param[2] = scaledX / screenWidth;
    param[0] = screenWidth / scaledWidth;
    param[1] = screenHeight / scaledHeight;
    param[3] = scaledY / screenHeight;
  } else {
    param[0] = 1.0f;
    param[1] = 1.0f;
    param[2] = 0.0f;
    param[3] = 0.0f;
  }
}

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
