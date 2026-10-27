#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ml {

class DrResMdoSeamWrkInst;

// Inferred type: stock entry of an instance map; the original type name is unknown.
struct DrSeamStockInstEntry {
  DrResMdoSeamWrkInst *unknown00; // Inferred role: work; original member name unknown.
  s16 unknown08;                  // Inferred role: index; original member name unknown.
  s16 unknown0a;                  // Inferred role: kind; original member name unknown.
  u8 _0c[0x10 - 0x0c];
};

static_assert(offsetof(DrSeamStockInstEntry, unknown08) == 0x08, "");
static_assert(sizeof(DrSeamStockInstEntry) == 0x10, "");

class DrResMdoSeamParmRead {
public:
  ~DrResMdoSeamParmRead();
  void addPos(const mm::Vec3 &position);
  void setStockEnvMdl(int index);
  void setStockBaseMap(int index);
  void setStockInstMap(int index, DrResMdoSeamWrkInst *work);
  void setStockLowMdl(int index);
  void setStockMpfMdl(int index);
  void setStockLight(int index);
  void resetTexture();
  void resetHeightLvTexture();

  u32 unknown00; // Inferred role: flags; original member name unknown.
  u8 _04[0x10 - 0x04];
  mm::Vec3 unknown10[3]; // Inferred role: positions; original member name unknown.
  s32 unknown40;         // Inferred role: position num; original member name unknown.
  u8 _44[0x68 - 0x44];
  s16 unknown68;    // Inferred role: stock env model; original member name unknown.
  s16 unknown6a[8]; // Inferred role: stock base maps; original member name unknown.
  u8 _7a[0x80 - 0x7a];
  DrSeamStockInstEntry unknown80[8]; // Inferred role: stock instance maps; original member name unknown.
  s16 unknown100[8];                 // Inferred role: stock low models; original member name unknown.
  s16 unknown110[4];                 // Inferred role: stock mpf models; original member name unknown.
  s16 unknown118[4];                 // Inferred role: stock lights; original member name unknown.
  u8 _120[0x5d0 - 0x120];
  u16 unknown5d0; // Inferred role: stock base map num; original member name unknown.
  u16 unknown5d2; // Inferred role: stock instance map num; original member name unknown.
  u16 unknown5d4; // Inferred role: stock low model num; original member name unknown.
  u16 unknown5d6; // Inferred role: stock mpf model num; original member name unknown.
  u16 unknown5d8; // Inferred role: stock light num; original member name unknown.
  u8 _5da[0x5e2 - 0x5da];
  u16 unknown5e2; // Inferred role: stock texture list num; original member name unknown.
  u8 _5e4[0x5e8 - 0x5e4];
  u16 unknown5e8; // Inferred role: stock height texture num; original member name unknown.
};

static_assert(offsetof(DrResMdoSeamParmRead, unknown10) == 0x10, "");
static_assert(offsetof(DrResMdoSeamParmRead, unknown40) == 0x40, "");
static_assert(offsetof(DrResMdoSeamParmRead, unknown68) == 0x68, "");
static_assert(offsetof(DrResMdoSeamParmRead, unknown6a) == 0x6a, "");
static_assert(offsetof(DrResMdoSeamParmRead, unknown80) == 0x80, "");
static_assert(offsetof(DrResMdoSeamParmRead, unknown100) == 0x100, "");
static_assert(offsetof(DrResMdoSeamParmRead, unknown110) == 0x110, "");
static_assert(offsetof(DrResMdoSeamParmRead, unknown118) == 0x118, "");
static_assert(offsetof(DrResMdoSeamParmRead, unknown5d0) == 0x5d0, "");
static_assert(offsetof(DrResMdoSeamParmRead, unknown5d8) == 0x5d8, "");
static_assert(offsetof(DrResMdoSeamParmRead, unknown5e2) == 0x5e2, "");
static_assert(offsetof(DrResMdoSeamParmRead, unknown5e8) == 0x5e8, "");

} // namespace ml
