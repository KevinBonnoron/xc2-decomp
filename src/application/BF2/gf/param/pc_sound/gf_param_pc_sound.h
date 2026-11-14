#pragma once
#include <stddef.h>

#include "types.h"

namespace fw {
class Reflection;
} // namespace fw

namespace gf {

// Names are the reflection names registered by PcSoundVolumeParam::createReflection (gf_param_pc_sound.cpp).
struct PcSoundVolumeParam {
  static void createReflection(fw::Reflection *reflection, const char *name, u32 index);

  f32 volumePlayer1;
  f32 volumePlayer2;
  f32 volumePlayer3;
  f32 volumePlayer4;
  f32 volumePlayer5;
};

static_assert(offsetof(PcSoundVolumeParam, volumePlayer2) == 0x04, "");
static_assert(offsetof(PcSoundVolumeParam, volumePlayer3) == 0x08, "");
static_assert(offsetof(PcSoundVolumeParam, volumePlayer4) == 0x0c, "");
static_assert(offsetof(PcSoundVolumeParam, volumePlayer5) == 0x10, "");
static_assert(sizeof(PcSoundVolumeParam) == 0x14, "");

} // namespace gf
