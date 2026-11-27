#include "framework/ik/ik_rotate_solver.h"

#include "anm/anm_pose.h"
#include "anm/anm_qs_transform.h"
#include "anm/anm_skeleton.h"
#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
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
    u16 index = this->unknown18->unknown18->getBoneID(boneName);
    if (index != anm::Skeleton::INVALID_BONE) {
      unknown50 = index;
      return true;
    }
  }

  return false;
}

RotateIkSolver::RotateIkSolver() : unknown40(mm::Vec3::zero), unknown50(0) {}

RotateIkSolver::~RotateIkSolver() {}

// The weighted components are single-use locals: the IR, the instruction scheduling and the register allocation are the same without them, but under -g their DBG_VALUEs change
// the A57 FP anti-dependency breaker (the game keeps s0 for the product with the z component and puts the last use of cosZ in s17; without the locals it is the other way
// round, 6 differing lines; RotateLocalIkSolver::calcIK is the same with the local space accessors).
void RotateIkSolver::calcIK(const UpdateInfo &info) {
  if (unknown18 != nullptr) {
    anm::QsTransform transform = unknown18->getBoneModelSpace(unknown50);
    f32 x = unknown20 * unknown40.x;
    f32 y = unknown20 * unknown40.y;
    f32 z = unknown20 * unknown40.z;
    mm::Quat rotation;
    mm::unknown005(rotation, mm::Vec3(x, y, z));
    transform.unknown10 = mm::Quat::mul(transform.unknown10, rotation);
    unknown18->setBoneModelSpace(unknown50, transform, anm::Pose::PROPAGATE_TYPE_UNKNOWN_1);
  }
}

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
    u16 index = this->unknown18->unknown18->getBoneID(boneName);
    if (index != anm::Skeleton::INVALID_BONE) {
      unknown50 = index;
      return true;
    }
  }

  return false;
}

RotateLocalIkSolver::RotateLocalIkSolver() : unknown40(mm::Vec3::zero), unknown50(0) {}

RotateLocalIkSolver::~RotateLocalIkSolver() {}

// The weighted components are single-use locals: the IR, the instruction scheduling and the register allocation are the same without them, but under -g their DBG_VALUEs change
// the A57 FP anti-dependency breaker (the game keeps s0 for the product with the z component and puts the last use of cosZ in s17; without the locals it is the other way
// round, 6 differing lines). RotateIkSolver::calcIK is the same with the model space accessors.
void RotateLocalIkSolver::calcIK(const UpdateInfo &info) {
  if (unknown18 != nullptr) {
    anm::QsTransform transform = unknown18->getBoneLocalSpace(unknown50);
    f32 x = unknown20 * unknown40.x;
    f32 y = unknown20 * unknown40.y;
    f32 z = unknown20 * unknown40.z;
    mm::Quat rotation;
    mm::unknown005(rotation, mm::Vec3(x, y, z));
    transform.unknown10 = mm::Quat::mul(transform.unknown10, rotation);
    unknown18->setBoneLocalSpace(unknown50, transform);
  }
}

const mm::mtl::RTTI *RotateIkSolver::getRTTI() const { return &m_rtti; }

const mm::mtl::RTTI *RotateLocalIkSolver::getRTTI() const { return &m_rtti; }

} // namespace fw
