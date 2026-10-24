#include "ui/shape/ui_shape_simple_face.h"

#include "layer/layer_acc_poly_obj.h"
#include "ui/ui_util.h"

namespace ui {

UIShapeSimpleFace::UIShapeSimpleFace(u32 vertexNum) : faceDirty(true) {
  setupBuffer(vertexNum, vertexNum * 3 - 6);
  faceVertices.setAllocator(UIUtil::getProgAllocator());
  faceVertices.reserve(vertexNum);
  for (u32 i = 0; i < vertexNum; i++) {
    faceVertices[i].y = 0.0f;
    faceVertices[i].x = 0.0f;
    faceVertices[i].a = 0xff;
    faceVertices[i].b = 0xff;
    faceVertices[i].g = 0xff;
    faceVertices[i].r = 0xff;
    faceVertices[i].v = 0.0f;
    faceVertices[i].u = 0.0f;
  }
  for (u32 i = 0; i < static_cast<u32>(indices.size()) / 3; i++) {
    u32 index[3] = {i, i + 1, i + 2};
    writeIndex(index, 3, i * 3);
  }
}

UIShapeSimpleFace::~UIShapeSimpleFace() { ; }

void UIShapeSimpleFace::writeFaceVertex(const layer::LayerPolyVertex *vertex, u32 num, u32 offset) {
  if (vertex == nullptr || num == 0) {
    return;
  }

  for (u32 i = 0; i < num; i++) {
    u32 index = offset + i;
    if (index >= faceVertices.size()) {
      return;
    }
    faceVertices[index] = vertex[i];
  }
  faceDirty = true;
}

static bool isCross(const layer::LayerPolyVertex &a, const layer::LayerPolyVertex &b, const layer::LayerPolyVertex &c, const layer::LayerPolyVertex &d) {
  f32 ta = (c.x - d.x) * (a.y - c.y) + (c.y - d.y) * (c.x - a.x);
  f32 tb = (c.x - d.x) * (b.y - c.y) + (c.y - d.y) * (c.x - b.x);
  f32 tc = (a.x - b.x) * (c.y - a.y) + (a.y - b.y) * (a.x - c.x);
  f32 td = (a.x - b.x) * (d.y - a.y) + (a.y - b.y) * (a.x - d.x);
  return tc * td < 0.0f && ta * tb < 0.0f;
}

void UIShapeSimpleFace::update(u32 frame) {
  if (!faceDirty) {
    return;
  }

  writeVertex(&faceVertices[0], faceVertices.size(), 0);
  for (u32 i = 0; i < static_cast<u32>(vertices.size()) - 1; i++) {
    u32 top = i;
    for (u32 j = i + 1; j < static_cast<u32>(vertices.size()); j++) {
      if (vertices[j].y < vertices[top].y || (vertices[j].y == vertices[top].y && vertices[j].x > vertices[top].x)) {
        top = j;
      }
    }
    if (i != top) {
      layer::LayerPolyVertex vertex = vertices[i];
      writeVertex(&vertices[top], 1, i);
      writeVertex(&vertex, 1, top);
    }
  }
  for (u32 i = 0; i < static_cast<u32>(vertices.size()) - 3; i++) {
    if (isCross(vertices[i], vertices[i + 2], vertices[i + 1], vertices[i + 3])) {
      layer::LayerPolyVertex vertex = vertices[i];
      writeVertex(&vertices[i + 1], 1, i);
      writeVertex(&vertex, 1, i + 1);
    }
  }
  faceDirty = false;
}

const mm::mtl::RTTI *UIShapeSimpleFace::getRTTI() const { return &m_rtti; }

} // namespace ui
