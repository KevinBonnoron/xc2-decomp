#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrResMdoPntAlpha {
public:
  enum PntAlphaFlag {
    PNT_ALPHA_FLAG_UNKNOWN_1 = 0x1,
    PNT_ALPHA_FLAG_UNKNOWN_2 = 0x2,
    PNT_ALPHA_FLAG_UNKNOWN_4 = 0x4,
  };

  void init();
  f32 getObjAlpha(bool unknown001);
  void setAlphaReset(bool unknown001);
  void create(const void *unknown001);

  u32 unknown00;         // Inferred role: state flags; original member name unknown.
  f32 unknown04;         // Inferred role: current alpha; original member name unknown.
  const void *unknown08; // Inferred role: owner key; original member name unknown.
};

static_assert(offsetof(DrResMdoPntAlpha, unknown00) == 0x00, "");
static_assert(offsetof(DrResMdoPntAlpha, unknown04) == 0x04, "");
static_assert(offsetof(DrResMdoPntAlpha, unknown08) == 0x08, "");
static_assert(sizeof(DrResMdoPntAlpha) == 0x10, "");

class DrResMdoPntAlphaMan {
public:
  static s32 getWrkSize(s32 unknown001);
  void setup(DrResMdoPntAlpha *unknown001, DrResMdoPntAlpha **unknown002, s32 unknown003);
  f32 getAlphaObj(const void *unknown001, bool unknown002);
  void setAlphaReset(const void *unknown001, bool unknown002);

  DrResMdoPntAlpha *unknown00;  // Inferred role: alpha objects; original member name unknown.
  DrResMdoPntAlpha **unknown08; // Inferred role: active alpha objects; original member name unknown.
  s32 unknown10;                // Inferred role: alpha object count; original member name unknown.
  s32 unknown14;                // Inferred role: active alpha object count; original member name unknown.
};

static_assert(offsetof(DrResMdoPntAlphaMan, unknown00) == 0x00, "");
static_assert(offsetof(DrResMdoPntAlphaMan, unknown08) == 0x08, "");
static_assert(offsetof(DrResMdoPntAlphaMan, unknown10) == 0x10, "");
static_assert(offsetof(DrResMdoPntAlphaMan, unknown14) == 0x14, "");
static_assert(sizeof(DrResMdoPntAlphaMan) == 0x18, "");

} // namespace ml
