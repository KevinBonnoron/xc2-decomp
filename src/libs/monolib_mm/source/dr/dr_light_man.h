#pragma once
#include <stddef.h>

#include "mm_math/mm_col3.h"
#include "types.h"

namespace ml {

class DrLightObj;
class DrLightObjAmb;
class DrLightObjDir;
class DrLightObjPnt;
class DrMan;
class DrLightObjSpt;
class DrShdLgtMan;

class DrLightMan {
public:
  DrLightMan(DrMan *drMan);
  ~DrLightMan();
  void render();
  void renderDir();
  void renderPnt();
  void renderSpt();
  void renderDebugDir();
  void stockBegin();
  void stockEnd();
  void update();
  void updateAfterPnt();
  void updateAfterSpt();
  void releaseFastLight();
  f32 getSkyLuminance() const;
  void releaseAmbLight(DrLightObjAmb *light);
  void releaseDirLight(DrLightObjDir *light);
  void releaseAllAmbLight();
  void releaseAllDirLight();
  void releasePntLight(DrLightObjPnt *light);
  void releaseSptLight(DrLightObjSpt *light);
  DrLightObjDir *createDirLight();
  void releaseAll();
  DrLightObjPnt *createInstantPntLight();
  DrLightObjSpt *createInstantSptLight();
  void releaseInstantPntLight(DrLightObjPnt *light);
  void releaseInstantSptLight(DrLightObjSpt *light);
  void debugRender();
  void renderDebugPnt();
  void renderDebugSpt();
  void updateAmb();
  void updatePnt();
  void updateSpt();

  DrLightObj *unknown000;       // Inferred role: first ambient light; original member name unknown.
  DrLightObj *unknown008;       // Inferred role: last ambient light; original member name unknown.
  DrLightObj *unknown010;       // Inferred role: first directional light; original member name unknown.
  DrLightObj *unknown018;       // Inferred role: last directional light; original member name unknown.
  DrLightObj *unknown020;       // Inferred role: first point light; original member name unknown.
  DrLightObj *unknown028;       // Inferred role: last point light; original member name unknown.
  DrLightObj *unknown030;       // Inferred role: first spot light; original member name unknown.
  DrLightObj *unknown038;       // Inferred role: last spot light; original member name unknown.
  DrLightObj *unknown040[2][2]; // Inferred role: first and last requested ambient light per buffer; original member name unknown.
  DrLightObj *unknown060[2][2]; // Inferred role: first and last requested directional light per buffer; original member name unknown.
  DrLightObj *unknown080[2][2]; // Inferred role: first and last requested point light per buffer; original member name unknown.
  DrLightObj *unknown0a0[2][2]; // Inferred role: first and last requested spot light per buffer; original member name unknown.
  DrLightObj *unknown0c0[2];    // Inferred role: first and last requested instant point light; original member name unknown.
  DrLightObj *unknown0d0[2];    // Inferred role: first and last requested instant spot light; original member name unknown.
  DrMan *unknowne0;             // Inferred role: dr man; original member name unknown.
  DrShdLgtMan *unknowne8;       // Inferred role: shd light man; original member name unknown.
  DrLightObjAmb *unknown0f0;    // Inferred role: fast ambient light; original member name unknown.
  DrLightObjDir *unknown0f8;    // Inferred role: fast directional light; original member name unknown.
  s32 unknown100;               // Inferred role: ambient light count; original member name unknown.
  s32 unknown104;               // Inferred role: directional light count; original member name unknown.
  s32 unknown108;               // Inferred role: instant point light count; original member name unknown.
  s32 unknown10c;               // Inferred role: instant spot light count; original member name unknown.
  u8 _110[0x120 - 0x110];
  mm::Col3 unknown120; // Inferred role: ambient color of the other buffer; original member name unknown.
  mm::Col3 unknown12c; // Inferred role: ambient color; original member name unknown.
  u8 _138[0x140 - 0x138];
  mm::Col3 unknown140; // Inferred role: vector copied into the fog table by DrFogMan::calcTbl; original member name unknown.
  u8 _14c[0x160 - 0x14c];
  f32 unknown160; // Inferred role: sun shadow strength; original member name unknown.
  u8 _164[0x168 - 0x164];
  u32 unknown168;         // Inferred role: stocked dir light count; original member name unknown.
  mm::Col3 unknown16c[3]; // Inferred role: colors of the stocked directional lights; original member name unknown.
  u8 _190[0x1b8 - 0x190];
  bool unknown1b8; // Inferred role: sun shadow stock; original member name unknown.
  bool unknown1b9; // Inferred role: sun shadow enable; original member name unknown.
};

static_assert(offsetof(DrLightMan, unknown000) == 0x00, "");
static_assert(offsetof(DrLightMan, unknown020) == 0x20, "");
static_assert(offsetof(DrLightMan, unknown030) == 0x30, "");
static_assert(offsetof(DrLightMan, unknown040) == 0x40, "");
static_assert(offsetof(DrLightMan, unknown080) == 0x80, "");
static_assert(offsetof(DrLightMan, unknown0a0) == 0xa0, "");
static_assert(offsetof(DrLightMan, unknown0c0) == 0xc0, "");
static_assert(offsetof(DrLightMan, unknown0d0) == 0xd0, "");
static_assert(offsetof(DrLightMan, unknowne0) == 0xe0, "");
static_assert(offsetof(DrLightMan, unknowne8) == 0xe8, "");
static_assert(offsetof(DrLightMan, unknown0f0) == 0xf0, "");
static_assert(offsetof(DrLightMan, unknown100) == 0x100, "");
static_assert(offsetof(DrLightMan, unknown108) == 0x108, "");
static_assert(offsetof(DrLightMan, unknown10c) == 0x10c, "");
static_assert(offsetof(DrLightMan, unknown120) == 0x120, "");
static_assert(offsetof(DrLightMan, unknown16c) == 0x16c, "");
static_assert(offsetof(DrLightMan, unknown140) == 0x140, "");
static_assert(offsetof(DrLightMan, unknown12c) == 0x12c, "");
static_assert(offsetof(DrLightMan, unknown160) == 0x160, "");
static_assert(offsetof(DrLightMan, unknown168) == 0x168, "");
static_assert(offsetof(DrLightMan, unknown1b8) == 0x1b8, "");
static_assert(offsetof(DrLightMan, unknown1b9) == 0x1b9, "");

// Inferred role: deletes every object of a list linked through unknown10 and empties the list; shared by DrLightMan::releaseAll and
// DrEnvironmentMan::releaseAll; original name unknown.
template <class T> void unknown2100(T *&first, T *&last) {
  T *object = first;
  while (object != nullptr) {
    T *next = object->unknown10;
    delete object;
    object = next;
  }
  first = nullptr;
  last = nullptr;
}

} // namespace ml
