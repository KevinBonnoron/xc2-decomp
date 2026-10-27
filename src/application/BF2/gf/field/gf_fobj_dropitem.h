#pragma once
#include <stddef.h>

#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;

class GfFobjDropitem {
public:
  virtual ~GfFobjDropitem() {}
  bool isEnableGet() const;
  void disposeEffect();

  u16 unknown08;  // Role and original member name unknown.
  u16 unknown0a;  // Role and original member name unknown.
  bool unknown0c; // Role and original member name unknown.
  u8 _0d;
  bool unknown0e; // Role and original member name unknown.
  u8 _0f;
  GF_OBJ_HANDLE *unknown10; // Inferred role: object; original member name unknown.
  u8 _18[0x20 - 0x18];
  u64 unknown20; // Role and original member name unknown.
  u32 unknown28; // Role and original member name unknown.
  u8 _2c[0x30 - 0x2c];
  s32 unknown30; // Inferred role: state; original member name unknown.
  u8 _34[0x38 - 0x34];
  u64 unknown38;  // Role and original member name unknown.
  u64 unknown40;  // Role and original member name unknown.
  u64 unknown48;  // Role and original member name unknown.
  bool unknown50; // Role and original member name unknown.
  u8 _51[0x54 - 0x51];
  u32 unknown54; // Inferred role: effect handle; original member name unknown.
  u8 _58[0x60 - 0x58];
};

static_assert(offsetof(GfFobjDropitem, unknown08) == 0x08, "");
static_assert(offsetof(GfFobjDropitem, unknown10) == 0x10, "");
static_assert(offsetof(GfFobjDropitem, unknown30) == 0x30, "");
static_assert(offsetof(GfFobjDropitem, unknown50) == 0x50, "");
static_assert(offsetof(GfFobjDropitem, unknown54) == 0x54, "");

} // namespace gf
