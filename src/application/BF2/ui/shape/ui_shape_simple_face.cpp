#include "ui/shape/ui_shape_simple_face.h"

#include "layer/layer_acc_poly_obj.h"
#include "ui/ui_util.h"

namespace ui {

UIShapeSimpleFace::UIShapeSimpleFace(u32 vertexNum) : unknown58(true) {
  setupBuffer(vertexNum, vertexNum * 3 - 6);
  unknown40.setAllocator(UIUtil::getProgAllocator());
  unknown40.reserve(vertexNum);
  for (u32 i = 0; i < vertexNum; i++) {
    unknown40[i].unknown04 = 0.0f;
    unknown40[i].unknown00 = 0.0f;
    unknown40[i].unknown0b = 0xff;
    unknown40[i].unknown0a = 0xff;
    unknown40[i].unknown09 = 0xff;
    unknown40[i].unknown08 = 0xff;
    unknown40[i].unknown10 = 0.0f;
    unknown40[i].unknown0c = 0.0f;
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
  f32 ta = (c.unknown00 - d.unknown00) * (a.unknown04 - c.unknown04) + (c.unknown04 - d.unknown04) * (c.unknown00 - a.unknown00);
  f32 tb = (c.unknown00 - d.unknown00) * (b.unknown04 - c.unknown04) + (c.unknown04 - d.unknown04) * (c.unknown00 - b.unknown00);
  f32 tc = (a.unknown00 - b.unknown00) * (c.unknown04 - a.unknown04) + (a.unknown04 - b.unknown04) * (a.unknown00 - c.unknown00);
  f32 td = (a.unknown00 - b.unknown00) * (d.unknown04 - a.unknown04) + (a.unknown04 - b.unknown04) * (a.unknown00 - d.unknown00);
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
      if (unknown08[j].unknown04 < unknown08[top].unknown04 || (unknown08[j].unknown04 == unknown08[top].unknown04 && unknown08[j].unknown00 > unknown08[top].unknown00)) {
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
