#pragma once
#include "gf/object/component/gf_component.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

class GfComBehavior : public GfComponent {
public:
  static mm::mtl::RTTI m_rtti;
};

} // namespace gf
