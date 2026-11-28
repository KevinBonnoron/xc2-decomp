#include "gf/menu/model_view/gf_menu_dynamics_calculator.h"

#include <math.h>

#include "anm/anm_array-inl.h"
#include "framework/memory/framework_memory.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/vector.h"
#include "skd/skd_dynamics.h"

namespace gf {

mm::mtl::IntrusivePtr<MenuForceCalculator> MenuForceCalculator::create() {
#line 30
  return new (fw::FrameworkMemory::getAllocator(5), 16, __FILE__, __LINE__) MenuForceCalculator();
}

MenuForceCalculator::MenuForceCalculator() : unknown18(0.0f) {}

MenuForceCalculator::~MenuForceCalculator() {}

void MenuForceCalculator::calcForce(f32 deltaTime, const skd::DynamicsSolver &solver, mm::mtl::Vector<mm::Vec3> *forces) {
  if (solver.unknown78 == 0) {
    unknown18 += deltaTime;
  }
  mm::Vec3 force = mm::Vec3::zero;
  if (unknown18 >= 1.0f && unknown18 < 10.0f) {
    // Decisions 44 and 57: the named product leaves a DBG_VALUE between the fmul and the fmov of the phi. Compared with and without the local (-g, print-after-all):
    // from SROA on, the IR and the register allocation are identical (up to that DBG_VALUE), and the first differing pass is "A57 FP Anti-dependency breaker"
    // (AArch64A57FPLoadBalancing): the game's `fmul s0, s0, s1` (0x71003e2318) with the local, `fmul s1, s0, s1` without it (107 instructions either way).
    f32 swing = sinf((unknown18 - 1.0f) / 9.0f * 6.2831855f) * 100.0f;
    force.z = swing;
  }
  for (u32 i = 0; i < forces->size(); i++) {
    const skd::ResNode &node = (*solver.unknown10.unknown00)[i];
    (*forces)[i] = mm::Vec3(force.x * node.unknown1c, force.y * node.unknown1c, force.z * node.unknown1c);
  }
}

const mm::mtl::RTTI *MenuForceCalculator::getRTTI() const { return &m_rtti; }

} // namespace gf
