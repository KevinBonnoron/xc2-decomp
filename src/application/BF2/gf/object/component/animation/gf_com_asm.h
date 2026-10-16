#pragma once
#include "gf/object/component/gf_component.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

enum AnimLayer {
  ANIM_LAYER_BASE = 0,
};

class GfComAsm : public GfComponent {
public:
  static mm::mtl::RTTI m_rtti;
  static const u32 COMPONENT_INDEX = 2;

  const char *getStateName(AnimLayer layer) const;
};

} // namespace gf
