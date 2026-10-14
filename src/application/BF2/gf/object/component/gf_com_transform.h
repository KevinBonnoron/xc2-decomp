#pragma once
#include "gf/object/component/gf_component.h"
#include "types.h"

namespace gf {

class GfComTransform : public GfComponent {
public:
  static mm::mtl::RTTI m_rtti;
  static const u32 COMPONENT_INDEX = 0;
};

} // namespace gf
