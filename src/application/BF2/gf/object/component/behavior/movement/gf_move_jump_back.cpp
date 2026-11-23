#include "gf/object/component/behavior/movement/gf_move_jump_back.h"

#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"
#include "fw/fw_update_info.h"

namespace gf {

void GfMoveJumpBackControler::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 15
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(Param));
#line 16
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("velocityMax", offsetof(Param, velocityMax), 0.001f, 10000.0f, 7.8f));
#line 17
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("accel", offsetof(Param, accel), 0.0f, 10000.0f, 10.0f));
  reflection->setReflectionStruct(index, value);
}

void GfMoveJumpBackControler::update(const fw::UpdateInfo &info, Packet &packet) {
  const Param *param = packet.m_paramAdapter.get<Param>();
  f32 speedMin = -(param->velocityMax * packet.unknown18);
  f32 speed = packet.unknown00.x * packet.unknown20.x + packet.unknown00.y * packet.unknown20.y + packet.unknown00.z * packet.unknown20.z - param->accel * info.unknown04;
  if (!(speed > speedMin)) {
    speed = speedMin;
  }
  packet.unknown00 = packet.unknown20 * speed;
}

} // namespace gf
