#include "ui/shape/ui_shape.h"

#include "layer/layer_acc_poly_obj.h"
#include "ui/ui_util.h"

namespace ui {

UIShape::UIShape() : dirty(false) {}

UIShape::~UIShape() {
  if (vertices.size() != 0) {
    vertices.destroy();
  }
  if (indices.size() != 0) {
    indices.destroy();
  }
}

void UIShape::setupBuffer(u32 vertexNum, u32 indexNum) {
  vertices.setAllocator(UIUtil::getProgAllocator());
  indices.setAllocator(UIUtil::getProgAllocator());
  vertices.reserve(vertexNum);
  indices.reserve(indexNum);
  for (u32 i = 0; i < vertexNum; i++) {
    vertices[i].y = 0.0f;
    vertices[i].x = 0.0f;
    vertices[i].a = 0xff;
    vertices[i].b = 0xff;
    vertices[i].g = 0xff;
    vertices[i].r = 0xff;
    vertices[i].v = 0.0f;
    vertices[i].u = 0.0f;
  }
  for (u32 i = 0; i < indexNum; i++) {
    indices[i] = 0;
  }
  indexRange = indexNum;
  dirty = true;
}

void UIShape::writeVertex(const layer::LayerPolyVertex *vertex, u32 num, u32 offset) {
  if (vertex == nullptr || num == 0) {
    return;
  }

  dirty = true;
  for (u32 i = 0; i < num; i++) {
    u32 index = offset + i;
    if (index >= vertices.size()) {
      break;
    }
    vertices[index] = vertex[i];
  }
}

void UIShape::writeIndex(const u32 *index, u32 num, u32 offset) {
  if (index == nullptr || num == 0) {
    return;
  }

  dirty = true;
  for (u32 i = 0; i < num; i++) {
    u32 position = offset + i;
    if (position >= indices.size()) {
      break;
    }
    indices[position] = index[i];
  }
}

void UIShape::setIndexRange(u32 range) { indexRange = range > indices.size() ? static_cast<u32>(indices.size()) : range; }

const mm::mtl::RTTI *UIShape::getRTTI() const { return &m_rtti; }

void UIShape::update(u32 frame) {}

} // namespace ui
