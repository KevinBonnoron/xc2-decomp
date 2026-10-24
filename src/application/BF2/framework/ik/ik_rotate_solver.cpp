#include "framework/ik/ik_rotate_solver.h"

#include "anm/anm_pose.h"
#include "anm/anm_skeleton.h"
#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/reference_object.h"

namespace fw {

RotateIkSolver *RotateIkSolver::create(const char *boneName, mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose) {
  // __LINE__ of the game: it is the line argument of operator new.
#line 31
  RotateIkSolver *solver = new (Allocator::getProcAllocator(), 16, __FILE__, __LINE__) RotateIkSolver();
  solver->addRef();
  if (!solver->setup(boneName, frame, pose)) {
    mm::mtl::safeRelease(solver);
  }

  return solver;
}

bool RotateIkSolver::setup(const char *boneName, mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose) {
  bind(frame, pose);
  if (boneName != nullptr) {
    u16 index = this->unknown18->skeleton->getBoneID(boneName);
    if (index != anm::Skeleton::INVALID_BONE) {
      unknown50 = index;
      return true;
    }
  }

  return false;
}

RotateIkSolver::RotateIkSolver() : unknown40(mm::Vec3::zero), unknown50(0) {}

RotateIkSolver::~RotateIkSolver() {}

RotateLocalIkSolver *RotateLocalIkSolver::create(const char *boneName, mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose) {
  // __LINE__ of the game: it is the line argument of operator new.
#line 112
  RotateLocalIkSolver *solver = new (Allocator::getProcAllocator(), 16, __FILE__, __LINE__) RotateLocalIkSolver();
  solver->addRef();
  if (!solver->setup(boneName, frame, pose)) {
    mm::mtl::safeRelease(solver);
  }

  return solver;
}

bool RotateLocalIkSolver::setup(const char *boneName, mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose) {
  bind(frame, pose);
  if (boneName != nullptr) {
    u16 index = this->unknown18->skeleton->getBoneID(boneName);
    if (index != anm::Skeleton::INVALID_BONE) {
      unknown50 = index;
      return true;
    }
  }

  return false;
}

RotateLocalIkSolver::RotateLocalIkSolver() : unknown40(mm::Vec3::zero), unknown50(0) {}

RotateLocalIkSolver::~RotateLocalIkSolver() {}

const mm::mtl::RTTI *RotateIkSolver::getRTTI() const { return &m_rtti; }

const mm::mtl::RTTI *RotateLocalIkSolver::getRTTI() const { return &m_rtti; }

} // namespace fw
