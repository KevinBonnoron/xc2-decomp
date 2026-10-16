#pragma once
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

  void activate(bool activate);
  bool isActive() const;
};

} // namespace ui
