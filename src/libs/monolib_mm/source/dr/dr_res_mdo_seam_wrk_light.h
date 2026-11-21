#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {
class DrEnvironmentObj;
class DrResMdoSeamMemObj;
class DrResMdoSeamParmRead;

// Inferred layout of the light map data; also the entry of the light table of the seam resource
// (stride 0x38, data offset 0x18 and size 0x1c read by DrMdoCtlSeamRead::callLightStream at 0x7100827840).
struct MdsSeamLgtMapData {
  f32 unknown00[3]; // Inferred role: maximum x, y and z of the box of the light; original member name unknown. Read by DrMdoCtlSeamLight::readLightCheck (0x71008246a0).
  f32 unknown0c[3]; // Inferred role: minimum x, y and z of the box of the light; original member name unknown.
  u32 unknown18;    // Inferred role: data offset in the seam file; original member name unknown.
  u32 unknown1c;    // Inferred role: memory size; original member name unknown.
  u16 unknown20;    // Inferred role: index of the bit tested in the DrMan bit table; original member name unknown.
  u8 _22[0x38 - 0x22];
};

static_assert(offsetof(MdsSeamLgtMapData, unknown0c) == 0x0c, "");
static_assert(offsetof(MdsSeamLgtMapData, unknown18) == 0x18, "");
static_assert(offsetof(MdsSeamLgtMapData, unknown1c) == 0x1c, "");
static_assert(offsetof(MdsSeamLgtMapData, unknown20) == 0x20, "");
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
  bool update(const DrResMdoSeamParmRead *parmRead, const u32 *gblIdx, bool isOpen);

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
