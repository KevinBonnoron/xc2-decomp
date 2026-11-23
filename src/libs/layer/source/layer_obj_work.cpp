#include "layer/layer_obj_work.h"

#include "layer/layer_manager.h"
#include "layer/layer_obj_manager.h"
#include "layer/layer_shd_manager.h"
#include "layer/layer_texture_obj.h"
#include "layer/layer_vertex_obj.h"
#include "ml/critical_section.h"
#include "mtl/mem_manager.h"

namespace layer {

LayerObjWork::LayerObjWork() {
  unknown2ac = 0;
  m_layerTextureObj = nullptr;
  m_layerVertexObj = nullptr;
  unknown298 = nullptr;
  unknown290 = nullptr;
  unknown2a0 = 1.0f;
  unknown2a4 = 0;
  unknown2a6 = 0;
  unknown2a8 = 0;
  unknown2b8 = 0.0f;
  unknown280 = nullptr;
  m_textureMax = 0;
  unknown2b0 = nullptr;
}

f32 LayerObjWork::getMaxSecond() const { return unknown298->unknown00->unknown18 * unknown298->unknown00->unknown1c * LayerManager::get()->m_frameRate; }

f32 LayerObjWork::getSecond() const { return unknown2b0->m_second * LayerManager::get()->m_frameRate; }

void LayerObjWork::setSecond(f32 second) { unknown2b0->m_second = LayerManager::get()->unknown80 * second; }

void LayerObjWork::setAddTexture(const void *data, u32 index) {
  ml::CS lock(LayerObjManager::getCriticalSection());
  resetAddTexutre(index);
  m_layerObjResTex.setAddTexture(data, index);
}

void LayerObjWork::resetAddTexutre(u32 index) { m_layerObjResTex.resetAddTexutre(index); }

void LayerObjWork::setAddTexture(grlib::CGLibTextureBuffer &texture, u32 index) {
  ml::CS lock(LayerObjManager::getCriticalSection());
  resetAddTexutre(index);
  m_layerObjResTex.setAddTexture(texture, index);
}

void LayerObjWork::resetAddAllTexutre() { m_layerObjResTex.resetAddAllTexutre(); }

void LayerObjWork::workCreate() {
  u32 offset = static_cast<const unknown013 *>(m_resData)->unknown10;
  if (offset != 0) {
    m_layerVertexObj = LayerManager::get()->m_layerShdManager->m_layerVertexMan->createVertexObj(static_cast<const u8 *>(m_resData) + offset);
  }
}

void LayerObjWork::workRelease() {
  m_layerObjResTex.clear();
  if (m_layerVertexObj != nullptr) {
    m_layerVertexObj->release();
    m_layerVertexObj = nullptr;
  }
  if (m_layerTextureObj != nullptr) {
    m_layerTextureObj->release();
    m_layerTextureObj = nullptr;
  }
  if (unknown290 != nullptr) {
    mtl::MemManager::deallocate(unknown290, 0, false);
    unknown290 = nullptr;
  }
}

void LayerObjWork::setupDefTexList() {
  for (s32 i = 0; i < static_cast<s32>(m_textureMax); i++) {
    unknown280[i] = m_layerTextureObj->getTexture(i);
  }
}

void LayerObjWork::updapteAddTexList() { m_layerObjResTex.updateTexutre(unknown280, m_layerTextureObj); }

void LayerObjWork::calcFrmParm(s32 count) {
  for (s32 i = 0; i < count; i++) {
    unknown2b0[i].m_second = 0.0f;
    unknown2b0[i].unknown04 = 0;
  }
  unknown298->unknown80 = static_cast<f32>(unknown298->unknown00->unknown18);
  unknown298->unknown84 = 0;
  unknown2b8 = 0.0f;
}

} // namespace layer
