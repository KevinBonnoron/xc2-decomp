#include "layer/layer_obj_top_mem_obj.h"

#include <string.h>

#include "grlib/cglib_ctl_shader.h"
#include "grlib/cglib_ctl_vertex.h"
#include "grlib/cglib_dec_shader.h"
#include "grlib/cglib_shader.h"
#include "grlib/cglib_texture_buffer.h"
#include "layer/layer_base.h"
#include "layer/layer_manager.h"
#include "layer/layer_obj_util.h"
#include "layer/layer_render_view.h"
#include "layer/layer_shd_manager.h"
#include "layer/layer_sort_man.h"
#include "mm_math/mm_col4.h"

namespace layer {

LayerObjTopMemObj::LayerObjTopMemObj(u32 width, u32 height, LayerMemType type) : m_layerObjSortMemObj(this) {
  unknowna8 |= 0x20000;
  m_memWidth = width;
  m_memHeight = height;
  unknown748 = 0;
  unknown74c = 0;
  unknown750 = type;
  unknown18 = LAYER_OBJ_TYPE_MEM;
  m_layerResViewPortInfo = nullptr;
  unknown238 = nullptr;
  unknown270 = 0xc;
  createWorkBuffer();
}

void LayerObjTopMemObj::createWorkBuffer() {
  m_cGLibDblUniformBlock.setup(0x80);
  m_layerResRenderInfo.unknown08 = 1.0f;
  m_layerResRenderInfo.unknown0c = static_cast<f32>(m_memHeight) / static_cast<f32>(m_memWidth);
  if (m_memWidth > m_memHeight) {
    m_layerResRenderInfo.unknown00 = 1.0f;
    m_layerResRenderInfo.unknown04 = static_cast<f32>(m_memHeight) / static_cast<f32>(m_memWidth);
  } else {
    m_layerResRenderInfo.unknown00 = static_cast<f32>(m_memWidth) / static_cast<f32>(m_memHeight);
    m_layerResRenderInfo.unknown04 = 1.0f;
  }
  m_layerResRenderInfo.m_pixelX = 0;
  m_layerResRenderInfo.m_pixelY = 0;
  m_layerResRenderInfo.m_pixelWidth = m_memWidth;
  m_layerResRenderInfo.m_pixelHeight = m_memHeight;
  u32 size;
  if (unknown750 == LAYER_MEM_TYPE_UNKNOWN_2) {
    size = 2 * m_memWidth * m_memHeight;
  } else {
    size = m_memWidth * m_memHeight;
    if (unknown750 == LAYER_MEM_TYPE_UNKNOWN_3) {
      unknown748 = size + (0x100 - size % 0x100) % 0x100;
      u32 secondSize = (m_memWidth >> 1) * (m_memHeight >> 1) * 2;
      unknown74c = secondSize + (0x10 - secondSize % 0x10) % 0x10;
      size = unknown748 + unknown74c;
    } else {
      size *= 3;
    }
  }
  size += (0x10 - size % 0x10) % 0x10;
  unknown6a0[0].setup(size);
  unknown6a0[1].setup(size);
  unknown678.setup(0x10);
  unknown6f0[0].setup(0x10);
  memset(unknown6f0[0].m_mapping, 0, 0x10);
  unknown6f0[1].setup(0x10);
  memset(unknown6f0[1].m_mapping, 0, 0x10);
}

LayerObjTopMemObj::~LayerObjTopMemObj() {
  baseRelease();
  releaseWorkBuffer();
}

void LayerObjTopMemObj::releaseWorkBuffer() {
  m_cGLibRenderTarget.release();
  m_cGLibDblUniformBlock.release();
  unknown678.release();
  unknown6a0[0].release();
  unknown6a0[1].release();
  unknown6f0[0].release();
  unknown6f0[1].release();
}

void LayerObjTopMemObj::resourceInit() {
  if (unknown270 & 0x8) {
    unknown270 &= ~0x8;
    m_cGLibRenderTarget.setTextureInfo(m_memWidth, m_memHeight, GRL_SURFACE_FORMAT_RGBA8, false, 0);
    m_cGLibRenderTarget.clearTexture(mm::Col4(0.0f, 0.0f, 0.0f, 0.0f), static_cast<GrlClaerMask>(0xf));
    u32 *info = static_cast<u32 *>(unknown678.m_mapping);
    info[0] = m_memWidth;
    info[1] = m_memHeight;
    if (unknown750 == LAYER_MEM_TYPE_UNKNOWN_3) {
      info[2] = m_memWidth >> 1;
      info[3] = m_memHeight >> 1;
    } else {
      info[2] = m_memWidth;
      info[3] = m_memHeight;
    }
    unknown678.updateData();
  }
}

void *LayerObjTopMemObj::getBuffer() { return unknown6a0[static_cast<u32>(LayerManager::s_nDebIdx)].m_mapping; }

void LayerObjTopMemObj::updateBufer() {
  u32 index = LayerManager::s_nDebIdx;
  memset(unknown6f0[index].m_mapping, 0, 0x10);
  unknown6f0[index].updateData();
  unknown6a0[index].updateData();
}

void LayerObjTopMemObj::setRender(bool render) {
  if (render) {
    unknown270 |= 0x4;
  } else {
    unknown270 &= ~0x4;
  }
}

bool LayerObjTopMemObj::isRender() const { return (unknown270 >> 2) & 0x1; }

void LayerObjTopMemObj::applyParams(const LayerRenderView *view, const LayerResMatrix &matrix, const LayerResColor &color) {
  m_layerResViewPortInfo = view->m_layerResViewPortInfo;
  m_layerResDispInfo.unknown001();
  LayerObjUtil::calcDispInfo(m_layerResDispInfo, matrix, m_layerResRenderInfo);
  if (unknowna8 & 0x90000) {
    return;
  }
  updateDefUniformBlock(m_cGLibDblUniformBlock, matrix, color, nullptr);
}

void LayerObjTopMemObj::setDrawList(LayerSortMan *sortMan, bool is3D) {
  if (unknowna8 & 0x90000) {
    return;
  }
  if (is3D) {
    if (unknowna8 & 0x400) {
      LayerManager::get()->m_layerObjManager->m_layerSortMan->set3DSpace(&m_layerObjSortMemObj, unknown200);
    } else if (!isClip()) {
      sortMan->set2DSpace(&m_layerObjSortMemObj, m_priority);
    }
  } else if (!isClip()) {
    sortMan->set2DSpace(&m_layerObjSortMemObj, m_priority);
  }
}

void LayerObjTopMemObj::setupRender() {
  u32 index = LayerManager::s_nDebIdx;
  unknown270 &= ~(1 << index);
  LayerShdManager *shader = LayerManager::get()->m_layerShdManager;
  shader->unknown4f0 = 9;
  shader->unknown4f8 = unknown750;
  grlib::CGLibDecShader *decShader = shader->setupShader();
  m_cGLibRenderTarget.setRenderTarget();
  unknown678.setUniformBlock((decShader->unknown38 + decShader->unknown58)->getUniformBlockOfs("U_MENU"));
  unknown6a0[index].setStorageBuffer(0);
  if (unknown750 != LAYER_MEM_TYPE_UNKNOWN_1) {
    unknown6a0[index].setStorageBuffer(1, unknown748, unknown74c);
  }
  unknown6f0[index].setStorageBuffer(2);
  shader->setupVertex(static_cast<LayerDefVertType>(3));
  shader->renderQuadsIndex();
  grlib::CGLibCtlShader::setMemoryBarrierBit(0x25);
  shader->unknown4f0 = 9;
  shader->unknown4f8 = 4;
  shader->setupShader();
  unknown6f0[index].setStorageBuffer(2);
  shader->setupVertex(static_cast<LayerDefVertType>(3));
  grlib::CGLibCtlVertex::renderVertex(GRL_PRIMITIVE_POINTS, 1);
  grlib::CGLibCtlShader::setMemoryBarrierBit(0x21);
  shader->getDefRenderTarget()->setRenderTarget();
}

void LayerObjTopMemObj::lastRender() {
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
  shader->setupTexture(*m_cGLibRenderTarget.unknown70, static_cast<LayerSamplerType>(m_texFilterType), 0);
  shader->renderQuadsIndex();
}

void LayerObjTopMemObj::finalRender() {
  setupRender();
  if (isRender()) {
    lastRender();
  }
}

} // namespace layer
