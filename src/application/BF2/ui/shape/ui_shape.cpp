#include "ui/shape/ui_shape.h"

#include "layer/layer_acc_poly_obj.h"
#include "ui/ui_util.h"

namespace ui {

UIShape::UIShape() : unknown3c(false) {}

UIShape::~UIShape() {
  if (unknown08.size() != 0) {
    unknown08.destroy();
  }
  if (unknown20.size() != 0) {
    unknown20.destroy();
  }
}

void UIShape::setupBuffer(u32 vertexNum, u32 indexNum) {
  unknown08.setAllocator(UIUtil::getProgAllocator());
  unknown20.setAllocator(UIUtil::getProgAllocator());
  unknown08.reserve(vertexNum);
  unknown20.reserve(indexNum);
  for (u32 i = 0; i < vertexNum; i++) {
    unknown08[i].unknown04 = 0.0f;
    unknown08[i].unknown00 = 0.0f;
    unknown08[i].unknown0b = 0xff;
    unknown08[i].unknown0a = 0xff;
    unknown08[i].unknown09 = 0xff;
    unknown08[i].unknown08 = 0xff;
    unknown08[i].unknown10 = 0.0f;
    unknown08[i].unknown0c = 0.0f;
  }
  for (u32 i = 0; i < indexNum; i++) {
    unknown20[i] = 0;
  }
  unknown38 = indexNum;
  unknown3c = true;
}

void UIShape::writeVertex(const layer::LayerPolyVertex *vertex, u32 num, u32 offset) {
  if (vertex == nullptr || num == 0) {
    return;
  }

  unknown3c = true;
  for (u32 i = 0; i < num; i++) {
    u32 index = offset + i;
    if (index >= unknown08.size()) {
      break;
    }
    unknown08[index] = vertex[i];
  }
}

void UIShape::writeIndex(const u32 *index, u32 num, u32 offset) {
  if (index == nullptr || num == 0) {
    return;
  }

  unknown3c = true;
  for (u32 i = 0; i < num; i++) {
    u32 position = offset + i;
    if (position >= unknown20.size()) {
      break;
    }
    unknown20[position] = index[i];
  }
}

void UIShape::setIndexRange(u32 range) { unknown38 = range > unknown20.size() ? static_cast<u32>(unknown20.size()) : range; }

const mm::mtl::RTTI *UIShape::getRTTI() const { return &m_rtti; }

void UIShape::update(u32 frame) {}

} // namespace ui
