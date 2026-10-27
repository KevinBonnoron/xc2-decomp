#include "framework/ik/ik_spherical_coordinates_solver.h"

#include "anm/anm_pose.h"
#include "anm/anm_skeleton.h"
#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"
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
    u16 index = this->unknown18->unknown18->getBoneID(boneName);
    if (index != anm::Skeleton::INVALID_BONE) {
      unknown70 = index;
      unknown78 = param;
      resetLimit();
      return true;
    }
  }

  return false;
}

void SphericalCoordinatesIkSolver::AngleLimit::createReflection(Reflection *reflection, const char *name, u32 index) {
#line 19
  ReflectionValueStruct *value = new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueStruct(name, sizeof(AngleLimit));
#line 20
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("limitAngleUp", offsetof(AngleLimit, limitAngleUp), 0.0f, 90.0f, 30.0f));
#line 21
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("limitAngleDown", offsetof(AngleLimit, limitAngleDown), 0.0f, 90.0f, 65.0f));
#line 22
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("limitAngleLeft", offsetof(AngleLimit, limitAngleLeft), 0.0f, 180.0f, 180.0f));
#line 23
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("limitAngleRight", offsetof(AngleLimit, limitAngleRight), 0.0f, 180.0f, 180.0f));
  reflection->setReflectionStruct(index, value);
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
