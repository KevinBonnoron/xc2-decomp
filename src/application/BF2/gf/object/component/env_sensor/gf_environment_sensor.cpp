#include <stddef.h>

#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"
#include "gf/object/component/env_sensor/gf_com_env_sensor.h"
#include "types.h"

namespace gf {

void EnviromentSensor::Parameter::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 17
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(Parameter));
#line 18
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("searchVertUp", offsetof(Parameter, searchVertUp), 0.0f, 1000.0f, 10.0f));
#line 19
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("searchVertDown", offsetof(Parameter, searchVertDown), 0.0f, 1000.0f, 100.0f));
#line 20
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("obstacleHeightBase", offsetof(Parameter, obstacleHeightBase), 0.0f, 1000.0f, 0.05f));
#line 21
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("obstacleHeightJump", offsetof(Parameter, obstacleHeightJump), 0.0f, 1000.0f, 0.5f));
#line 22
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("obstacleSearchLength", offsetof(Parameter, obstacleSearchLength), 0.0f, 1000.0f, 1.0f));
#line 23
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("wallEndHeight", offsetof(Parameter, wallEndHeight), 0.0f, 1000.0f, 2.0f));
#line 24
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("wallEndMoveDist", offsetof(Parameter, wallEndMoveDist), 0.0f, 1000.0f, 2.0f));
#line 25
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("wallEndSearchDown", offsetof(Parameter, wallEndSearchDown), 0.0f, 1000.0f, 2.0f));
#line 26
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("descendWallSearchFront", offsetof(Parameter, descendWallSearchFront), 0.0f, 1000.0f, 2.0f));
#line 27
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("descendWallSearchDown", offsetof(Parameter, descendWallSearchDown), 0.0f, 1000.0f, 1.05f));
#line 28
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("descendWallSearchDist", offsetof(Parameter, descendWallSearchDist), 0.0f, 1000.0f, 10.0f));
  reflection->setReflectionStruct(index, value);
}

// Placed here, not in gf_com_env_sensor.cpp (where clang would inline it into GfComEnvSensor::GfComEnvSensor()): the game puts it right after
// Parameter::createReflection (1.0.0: 0x710051cfe8 + 0x93c = 0x710051d924), a function this unit already defines, and GfComEnvSensor::GfComEnvSensor()
// calls it out of line (0x710051b1ec).
EnviromentSensor::EnviromentSensor() : m_envSensorCheckFlags(0), unknown24(0), unknown30(), unknown1f0(), unknown290(1.0f) {}

} // namespace gf
