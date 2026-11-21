#include "gf/object/component/behavior/movement/gf_move_jump.h"

#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"
#include "fw/fw_update_info.h"

namespace gf {

void GfMoveJumpControler::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 15
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(Param));
#line 16
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("velocityMax", offsetof(Param, velocityMax), 0.001f, 10000.0f, 7.8f));
#line 17
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("accel", offsetof(Param, accel), 0.0f, 10000.0f, 10.0f));
#line 18
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("angularVelMax", offsetof(Param, angularVelMax), 0.0f, 10000.0f, 10.0f));
#line 19
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("angularAccel", offsetof(Param, angularAccel), 0.0f, 10000.0f, 10.0f));
  reflection->setReflectionStruct(index, value);
}

void GfMoveJumpControler::update(const fw::UpdateInfo &info, Packet &packet) {
  calcVelocity(info.unknown04, packet);
  calcAngularVelocity(info.unknown04, packet);
}

void GfMoveJumpControler::calcVelocity(f32 deltaTime, Packet &packet) {
  const Param *param = packet.unknown18.get<Param>();
  f32 speedMax = param->velocityMax * packet.unknown20;
  f32 speed = packet.unknown00.x * packet.unknown40.x + packet.unknown00.y * packet.unknown40.y + packet.unknown00.z * packet.unknown40.z;
  if (speedMax > speed) {
    speed = speed + param->accel * deltaTime;
    speed = speed < speedMax ? speed : speedMax;
  } else if (speedMax < speed) {
    speed = speed - param->accel * deltaTime;
    speed = speed > speedMax ? speed : speedMax;
  }
  packet.unknown00 = mm::Vec3(speed * packet.unknown40.x, speed * packet.unknown40.y, speed * packet.unknown40.z);
}

} // namespace gf
