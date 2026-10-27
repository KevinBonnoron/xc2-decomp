#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {
class DrEnvironmentObj;
class DrResMdoSeamMemObj;

struct MdsSeamLgtMapData {
  u8 _00[0x1c];
  u32 unknown1c; // Inferred role: memory size; original member name unknown.
  u8 _20[0x38 - 0x20];
};

static_assert(offsetof(MdsSeamLgtMapData, unknown1c) == 0x1c, "");
static_assert(sizeof(MdsSeamLgtMapData) == 0x38, "");

class DrResMdoSeamWrkLight {
public:
  static f32 SEAM_LIGHT_READ_CHECK;

  DrResMdoSeamWrkLight();
  virtual ~DrResMdoSeamWrkLight();
  void release();
  void objLgtRelease();
  void delCall();
  void setupWork(const MdsSeamLgtMapData *data);
  void changeMemCall();

  DrResMdoSeamWrkLight *unknown08;    // Inferred role: next; original member name unknown.
  DrResMdoSeamWrkLight *unknown10;    // Inferred role: prev; original member name unknown.
  const MdsSeamLgtMapData *unknown18; // Inferred role: light data; original member name unknown.
  DrEnvironmentObj *unknown20;        // Inferred role: environment object; original member name unknown.
  DrResMdoSeamMemObj *unknown28;      // Inferred role: memory object; original member name unknown.
  s32 unknown30;                      // Inferred role: index; original member name unknown.
  u32 unknown34;                      // Inferred role: memory size; original member name unknown.
  u16 unknown38;                      // Inferred role: out of range count; original member name unknown.
  u16 unknown3a;                      // Inferred role: state flags; original member name unknown.
};

static_assert(offsetof(DrResMdoSeamWrkLight, unknown18) == 0x18, "");
static_assert(offsetof(DrResMdoSeamWrkLight, unknown28) == 0x28, "");
static_assert(offsetof(DrResMdoSeamWrkLight, unknown30) == 0x30, "");
static_assert(offsetof(DrResMdoSeamWrkLight, unknown38) == 0x38, "");
static_assert(sizeof(DrResMdoSeamWrkLight) == 0x40, "");

} // namespace ml
