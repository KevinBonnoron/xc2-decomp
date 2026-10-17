#pragma once
#include "gf/object/component/gf_component.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

class GfComAnimation : public GfComponent {
public:
  static mm::mtl::RTTI m_rtti;

  GfComAnimation();
  ~GfComAnimation() override;
  const mm::mtl::RTTI *getRTTI() const override;
};

} // namespace gf
