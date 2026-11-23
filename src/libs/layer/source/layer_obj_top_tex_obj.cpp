#include "layer/layer_obj_top_tex_obj.h"

#include "grlib/cglib_texture_buffer.h"
#include "layer/layer_base.h"
#include "layer/layer_manager.h"
#include "layer/layer_obj_manager.h"
#include "layer/layer_obj_util.h"
#include "layer/layer_render_view.h"
#include "layer/layer_shd_manager.h"
#include "layer/layer_sort_man.h"
#include "types.h"

namespace layer {

LayerObjTopTexObj::LayerObjTopTexObj(const grlib::CGLibTextureBuffer *texture) : m_layerObjSortTexObj(this) {
  unknown270 = texture;
  unknown18 = LAYER_OBJ_TYPE_TEX;
  unknowna8 |= 0x20000;
  m_layerResViewPortInfo = nullptr;
  unknown238 = nullptr;
  createWorkBuffer();
}

void LayerObjTopTexObj::finalRender() {
  LayerShdManager *shader = LayerManager::get()->m_layerShdManager;
  if (!shader->unknown002(m_layerObjTopMaskObj, m_layerResViewPortInfo)) {
    return;
  }
  shader->unknown003(LayerShdManager::s_resDefBlend[unknownc5]);
  shader->unknown004(this);
  shader->unknown4f2 = 1;
  shader->setSecTexture(unknown220[2]);
  shader->setupVertex(static_cast<LayerDefVertType>(1));
  shader->unknown4f0 = 1;
  shader->setupShader(&m_cGLibDblUniformBlock);
  shader->setupTexture(*unknown270, static_cast<LayerSamplerType>(m_texFilterType), 0);
  shader->renderQuadsIndex();
}

LayerObjTopTexObj::~LayerObjTopTexObj() {
  baseRelease();
  releaseWorkBuffer();
}

void LayerObjTopTexObj::createWorkBuffer() {
  m_cGLibDblUniformBlock.setup(0x80);
  u32 width = 0x40;
  u32 height = 0x40;
  if (unknown270->isInitialized()) {
    width = unknown270->getWidth();
    height = unknown270->getHeight();
  }
  unknown005(width, height);
}

void LayerObjTopTexObj::releaseWorkBuffer() { m_cGLibDblUniformBlock.release(); }

void LayerObjTopTexObj::applyParams(const LayerRenderView *view, const LayerResMatrix &matrix, const LayerResColor &color) {
  m_layerResViewPortInfo = view->m_layerResViewPortInfo;
  m_layerResDispInfo.unknown001();
  LayerObjUtil::calcDispInfo(m_layerResDispInfo, matrix, m_layerResRenderInfo);
  if (unknowna8 & 0x90000) {
    return;
  }
  updateDefUniformBlock(m_cGLibDblUniformBlock, matrix, color, nullptr);
}

void LayerObjTopTexObj::setDrawList(LayerSortMan *sortMan, bool is3D) {
  if (unknowna8 & 0x90000) {
    return;
  }
  if (is3D) {
    if (unknowna8 & 0x400) {
      LayerManager::get()->m_layerObjManager->m_layerSortMan->set3DSpace(&m_layerObjSortTexObj, unknown200);
    } else if (!isClip()) {
      sortMan->set2DSpace(&m_layerObjSortTexObj, m_priority);
    }
  } else if (!isClip()) {
    sortMan->set2DSpace(&m_layerObjSortTexObj, m_priority);
  }
}

} // namespace layer
