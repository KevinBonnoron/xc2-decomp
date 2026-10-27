#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

// Inferred role: light file header; original type name unknown.
struct LgtFileHeader {
  u8 _00[0x1c];
  u32 unknown1c; // Inferred role: offset of the time data; original member name unknown.
};

class DrEnvironmentTime {
public:
  DrEnvironmentTime();
  bool setEnvTimeData(const LgtFileHeader *header, const u8 *data, bool isLoop);
  void changeMemEnvTimeData(const LgtFileHeader *header, const u8 *data);

  const u8 *unknown00; // Inferred role: time data; original member name unknown.
  const u8 *unknown08; // Inferred role: time table; original member name unknown.
  s32 unknown10;       // Inferred role: time count; original member name unknown.
  s32 unknown14;       // Inferred role: unknown value cleared by the constructor; original member name unknown.
  f32 unknown18;       // Inferred role: unknown constant; original member name unknown.
  f32 unknown1c;       // Inferred role: unknown constant; original member name unknown.
  s32 unknown20;       // Inferred role: unknown value cleared by the constructor; original member name unknown.
  s32 unknown24;       // Inferred role: unknown value cleared by the constructor; original member name unknown.
  bool unknown28;      // Inferred role: loop flag; original member name unknown.
  u8 unknown29;        // Inferred role: unknown value cleared by the constructor; original member name unknown.
  u8 _2a[0x2c - 0x2a];
  s32 unknown2c; // Inferred role: unknown value cleared by the constructor; original member name unknown.
};

static_assert(offsetof(DrEnvironmentTime, unknown08) == 0x08, "");
static_assert(offsetof(DrEnvironmentTime, unknown10) == 0x10, "");
static_assert(offsetof(DrEnvironmentTime, unknown18) == 0x18, "");
static_assert(offsetof(DrEnvironmentTime, unknown1c) == 0x1c, "");
static_assert(offsetof(DrEnvironmentTime, unknown28) == 0x28, "");
static_assert(offsetof(DrEnvironmentTime, unknown2c) == 0x2c, "");

} // namespace ml
