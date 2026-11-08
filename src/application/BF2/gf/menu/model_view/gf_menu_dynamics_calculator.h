#pragma once
#include <stddef.h>

#include "framework/dynamics/force_calculator.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

// Evidence: size 0x20 from the operator new of create; the constructor stores the two vtables at 0x00 and 0x10 (ForceCalculator and its skd::ForceInterface base), the reference
// count at 0x08 and zeroes the member at 0x18.
class MenuForceCalculator : public fw::ForceCalculator {
public:
  static mm::mtl::RTTI m_rtti;

  static mm::mtl::IntrusivePtr<MenuForceCalculator> create();
  MenuForceCalculator();
  ~MenuForceCalculator() override;
  void calcForce(f32 deltaTime, const skd::DynamicsSolver &solver, mm::mtl::Vector<mm::Vec3> *forces) override;
  const mm::mtl::RTTI *getRTTI() const override;

  f32 unknown18; // Inferred role: elapsed time; original member name unknown.
};

static_assert(offsetof(MenuForceCalculator, unknown18) == 0x18, "");
static_assert(sizeof(MenuForceCalculator) == 0x20, "");

} // namespace gf
