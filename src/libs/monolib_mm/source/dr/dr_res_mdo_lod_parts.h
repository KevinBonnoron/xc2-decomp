#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

// Layout from DrResMdoLodParts::calcPixel and calcAutoPixel.
struct MdsMdlLodData {
  u8 _00[0x10 - 0x00];
  f32 unknown10; // Inferred role: pixel size threshold; original member name unknown.
  u8 _14[0x15 - 0x14];
  u8 unknown15; // Inferred role: PIXEL_RATIO index; original member name unknown.
  u8 unknown16; // Inferred role: lod mode, 0 position and 1 pixel ratio; original member name unknown.
};

static_assert(offsetof(MdsMdlLodData, unknown10) == 0x10, "");
static_assert(offsetof(MdsMdlLodData, unknown15) == 0x15, "");
static_assert(offsetof(MdsMdlLodData, unknown16) == 0x16, "");

// Layout from DrResMdoLodParts::calcPixel and calcAutoPixel.
struct DrResMdlLodArg {
  u8 _00[0x10 - 0x00];
  bool unknown10; // Inferred role: lod state reset request; original member name unknown.
  u8 _11[0x18 - 0x11];
  f32 unknown18; // Inferred role: pixel size; original member name unknown.
};

static_assert(offsetof(DrResMdlLodArg, unknown10) == 0x10, "");
static_assert(offsetof(DrResMdlLodArg, unknown18) == 0x18, "");

class DrResMdoLodParts {
public:
  DrResMdoLodParts();
  void setup(const MdsMdlLodData *lodData);
  void calcPixel(const DrResMdlLodArg &arg, bool &isDisp);
  void calcAutoPixel(const DrResMdlLodArg &arg, bool &isDisp);

  static f32 PIXEL_RATIO[4];

  u64 unknown00; // Inferred role: state; original member name unknown.
  u32 unknown08; // Inferred role: state; original member name unknown.
  u8 _0c[0x10 - 0x0c];
  f32 unknown10;                        // Inferred role: ratio; original member name unknown.
  u32 unknown14;                        // Inferred role: state; original member name unknown.
  const MdsMdlLodData *m_mdsMdlLodData; // Inferred role: lod data; original member name unknown.
};

static_assert(offsetof(DrResMdoLodParts, unknown08) == 0x08, "");
static_assert(offsetof(DrResMdoLodParts, unknown10) == 0x10, "");
static_assert(offsetof(DrResMdoLodParts, m_mdsMdlLodData) == 0x18, "");
static_assert(sizeof(DrResMdoLodParts) == 0x20, "");

} // namespace ml
