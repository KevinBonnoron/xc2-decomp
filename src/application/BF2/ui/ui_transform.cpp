#include "ui/ui_transform.h"

namespace ui {

UITransform::UITransform() {
  unknown08.x = 0;
  unknown08.y = 0;
  unknown10.x = 1.0f;
  unknown10.y = 1.0f;
  unknown20 = 0.0f;
  unknown24 = false;
}

UITransform::~UITransform() { ; }

void UITransform::syncParent() {}

void UITransform::setPos(s16 x, s16 y) {
  if (unknown08.x != x || unknown08.y != y) {
    unknown24 = true;
  }
  unknown08.x = x;
  unknown08.y = y;
}

void UITransform::setScale(f32 x, f32 y) {
  if (unknown10.x != x || unknown10.y != y) {
    unknown24 = true;
  }
  unknown10.x = x;
  unknown10.y = y;
}

void UITransform::setParent(const UITransform *, bool) {}

UITransform &UITransform::operator=(const UITransform &other) {
  unknown08 = other.unknown08;
  unknown10 = other.unknown10;
  unknown20 = other.unknown20;
  unknown20 = other.unknown20;
  unknown24 = true;
  return *this;
}

} // namespace ui
