#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {

struct CGLibShaderBlockInfo {
  u32 unknown00; // Inferred role: name ofs; original member name unknown.
  u16 unknown04; // Inferred role: value num; original member name unknown.
  u16 unknown06; // Inferred role: value idx; original member name unknown.
  u32 unknown08; // Inferred role: stage bind ofs; original member name unknown.
  u8 unknown0c;  // Inferred role: index; original member name unknown.
  u8 unknown0d;  // Inferred role: stage bind num; original member name unknown.
  u16 unknown0e; // Inferred role: size; original member name unknown.
};

static_assert(sizeof(CGLibShaderBlockInfo) == 0x10, "");

struct CGLibShaderInfo {
  u8 _00[0x20 - 0x00];
  s16 unknown20; // Inferred role: uniform block num; original member name unknown.
  u16 unknown22; // Inferred role: uniform block max; original member name unknown.
  u32 unknown24; // Inferred role: uniform block ofs; original member name unknown.
  u32 unknown28; // Inferred role: uniform block idx ofs; original member name unknown.
  s16 unknown2c; // Inferred role: storage buffer num; original member name unknown.
  u16 unknown2e; // Inferred role: storage buffer max; original member name unknown.
  u32 unknown30; // Inferred role: storage buffer ofs; original member name unknown.
  u32 unknown34; // Inferred role: storage buffer idx ofs; original member name unknown.
};

static_assert(offsetof(CGLibShaderInfo, unknown20) == 0x20, "");
static_assert(offsetof(CGLibShaderInfo, unknown34) == 0x34, "");

class CGLibShader {
public:
  CGLibShader();
  int getTextureLocation(const char *name) const;
  int getUniformBlockOfs(const char *name) const;

  const u8 *m_data;
  const CGLibShaderInfo *unknown08; // Inferred role: info; original member name unknown.
  u8 _10[0xd8 - 0x10];
};

static_assert(sizeof(CGLibShader) == 0xd8, "");

} // namespace grlib
