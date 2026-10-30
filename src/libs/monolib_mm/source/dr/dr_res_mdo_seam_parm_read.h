#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ml {

class DrResMdoSeamWrkInst;

// Inferred type: read request of the seam; the original type name is unknown.
struct _wkSeamReadWait {
  u8 _00[0x08];
  s16 unknown08; // Inferred role: resource index; original member name unknown.
  s16 unknown0a; // Inferred role: resource kind; original member name unknown.
  u8 _0c[0x10 - 0x0c];
};

static_assert(offsetof(_wkSeamReadWait, unknown08) == 0x08, "");
static_assert(offsetof(_wkSeamReadWait, unknown0a) == 0x0a, "");
static_assert(sizeof(_wkSeamReadWait) == 0x10, "");

// Inferred type: read call of the seam; the original type name is unknown.
struct _wkSeamReadCall {
  u8 _00[0x18];
  s16 unknown18; // Inferred role: resource index; original member name unknown.
  u8 _1a[0x1e - 0x1a];
  s16 unknown1e; // Inferred role: resource kind; original member name unknown.
  u8 _20[0x28 - 0x20];
};

static_assert(offsetof(_wkSeamReadCall, unknown18) == 0x18, "");
static_assert(offsetof(_wkSeamReadCall, unknown1e) == 0x1e, "");
static_assert(sizeof(_wkSeamReadCall) == 0x28, "");

// Inferred type: bit tables of the read packet; the original type name is unknown.
struct wkSeamReadPacDataInf {
  u32 unknown00;  // Inferred role: bit tables size; original member name unknown.
  u32 *unknown08; // Inferred role: vertex bits; original member name unknown.
  u32 *unknown10; // Inferred role: texture bits; original member name unknown.
};

static_assert(offsetof(wkSeamReadPacDataInf, unknown08) == 0x08, "");
static_assert(offsetof(wkSeamReadPacDataInf, unknown10) == 0x10, "");

// Inferred role: stock entry of an instance map; original type name unknown.
struct unknown062 {
  DrResMdoSeamWrkInst *unknown00; // Inferred role: work; original member name unknown.
  s16 unknown08;                  // Inferred role: index; original member name unknown.
  s16 unknown0a;                  // Inferred role: kind; original member name unknown.
  u8 _0c[0x10 - 0x0c];
};

static_assert(offsetof(unknown062, unknown08) == 0x08, "");
static_assert(sizeof(unknown062) == 0x10, "");

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
  DrResMdoSeamParmRead();
  void setStockVertex(f32 level, int index);
  void setStockTexture(f32 level, int index);
  bool isReadInfo(const _wkSeamReadWait &wait);

  u32 unknown00; // Inferred role: flags; original member name unknown.
  u8 _04[0x10 - 0x04];
  mm::Vec3 unknown10[3]; // Inferred role: positions; original member name unknown.
  s32 unknown40;         // Inferred role: position num; original member name unknown.
  u8 _44[0x50 - 0x44];
  u64 unknown50; // Inferred role: cleared by the constructor; original member name unknown.
  u32 unknown58; // Inferred role: cleared by the constructor; original member name unknown.
  u8 _5c[0x68 - 0x5c];
  s16 unknown68;    // Inferred role: stock env model; original member name unknown.
  s16 unknown6a[8]; // Inferred role: stock base maps; original member name unknown.
  u8 _7a[0x80 - 0x7a];
  unknown062 unknown80[8]; // Inferred role: stock instance maps; original member name unknown.
  s16 unknown100[8];       // Inferred role: stock low models; original member name unknown.
  s16 unknown110[4];       // Inferred role: stock mpf models; original member name unknown.
  s16 unknown118[4];       // Inferred role: stock lights; original member name unknown.
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
  u16 unknown5ea; // Inferred role: highest vertex index; original member name unknown.
  u16 unknown5ec; // Inferred role: lowest vertex index; original member name unknown.
  u16 unknown5ee; // Inferred role: highest texture index; original member name unknown.
  u16 unknown5f0; // Inferred role: lowest texture index; original member name unknown.
  u8 _5f2[0x610 - 0x5f2];
  _wkSeamReadCall *unknown610; // Inferred role: read calls; original member name unknown.
  s32 unknown618;              // Inferred role: read call num; original member name unknown.
  u8 _61c[0x62c - 0x61c];
  u16 unknown62c; // Inferred role: cleared by the constructor; original member name unknown.
  u8 _62e[0x630 - 0x62e];
  wkSeamReadPacDataInf *unknown630; // Inferred role: read packet; original member name unknown.
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
static_assert(offsetof(DrResMdoSeamParmRead, unknown50) == 0x50, "");
static_assert(offsetof(DrResMdoSeamParmRead, unknown58) == 0x58, "");
static_assert(offsetof(DrResMdoSeamParmRead, unknown5ea) == 0x5ea, "");
static_assert(offsetof(DrResMdoSeamParmRead, unknown5f0) == 0x5f0, "");
static_assert(offsetof(DrResMdoSeamParmRead, unknown610) == 0x610, "");
static_assert(offsetof(DrResMdoSeamParmRead, unknown618) == 0x618, "");
static_assert(offsetof(DrResMdoSeamParmRead, unknown62c) == 0x62c, "");
static_assert(offsetof(DrResMdoSeamParmRead, unknown630) == 0x630, "");

} // namespace ml
