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
    u16 index = this->pose->skeleton->getBoneID(boneName);
    if (index != anm::Skeleton::INVALID_BONE) {
      boneIndex = index;
      return true;
    }
  }

  return false;
}

RotateIkSolver::RotateIkSolver() : rotation(mm::Vec3::zero), boneIndex(0) {}

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
    u16 index = this->pose->skeleton->getBoneID(boneName);
    if (index != anm::Skeleton::INVALID_BONE) {
      boneIndex = index;
      return true;
    }
  }

  return false;
}

RotateLocalIkSolver::RotateLocalIkSolver() : rotation(mm::Vec3::zero), boneIndex(0) {}

RotateLocalIkSolver::~RotateLocalIkSolver() {}

const mm::mtl::RTTI *RotateIkSolver::getRTTI() const { return &m_rtti; }

const mm::mtl::RTTI *RotateLocalIkSolver::getRTTI() const { return &m_rtti; }

} // namespace fw
