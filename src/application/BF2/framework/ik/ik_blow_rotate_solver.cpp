#include "framework/ik/ik_blow_rotate_solver.h"

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
  solver->boneIndex = boneIndex;
  return solver;
}

bool BlowRotateIkSolver::setup(mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose) {
  bind(frame, pose);
  return true;
}

BlowRotateIkSolver::BlowRotateIkSolver() : rotation(mm::Quat::identity), boneIndex(1) {}

BlowRotateIkSolver::~BlowRotateIkSolver() {}

const mm::mtl::RTTI *BlowRotateIkSolver::getRTTI() const { return &m_rtti; }

} // namespace fw
