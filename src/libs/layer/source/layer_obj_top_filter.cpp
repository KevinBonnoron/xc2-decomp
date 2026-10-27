#include "layer/layer_obj_top_filter.h"

#include "layer/layer_filter_flow_map_obj.h"
#include "layer/layer_filter_gs_blur_obj.h"
#include "layer/layer_filter_obj.h"
#include "layer/layer_manager.h"
#include "mtl/alloc_handle.h"

namespace layer {

LayerFilterObj *LayerObjTopFilter::getFilterObj() const {
  LayerFilterObj *filter = unknown278[LayerManager::s_nStkIdx];
  if (filter == nullptr) {
    filter = unknown278[LayerManager::s_nDebIdx];
    if (filter == nullptr) {
      filter = unknown270;
    }
  }
  return filter;
}

u32 LayerObjTopFilter::getFilterType() const {
  LayerFilterObj *filter = getFilterObj();
  if (filter == nullptr) {
    return 0;
  }
  return filter->m_filterType;
}

void LayerObjTopFilter::releaseWorkBuffer() {
  if (unknown270 != nullptr) {
    delete unknown270;
    unknown270 = nullptr;
  }
  if (unknown288 != nullptr) {
    delete unknown288;
    unknown288 = nullptr;
  }
  if (unknown278[0] != nullptr) {
    delete unknown278[0];
    unknown278[0] = nullptr;
  }
  if (unknown278[1] != nullptr) {
    delete unknown278[1];
    unknown278[1] = nullptr;
  }
  unknown290.release();
}

void LayerObjTopFilter::resourceInit() {
  unknown290.setup(0x80);
  if (unknown270 != nullptr) {
    unknown270->resourceInit();
  }
}

void LayerObjTopFilter::applyPartsSetup() {
  if (unknown288 != nullptr) {
    delete unknown288;
    unknown288 = nullptr;
  }
  if (unknown270 != nullptr && unknown270->isReleaseCall()) {
    unknown288 = unknown270;
    unknown270 = nullptr;
  }
  s32 index = LayerManager::s_nDebIdx;
  if (unknown278[index] != nullptr) {
    if (unknown270 != nullptr) {
      unknown288 = unknown270;
    }
    unknown270 = unknown278[index];
    unknown278[index] = nullptr;
    unknown270->resourceInit();
  }
}

LayerObjTopFilter::~LayerObjTopFilter() {
  baseRelease();
  releaseWorkBuffer();
}

void LayerObjTopFilter::createGaussianBlur(u32 width, u32 height) {
  if (unknown270 != nullptr) {
    unknown270->releaseCall();
  }
  f32 sclY = static_cast<f32>(height) / static_cast<f32>(width);
  unknown188 = 1.0f;
  unknown18c = sclY;
  f32 sclX = 1.0f;
  if (width <= height) {
    sclY = 1.0f;
    sclX = static_cast<f32>(width) / static_cast<f32>(height);
  }
  unknown180 = sclX;
  unknown184 = sclY;
  unknown190 = 0;
  unknown192 = 0;
  unknown194 = width;
  unknown196 = height;
  LayerFilterGsBlurObj *filter = new (LayerManager::get()->unknown28) LayerFilterGsBlurObj(width, height);
  if (unknown270 == nullptr && unknown278[0] == nullptr && unknown278[1] == nullptr) {
    unknown270 = filter;
  } else {
    unknown278[LayerManager::s_nStkIdx] = filter;
  }
}

void LayerObjTopFilter::setGaussianBlurParameter(f32 strength, f32 scale, u32 sampleNum, bool isHalf, u32 passNum) {
  static_cast<LayerFilterGsBlurObj *>(getFilterObj())->setParameter(strength, scale, sampleNum, isHalf, passNum);
}

void LayerObjTopFilter::createFlowMap(u32 width, u32 height, const void *data) {
  if (unknown270 != nullptr) {
    unknown270->releaseCall();
  }
  f32 sclY = static_cast<f32>(height) / static_cast<f32>(width);
  unknown188 = 1.0f;
  unknown18c = sclY;
  f32 sclX = 1.0f;
  if (width <= height) {
    sclY = 1.0f;
    sclX = static_cast<f32>(width) / static_cast<f32>(height);
  }
  unknown180 = sclX;
  unknown184 = sclY;
  unknown190 = 0;
  unknown192 = 0;
  unknown194 = width;
  unknown196 = height;
  LayerFilterFlowMapObj *filter = new (LayerManager::get()->unknown28) LayerFilterFlowMapObj(width, height, data);
  if (unknown270 == nullptr && unknown278[0] == nullptr && unknown278[1] == nullptr) {
    unknown270 = filter;
  } else {
    unknown278[LayerManager::s_nStkIdx] = filter;
  }
}

void LayerObjTopFilter::setFlowMapParameter(f32 speed, f32 strength) { static_cast<LayerFilterFlowMapObj *>(getFilterObj())->setParameter(speed, strength); }

} // namespace layer
