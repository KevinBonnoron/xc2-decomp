#include "gf/param/pc_sound/gf_param_pc_sound.h"

#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"

namespace gf {

void PcSoundVolumeParam::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 14
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(PcSoundVolumeParam));
#line 15
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("volumePlayer1", offsetof(PcSoundVolumeParam, volumePlayer1), 0.0f, 1.0f, 1.0f));
#line 16
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("volumePlayer2", offsetof(PcSoundVolumeParam, volumePlayer2), 0.0f, 1.0f, 1.0f));
#line 17
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("volumePlayer3", offsetof(PcSoundVolumeParam, volumePlayer3), 0.0f, 1.0f, 1.0f));
#line 18
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("volumePlayer4", offsetof(PcSoundVolumeParam, volumePlayer4), 0.0f, 1.0f, 1.0f));
#line 19
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("volumePlayer5", offsetof(PcSoundVolumeParam, volumePlayer5), 0.0f, 1.0f, 1.0f));
  reflection->setReflectionStruct(index, value);
}

} // namespace gf
