// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/gf/object/component/pc/param/gf_pc_param_reflection.cpp.
#include "gf/object/component/pc/param/gf_pc_param_reflection.h"

#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"
#include "gf/object/component/pc/param/gf_pc_param.h"
#include "mm_mtl/vector.h"

namespace gf {
namespace pc {

fw::Reflection *createReflection() {
#line 28
  fw::Reflection *reflection = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::Reflection();
  reflection->unknown10.resize(5, nullptr);
  InputParam::createReflection(reflection, "input", 0);
  MoveParam::createReflection(reflection, "move", 1);
  WarpParam::createReflection(reflection, "warp", 2);
  SensorAIParam::createReflection(reflection, "sensor_ai", 3);
  SlideParam::createReflection(reflection, "slide", 4);
  return reflection;
}

} // namespace pc
} // namespace gf
