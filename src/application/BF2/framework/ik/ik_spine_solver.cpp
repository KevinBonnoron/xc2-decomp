#include "framework/ik/ik_spine_solver.h"

#include "anm/anm_pose.h"
#include "anm/anm_qs_transform.h"
#include "anm/anm_skeleton.h"
#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"
#include "mm_math/mm_math.h"
#include "mm_mtl/intrusive_ptr.h"

namespace fw {

void SpineIkSolver::Param::createReflection(Reflection *reflection, const char *name, u32 index) {
#line 21
  ReflectionValueStruct *value = new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueStruct(name, sizeof(Param));
#line 22
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("angleThreasold0", offsetof(Param, angleThreasold0), 0.0f, 180.0f, 20.0f));
#line 23
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("angleThreasold1", offsetof(Param, angleThreasold1), 0.0f, 180.0f, 20.0f));
#line 24
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("response0", offsetof(Param, response0), 0.0f, 10.0f, 0.5f));
#line 25
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("response1", offsetof(Param, response1), 0.0f, 10.0f, 0.5f));
#line 26
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("limitAngle0", offsetof(Param, limitAngle0), 0.0f, 180.0f, 90.0f));
#line 27
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("limitAngle1", offsetof(Param, limitAngle1), 0.0f, 180.0f, 90.0f));
  reflection->setReflectionStruct(index, value);
}

bool SpineIkSolver::setupLimit(const ParamAdapter &param, const char *boneName, const char *endBoneName, mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose) {
  bind(frame, pose);
  const anm::Skeleton *skeleton = unknown18->unknown18;
  if (boneName != nullptr) {
    unknown34 = skeleton->getBoneID(boneName);
  }
  if (endBoneName != nullptr) {
    unknown36 = skeleton->getBoneID(endBoneName);
  }
  unknown80 = param;
  resetLimit();
  return unknown34 != anm::Skeleton::INVALID_BONE || unknown36 != anm::Skeleton::INVALID_BONE;
}

SpineIkSolver::SpineIkSolver()
    : unknown34(0xffff), unknown36(0xffff), unknown38(0.0f), unknown3c(0.0f), unknown40(0.1f), unknown44(0.1f), unknown48(1.5f), unknown4c(1.5f), unknown50(mm::Vec3::zero), unknown60(mm::Vec3::zero),
      unknown70(mm::Vec3::unitZ), unknown80(), unknown88(false), unknown90(mm::Quat::identity), unknowna0(mm::Quat::identity), unknownb8() {
  unknownb0 = 0.0f;
  unknownb4 = 0.0f;
}

SpineIkSolver::~SpineIkSolver() {}

void SpineIkSolver::resetLimit() {
  const f32 *limit = unknown80.get<f32>();
  unknown38 = limit[0] * mm::DEG_TO_RAD;
  unknown3c = limit[1] * mm::DEG_TO_RAD;
  unknown40 = limit[2];
  unknown44 = limit[3];
  unknown48 = limit[4] * mm::DEG_TO_RAD;
  unknown4c = limit[5] * mm::DEG_TO_RAD;
}

void SpineIkSolver::startTargetFade(f32 time) {
  if (time > 0.0f) {
    unknown88 = true;
    if (unknown34 != 0xffff) {
      unknown90 = unknown18->getBoneModelSpace(unknown34).unknown10;
    }
    if (unknown36 != 0xffff) {
      unknowna0 = unknown18->getBoneModelSpace(unknown36).unknown10;
    }
    unknownb0 = 0.0f;
    unknownb4 = time;
  }
}

void SpineIkSolver::onDisable() {
  unknown88 = false;
  unknown90 = mm::Quat::identity;
  unknowna0 = mm::Quat::identity;
  unknownb0 = 0.0f;
  unknownb4 = 0.0f;
}

const mm::mtl::RTTI *SpineIkSolver::getRTTI() const { return &m_rtti; }

} // namespace fw
