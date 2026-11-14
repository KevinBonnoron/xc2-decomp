#pragma once
#include <stddef.h>

#include "mm_math/mm_col3.h"
#include "types.h"

namespace ml {
class DrMan;
class DrFogObj;

class DrFogMan {
public:
  DrFogMan(DrMan *man);
  ~DrFogMan();
  void releaseAll();
  void update();
  void updateGbl();
  void calcTbl();
  void createGblFog();
  void releaseGblFog(DrFogObj *fog);
  bool isFogOn() const;

  DrMan *unknown00;    // Inferred role: dr man; original member name unknown.
  DrFogObj *unknown08; // Inferred role: first fog; original member name unknown.
  DrFogObj *unknown10; // Inferred role: last fog; original member name unknown.
  mm::Col3 unknown18;  // Inferred role: color; original member name unknown.
  mm::Col3 unknown24;  // Inferred role: side color; original member name unknown.
  mm::Col3 unknown30;  // Inferred role: sun color; original member name unknown.
  f32 unknown3c;       // Inferred role: near; original member name unknown.
  f32 unknown40;       // Inferred role: far; original member name unknown.
  f32 unknown44;       // Inferred role: str; original member name unknown.
  f32 unknown48;
  f32 unknown4c;
  f32 unknown50;
  f32 unknown54; // Inferred role: pow; original member name unknown.
  f32 unknown58;
  f32 unknown5c;
  f32 unknown60[28]; // Inferred role: fog table, the first 27 entries are copied to IDrDrawWorkInfo::m_fogTbl; original member name unknown.
  bool m_fogOn;
  bool unknownd1;
};

static_assert(offsetof(DrFogMan, unknown08) == 0x08, "");
static_assert(offsetof(DrFogMan, unknown18) == 0x18, "");
static_assert(offsetof(DrFogMan, unknown3c) == 0x3c, "");
static_assert(offsetof(DrFogMan, unknown60) == 0x60, "");
static_assert(offsetof(DrFogMan, m_fogOn) == 0xd0, "");

} // namespace ml
