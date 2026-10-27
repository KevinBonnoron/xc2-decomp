#include "layer/layer_obj_font.h"

#include "layer/layer_manager.h"

namespace layer {

void LayerObjFont::setColorMap(const LayerFontIconObj *colorMap, u32 index) {
  m_colorMap = colorMap;
  unknown29c = index;
}

void LayerObjFont::setBorderWeight(f32 weight) {
  s32 index = LayerManager::s_nStkIdx;
  unknown2c4[index] = weight;
  unknown2bc |= 1 << index;
}

void LayerObjFont::setSlopeRot(f32 rot) { m_slopeRot = rot; }

f32 LayerObjFont::getSlopeRot() const { return m_slopeRot; }

} // namespace layer
