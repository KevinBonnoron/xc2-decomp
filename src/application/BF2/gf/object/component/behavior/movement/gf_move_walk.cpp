#include "gf/object/component/behavior/movement/gf_move_walk.h"

#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"

namespace gf {

void GfMoveWalkControler::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 15
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(Param));
#line 16
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("velocity", offsetof(Param, velocity), 0.0f, 10000.0f, 2.0f));
#line 17
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("angularVelMin", offsetof(Param, angularVelMin), 0.0f, 10000.0f, 4.0f));
#line 18
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("angularVelMax", offsetof(Param, angularVelMax), 0.0f, 10000.0f, 10.0f));
  reflection->setReflectionStruct(index, value);
}

void GfMoveWalkControler::enter(Packet &packet) {
  const Param *param = packet.m_paramAdapter.get<Param>();
  packet.unknown00 = packet.unknown30 * param->velocity * packet.unknown40;
}

} // namespace gf
