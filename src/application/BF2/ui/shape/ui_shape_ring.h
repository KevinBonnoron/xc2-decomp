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

  u32 divisionNum;
  f32 weight;
  f32 weightScale;
  f32 scale;
  f32 prevScale;
  f32 prevWeightScale;
};

static_assert(offsetof(UIShapeRing, divisionNum) == 0x40, "");
static_assert(offsetof(UIShapeRing, weight) == 0x44, "");
static_assert(offsetof(UIShapeRing, weightScale) == 0x48, "");
static_assert(offsetof(UIShapeRing, scale) == 0x4c, "");
static_assert(offsetof(UIShapeRing, prevScale) == 0x50, "");
static_assert(offsetof(UIShapeRing, prevWeightScale) == 0x54, "");
static_assert(sizeof(UIShapeRing) == 0x58, "");

} // namespace ui
