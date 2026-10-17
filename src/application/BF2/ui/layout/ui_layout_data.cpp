#include "ui/layout/ui_layout_data.h"

#include "framework/memory/framework_memory.h"
#include "layer/layer_acc_layout_binary.h"
#include "mm_math/mm_rect.h"

namespace ui {

UILayoutData::UILayoutData(void *data) : data(data), parent(nullptr) {}

UILayoutData::~UILayoutData() { ; }

UILayoutData *UILayoutData::create(void *data, mm::mtl::IAllocator *allocator, const UILayoutData *parent) {
// __LINE__ is the line argument of the operator new call.
#line 47
  UILayoutData *layoutData = new (allocator, 16, __FILE__, __LINE__) UILayoutData(data);
  layoutData->addRef();
  layoutData->parent = parent;
  return layoutData;
}

bool UILayoutData::getLayoutRect(const char *name, mm::Rect<s16> &rect) const {
  if (data == nullptr) {
    return false;
  }

  layer::LayerAccLayoutBinary binary(data);
  u32 index = binary.getPosIdx(name);
  if (index == 0xffffffff && parent != nullptr) {
    return parent->getLayoutRect(name, rect);
  }

  f32 pos[2];
  f32 size[2];
  binary.setLayoutPosData(pos[0], pos[1], size[0], size[1], index);
  rect.x = pos[0];
  rect.y = pos[1];
  rect.width = size[0];
  rect.height = size[1];
  return true;
}

} // namespace ui
