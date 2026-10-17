#pragma once
#include "gf/object/component/behavior/gf_com_behavior.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

class GfComBehaviorGmk : public GfComBehavior {
public:
  static mm::mtl::RTTI m_rtti;

  void createMenuObj();
  void disposeMenuObj();
};

} // namespace gf
