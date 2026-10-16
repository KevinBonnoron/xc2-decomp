#pragma once
#include <stddef.h>

#include "types.h"
#include "ui/ui_object.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace ui {

class UIShape;

class UIPolygonObject : public UIObject {
public:
  enum ShapeType {
    SHAPE_TYPE_SIMPLE_FACE = 1,
    SHAPE_TYPE_RING = 2,
    SHAPE_TYPE_PARTICLE = 3,
  };

  static mm::mtl::RTTI m_rtti;

  UIShape *shape;
  u8 _110[0x118 - 0x110];
  u32 shapeType;
};

static_assert(offsetof(UIPolygonObject, shape) == 0x108, "");
static_assert(offsetof(UIPolygonObject, shapeType) == 0x118, "");

} // namespace ui
