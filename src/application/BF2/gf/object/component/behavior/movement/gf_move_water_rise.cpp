#include "gf/object/component/behavior/movement/gf_move_water_rise.h"

#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"
#include "fw/fw_update_info.h"

namespace gf {

void GfMoveWaterRiseControler::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 15
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(Param));
#line 16
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("accel", offsetof(Param, accel), 0.0f, 10000.0f, 3.0f));
#line 17
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("speedMax", offsetof(Param, speedMax), 0.0f, 10000.0f, 1.8f));
#line 18
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("brake", offsetof(Param, brake), 0.0f, 10000.0f, 10.0f));
#line 19
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("speedMin", offsetof(Param, speedMin), 0.0f, 10000.0f, 0.1f));
  reflection->setReflectionStruct(index, value);
}

void GfMoveWaterRiseControler::update(const fw::UpdateInfo &info, Packet &packet) {
  const Param *param = packet.m_paramAdapter.get<Param>();
  f32 speed = packet.unknown00;
  if (packet.unknown10) {
    f32 sign = speed >= 0.0f ? 1.0f : -1.0f;
    speed = speed * sign - info.unknown04 * param->brake;
    packet.unknown00 = sign * (speed > param->speedMin ? speed : param->speedMin);
    return;
  }
  speed = speed + info.unknown04 * param->accel;
  packet.unknown00 = speed < param->speedMax ? speed : param->speedMax;
}

} // namespace gf
