#pragma once
#include <stddef.h>

#include "types.h"

namespace ui {

class UIParticleData {
public:
  UIParticleData();
  virtual ~UIParticleData();
  void deserialize(const void *data, u32 size);

  u8 unknown08[0xa0]; // Inferred role: particle data; original member names unknown.
};

static_assert(offsetof(UIParticleData, unknown08) == 0x08, "");
static_assert(sizeof(UIParticleData) == 0xa8, "");

} // namespace ui
