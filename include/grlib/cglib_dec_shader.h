#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {

class CGLibShader;

class CGLibDecShader {
public:
  CGLibDecShader();
  ~CGLibDecShader();
  u32 getDeclarationOfs(const char *name) const;
  void setDeclarationIdx(u32 offset, u32 index);

  u8 _00[0x38 - 0x00];
  CGLibShader *unknown38; // Inferred role: shaders; original member name unknown.
  u8 _40[0x58 - 0x40];
  u32 unknown58; // Inferred role: shader idx; original member name unknown.
  u8 _5c[0x68 - 0x5c];
};

static_assert(offsetof(CGLibDecShader, unknown38) == 0x38, "");
static_assert(offsetof(CGLibDecShader, unknown58) == 0x58, "");
static_assert(sizeof(CGLibDecShader) == 0x68, "");

} // namespace grlib
