#pragma once
#include <stddef.h>

#include "gf/object/component/gf_component.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

class GfComDynamics : public GfComponent {
public:
  static mm::mtl::RTTI m_rtti;
  static const u32 COMPONENT_INDEX = 8;

  void resetMovement();
  u32 getSolverCount() const;
  void setSolverBlendWeight(u32 index, f32 weight);

  u8 _10[0x82 - 0x10];
  bool isReset;
};

static_assert(offsetof(GfComDynamics, isReset) == 0x82, "");

} // namespace gf
