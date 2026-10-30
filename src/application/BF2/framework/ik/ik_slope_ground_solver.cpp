#include "framework/ik/ik_slope_ground_solver.h"

#include "framework/ik/ik_foot_placement_solver.h"
#include "fw/fw_param_manager.h"

namespace fw {
class IKFootGroundInterface;

SlopeGroundSolver::~SlopeGroundSolver() {}

FootPlacementIKSolver *SlopeGroundSolver::createFootPlacementIK(IKFootIndex index, ParamAdapter &param, const char *footName, const char *kneeName, const char *hipName, bool isMirror) {
  FootPlacementIKSolver::Description description;
  description.unknown00 = footName;
  description.unknown08 = kneeName;
  description.unknown10 = hipName;
  description.unknown25 = isMirror;
  description.unknown28 = param;
  IKFootGroundInterface *ground = unknown90 != nullptr ? unknown90->getFootGround(index) : nullptr;
  FootPlacementIKSolver *solver = FootPlacementIKSolver::create(description, unknown10, *unknown18, ground);
  unknown50[index] = solver;
  if (solver != nullptr) {
    solver->release();
  }
  return solver;
}

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
