#include "framework/ik/ik_trans_solver.h"

#include "anm/anm_pose.h"
#include "anm/anm_skeleton.h"
#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/reference_object.h"

namespace fw {

TransLocalIkSolver *TransLocalIkSolver::create(const char *boneName, mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose) {
  // __LINE__ of the game: it is the line argument of operator new.
#line 31
  TransLocalIkSolver *solver = new (Allocator::getProcAllocator(), 16, __FILE__, __LINE__) TransLocalIkSolver();
  solver->addRef();
  if (!solver->setup(boneName, frame, pose)) {
    mm::mtl::safeRelease(solver);
  }

  return solver;
}

bool TransLocalIkSolver::setup(const char *boneName, mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose) {
  bind(frame, pose);
  if (boneName != nullptr) {
    u16 index = pose.skeleton->getBoneID(boneName);
    if (index != anm::Skeleton::INVALID_BONE) {
      unknown50 = index;
      return true;
    }
  }

  return false;
}

TransLocalIkSolver::TransLocalIkSolver() : unknown40(mm::Vec3::zero), unknown50(anm::Skeleton::INVALID_BONE) {}

TransLocalIkSolver::~TransLocalIkSolver() {}

const mm::mtl::RTTI *TransLocalIkSolver::getRTTI() const { return &m_rtti; }

} // namespace fw
