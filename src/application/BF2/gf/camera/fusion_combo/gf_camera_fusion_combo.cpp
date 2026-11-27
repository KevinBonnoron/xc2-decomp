#include "gf/camera/fusion_combo/gf_camera_fusion_combo.h"

#include <math.h>

#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"

namespace gf {

void FusionComboCamera::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 17
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(unknown001));
#line 18
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("zoom_frame", offsetof(unknown001, zoom_frame), 0.0f, 1000.0f, 60.0f));
#line 19
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("zoom_start_distance", offsetof(unknown001, zoom_start_distance), -100.0f, 100.0f, 3.0f));
#line 20
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("zoom_end_distance", offsetof(unknown001, zoom_end_distance), -100.0f, 100.0f, 1.5f));
#line 21
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("zoom_base_width", offsetof(unknown001, zoom_base_width), 0.0f, 100.0f, 0.25f));
#line 22
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("zoom_add_width", offsetof(unknown001, zoom_add_width), 0.0f, 100.0f, 0.3f));
#line 23
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("zoom_base_height", offsetof(unknown001, zoom_base_height), 0.0f, 100.0f, 1.2f));
#line 24
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("zoom_add_height", offsetof(unknown001, zoom_add_height), 0.0f, 100.0f, 0.7f));
#line 25
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueS32("zoom_mode", offsetof(unknown001, zoom_mode), 0, 1, 0));
#line 27
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("around_frame", offsetof(unknown001, around_frame), 0.0f, 1000.0f, 210.0f));
#line 28
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("around_start_distance", offsetof(unknown001, around_start_distance), 0.0f, 1000.0f, 10.0f));
#line 29
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("around_end_distance", offsetof(unknown001, around_end_distance), 0.0f, 1000.0f, 2.0f));
#line 30
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("around_rotate", offsetof(unknown001, around_rotate), 0.0f, 1000.0f, 360.0f));
#line 31
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("around_add_yaw", offsetof(unknown001, around_add_yaw), 0.0f, 180.0f, 45.0f));
#line 32
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("around_add_pitch", offsetof(unknown001, around_add_pitch), 0.0f, 180.0f, 45.0f));
#line 33
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueS32("around_mode", offsetof(unknown001, around_mode), 0, 1, 0));
#line 35
  fw::ReflectionValueBitset32 *flags = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueBitset32("flags", offsetof(unknown001, flags));
#line 36
  flags->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueFlag("collision_enable", 1, false));
#line 37
  flags->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueFlag("speed_enable", 2, true));
  value->add(flags);
  reflection->setReflectionStruct(index, value);
}

FusionComboCamera::~FusionComboCamera() {}

void FusionComboCamera::onActivate() {}

bool FusionComboCamera::isPlayEnd() const { return unknown120 <= unknown124; }

// 1.0.0: 0x71001d60e0, 63 instructions. The game rotates the opposite direction (the negated unit axis, rotated in place by mm::unknown010) and passes it with a copy of the axis. `direction`
// is declared before `reference`: the game keeps the copy of the axis at sp and the direction above it. The other order has 12 lines of difference; `direction = rotation.rotate(...)`
// has 30 (axis first) or 78 (direction first).
f32 FusionComboCamera::getYaw(const mm::Quat &rotation) {
  mm::Vec3 direction;
  mm::Vec3 reference = mm::Vec3::unitZ;
  direction = mm::Vec3(-reference.x, -reference.y, -reference.z);
  mm::unknown010(rotation, direction);
  return getYaw(direction, reference);
}

void FusionComboCamera::getAxis(const mm::Vec3 &from, const mm::Vec3 &to, mm::Vec3 &axis) {
  mm::Vec3 first = from;
  mm::Vec3 second = to;
  if (!first.unknown003() && !second.unknown003()) {
    first.unknown002();
    second.unknown002();
    axis.unknown004(second, first);
  }
}

f32 FusionComboCamera::getYaw(const mm::Vec3 &direction, const mm::Vec3 &reference) {
  mm::Vec3 from(direction.x, 0.0f, direction.z);
  mm::Vec3 to(reference.x, 0.0f, reference.z);
  if ((fabsf(from.x) <= 0.000001f && fabsf(from.z) <= 0.000001f) || (fabsf(to.x) <= 0.000001f && fabsf(to.z) <= 0.000001f)) {
    return 0.0f;
  }
  from.unknown002();
  to.unknown002();
  f32 cosine = to.x * from.x + to.y * from.y + to.z * from.z;
  mm::clampRef(cosine, -1.0f, 1.0f);
  f32 angle = mm::acos(cosine);
  return from.x * to.z - from.z * to.x < 0.0f ? 6.2831855f - angle : angle;
}

f32 FusionComboCamera::getPitch(const mm::Vec3 &direction, const mm::Vec3 &reference) {
  f32 yaw = getYaw(direction, reference);
  mm::Vec3 from = direction;
  mm::Vec3 to = reference;
  mm::Quat rotation;
  rotation.x = 0.0f;
  rotation.y = sinf(yaw * -0.5f);
  rotation.z = 0.0f;
  rotation.w = cosf(yaw * -0.5f);
  from = rotation.rotate(from);
  from.unknown001();
  to.unknown001();
  f32 cosine = to.x * from.x + to.y * from.y + to.z * from.z;
  mm::clampRef(cosine, -1.0f, 1.0f);
  f32 angle = mm::acos(cosine);
  return from.z * to.y - from.y * to.z < 0.0f ? -angle : angle;
}

f32 FusionComboCamera::fastOut(f32 t) {
  f32 x = sinf(t * 1.5707964f + 4.712389f) + 1.0f;
  return x + (1.0f - x) * 0.0f;
}

f32 FusionComboCamera::slowOut(f32 t) {
  f32 x = sinf((1.0f - t) * 1.5707964f + 4.712389f) + 1.0f;
  return 1.0f - (x + (1.0f - x) * 0.0f);
}

f32 FusionComboCamera::curve(f32 a, f32 b, f32 t) {
  f32 x = sinf(t * 1.5707964f + 4.712389f) + 1.0f;
  return (1.0f - x) * a + x * b;
}

const mm::mtl::RTTI *FusionComboCamera::getRTTI() const { return &m_rtti; }

const char *FusionComboCamera::getName() const { return "FusionComboCamera"; }

} // namespace gf
