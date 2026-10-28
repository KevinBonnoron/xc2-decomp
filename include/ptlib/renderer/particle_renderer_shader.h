#pragma once
#include <stddef.h>

#include "grlib/cglib_shd_list.h"
#include "types.h"

namespace grlib {
class CGLibDecShader;
} // namespace grlib

namespace ptlib {
namespace renderer {

enum EffShdType {
  EFF_SHD_TYPE_UNKNOWN_13 = 13,
};

// Inferred role: declaration offsets of the VERIATION_MODE, SOFT_MODE, SHADOW_MODE, CLIP_MODE and USING_TEMPORAL_AA
// declarations of a shader; original type name unknown.
struct unknown001 {
  u32 unknown00;
  u32 unknown04;
  u32 unknown08;
  u32 unknown0c;
  u32 unknown10;
};

static_assert(sizeof(unknown001) == 0x14, "");

// Layout evidence: constructor 0x7100939804, init 0x71009398e4.
class ShaderManager {
public:
  ShaderManager();
  ~ShaderManager();
  void init();
  void term();
  void reload();
  grlib::CGLibDecShader *getShaderByIndex(EffShdType type);

  void *unknown00;                   // Inferred role: shader file; original member name unknown.
  grlib::CGLibShdListData unknown08; // Inferred role: shader list; original member name unknown.
  unknown001 unknown60[16];          // Inferred role: declaration offsets of each shader; original member name unknown.
};

static_assert(offsetof(ShaderManager, unknown08) == 0x08, "");
static_assert(offsetof(ShaderManager, unknown60) == 0x60, "");
static_assert(sizeof(ShaderManager) == 0x1a0, "");

} // namespace renderer
} // namespace ptlib
