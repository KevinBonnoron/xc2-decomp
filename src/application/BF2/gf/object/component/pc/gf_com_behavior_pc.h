#pragma once
#include "gf/object/component/behavior/gf_com_behavior.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

class GfComBehaviorPc : public GfComBehavior {
public:
  static mm::mtl::RTTI m_rtti;
};

} // namespace gf
