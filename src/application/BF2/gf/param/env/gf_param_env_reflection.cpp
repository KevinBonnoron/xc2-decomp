// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/gf/param/env/gf_param_env_reflection.cpp.
#include "gf/param/env/gf_param_env_reflection.h"

#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"
#include "gf/object/component/env_sensor/gf_com_env_sensor.h"
#include "gf/param/env/gf_param_env_foot.h"
#include "mm_mtl/vector.h"

namespace gf {

fw::Reflection *createReflectionEnv() {
#line 27
  fw::Reflection *reflection = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::Reflection();
  reflection->unknown10.resize(3, nullptr);
  EnviromentSensor::Parameter::createReflection(reflection, "env00", 0);
  EnviromentSensor::Parameter::createReflection(reflection, "envPC", 1);
  FootEnvParam::createReflection(reflection, "envFoot", 2);
  return reflection;
}

} // namespace gf
