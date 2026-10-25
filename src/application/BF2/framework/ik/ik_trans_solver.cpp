#include "framework/ik/ik_trans_solver.h"

#include "anm/anm_pose.h"
#include "anm/anm_qs_transform.h"
#include "anm/anm_skeleton.h"
#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "mm_math/mm_vec4.h"
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
    u16 index = pose.unknown18->getBoneID(boneName);
    if (index != anm::Skeleton::INVALID_BONE) {
      unknown50 = index;
      return true;
    }
  }

  return false;
}

TransLocalIkSolver::TransLocalIkSolver() : unknown40(mm::Vec3::zero), unknown50(anm::Skeleton::INVALID_BONE) {}

TransLocalIkSolver::~TransLocalIkSolver() {}

void TransLocalIkSolver::calcIK(const UpdateInfo &info) {
  if (unknown18 != nullptr) {
    anm::QsTransform transform = unknown18->getBoneLocalSpace(unknown50);
    mm::Vec3 offset = unknown40 * unknown20;
    transform.unknown00.x += offset.x;
    transform.unknown00.y += offset.y;
    transform.unknown00.z += offset.z;
    transform.unknown00.w += 1.0f;
    unknown18->setBoneLocalSpace(unknown50, transform);
  }
}

const mm::mtl::RTTI *TransLocalIkSolver::getRTTI() const { return &m_rtti; }

} // namespace fw
