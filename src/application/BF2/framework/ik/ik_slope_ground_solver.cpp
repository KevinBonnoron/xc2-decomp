#include "framework/ik/ik_slope_ground_solver.h"

#include "framework/ik/ik_foot_placement_solver.h"
#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "fw/fw_param_manager.h"

namespace fw {
class IKFootGroundInterface;
struct UpdateInfo;

// __LINE__ of the game: it is the line argument of operator new.
#line 33
SlopeGroundSolver *SlopeGroundSolver::create(const Description &description, mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose, IKGroundInterface *ground) {
  SlopeGroundSolver *solver = new (Allocator::getProcAllocator(), 16, __FILE__, __LINE__) SlopeGroundSolver();
  solver->addRef();
  solver->createImpl(description, frame, pose, ground);
  return solver;
}

SlopeGroundSolver::SlopeGroundSolver() : unknown40(mm::Quat::identity), unknown88(true), unknown89(true) {}

SlopeGroundSolver::~SlopeGroundSolver() {}

FootPlacementIKSolver *SlopeGroundSolver::createFootPlacementIK(IKFootIndex index, ParamAdapter &param, const char *footName, const char *kneeName, const char *hipName, bool isMirror) {
  FootPlacementIKSolver::Description description;
  description.unknown00 = footName;
  description.unknown08 = kneeName;
  description.unknown10 = hipName;
  description.unknown25 = isMirror;
  description.m_paramAdapter = param;
  IKFootGroundInterface *ground = m_iKGroundInterface != nullptr ? m_iKGroundInterface->getFootGround(index) : nullptr;
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

void SlopeGroundSolver::solve(const UpdateInfo &info) {
  if (m_iKGroundInterface != nullptr) {
    slopeBody(info);
    if (unknown50.size() != 0) {
      solveFoot(info);
    }
  }
}

void SlopeGroundSolver::solveFoot(const UpdateInfo &info) {
  for (u32 i = 0; i < unknown50.size(); i++) {
    if (unknown50[i].get() != nullptr) {
      unknown50[i]->unknownc0 = unknown40;
      unknown50[i]->solve(info);
    }
  }
}

const mm::mtl::RTTI *SlopeGroundSolver::getRTTI() const { return &m_rtti; }

} // namespace fw
