#pragma once
#include <stddef.h>

#include "types.h"
#include "ui/shape/ui_shape.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace ui {

class UIShapeParticle : public UIShape {
public:
  static mm::mtl::RTTI m_rtti;

  UIShapeParticle(void *data, u32 size, u32 width, u32 height);
  void activate(bool activate);
  bool isActive() const;

  s32 emitterId;
  u32 width;
  u32 height;
};

static_assert(offsetof(UIShapeParticle, emitterId) == 0x40, "");
static_assert(offsetof(UIShapeParticle, width) == 0x44, "");
static_assert(offsetof(UIShapeParticle, height) == 0x48, "");
static_assert(sizeof(UIShapeParticle) == 0x50, "");

} // namespace ui
