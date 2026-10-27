#pragma once
#include <stddef.h>

#include "gf/object/component/behavior/gf_com_behavior.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

class GfComBehaviorNpc : public GfComBehavior {
public:
  static mm::mtl::RTTI m_rtti;

  void validateBindedGmkInstInfo(bool param1);

  u8 _10[0x100 - 0x10];
  bool unknown100; // Role and original member name unknown.
};

static_assert(offsetof(GfComBehaviorNpc, unknown100) == 0x100, "");

} // namespace gf
