#include "framework/ik/ik_spine_rotate_solver.h"

#include "anm/anm_pose.h"
#include "anm/anm_skeleton.h"
#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "mm_mtl/intrusive_ptr.h"

namespace fw {

SpineRotateIKSolver *SpineRotateIKSolver::create(const ParamAdapter &param, const char *boneName, const char *endBoneName, mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose) {
#line 42
  SpineRotateIKSolver *solver = new (Allocator::getProcAllocator(), 16, __FILE__, __LINE__) SpineRotateIKSolver();
  solver->addRef();
  bool isSetup = solver->setupLimit(param, boneName, endBoneName, frame, pose);
  if (solver != nullptr && !isSetup) {
    solver->release();
    solver = nullptr;
  }

  return solver;
}

bool SpineRotateIKSolver::setupLimit(const ParamAdapter &param, const char *boneName, const char *endBoneName, mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose) {
  bind(frame, pose);
  unknown38 = param;
  const anm::Skeleton *skeleton = unknown18->unknown18;
  if (boneName != nullptr) {
    unknown40 = skeleton->getBoneID(boneName);
  }
  if (endBoneName != nullptr) {
    unknown42 = skeleton->getBoneID(endBoneName);
  }

  return unknown40 != anm::Skeleton::INVALID_BONE || unknown42 != anm::Skeleton::INVALID_BONE;
}

SpineRotateIKSolver::SpineRotateIKSolver() : unknown38(), unknown40(0xffff), unknown42(0xffff), unknown44() {}

SpineRotateIKSolver::~SpineRotateIKSolver() {}

const mm::mtl::RTTI *SpineRotateIKSolver::getRTTI() const { return &m_rtti; }

} // namespace fw
