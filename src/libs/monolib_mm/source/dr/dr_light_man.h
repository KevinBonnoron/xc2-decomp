#pragma once
#include <stddef.h>

#include "mm_math/mm_col3.h"
#include "types.h"

namespace ml {

class DrLightObjAmb;
class DrLightObjDir;
class DrLightObjPnt;
class DrMan;
class DrLightObjSpt;

class DrLightMan {
public:
  void render();
  void renderDir();
  void renderPnt();
  void renderSpt();
  void renderDebugDir();
  void stockBegin();
  void stockEnd();
  void updateAfterPnt();
  void updateAfterSpt();
  void releaseFastLight();
  f32 getSkyLuminance() const;
  void releaseAmbLight(DrLightObjAmb *light);
  void releaseDirLight(DrLightObjDir *light);
  void releasePntLight(DrLightObjPnt *light);
  void releaseSptLight(DrLightObjSpt *light);
  DrLightObjPnt *createInstantPntLight();
  DrLightObjSpt *createInstantSptLight();
  void releaseInstantPntLight(DrLightObjPnt *light);
  void releaseInstantSptLight(DrLightObjSpt *light);

  u8 _000[0xe0];
  DrMan *unknowne0; // Inferred role: dr man; original member name unknown.
  u8 _0e8[0xf0 - 0x0e8];
  DrLightObjAmb *unknown0f0; // Inferred role: fast ambient light; original member name unknown.
  DrLightObjDir *unknown0f8; // Inferred role: fast directional light; original member name unknown.
  s32 unknown100;            // Inferred role: ambient light count; original member name unknown.
  s32 unknown104;            // Inferred role: directional light count; original member name unknown.
  s32 unknown108;            // Inferred role: instant point light count; original member name unknown.
  s32 unknown10c;            // Inferred role: instant spot light count; original member name unknown.
  u8 _110[0x120 - 0x110];
  mm::Col3 unknown120; // Inferred role: ambient color of the other buffer; original member name unknown.
  mm::Col3 unknown12c; // Inferred role: ambient color; original member name unknown.
  u8 _138[0x160 - 0x138];
  f32 unknown160; // Inferred role: sun shadow strength; original member name unknown.
  u8 _164[0x168 - 0x164];
  u32 unknown168; // Inferred role: stocked dir light count; original member name unknown.
  u8 _16c[0x1b8 - 0x16c];
  bool unknown1b8; // Inferred role: sun shadow stock; original member name unknown.
  bool unknown1b9; // Inferred role: sun shadow enable; original member name unknown.
};

static_assert(offsetof(DrLightMan, unknowne0) == 0xe0, "");
static_assert(offsetof(DrLightMan, unknown0f0) == 0xf0, "");
static_assert(offsetof(DrLightMan, unknown100) == 0x100, "");
static_assert(offsetof(DrLightMan, unknown108) == 0x108, "");
static_assert(offsetof(DrLightMan, unknown10c) == 0x10c, "");
static_assert(offsetof(DrLightMan, unknown120) == 0x120, "");
static_assert(offsetof(DrLightMan, unknown12c) == 0x12c, "");
static_assert(offsetof(DrLightMan, unknown160) == 0x160, "");
static_assert(offsetof(DrLightMan, unknown168) == 0x168, "");
static_assert(offsetof(DrLightMan, unknown1b8) == 0x1b8, "");
static_assert(offsetof(DrLightMan, unknown1b9) == 0x1b9, "");

} // namespace ml
