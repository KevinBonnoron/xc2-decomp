#include "gf/menu/model_view/gf_menu_dynamics_calculator.h"

#include "framework/memory/framework_memory.h"

namespace gf {

mm::mtl::IntrusivePtr<MenuForceCalculator> MenuForceCalculator::create() {
#line 30
  return new (fw::FrameworkMemory::getAllocator(5), 16, __FILE__, __LINE__) MenuForceCalculator();
}

MenuForceCalculator::MenuForceCalculator() : unknown18(0.0f) {}

MenuForceCalculator::~MenuForceCalculator() {}

const mm::mtl::RTTI *MenuForceCalculator::getRTTI() const { return &m_rtti; }

} // namespace gf
