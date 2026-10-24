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

class UIShapeRing : public UIShape {
public:
  static mm::mtl::RTTI m_rtti;

  UIShapeRing(u32 num, f32 weight);
  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual ~UIShapeRing();
  virtual void update(u32 frame);

  void buildVertex();
  void setScale(f32 scale);
  void setWeightScale(f32 weightScale);

  u32 unknown40; // Inferred role: division num; original member name unknown.
  f32 unknown44; // Inferred role: weight; original member name unknown.
  f32 m_weightScale;
  f32 m_scale;
  f32 unknown50; // Inferred role: prev scale; original member name unknown.
  f32 unknown54; // Inferred role: prev weight scale; original member name unknown.
};

static_assert(offsetof(UIShapeRing, unknown40) == 0x40, "");
static_assert(offsetof(UIShapeRing, unknown44) == 0x44, "");
static_assert(offsetof(UIShapeRing, m_weightScale) == 0x48, "");
static_assert(offsetof(UIShapeRing, m_scale) == 0x4c, "");
static_assert(offsetof(UIShapeRing, unknown50) == 0x50, "");
static_assert(offsetof(UIShapeRing, unknown54) == 0x54, "");
static_assert(sizeof(UIShapeRing) == 0x58, "");

} // namespace ui
