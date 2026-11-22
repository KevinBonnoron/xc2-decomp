#include "layer/layer_obj_font.h"

#include "grlib/cglib_dbl_uniform_block.h"
#include "grlib/cglib_vtx_one_instans.h"
#include "layer/layer_acc_font_obj.h"
#include "layer/layer_font_draw_buffer.h"
#include "layer/layer_font_style_obj.h"
#include "layer/layer_manager.h"
#include "mtl/mem_manager.h"

namespace layer {

LayerObjFont::LayerObjFont() {
  unknown250 = nullptr;
  unknown258[0] = nullptr;
  unknown258[1] = nullptr;
  unknown268 = nullptr;
  m_layerResViewPortInfo = nullptr;
  m_layerFontResObj = nullptr;
  m_layerFontStyleObj = nullptr;
  unknown288 = nullptr;
  m_colorMap = nullptr;
  unknown298 = 0;
  unknown29c = 0;
  m_fontPixelX = 0;
  m_fontPixelY = 0;
  m_fontPixelWidth = 0;
  m_fontPixelHeight = 0;
  m_horizontal = 0;
  m_vertical = 0;
  m_displayArea = 0;
  m_dispSetting = 0;
  m_slopeRot = 0.0f;
  unknown2bc = 0;
  m_borderWeight = 0.0f;
  unknown2c4[0] = 0.0f;
  unknown2c4[1] = 0.0f;
}

void LayerObjFont::workPartsRelease(LayerResFontInfo *&info) {
  info->unknown60->~CGLibVtxOneInstans();
  info->unknown68->~CGLibDblUniformBlock();
  if (info != nullptr) {
    mtl::MemManager::deallocate(info, 0, false);
    info = nullptr;
  }
}

void LayerObjFont::workRelease() {
  if (unknown250 != nullptr) {
    workPartsRelease(unknown250);
  }
  if (unknown258[0] != nullptr) {
    workPartsRelease(unknown258[0]);
  }
  if (unknown258[1] != nullptr) {
    workPartsRelease(unknown258[1]);
  }
  if (unknown268 != nullptr) {
    workPartsRelease(unknown268);
  }
}

void LayerObjFont::setMsg(const u8 *text, const LayerFontResObj *res, const LayerFontStyleObj *style, const LayerFontIconObj *icon, u32 flags) {
  if (unknown258[LayerManager::s_nStkIdx] != nullptr) {
    workPartsRelease(unknown258[LayerManager::s_nStkIdx]);
  }
  m_layerFontResObj = res;
  m_layerFontStyleObj = style;
  unknown298 = flags;
  unknown288 = icon;
  LayerFontDrawBuffer buffer(res, style, style->getStyleData(flags), unknown288, static_cast<LayerFontSetting>(m_dispSetting), this);
  buffer.unknown4a0 = m_horizontal;
  buffer.unknown4a4 = m_vertical;
  unknown258[LayerManager::s_nStkIdx] = buffer.createChar(text);
}

void LayerObjFont::setMsg(const wchar_t *text, const LayerFontResObj *res, const LayerFontStyleObj *style, const LayerFontIconObj *icon, u32 flags) {
  if (unknown258[LayerManager::s_nStkIdx] != nullptr) {
    workPartsRelease(unknown258[LayerManager::s_nStkIdx]);
  }
  m_layerFontResObj = res;
  m_layerFontStyleObj = style;
  unknown298 = flags;
  unknown288 = icon;
  LayerFontDrawBuffer buffer(res, style, style->getStyleData(flags), unknown288, static_cast<LayerFontSetting>(m_dispSetting), this);
  buffer.unknown4a0 = m_horizontal;
  buffer.unknown4a4 = m_vertical;
  unknown258[LayerManager::s_nStkIdx] = buffer.createChar(text);
}

bool LayerObjFont::isMsg(const LayerResFontInfo *info, const u8 *msg) const {
  u32 length = info->unknown18;
  u32 i = 0;
  while (i < length && msg[i] != 0) {
    if (info->unknown10[i] != msg[i]) {
      return false;
    }
    i++;
  }
  return i >= length && msg[i] == 0;
}

bool LayerObjFont::isMsg(const LayerResFontInfo *info, const wchar_t *msg) const {
  u32 length = info->unknown18;
  u32 i = 0;
  while (i < length && msg[i] != 0) {
    if (info->unknown10[i] != reinterpret_cast<const u8 *>(msg)[i]) {
      return false;
    }
    i++;
  }
  return i >= length && msg[i] == 0;
}

void LayerObjFont::updateAddDel() {
  if (unknown268 != nullptr) {
    workPartsRelease(unknown268);
  }
  s32 index = LayerManager::s_nDebIdx;
  if (unknown258[index] != nullptr) {
    unknown268 = unknown250;
    unknown250 = unknown258[index];
    unknown258[index] = nullptr;
  }
}

void LayerObjFont::setColorMap(const LayerFontIconObj *colorMap, u32 index) {
  m_colorMap = colorMap;
  unknown29c = index;
}

void LayerObjFont::setBorderWeight(f32 weight) {
  s32 index = LayerManager::s_nStkIdx;
  unknown2c4[index] = weight;
  unknown2bc |= 1 << index;
}

f32 LayerObjFont::getBorderWeight() const {
  if (unknown2bc & (1 << LayerManager::s_nStkIdx)) {
    return unknown2c4[LayerManager::s_nStkIdx];
  }
  if (unknown2bc & (1 << LayerManager::s_nDebIdx)) {
    return unknown2c4[LayerManager::s_nDebIdx];
  }
  return m_borderWeight;
}

void LayerObjFont::setSlopeRot(f32 rot) { m_slopeRot = rot; }

f32 LayerObjFont::getSlopeRot() const { return m_slopeRot; }

} // namespace layer
