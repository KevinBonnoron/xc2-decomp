#include "framework/ik/ik_slope_ground_solver.h"

#include "framework/ik/ik_foot_placement_solver.h"

namespace fw {

SlopeGroundSolver::~SlopeGroundSolver() {}

void SlopeGroundSolver::setEnablePlacement(bool enable) {
  unknown89 = enable;
  for (u32 i = 0; i < unknown50.size(); i++) {
    if (unknown50[i].get() != nullptr) {
      unknown50[i]->unknown003(enable);
    }
  }
}

const mm::mtl::RTTI *SlopeGroundSolver::getRTTI() const { return &m_rtti; }

} // namespace fw
