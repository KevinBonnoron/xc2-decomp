#include "layer/layer_obj_top_font.h"

#include "layer/layer_base.h"
#include "layer/layer_font_icon_obj.h"
#include "layer/layer_font_res_obj.h"
#include "layer/layer_font_tag.h"
#include "layer/layer_manager.h"
#include "layer/layer_obj_manager.h"
#include "layer/layer_shd_manager.h"
#include "layer/layer_sort_man.h"
#include "layer/layer_texture_obj.h"

namespace layer {

LayerObjTopFont::LayerObjTopFont() {
  unknown18 = LAYER_OBJ_TYPE_FONT;
  unknowna8 |= 0x20000;
}

LayerObjTopFont::~LayerObjTopFont() {
  baseRelease();
  workRelease();
}

void LayerObjTopFont::applyPartsSetup() {
  updateAddDel();
  if (unknown2bc & (1 << LayerManager::s_nDebIdx)) {
    m_borderWeight = unknown2c4[LayerManager::s_nDebIdx];
    unknown2bc &= ~(1 << LayerManager::s_nDebIdx);
  }
}

void LayerObjTopFont::applyParams(const LayerRenderView *view, const LayerResMatrix &matrix, const LayerResColor &color) { updateShaderParms(view, matrix, color); }

void LayerObjTopFont::setDrawList(LayerSortMan *sortMan, bool is3D) {
  if ((unknowna8 & 0x90000) || unknown250 == nullptr) {
    return;
  }
  if (is3D) {
    if (unknowna8 & 0x400) {
      LayerManager::get()->m_layerObjManager->m_layerSortMan->set3DSpace(unknown250->m_layerSortObj, unknown200);
    } else if (!isClip()) {
      sortMan->set2DSpace(unknown250->m_layerSortObj, m_priority);
    }
  } else if (!isClip()) {
    sortMan->set2DSpace(unknown250->m_layerSortObj, m_priority);
  }
}

void LayerObjTopFont::alphaRender() {}

void LayerObjTopFont::lastRender() {}

// Inferred helper: sets up the shader, the instances and the font texture of one font render pass; original name unknown.
inline void LayerObjTopFont::unknown001(LayerShdManager *shader, s16 type) {
  shader->unknown4f6 = type;
  shader->unknown4f0 = 2;
  shader->setupShader(unknown250->unknown68);
  shader->setupInstaceVertex(*unknown250->unknown60, LayerFontTag::FONT_INSTANCE_SIZE, 0);
  shader->setupTexture(*unknown250->m_layerFontResObj->unknown60, static_cast<LayerSamplerType>(m_texFilterType), 0);
}

void LayerObjTopFont::finalRender() {
  LayerShdManager *shader = LayerManager::get()->m_layerShdManager;
  if (!shader->unknown002(m_layerObjTopMaskObj, m_layerResViewPortInfo)) {
    return;
  }
  shader->unknown003(LayerShdManager::s_resDefBlend[unknownc5]);
  shader->unknown004(this);
  shader->setupVertex(static_cast<LayerDefVertType>(2));
  if (unknown250->unknown40 != 0) {
    if (m_borderWeight > LayerManager::get()->m_fontBorderWeight) {
      unknown001(shader, 5);
      shader->renderInstaceQuadsIndex(unknown250->unknown40);
      unknown001(shader, m_colorMap != nullptr ? 4 : 3);
      if (m_colorMap != nullptr) {
        const LayerTextureObj *colorMap = m_colorMap->m_layerTextureObj;
        shader->setupTexture(*colorMap->getTexture(0), static_cast<LayerSamplerType>(m_texFilterType), 1);
      }
      shader->renderInstaceQuadsIndex(unknown250->unknown40);
    } else {
      unknown001(shader, m_colorMap != nullptr ? 2 : 1);
      if (m_colorMap != nullptr) {
        const LayerTextureObj *colorMap = m_colorMap->m_layerTextureObj;
        shader->setupTexture(*colorMap->getTexture(0), static_cast<LayerSamplerType>(m_texFilterType), 1);
      }
      shader->renderInstaceQuadsIndex(unknown250->unknown40);
    }
  }
  if (unknown250->unknown30 == 0) {
    return;
  }
  shader->unknown4f6 = 6;
  shader->unknown4f0 = 2;
  shader->setupShader(unknown250->unknown68);
  shader->setupInstaceVertex(*unknown250->unknown60, LayerFontTag::FONT_INSTANCE_SIZE, unknown250->unknown2c);
  const LayerTextureObj *icon = unknown288->m_layerTextureObj;
  shader->setupTexture(*icon->getTexture(0), static_cast<LayerSamplerType>(m_texFilterType), 0);
  shader->renderInstaceQuadsIndex(unknown250->unknown30);
}

} // namespace layer
