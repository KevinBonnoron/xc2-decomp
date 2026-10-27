#include <stddef.h>

#include "anm/anm_pose.h"
#include "anm/anm_qs_transform.h"
#include "framework/ik/ik_look_at_solver.h"
#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"
#include "fw/fw_param_manager.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace fw {

void LookAtIkSolver::BoxLimit::createReflection(Reflection *reflection, const char *name, u32 index) {
#line 23
  ReflectionValueStruct *value = new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueStruct(name, sizeof(BoxLimit));
#line 24
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("limitAngleUp", offsetof(BoxLimit, limitAngleUp), 0.0f, 90.0f, 45.0f));
#line 25
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("limitAngleDown", offsetof(BoxLimit, limitAngleDown), 0.0f, 90.0f, 30.0f));
#line 26
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("limitAngleLeft", offsetof(BoxLimit, limitAngleLeft), 0.0f, 90.0f, 60.0f));
#line 27
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("limitAngleRight", offsetof(BoxLimit, limitAngleRight), 0.0f, 90.0f, 60.0f));
  reflection->setReflectionStruct(index, value);
}

LookAtIkSolver::LookAtIkSolver()
    : unknowna0(mm::Vec3::zero), unknownb0(mm::Vec3::zero), unknownc0(), unknownc8(0xffff), unknowncc(1.0f), unknownd0(1.0f), unknownd4(false), unknowne0(mm::Quat::identity), unknownf0(0.0f),
      unknownf4(0.0f) {}

LookAtIkSolver::~LookAtIkSolver() {}

void LookAtIkSolver::startTargetFade(f32 time) {
  if (time > 0.0f) {
    unknownd4 = true;
    unknowne0 = unknown18->getBoneModelSpace(unknownc8).unknown10;
    unknownf0 = 0.0f;
    unknownf4 = time;
  }
}

void LookAtIkSolver::resetLimitParam() {
  const f32 *limit = unknownc0.get<f32>();
  unknown80 = limit[0] * mm::DEG_TO_RAD;
  unknown84 = limit[1] * mm::DEG_TO_RAD;
  unknown88 = limit[2] * mm::DEG_TO_RAD;
  unknown8c = limit[3] * mm::DEG_TO_RAD;
}

void LookAtIkSolver::onDisable() {
  unknownd4 = false;
  unknowne0 = mm::Quat::identity;
  unknownf0 = 0.0f;
  unknownf4 = 0.0f;
}

const mm::mtl::RTTI *LookAtIkSolver::getRTTI() const { return &m_rtti; }

} // namespace fw
