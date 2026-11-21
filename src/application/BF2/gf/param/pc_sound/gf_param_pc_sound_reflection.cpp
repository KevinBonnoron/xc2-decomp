// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/gf/param/pc_sound/gf_param_pc_sound_reflection.cpp.
#include "gf/param/pc_sound/gf_param_pc_sound_reflection.h"

#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"
#include "gf/param/pc_sound/gf_param_pc_sound.h"
#include "mm_mtl/vector.h"

namespace gf {

fw::Reflection *createReflectionPcSound() {
#line 26
  fw::Reflection *reflection = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::Reflection();
  reflection->unknown10.resize(1, nullptr);
  PcSoundVolumeParam::createReflection(reflection, "volume", 0);
  return reflection;
}

} // namespace gf
