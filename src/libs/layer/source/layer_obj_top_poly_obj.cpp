#include "layer/layer_obj_top_poly_obj.h"

#include <string.h>

#include "grlib/cglib_ctl_vertex.h"
#include "grlib/cglib_texture_buffer.h"
#include "grlib/cglib_vtx_index.h"
#include "grlib/cglib_vtx_vertex.h"
#include "layer/layer_acc_poly_obj.h"
#include "layer/layer_base.h"
#include "layer/layer_link_list.h"
#include "layer/layer_manager.h"
#include "layer/layer_obj_manager.h"
#include "layer/layer_obj_util.h"
#include "layer/layer_render_view.h"
#include "layer/layer_res_add_tex_obj.h"
#include "layer/layer_shd_manager.h"
#include "layer/layer_sort_man.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace layer {

LayerObjTopPolyObj::LayerObjTopPolyObj(u32 width, u32 height, u16 vertexNum, u16 indexNum, LayerPrimitiveType type) : m_layerObjSortPolyObj(this) {
  unknown18 = LAYER_OBJ_TYPE_POLY;
  unknown278 = nullptr;
  m_index = nullptr;
  unknown250 = 0;
  unknown368 = nullptr;
  unknowna8 |= 0x20000;
  m_layerResViewPortInfo = nullptr;
  unknown238 = nullptr;
  createWorkBuffer(width, height);
  createVertex(vertexNum, indexNum, type);
}

LayerObjTopPolyObj::~LayerObjTopPolyObj() {
  baseRelease();
  releaseWorkBuffer();
}

void LayerObjTopPolyObj::releasePoly(layPolyWork &work) {
  if (work.unknown00[0] != nullptr) {
    delete work.unknown00[0];
    work.unknown00[0] = nullptr;
  }
  if (work.unknown00[1] != nullptr) {
    delete work.unknown00[1];
    work.unknown00[1] = nullptr;
  }
  if (work.unknown10[0] != nullptr) {
    delete work.unknown10[0];
    work.unknown10[0] = nullptr;
  }
  if (work.unknown10[1] != nullptr) {
    delete work.unknown10[1];
    work.unknown10[1] = nullptr;
  }
}

void LayerObjTopPolyObj::releaseWorkBuffer() {
  m_cGLibDblUniformBlock.release();
  releasePoly(m_layPolyWork);
  m_layerObjResTex.clear();
  if (unknown368 != nullptr) {
    mtl::MemManager::deallocate(unknown368, 0, false);
    unknown368 = nullptr;
  }
}

void LayerObjTopPolyObj::createWorkBuffer(u32 width, u32 height) {
  m_cGLibDblUniformBlock.setup(0x60);
  unknown005(width, height);
  memset(&m_layPolyWork, 0, sizeof(m_layPolyWork));
}

void LayerObjTopPolyObj::createVertex(u16 vertexNum, u16 indexNum, LayerPrimitiveType type) {
  m_layPolyWork.unknown40 = vertexNum;
  m_layPolyWork.unknown42 = indexNum;
  m_layPolyWork.unknown50 = 1;
  m_layPolyWork.unknown52 = 1;
  m_layPolyWork.unknown44[0] = 0;
  m_layPolyWork.unknown44[1] = 0;
  m_layPolyWork.unknown4c = 0;
  m_layPolyWork.unknown48[1] = indexNum;
  m_layPolyWork.unknown48[0] = indexNum;
  m_layPolyWork.unknown4e = indexNum;
  u32 vertexSize = vertexNum * sizeof(LayerPolyVertex);
  u32 indexSize = indexNum * sizeof(u16);
  u8 *memory = static_cast<u8 *>(mtl::MemManager::allocate(LayerManager::get()->unknown2c, vertexSize * 2 + indexSize * 2, 0x10, false, "no name", 0));
  for (s32 i = 0; i < 2; i++) {
    m_layPolyWork.unknown00[i] = new (LayerManager::get()->unknown2c) grlib::CGLibVtxVertex();
    m_layPolyWork.unknown10[i] = new (LayerManager::get()->unknown2c) grlib::CGLibVtxIndex();
    m_layPolyWork.unknown00[i]->createVertexBuff(vertexSize, sizeof(LayerPolyVertex));
    if (type == LAYER_PRIMITIVE_TYPE_UNKNOWN_0) {
      m_layPolyWork.unknown10[i]->createIndexBuff(indexNum, GRL_PRIMITIVE_TRIANGLES, GRL_INDEX_FORMAT_U16);
    } else {
      m_layPolyWork.unknown10[i]->createIndexBuff(indexNum, GRL_PRIMITIVE_UNKNOWN_6, GRL_INDEX_FORMAT_U16);
    }
    m_layPolyWork.unknown20[i] = &memory[vertexSize * i];
    m_layPolyWork.unknown30[i] = &memory[vertexSize * 2 + indexSize * i];
  }
  unknown368 = memory;
}

void LayerObjTopPolyObj::updateVertexBuffer() {
  void *buffer;
  u32 size;
  if (unknown250 & (4 << LayerManager::s_nDebIdx)) {
    unknown250 &= ~(4 << LayerManager::s_nDebIdx);
    unknown250 |= 1;
    m_layPolyWork.unknown50 = (m_layPolyWork.unknown50 == 0);
    m_layPolyWork.unknown00[m_layPolyWork.unknown50]->lock(&buffer, &size);
    memcpy(buffer, m_layPolyWork.unknown20[LayerManager::s_nDebIdx], size);
    m_layPolyWork.unknown00[m_layPolyWork.unknown50]->unlock();
  }
  if (unknown250 & (0x10 << LayerManager::s_nDebIdx)) {
    unknown250 &= ~(0x10 << LayerManager::s_nDebIdx);
    unknown250 |= 2;
    m_layPolyWork.unknown52 = (m_layPolyWork.unknown52 == 0);
    m_layPolyWork.unknown10[m_layPolyWork.unknown52]->lock(&buffer, &size);
    memcpy(buffer, m_layPolyWork.unknown30[LayerManager::s_nDebIdx], size);
    m_layPolyWork.unknown10[m_layPolyWork.unknown52]->unlock();
  }
  if (unknown250 & (0x40 << LayerManager::s_nDebIdx)) {
    unknown250 &= ~(0x40 << LayerManager::s_nDebIdx);
    m_layPolyWork.unknown4c = m_layPolyWork.unknown44[LayerManager::s_nDebIdx];
    m_layPolyWork.unknown4e = m_layPolyWork.unknown48[LayerManager::s_nDebIdx];
  }
  m_layerObjResTex.updateTexutre(nullptr, nullptr);
  grlib::CGLibTextureBuffer *texture = nullptr;
  if (m_layerObjResTex.unknown00.unknown00 != nullptr) {
    texture = m_layerObjResTex.unknown00.unknown00->getTexObj(0);
  }
  unknown278 = texture;
}

void LayerObjTopPolyObj::applyPartsSetup() { updateVertexBuffer(); }

void LayerObjTopPolyObj::LockVertex() { m_index = m_layPolyWork.unknown20[LayerManager::s_nStkIdx]; }

void LayerObjTopPolyObj::setVertex(u32 index, const LayerPolyVertex &vertex) { static_cast<LayerPolyVertex *>(m_index)[index] = vertex; }

void LayerObjTopPolyObj::UnlockVertex() {
  unknown250 |= 4 << LayerManager::s_nStkIdx;
  m_index = nullptr;
}

void LayerObjTopPolyObj::LockIndex() { m_index = m_layPolyWork.unknown30[LayerManager::s_nStkIdx]; }

void LayerObjTopPolyObj::setIndex(u32 index, u16 vertexIndex) { static_cast<u16 *>(m_index)[index] = vertexIndex; }

void LayerObjTopPolyObj::UnlockIndex() {
  unknown250 |= 0x10 << LayerManager::s_nStkIdx;
  m_index = nullptr;
}

void LayerObjTopPolyObj::setTexutre(const void *data) { m_layerObjResTex.setAddTexture(data, 0); }

void LayerObjTopPolyObj::setTexutre(grlib::CGLibTextureBuffer &texture) { m_layerObjResTex.setAddTexture(texture, 0); }

void LayerObjTopPolyObj::resetTexutre() { m_layerObjResTex.resetAddAllTexutre(); }

void LayerObjTopPolyObj::setIndexInfo(u16 start, u16 num) {
  s32 index = LayerManager::s_nStkIdx;
  unknown250 |= 0x40 << index;
  m_layPolyWork.unknown44[index] = start;
  m_layPolyWork.unknown48[index] = num;
}

void LayerObjTopPolyObj::applyParams(const LayerRenderView *view, const LayerResMatrix &matrix, const LayerResColor &color) { updateUniformBlock(view, matrix, color); }

void LayerObjTopPolyObj::updateUniformBlock(const LayerRenderView *view, const LayerResMatrix &matrix, const LayerResColor &color) {
  m_layerResViewPortInfo = view->m_layerResViewPortInfo;
  m_layerResDispInfo.unknown001();
  LayerObjUtil::calcDispInfo(m_layerResDispInfo, matrix, m_layerResRenderInfo);
  if (unknowna8 & 0x90000) {
    return;
  }
  updateDefUniformBlock(m_cGLibDblUniformBlock, matrix, color, nullptr);
}

void LayerObjTopPolyObj::setDrawList(LayerSortMan *sortMan, bool is3D) {
  if (unknowna8 & 0x90000) {
    return;
  }
  if (is3D) {
    if (unknowna8 & 0x400) {
      LayerManager::get()->m_layerObjManager->m_layerSortMan->set3DSpace(&m_layerObjSortPolyObj, unknown200);
    } else if (!isClip()) {
      sortMan->set2DSpace(&m_layerObjSortPolyObj, m_priority);
    }
  } else if (!isClip()) {
    sortMan->set2DSpace(&m_layerObjSortPolyObj, m_priority);
  }
}

void LayerObjTopPolyObj::finalRender() {
  LayerShdManager *shader = LayerManager::get()->m_layerShdManager;
  if (!shader->unknown002(m_layerObjTopMaskObj, m_layerResViewPortInfo)) {
    return;
  }
  shader->unknown003(LayerShdManager::s_resDefBlend[unknownc5]);
  shader->unknown004(this);
  if (unknown278 != nullptr && unknown278->isInitialized()) {
    shader->unknown4f8 = 2;
  } else {
    shader->unknown4f8 = 1;
  }
  shader->setSecTexture(unknown220[2]);
  grlib::CGLibCtlVertex::setVertex(*m_layPolyWork.unknown00[m_layPolyWork.unknown50]);
  shader->unknown4f0 = 6;
  shader->setupShader(&m_cGLibDblUniformBlock);
  if (unknown278 != nullptr && unknown278->isInitialized()) {
    shader->setupTexture(*unknown278, static_cast<LayerSamplerType>(m_texFilterType), 0);
  }
  m_layPolyWork.unknown10[m_layPolyWork.unknown52]->drawIndex(m_layPolyWork.unknown4e, m_layPolyWork.unknown4c * 2);
}

} // namespace layer
