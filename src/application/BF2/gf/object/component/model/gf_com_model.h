#pragma once
#include <stddef.h>

#include "gf/object/component/gf_component.h"
#include "types.h"

namespace fw {
class ModelObject;
} // namespace fw
namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

class GfComModel : public GfComponent {
public:
  static mm::mtl::RTTI m_rtti;
  static const u32 COMPONENT_INDEX = 1;

  void setModelScale(f32 scale);

  u8 _10[0x18 - 0x10];
  fw::ModelObject *modelObject;
};

static_assert(offsetof(GfComModel, modelObject) == 0x18, "");

} // namespace gf
