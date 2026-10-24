#include "framework/ik/ik_spherical_coordinates_solver.h"

#include "anm/anm_pose.h"
#include "anm/anm_skeleton.h"
#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "mm_math/mm_math.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/reference_object.h"

namespace fw {

SphericalCoordinatesIkSolver *SphericalCoordinatesIkSolver::create(const ParamAdapter &param, const char *boneName, mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose) {
  // __LINE__ of the game: it is the line argument of operator new.
#line 37
  SphericalCoordinatesIkSolver *solver = new (Allocator::getProcAllocator(), 16, __FILE__, __LINE__) SphericalCoordinatesIkSolver();
  if (solver->setupLimit(param, boneName, frame, pose)) {
    solver->addRef();
  } else {
    mm::mtl::safeRelease(solver);
  }

  return solver;
}

bool SphericalCoordinatesIkSolver::setupLimit(const ParamAdapter &param, const char *boneName, mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose) {
  bind(frame, pose);
  if (boneName != nullptr) {
    u16 index = this->unknown18->skeleton->getBoneID(boneName);
    if (index != anm::Skeleton::INVALID_BONE) {
      unknown70 = index;
      unknown78 = param;
      resetLimit();
      return true;
    }
  }

  return false;
}

SphericalCoordinatesIkSolver::SphericalCoordinatesIkSolver() : m_enable(false), unknown78() {}

SphericalCoordinatesIkSolver::~SphericalCoordinatesIkSolver() {}

void SphericalCoordinatesIkSolver::resetLimitParam() {
  const AngleLimit *limit = unknown78.get<AngleLimit>();
  unknown40 = limit->limitAngleUp * mm::DEG_TO_RAD;
  unknown44 = limit->limitAngleDown * mm::DEG_TO_RAD;
  unknown48 = limit->limitAngleLeft * mm::DEG_TO_RAD;
  unknown4c = limit->limitAngleRight * mm::DEG_TO_RAD;
}

const mm::mtl::RTTI *SphericalCoordinatesIkSolver::getRTTI() const { return &m_rtti; }

bool SphericalCoordinatesIkSolver::isEnable() const { return m_enable; }

} // namespace fw
