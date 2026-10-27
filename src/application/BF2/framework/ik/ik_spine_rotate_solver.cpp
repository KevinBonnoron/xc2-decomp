#include "framework/ik/ik_spine_rotate_solver.h"

#include "anm/anm_pose.h"
#include "anm/anm_skeleton.h"
#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"
#include "mm_mtl/intrusive_ptr.h"

namespace fw {

void SpineRotateIKSolver::Param::createReflection(Reflection *reflection, const char *name, u32 index) {
#line 18
  ReflectionValueStruct *value = new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueStruct(name, sizeof(Param));
#line 19
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("minYaw0", offsetof(Param, minYaw0), -90.0f, 0.0f, -90.0f));
#line 20
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("maxYaw0", offsetof(Param, maxYaw0), 0.0f, 90.0f, 90.0f));
#line 21
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("minPitch0", offsetof(Param, minPitch0), -90.0f, 0.0f, -90.0f));
#line 22
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("maxPitch0", offsetof(Param, maxPitch0), 0.0f, 90.0f, 90.0f));
#line 23
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("minYaw1", offsetof(Param, minYaw1), -90.0f, 0.0f, -90.0f));
#line 24
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("maxYaw1", offsetof(Param, maxYaw1), 0.0f, 90.0f, 90.0f));
#line 25
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("minPitch1", offsetof(Param, minPitch1), -90.0f, 0.0f, -90.0f));
#line 26
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("maxPitch1", offsetof(Param, maxPitch1), 0.0f, 90.0f, 90.0f));
#line 27
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("ratio", offsetof(Param, ratio), 0.0f, 1.0f, 1.0f));
  reflection->setReflectionStruct(index, value);
}

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
