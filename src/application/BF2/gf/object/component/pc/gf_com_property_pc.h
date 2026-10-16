#pragma once
#include <stddef.h>

#include "gf/object/component/property/gf_com_property.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

class GfComPropertyPc : public GfComProperty {
public:
  static mm::mtl::RTTI m_rtti;

  u8 _38[0x160 - 0x38];
  mm::Vec3 position;
};

static_assert(offsetof(GfComPropertyPc, position) == 0x160, "");

} // namespace gf
