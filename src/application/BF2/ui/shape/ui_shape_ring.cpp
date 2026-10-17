#include "ui/shape/ui_shape_ring.h"

#include <math.h>

#include "layer/layer_acc_poly_obj.h"

namespace ui {

UIShapeRing::UIShapeRing(u32 num, f32 weight) : divisionNum(num * 4), weight(weight) {
  weightScale = prevWeightScale = 1.0f;
  scale = prevScale = 1.0f;
  setupBuffer(divisionNum * 2, divisionNum * 6);
  u32 vertexNum = divisionNum * 2;
  for (u32 i = 0; i < divisionNum; i++) {
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
  u32 num = divisionNum;
  layer::LayerPolyVertex vertex;
  vertex.u = 0.0f;
  vertex.r = 0xff;
  vertex.g = 0xff;
  vertex.b = 0xff;
  vertex.a = 0xff;
  vertex.v = 0.0f;
  if (num == 0) {
    return;
  }

  f32 step = 360.0f / num * 0.017453292f;
  f32 angle = 1.5707964f;
  for (u32 i = 0; i < divisionNum; i++) {
    f32 dx = cosf(angle);
    f32 dy = -sinf(angle);
    f32 width = weight * 0.5f * weightScale;
    vertex.x = dx * scale + dx * width;
    vertex.y = dy * scale + dy * width;
    vertex.u = 0.0f;
    vertex.v = 0.0f;
    writeVertex(&vertex, 1, i * 2);
    width = weight * 0.5f * weightScale;
    vertex.x = dx * scale - dx * width;
    vertex.y = dy * scale - dy * width;
    vertex.u = 0.0f;
    vertex.v = 1.0f;
    writeVertex(&vertex, 1, i * 2 + 1);
    angle += step;
  }
}

UIShapeRing::~UIShapeRing() { ; }

void UIShapeRing::setScale(f32 scale) { this->scale = scale; }

void UIShapeRing::setWeightScale(f32 weightScale) { this->weightScale = weightScale; }

void UIShapeRing::update(u32 frame) {
  if (scale != prevScale || weightScale != prevWeightScale) {
    buildVertex();
    prevScale = scale;
    prevWeightScale = weightScale;
  }
}

const mm::mtl::RTTI *UIShapeRing::getRTTI() const { return &m_rtti; }

} // namespace ui
