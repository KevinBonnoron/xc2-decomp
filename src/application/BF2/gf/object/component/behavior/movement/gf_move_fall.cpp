#include "gf/object/component/behavior/movement/gf_move_fall.h"

#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"
#include "fw/fw_update_info.h"

namespace gf {

void GfMoveFallControler::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 15
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(Param));
#line 16
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("accel", offsetof(Param, accel), 0.001f, 10000.0f, 10.0f));
#line 17
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("speedMax", offsetof(Param, speedMax), 0.0f, 10000.0f, 50.0f));
  reflection->setReflectionStruct(index, value);
}

void GfMoveFallControler::update(const fw::UpdateInfo &info, Packet &packet) {
  const Param *param = packet.m_paramAdapter.get<Param>();
  f32 speed = packet.unknown00 - info.unknown04 * param->accel;
  f32 speedMin = -param->speedMax;
  packet.unknown00 = speed > speedMin ? speed : speedMin;
}

} // namespace gf
