#pragma once
#include <stddef.h>

#include "fw/fw_param_manager.h"
#include "gf/object/component/property/gf_com_property.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_ptr.h"
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
  u8 _170[0x318 - 0x170];
  mm::mtl::IntrusivePtr<fw::ParamList> paramList;
};

static_assert(offsetof(GfComPropertyPc, position) == 0x160, "");
static_assert(offsetof(GfComPropertyPc, paramList) == 0x318, "");

} // namespace gf
