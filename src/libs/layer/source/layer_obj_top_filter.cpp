#include "layer/layer_obj_top_filter.h"

#include "grlib/cglib_render_target.h"
#include "layer/layer_filter_flow_map_obj.h"
#include "layer/layer_filter_gs_blur_obj.h"
#include "layer/layer_filter_obj.h"
#include "layer/layer_manager.h"
#include "layer/layer_obj_manager.h"
#include "layer/layer_obj_util.h"
#include "layer/layer_render_view.h"
#include "layer/layer_res_view_port_info.h"
#include "layer/layer_shd_manager.h"
#include "layer/layer_sort_man.h"
#include "mm_math/mm_col4.h"
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

void LayerObjTopFilter::setupWorkBuffer(u32 width, u32 height) { unknown005(width, height); }

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
  m_cGLibDblUniformBlock.release();
}

void LayerObjTopFilter::resourceInit() {
  m_cGLibDblUniformBlock.setup(0x80);
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

void LayerObjTopFilter::applyParams(const LayerRenderView *view, const LayerResMatrix &matrix, const LayerResColor &color) {
  m_layerResViewPortInfo = view->m_layerResViewPortInfo;
  m_layerResDispInfo.unknown001();
  LayerObjUtil::calcDispInfo(m_layerResDispInfo, matrix, m_layerResRenderInfo);
  if (unknowna8 & 0x90000) {
    return;
  }
  if (unknown270 == nullptr) {
    return;
  }
  const grlib::CGLibRenderTarget *target = nullptr;
  if (view->m_layerResViewPortInfo != nullptr) {
    target = view->m_layerResViewPortInfo->unknown10;
  }
  if (target == nullptr) {
    target = LayerManager::get()->m_layerShdManager->getDefRenderTarget();
  }
  updateDefUniformBlock(m_cGLibDblUniformBlock, matrix, color, target);
  unknown270->update(matrix, color, view, unknown1f8);
  unknown2c8 = color.m_mulCol.a < 1.0f;
}

void LayerObjTopFilter::setDrawList(LayerSortMan *sortMan, bool is3D) {
  if ((unknowna8 & 0x90000) || unknown270 == nullptr) {
    return;
  }
  if (is3D) {
    if (unknowna8 & 0x400) {
      LayerManager::get()->m_layerObjManager->m_layerSortMan->set3DSpace(&m_layerObjSortFilter, unknown200);
    } else if (!isClip()) {
      sortMan->set2DSpace(&m_layerObjSortFilter, m_priority);
    }
  } else if (!isClip()) {
    sortMan->set2DSpace(&m_layerObjSortFilter, m_priority);
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
  m_layerResRenderInfo.unknown08 = 1.0f;
  m_layerResRenderInfo.unknown0c = sclY;
  f32 sclX = 1.0f;
  if (width <= height) {
    sclY = 1.0f;
    sclX = static_cast<f32>(width) / static_cast<f32>(height);
  }
  m_layerResRenderInfo.unknown00 = sclX;
  m_layerResRenderInfo.unknown04 = sclY;
  m_layerResRenderInfo.m_pixelX = 0;
  m_layerResRenderInfo.m_pixelY = 0;
  m_layerResRenderInfo.m_pixelWidth = width;
  m_layerResRenderInfo.m_pixelHeight = height;
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
  m_layerResRenderInfo.unknown08 = 1.0f;
  m_layerResRenderInfo.unknown0c = sclY;
  f32 sclX = 1.0f;
  if (width <= height) {
    sclY = 1.0f;
    sclX = static_cast<f32>(width) / static_cast<f32>(height);
  }
  m_layerResRenderInfo.unknown00 = sclX;
  m_layerResRenderInfo.unknown04 = sclY;
  m_layerResRenderInfo.m_pixelX = 0;
  m_layerResRenderInfo.m_pixelY = 0;
  m_layerResRenderInfo.m_pixelWidth = width;
  m_layerResRenderInfo.m_pixelHeight = height;
  LayerFilterFlowMapObj *filter = new (LayerManager::get()->unknown28) LayerFilterFlowMapObj(width, height, data);
  if (unknown270 == nullptr && unknown278[0] == nullptr && unknown278[1] == nullptr) {
    unknown270 = filter;
  } else {
    unknown278[LayerManager::s_nStkIdx] = filter;
  }
}

void LayerObjTopFilter::setFlowMapParameter(f32 speed, f32 strength) { static_cast<LayerFilterFlowMapObj *>(getFilterObj())->setParameter(speed, strength); }

void LayerObjTopFilter::finalRender() {
  LayerShdManager *shader = LayerManager::get()->m_layerShdManager;
  shader->setShaderMaskOff();
  unknown270->render();
  grlib::CGLibRenderTarget *target = shader->getDefRenderTarget();
  target->setRenderTarget();
  if (!shader->unknown002(m_layerObjTopMaskObj, m_layerResViewPortInfo)) {
    return;
  }
  if (unknown2c8) {
    shader->unknown4f8 = 3;
  } else {
    shader->unknown4f8 = 1;
  }
  shader->unknown003(2);
  shader->unknown004(this);
  shader->unknown4f2 = 1;
  shader->setSecTexture(unknown220[2]);
  shader->setupVertex(static_cast<LayerDefVertType>(1));
  shader->unknown4f0 = 1;
  shader->setupShader(&m_cGLibDblUniformBlock);
  shader->setupTexture(*unknown270->getTexture(), static_cast<LayerSamplerType>(unknown270->unknown0c), 0);
  shader->setupTexture(*target->unknown70, static_cast<LayerSamplerType>(2), 1);
  shader->renderQuadsIndex();
}

} // namespace layer
