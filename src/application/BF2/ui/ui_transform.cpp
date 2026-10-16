#include "ui/ui_transform.h"

namespace ui {

UITransform::UITransform() {
  pos.x = 0;
  pos.y = 0;
  scale.x = 1.0f;
  scale.y = 1.0f;
  rot = 0.0f;
  dirty = false;
}

UITransform::~UITransform() { ; }

void UITransform::syncParent() {}

void UITransform::setPos(s16 x, s16 y) {
  if (pos.x != x || pos.y != y) {
    dirty = true;
  }
  pos.x = x;
  pos.y = y;
}

void UITransform::setScale(f32 x, f32 y) {
  if (scale.x != x || scale.y != y) {
    dirty = true;
  }
  scale.x = x;
  scale.y = y;
}

void UITransform::setParent(const UITransform *, bool) {}

UITransform &UITransform::operator=(const UITransform &other) {
  pos = other.pos;
  scale = other.scale;
  rot = other.rot;
  rot = other.rot;
  dirty = true;
  return *this;
}

} // namespace ui
