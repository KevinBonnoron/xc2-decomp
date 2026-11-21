#include "gf/object/component/behavior/movement/gf_move_run.h"

#include <math.h>

#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"
#include "mm_math/mm_math.h"

namespace gf {

void GfMoveRunControler::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 15
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(Param));
#line 16
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("velocityMin", offsetof(Param, velocityMin), 0.0f, 10000.0f, 1.7f));
#line 17
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("velocityMax", offsetof(Param, velocityMax), 0.001f, 10000.0f, 7.8f));
#line 18
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("accel", offsetof(Param, accel), 0.0f, 10000.0f, 10.0f));
#line 19
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("brake", offsetof(Param, brake), 0.0f, 10000.0f, 10.0f));
#line 20
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("angularVelMin", offsetof(Param, angularVelMin), 0.0f, 10000.0f, 10.0f));
#line 21
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("angularVelMax", offsetof(Param, angularVelMax), 0.0f, 10000.0f, 10.0f));
  reflection->setReflectionStruct(index, value);
}

// The game multiplies the direction in each branch (0x71004fd6f8, 23 instructions); one product after the test compiles to 20.
void GfMoveRunControler::enter(Packet &packet, bool isInherit) {
  const Param *param = packet.unknown18.get<Param>();
  f32 speed = param->velocityMin;
  if (isInherit) {
    speed = speed + (param->velocityMax * packet.unknown50 - speed) * packet.unknown20;
    packet.unknown00 = packet.unknown40 * speed;
  } else {
    packet.unknown00 = packet.unknown40 * speed;
  }
}

void GfMoveRunControler::calcAngularVelocity(f32 deltaTime, Packet &packet) {
  const Param *param = packet.unknown18.get<Param>();
  const mm::Vec3 &target = packet.unknown30;
  const mm::Vec3 &current = packet.unknown40;
  f32 cosine = mm::clamp(current.x * target.x + current.y * target.y + current.z * target.z, -1.0f, 1.0f);
  f32 angle = mm::acos(cosine);
  f32 angularVel = param->angularVelMin + angle / 3.1415927f * (param->angularVelMax - param->angularVelMin);
  mm::Vec3 axis(target.y * current.z - target.z * current.y, target.z * current.x - current.z * target.x, current.y * target.x - target.y * current.x);
  f32 rate = angle / deltaTime;
  f32 sign = axis.x * mm::Vec3::unitY.x + axis.y * mm::Vec3::unitY.y + axis.z * mm::Vec3::unitY.z >= 0.0f ? -1.0f : 1.0f;
  f32 speed = fabsf(rate);
  packet.unknown10 = (angularVel < speed ? angularVel : speed) * sign;
}

void GfMoveRunControler::calcVelocity(f32 deltaTime, Packet &packet) {
  const Param *param = packet.unknown18.get<Param>();
  f32 speedRange = param->velocityMax * packet.unknown50 + packet.unknown54 - param->velocityMin;
  f32 speedTarget = param->velocityMin + speedRange * packet.unknown20;
  f32 speed = sqrtf(packet.unknown00.x * packet.unknown00.x + packet.unknown00.y * packet.unknown00.y + packet.unknown00.z * packet.unknown00.z);
  if (speedTarget > speed) {
    speed = speed + param->accel * deltaTime;
    speed = speed < speedTarget ? speed : speedTarget;
  } else if (speedTarget < speed) {
    speed = speed - param->brake * deltaTime;
    speed = speed > speedTarget ? speed : speedTarget;
  }
  packet.unknown00 = mm::Vec3(speed * packet.unknown40.x, speed * packet.unknown40.y, speed * packet.unknown40.z);
}

} // namespace gf
