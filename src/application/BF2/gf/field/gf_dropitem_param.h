#pragma once
#include <stddef.h>

#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace gf {

class GfDropitemParam {
public:
  f32 unknown00;  // Role and original member name unknown.
  f32 unknown04;  // Role and original member name unknown.
  f32 unknown08;  // Role and original member name unknown.
  f32 unknown0c;  // Role and original member name unknown.
  f32 unknown10;  // Role and original member name unknown.
  f32 unknown14;  // Role and original member name unknown.
  f32 unknown18;  // Role and original member name unknown.
  f32 unknown1c;  // Role and original member name unknown.
  f32 unknown20;  // Role and original member name unknown.
  f32 unknown24;  // Role and original member name unknown.
  f32 unknown28;  // Role and original member name unknown.
  f32 unknown2c;  // Role and original member name unknown.
  f32 unknown30;  // Role and original member name unknown.
  f32 unknown34;  // Role and original member name unknown.
  f32 unknown38;  // Role and original member name unknown.
  f32 unknown3c;  // Role and original member name unknown.
  f32 unknown40;  // Role and original member name unknown.
  f32 unknown44;  // Role and original member name unknown.
  bool unknown48; // Role and original member name unknown.
  u8 _49[0x4c - 0x49];
  f32 unknown4c; // Role and original member name unknown.
  f32 unknown50; // Role and original member name unknown.
  f32 unknown54; // Role and original member name unknown.
  u32 unknown58; // Role and original member name unknown.
};

static_assert(offsetof(GfDropitemParam, unknown1c) == 0x1c, "");
static_assert(offsetof(GfDropitemParam, unknown48) == 0x48, "");
static_assert(offsetof(GfDropitemParam, unknown4c) == 0x4c, "");
static_assert(offsetof(GfDropitemParam, unknown58) == 0x58, "");
static_assert(sizeof(GfDropitemParam) == 0x5c, "");

class GfDropitemParamInst {
public:
  GfDropitemParamInst(const GfDropitemParam *param, f32 height);
  void create(const GfDropitemParam &param, f32 height);
  f32 getGravity() const;
  mm::Vec3 &getInitVelocity(mm::Vec3 &velocity) const;

  const GfDropitemParam *unknown00; // Inferred role: base parameters; original member name unknown.
  f32 unknown08;                    // Role and original member name unknown.
  f32 unknown0c;                    // Role and original member name unknown.
};

static_assert(offsetof(GfDropitemParamInst, unknown08) == 0x08, "");
static_assert(sizeof(GfDropitemParamInst) == 0x10, "");

} // namespace gf
