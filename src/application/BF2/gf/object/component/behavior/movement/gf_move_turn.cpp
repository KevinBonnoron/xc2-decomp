#include "gf/object/component/behavior/movement/gf_move_turn.h"

#include <math.h>

#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"
#include "fw/fw_update_info.h"
#include "mm_math/mm_math.h"

namespace gf {

void GfMoveTurnControler::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 14
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(Param));
#line 15
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("angularVelMin", offsetof(Param, angularVelMin), 0.0f, 10000.0f, 10.0f));
#line 16
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("angularVelMax", offsetof(Param, angularVelMax), 0.0f, 10000.0f, 10.0f));
  reflection->setReflectionStruct(index, value);
}

void GfMoveTurnControler::update(const fw::UpdateInfo &info, Packet &packet) {
  const Param *param = packet.m_paramAdapter.get<Param>();
  const mm::Vec3 &target = packet.unknown10;
  const mm::Vec3 &current = packet.unknown20;
  f32 cosine = mm::clamp(current.x * target.x + current.y * target.y + current.z * target.z, -1.0f, 1.0f);
  f32 angle = mm::acos(cosine > 0.9999 ? 1.0f : cosine);
  f32 angularVel = param->angularVelMin + angle / 3.1415927f * (param->angularVelMax - param->angularVelMin);
  mm::Vec3 axis(target.y * current.z - target.z * current.y, target.z * current.x - current.z * target.x, current.y * target.x - target.y * current.x);
  f32 rate = angle / info.unknown04;
  f32 sign = axis.x * mm::Vec3::unitY.x + axis.y * mm::Vec3::unitY.y + axis.z * mm::Vec3::unitY.z >= 0.0f ? -1.0f : 1.0f;
  f32 speed = fabsf(rate);
  packet.unknown00 = (angularVel < speed ? angularVel : speed) * sign;
}

} // namespace gf
