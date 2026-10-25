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
  virtual ~UIShapeParticle();
  void activate(bool activate);
  bool isActive() const;
  virtual const mm::mtl::RTTI *getRTTI() const;

  s32 unknown40; // Inferred role: emitter id; original member name unknown.
  u32 unknown44; // Inferred role: width; original member name unknown.
  u32 unknown48; // Inferred role: height; original member name unknown.
};

static_assert(offsetof(UIShapeParticle, unknown40) == 0x40, "");
static_assert(offsetof(UIShapeParticle, unknown44) == 0x44, "");
static_assert(offsetof(UIShapeParticle, unknown48) == 0x48, "");
static_assert(sizeof(UIShapeParticle) == 0x50, "");

} // namespace ui
