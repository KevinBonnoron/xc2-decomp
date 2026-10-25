#pragma once
#include <stddef.h>

#include "mm_mtl/vector.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace ui {

class UIParticleEmitter {
public:
  struct Particle {
    u8 _00[0x60];
  };

  virtual ~UIParticleEmitter();
  void update(const fw::UpdateInfo &info);

  f32 unknown08; // Inferred role: emission scale; original member name unknown.
  u8 _0c[4];
  f32 unknown10; // Inferred role: pos x; original member name unknown.
  f32 unknown14; // Inferred role: pos y; original member name unknown.
  u8 _18[0x08];
  f32 unknown20; // Inferred role: rot; original member name unknown.
  u8 _24[0xe0 - 0x24];
  mm::mtl::Vector<Particle> unknowne0; // Inferred role: particles; original member name unknown.
  bool unknown108;                     // Inferred role: active; original member name unknown.
};

static_assert(offsetof(UIParticleEmitter, unknowne0) == 0xe0, "");
static_assert(offsetof(UIParticleEmitter, unknown108) == 0x108, "");

} // namespace ui
