#pragma once
#include <stddef.h>

#include "grlib/cglib_depth_target.h"
#include "types.h"

namespace ml {

class MdoShdPxlWrkTex : public grlib::CGLibDepthTarget {
public:
  u8 _128[0x800 - 0x128];
  f32 unknown800; // Inferred role: shadow texture size; original member name unknown.
  s32 unknown804; // Inferred role: reference count; original member name unknown.
  s16 unknown808; // Inferred role: shadow type; original member name unknown.
  s16 unknown80a; // Inferred role: shadow quality level; original member name unknown.
  u8 _80c[0x810 - 0x80c];
};

static_assert(offsetof(MdoShdPxlWrkTex, unknown800) == 0x800, "");
static_assert(offsetof(MdoShdPxlWrkTex, unknown804) == 0x804, "");
static_assert(offsetof(MdoShdPxlWrkTex, unknown808) == 0x808, "");
static_assert(offsetof(MdoShdPxlWrkTex, unknown80a) == 0x80a, "");
static_assert(sizeof(MdoShdPxlWrkTex) == 0x810, "");

} // namespace ml
