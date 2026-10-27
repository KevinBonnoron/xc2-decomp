#include "framework/ik/ik_blow_rotate_solver.h"

#include "anm/anm_pose.h"
#include "anm/anm_qs_transform.h"
#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "mm_mtl/intrusive_ptr.h"

namespace fw {

BlowRotateIkSolver *BlowRotateIkSolver::create(mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose, u32 boneIndex) {
  // __LINE__ of the game: it is the line argument of operator new.
#line 30
  BlowRotateIkSolver *solver = new (Allocator::getProcAllocator(), 16, __FILE__, __LINE__) BlowRotateIkSolver();
  solver->addRef();
  solver->setup(frame, pose);
  solver->unknown50 = boneIndex;
  return solver;
}

bool BlowRotateIkSolver::setup(mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose) {
  bind(frame, pose);
  return true;
}

BlowRotateIkSolver::BlowRotateIkSolver() : unknown40(mm::Quat::identity), unknown50(1) {}

BlowRotateIkSolver::~BlowRotateIkSolver() {}

void BlowRotateIkSolver::calcIK(const UpdateInfo &info) {
  if (unknown18 != nullptr) {
    anm::QsTransform transform = unknown18->getBoneModelSpace(unknown50);
    transform.unknown10 = mm::Quat::mul(unknown40, transform.unknown10);
    unknown18->setBoneModelSpace(unknown50, transform, anm::Pose::PROPAGATE_TYPE_UNKNOWN_1);
  }
}

const mm::mtl::RTTI *BlowRotateIkSolver::getRTTI() const { return &m_rtti; }

} // namespace fw
