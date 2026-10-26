#pragma once
#include <stddef.h>

#include "grlib/cglib_texture_buffer.h"
#include "mm_math/mm_col3.h"
#include "mm_math/mm_mat44.h"
#include "types.h"

namespace ml {

class DrLightObjGlobalIBL {
public:
  static const int TEXTURE_MAX = 7;
  static const int SH_TERM_NUM = 4;

  int getPriority() const;

  u8 _00[0x08 - 0x00];
  int unknown08; // Inferred role: version; original member name unknown.
  int m_priority;
  u8 _10[0x14 - 0x10];
  int unknown14; // Inferred role: texture num; original member name unknown.
  u8 _18[0x78 - 0x18];
  grlib::CGLibTextureBuffer unknown78[TEXTURE_MAX]; // Inferred role: textures; original member name unknown.
  u8 _388[0x3a0 - 0x388];
  mm::Col3 unknown3a0; // Inferred role: additional ambient; original member name unknown.
  u8 _3ac[0x3b0 - 0x3ac];
  f32 unknown3b0; // Inferred role: sky intensity; original member name unknown.
  f32 unknown3b4; // Inferred role: dir light intensity; original member name unknown.
  u8 _3b8[0x450 - 0x3b8];
  f32 unknown450[TEXTURE_MAX][SH_TERM_NUM][9];     // Inferred role: sh terms; original member name unknown.
  mm::Mat44 unknown840[TEXTURE_MAX * SH_TERM_NUM]; // Inferred role: sh matrices; original member name unknown.
};

static_assert(offsetof(DrLightObjGlobalIBL, unknown08) == 0x08, "");
static_assert(offsetof(DrLightObjGlobalIBL, m_priority) == 0x0c, "");
static_assert(offsetof(DrLightObjGlobalIBL, unknown14) == 0x14, "");
static_assert(offsetof(DrLightObjGlobalIBL, unknown78) == 0x78, "");
static_assert(offsetof(DrLightObjGlobalIBL, unknown3a0) == 0x3a0, "");
static_assert(offsetof(DrLightObjGlobalIBL, unknown3b0) == 0x3b0, "");
static_assert(offsetof(DrLightObjGlobalIBL, unknown3b4) == 0x3b4, "");
static_assert(offsetof(DrLightObjGlobalIBL, unknown450) == 0x450, "");
static_assert(offsetof(DrLightObjGlobalIBL, unknown840) == 0x840, "");

} // namespace ml
