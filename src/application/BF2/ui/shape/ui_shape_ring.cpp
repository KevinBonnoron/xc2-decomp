#include "ui/shape/ui_shape_ring.h"

#include <math.h>

#include "layer/layer_acc_poly_obj.h"

namespace ui {

UIShapeRing::UIShapeRing(u32 num, f32 weight) : unknown40(num * 4), unknown44(weight) {
  m_weightScale = unknown54 = 1.0f;
  m_scale = unknown50 = 1.0f;
  setupBuffer(unknown40 * 2, unknown40 * 6);
  u32 vertexNum = unknown40 * 2;
  for (u32 i = 0; i < unknown40; i++) {
    u32 vertex = i * 2;
    u32 index[6];
    index[0] = vertex % vertexNum;
    index[1] = (vertex + 2) % vertexNum;
    index[2] = (vertex + 1) % vertexNum;
    index[3] = (vertex + 2) % vertexNum;
    index[4] = (vertex + 1) % vertexNum;
    index[5] = (vertex + 3) % vertexNum;
    writeIndex(index, 6, i * 6);
  }
  buildVertex();
}

void UIShapeRing::buildVertex() {
  u32 num = unknown40;
  layer::LayerPolyVertex vertex;
  vertex.unknown0c = 0.0f;
  vertex.unknown08 = 0xff;
  vertex.unknown09 = 0xff;
  vertex.unknown0a = 0xff;
  vertex.unknown0b = 0xff;
  vertex.unknown10 = 0.0f;
  if (num == 0) {
    return;
  }

  f32 step = 360.0f / num * 0.017453292f;
  f32 angle = 1.5707964f;
  for (u32 i = 0; i < unknown40; i++) {
    f32 dx = cosf(angle);
    f32 dy = -sinf(angle);
    f32 width = unknown44 * 0.5f * m_weightScale;
    vertex.unknown00 = dx * m_scale + dx * width;
    vertex.unknown04 = dy * m_scale + dy * width;
    vertex.unknown0c = 0.0f;
    vertex.unknown10 = 0.0f;
    writeVertex(&vertex, 1, i * 2);
    width = unknown44 * 0.5f * m_weightScale;
    vertex.unknown00 = dx * m_scale - dx * width;
    vertex.unknown04 = dy * m_scale - dy * width;
    vertex.unknown0c = 0.0f;
    vertex.unknown10 = 1.0f;
    writeVertex(&vertex, 1, i * 2 + 1);
    angle += step;
  }
}

UIShapeRing::~UIShapeRing() { ; }

void UIShapeRing::setScale(f32 scale) { this->m_scale = scale; }

void UIShapeRing::setWeightScale(f32 weightScale) { this->m_weightScale = weightScale; }

void UIShapeRing::update(u32 frame) {
  if (m_scale != unknown50 || m_weightScale != unknown54) {
    buildVertex();
    unknown50 = m_scale;
    unknown54 = m_weightScale;
  }
}

const mm::mtl::RTTI *UIShapeRing::getRTTI() const { return &m_rtti; }

} // namespace ui
