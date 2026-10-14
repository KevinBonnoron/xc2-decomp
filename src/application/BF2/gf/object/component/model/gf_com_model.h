#pragma once
#include "gf/object/component/gf_component.h"
#include "types.h"

namespace gf {

class GfComModel : public GfComponent {
public:
  static mm::mtl::RTTI m_rtti;
  static const u32 COMPONENT_INDEX = 1;
};

} // namespace gf
