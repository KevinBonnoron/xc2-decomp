#include "ui/layout/ui_layout_data.h"

#include "framework/memory/framework_memory.h"
#include "layer/layer_acc_layout_binary.h"
#include "layer/layer_obj.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "ui/ui_displayinfo.h"
#include "ui/ui_object.h"
#include "ui/ui_transform.h"

namespace ui {

UILayoutData::UILayoutData(void *data) : unknown10(data), unknown18(nullptr) {}

UILayoutData::~UILayoutData() { ; }

UILayoutData *UILayoutData::create(void *data, mm::mtl::IAllocator *allocator, const UILayoutData *parent) {
// __LINE__ is the line argument of the operator new call.
#line 47
  UILayoutData *layoutData = new (allocator, 16, __FILE__, __LINE__) UILayoutData(data);
  layoutData->addRef();
  layoutData->unknown18 = parent;
  return layoutData;
}

bool UILayoutData::attachLayout(const char *name, UIObject *object) const {
  layer::LayerAccLayoutBinary binary(unknown10);
  u32 index = binary.getPosIdx(name);
  if (index == 0xffffffff) {
    return unknown18 != nullptr ? unknown18->attachLayout(name, object) : false;
  }

  if (object->unknownd8 == UI_OBJECT_TYPE_LAYOUT) {
    f32 pos[2];
    f32 size[2];
    binary.setLayoutPosData(pos[0], pos[1], size[0], size[1], name);
    if (object->unknown50.unknown2c == 1 || object->unknown50.unknown2e == 1) {
      object->setPos(mm::Pnt<s16>(static_cast<s16>(pos[0]), static_cast<s16>(pos[1])));
    } else {
      object->setPosCenter(mm::Pnt<s16>(static_cast<s16>(pos[0] + size[0] * 0.5f), static_cast<s16>(pos[1] + size[1] * 0.5f)));
      object->unknown20.setScale(size[0] / object->unknown50.unknown2c, size[1] / object->unknown50.unknown2e);
    }
  } else {
    binary.setLayoutObj(static_cast<layer::LayerObj *>(object->unknownc8), name, true);
    UIObject::importTransform(object->unknown20, object->unknownc8);
    if (object->unknown50.unknown09 == UI_DISPLAY_MODE_CENTER) {
      mm::Pnt<s16> pos;
      pos.x = object->unknown20.getPos().x;
      pos.y = object->unknown20.getPos().y;
      object->setPosCenter(pos);
    }
  }
  return true;
}

bool UILayoutData::getLayoutRect(const char *name, mm::Rect<s16> &rect) const {
  if (unknown10 == nullptr) {
    return false;
  }

  layer::LayerAccLayoutBinary binary(unknown10);
  u32 index = binary.getPosIdx(name);
  if (index == 0xffffffff && unknown18 != nullptr) {
    return unknown18->getLayoutRect(name, rect);
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
