#pragma once
#include <stddef.h>

#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;

class GfFieldLocalSteer {
public:
  void dispose();
  bool isTimeOutCollide() const;
  f32 getCurAngle() const;

  GF_OBJ_HANDLE *unknown00; // Inferred role: object; original member name unknown.
  f32 unknown08;            // Role and original member name unknown.
  f32 unknown0c;            // Role and original member name unknown.
  f32 unknown10;            // Role and original member name unknown.
  bool unknown14;           // Role and original member name unknown.
  u8 _15[0x18 - 0x15];
  u64 unknown18; // Role and original member name unknown.
  u8 _20[0x24 - 0x20];
  f32 unknown24; // Inferred role: collide time; original member name unknown.
  u8 _28[0x30 - 0x28];
  f32 unknown30; // Inferred role: start angle; original member name unknown.
  f32 unknown34; // Inferred role: target angle; original member name unknown.
  f32 unknown38; // Inferred role: duration; original member name unknown.
  f32 unknown3c; // Inferred role: elapsed time; original member name unknown.
};

static_assert(offsetof(GfFieldLocalSteer, unknown08) == 0x08, "");
static_assert(offsetof(GfFieldLocalSteer, unknown14) == 0x14, "");
static_assert(offsetof(GfFieldLocalSteer, unknown18) == 0x18, "");
static_assert(offsetof(GfFieldLocalSteer, unknown24) == 0x24, "");
static_assert(offsetof(GfFieldLocalSteer, unknown30) == 0x30, "");
static_assert(offsetof(GfFieldLocalSteer, unknown3c) == 0x3c, "");
static_assert(sizeof(GfFieldLocalSteer) == 0x40, "");

} // namespace gf
