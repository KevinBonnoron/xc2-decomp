#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {
class DrMan;

// Light file header; layout from DrEnvironmentObjLgt::setupLgt (1.0.0: 0x71007e0388) and changeMemCall (0x71007e1890).
struct LgtFileHeader {
  u8 _00[0x04];
  u32 unknown04; // Inferred role: version, 10008 makes the time data loop; original member name unknown.
  u32 unknown08; // Inferred role: offset of the light object table; original member name unknown.
  u32 unknown0c; // Inferred role: offset of the light position table; original member name unknown.
  u8 _10[0x14 - 0x10];
  u32 unknown14; // Inferred role: offset of the fog table; original member name unknown.
  u8 _18[0x1c - 0x18];
  u32 unknown1c; // Inferred role: offset of the time data; original member name unknown.
  u32 unknown20; // Inferred role: offset of the animation data, the light object table one when zero; original member name unknown.
  u32 unknown24; // Inferred role: offset of the fog weather variant table; original member name unknown.
  u32 unknown28; // Inferred role: flags, bit 7 local IBL lights, bit 16 clip list; original member name unknown.
  u32 unknown2c; // Inferred role: clip list offset passed to DrResWrkClipList; original member name unknown.
};

static_assert(offsetof(LgtFileHeader, unknown14) == 0x14, "");
static_assert(offsetof(LgtFileHeader, unknown1c) == 0x1c, "");
static_assert(offsetof(LgtFileHeader, unknown2c) == 0x2c, "");

class DrEnvironmentTime {
public:
  DrEnvironmentTime();
  bool setEnvTimeData(const LgtFileHeader *header, const u8 *data, bool isLoop);
  void changeMemEnvTimeData(const LgtFileHeader *header, const u8 *data);
  void setWeatherNum(DrMan *drMan, bool isChange, int screen);

  const u8 *unknown00; // Inferred role: time data; original member name unknown.
  const u8 *unknown08; // Inferred role: time table; original member name unknown.
  s32 unknown10;       // Inferred role: time count; original member name unknown.
  f32 unknown14;       // Inferred role: time, copied from DrMan::m_timerVal by DrEnvironmentObjLgt::update; original member name unknown.
  f32 unknown18;       // Inferred role: blend rate toward the time color; original member name unknown.
  f32 unknown1c;       // Inferred role: unknown constant; original member name unknown.
  f32 unknown20;       // Inferred role: blend frames left, the time color is blended while not zero; original member name unknown.
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
