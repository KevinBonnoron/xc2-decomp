#include "ui/shape/ui_shape_simple_face.h"

#include "layer/layer_acc_poly_obj.h"
#include "ui/ui_util.h"

namespace ui {

UIShapeSimpleFace::UIShapeSimpleFace(u32 vertexNum) : unknown58(true) {
  setupBuffer(vertexNum, vertexNum * 3 - 6);
  unknown40.setAllocator(UIUtil::getProgAllocator());
  unknown40.reserve(vertexNum);
  for (u32 i = 0; i < vertexNum; i++) {
    unknown40[i].y = 0.0f;
    unknown40[i].x = 0.0f;
    unknown40[i].a = 0xff;
    unknown40[i].b = 0xff;
    unknown40[i].g = 0xff;
    unknown40[i].r = 0xff;
    unknown40[i].v = 0.0f;
    unknown40[i].u = 0.0f;
  }
  for (u32 i = 0; i < static_cast<u32>(unknown20.size()) / 3; i++) {
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
    if (index >= unknown40.size()) {
      return;
    }
    unknown40[index] = vertex[i];
  }
  unknown58 = true;
}

static bool isCross(const layer::LayerPolyVertex &a, const layer::LayerPolyVertex &b, const layer::LayerPolyVertex &c, const layer::LayerPolyVertex &d) {
  f32 ta = (c.x - d.x) * (a.y - c.y) + (c.y - d.y) * (c.x - a.x);
  f32 tb = (c.x - d.x) * (b.y - c.y) + (c.y - d.y) * (c.x - b.x);
  f32 tc = (a.x - b.x) * (c.y - a.y) + (a.y - b.y) * (a.x - c.x);
  f32 td = (a.x - b.x) * (d.y - a.y) + (a.y - b.y) * (a.x - d.x);
  return tc * td < 0.0f && ta * tb < 0.0f;
}

void UIShapeSimpleFace::update(u32 frame) {
  if (!unknown58) {
    return;
  }

  writeVertex(&unknown40[0], unknown40.size(), 0);
  for (u32 i = 0; i < static_cast<u32>(unknown08.size()) - 1; i++) {
    u32 top = i;
    for (u32 j = i + 1; j < static_cast<u32>(unknown08.size()); j++) {
      if (unknown08[j].y < unknown08[top].y || (unknown08[j].y == unknown08[top].y && unknown08[j].x > unknown08[top].x)) {
        top = j;
      }
    }
    if (i != top) {
      layer::LayerPolyVertex vertex = unknown08[i];
      writeVertex(&unknown08[top], 1, i);
      writeVertex(&vertex, 1, top);
    }
  }
  for (u32 i = 0; i < static_cast<u32>(unknown08.size()) - 3; i++) {
    if (isCross(unknown08[i], unknown08[i + 2], unknown08[i + 1], unknown08[i + 3])) {
      layer::LayerPolyVertex vertex = unknown08[i];
      writeVertex(&unknown08[i + 1], 1, i);
      writeVertex(&vertex, 1, i + 1);
    }
  }
  unknown58 = false;
}

const mm::mtl::RTTI *UIShapeSimpleFace::getRTTI() const { return &m_rtti; }

} // namespace ui
