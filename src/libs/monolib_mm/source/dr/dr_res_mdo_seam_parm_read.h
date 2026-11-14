#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ml {

class DrResMdoSeamWrkBase;
class DrResMdoSeamWrkInst;
class DrResMdoSeamMemObj;
class DrResMdoSeamWrkMpf;

// Inferred type: read request of the seam; the original type name is unknown.
struct _wkSeamReadWait {
  void *unknown00; // Inferred role: work; original member name unknown.
  u16 unknown08;   // Inferred role: resource index; original member name unknown.
  s16 unknown0a;   // Inferred role: resource kind; original member name unknown.
  u8 unknown0c;    // Inferred role: unknown, copied to the read call; original member name unknown.
  u8 _0d[0x10 - 0x0d];
};

static_assert(offsetof(_wkSeamReadWait, unknown08) == 0x08, "");
static_assert(offsetof(_wkSeamReadWait, unknown0a) == 0x0a, "");
static_assert(offsetof(_wkSeamReadWait, unknown0c) == 0x0c, "");
static_assert(sizeof(_wkSeamReadWait) == 0x10, "");

// Inferred type: read call of the seam; the original type name is unknown.
struct _wkSeamReadCall {
  DrResMdoSeamMemObj *unknown00; // Inferred role: memory object; original member name unknown.
  void *unknown08;               // Inferred role: work; original member name unknown.
  void *unknown10;               // Inferred role: linked work, set by the instance map; original member name unknown.
  u16 unknown18;                 // Inferred role: resource index; original member name unknown.
  u16 unknown1a;                 // Inferred role: unknown, copied from the read request; original member name unknown.
  u16 unknown1c;                 // Inferred role: file handle index; original member name unknown.
  s16 unknown1e;                 // Inferred role: resource kind; original member name unknown.
  s32 unknown20;                 // Inferred role: read size; original member name unknown.
  u8 _24[0x28 - 0x24];
};

static_assert(offsetof(_wkSeamReadCall, unknown08) == 0x08, "");
static_assert(offsetof(_wkSeamReadCall, unknown10) == 0x10, "");
static_assert(offsetof(_wkSeamReadCall, unknown18) == 0x18, "");
static_assert(offsetof(_wkSeamReadCall, unknown1a) == 0x1a, "");
static_assert(offsetof(_wkSeamReadCall, unknown1c) == 0x1c, "");
static_assert(offsetof(_wkSeamReadCall, unknown1e) == 0x1e, "");
static_assert(offsetof(_wkSeamReadCall, unknown20) == 0x20, "");
static_assert(sizeof(_wkSeamReadCall) == 0x28, "");

// Inferred type: bit tables of the read packet; the original type name is unknown.
struct wkSeamReadPacDataInf {
  u32 unknown00;  // Inferred role: bit tables size; original member name unknown.
  u32 *unknown08; // Inferred role: vertex bits; original member name unknown.
  u32 *unknown10; // Inferred role: texture bits; original member name unknown.
  u32 *unknown18; // Inferred role: base map vertex bits; original member name unknown.
  u32 *unknown20; // Inferred role: instance map position bits; original member name unknown.
  u32 *unknown28; // Inferred role: mpf poli bits; original member name unknown.
  u32 *unknown30; // Inferred role: mpf instance bits; original member name unknown.
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
  // Inferred role: stock entry of the position read lists, with the highest and lowest requested index; original type name unknown.
  template <typename T> struct unknown001 {
    T *unknown00;  // Inferred role: work; original member name unknown.
    u16 unknown08; // Inferred role: highest index; original member name unknown.
    u16 unknown0a; // Inferred role: lowest index; original member name unknown.
    u8 _0c[0x10 - 0x0c];
  };

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
  void begin(wkSeamReadPacDataInf *packet);
  void setStockVertex(f32 level, int index);
  void setStockTexture(f32 level, int index);
  bool isReadInfo(const _wkSeamReadWait &wait);
  bool isReadAllInfo(const _wkSeamReadWait &wait);
  void setStockBaseVertex(int index, DrResMdoSeamWrkBase *work);
  void setStockInstPos(int index, DrResMdoSeamWrkInst *work);
  void setStockMpfPoli(int index, DrResMdoSeamWrkMpf *work);
  void setStockMpfInst(int index, DrResMdoSeamWrkMpf *work);

  u32 unknown00; // Inferred role: flags; original member name unknown.
  u8 _04[0x10 - 0x04];
  mm::Vec3 unknown10[3]; // Inferred role: positions; original member name unknown.
  s32 unknown40;         // Inferred role: position num; original member name unknown.
  u8 _44[0x50 - 0x44];
  mm::Vec3 unknown50; // Inferred role: main read position; original member name unknown.
  u8 _60[0x68 - 0x60];
  s16 m_stockEnvMdl;
  s16 unknown6a[8]; // Inferred role: stock base maps; original member name unknown.
  u8 _7a[0x80 - 0x7a];
  unknown062 unknown80[8]; // Inferred role: stock instance maps; original member name unknown.
  s16 unknown100[8];       // Inferred role: stock low models; original member name unknown.
  s16 unknown110[4];       // Inferred role: stock mpf models; original member name unknown.
  s16 unknown118[4];       // Inferred role: stock lights; original member name unknown.
  u8 _120[0x3d0 - 0x120];
  unknown001<DrResMdoSeamWrkBase> unknown3d0[8]; // Inferred role: stock base map vertex works; original member name unknown.
  unknown001<DrResMdoSeamWrkInst> unknown450[8]; // Inferred role: stock instance map position works; original member name unknown.
  unknown001<DrResMdoSeamWrkMpf> unknown4d0[8];  // Inferred role: stock mpf instance works; original member name unknown.
  unknown001<DrResMdoSeamWrkMpf> unknown550[8];  // Inferred role: stock mpf poli works; original member name unknown.
  u16 unknown5d0;                                // Inferred role: stock base map num; original member name unknown.
  u16 unknown5d2;                                // Inferred role: stock instance map num; original member name unknown.
  u16 unknown5d4;                                // Inferred role: stock low model num; original member name unknown.
  u16 unknown5d6;                                // Inferred role: stock mpf model num; original member name unknown.
  u16 unknown5d8;                                // Inferred role: stock light num; original member name unknown.
  u16 unknown5da;                                // Inferred role: cleared by begin; original member name unknown.
  u16 unknown5dc;                                // Inferred role: cleared by begin; original member name unknown.
  u16 unknown5de;                                // Inferred role: cleared by begin; original member name unknown.
  u16 unknown5e0;                                // Inferred role: cleared by begin; original member name unknown.
  u16 unknown5e2;                                // Inferred role: stock texture list num; original member name unknown.
  u16 unknown5e4;                                // Inferred role: cleared by begin; original member name unknown.
  u16 unknown5e6;                                // Inferred role: cleared by begin; original member name unknown.
  u16 unknown5e8;                                // Inferred role: stock height texture num; original member name unknown.
  u16 unknown5ea;                                // Inferred role: highest vertex index; original member name unknown.
  u16 unknown5ec;                                // Inferred role: lowest vertex index; original member name unknown.
  u16 unknown5ee;                                // Inferred role: highest texture index; original member name unknown.
  u16 unknown5f0;                                // Inferred role: lowest texture index; original member name unknown.
  u16 unknown5f2;                                // Inferred role: highest base map vertex index; original member name unknown.
  u16 unknown5f4;                                // Inferred role: lowest base map vertex index; original member name unknown.
  u16 unknown5f6;                                // Inferred role: highest instance map position index; original member name unknown.
  u16 unknown5f8;                                // Inferred role: lowest instance map position index; original member name unknown.
  u16 unknown5fa;                                // Inferred role: highest mpf poli index; original member name unknown.
  u16 unknown5fc;                                // Inferred role: lowest mpf poli index; original member name unknown.
  u16 unknown5fe;                                // Inferred role: highest mpf instance index; original member name unknown.
  u16 unknown600;                                // Inferred role: lowest mpf instance index; original member name unknown.
  u16 unknown602;                                // Inferred role: stock base map vertex work num; original member name unknown.
  u16 unknown604;                                // Inferred role: stock instance map position work num; original member name unknown.
  u16 unknown606;                                // Inferred role: stock mpf instance work num; original member name unknown.
  u16 unknown608;                                // Inferred role: stock mpf poli work num; original member name unknown.
  u8 _60a[0x610 - 0x60a];
  _wkSeamReadCall *unknown610; // Inferred role: read calls; original member name unknown.
  s32 unknown618;              // Inferred role: read call num; original member name unknown.
  u8 _61c[0x620 - 0x61c];
  _wkSeamReadWait *unknown620; // Inferred role: read waits; original member name unknown.
  s32 unknown628;              // Inferred role: read wait num; original member name unknown.
  u8 unknown62c;               // Inferred role: cleared by the constructor and begin; original member name unknown.
  u8 unknown62d;               // Inferred role: cleared by the constructor; original member name unknown.
  u8 _62e[0x630 - 0x62e];
  wkSeamReadPacDataInf *unknown630; // Inferred role: read packet; original member name unknown.
};

static_assert(sizeof(DrResMdoSeamParmRead::unknown001<DrResMdoSeamWrkBase>) == 0x10, "");
static_assert(offsetof(DrResMdoSeamParmRead, unknown3d0) == 0x3d0, "");
static_assert(offsetof(DrResMdoSeamParmRead, unknown450) == 0x450, "");
static_assert(offsetof(DrResMdoSeamParmRead, unknown4d0) == 0x4d0, "");
static_assert(offsetof(DrResMdoSeamParmRead, unknown550) == 0x550, "");
static_assert(offsetof(DrResMdoSeamParmRead, unknown5f2) == 0x5f2, "");
static_assert(offsetof(DrResMdoSeamParmRead, unknown600) == 0x600, "");
static_assert(offsetof(DrResMdoSeamParmRead, unknown602) == 0x602, "");
static_assert(offsetof(DrResMdoSeamParmRead, unknown608) == 0x608, "");
static_assert(offsetof(DrResMdoSeamParmRead, unknown10) == 0x10, "");
static_assert(offsetof(DrResMdoSeamParmRead, unknown40) == 0x40, "");
static_assert(offsetof(DrResMdoSeamParmRead, m_stockEnvMdl) == 0x68, "");
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
static_assert(offsetof(DrResMdoSeamParmRead, unknown5ea) == 0x5ea, "");
static_assert(offsetof(DrResMdoSeamParmRead, unknown5f0) == 0x5f0, "");
static_assert(offsetof(DrResMdoSeamParmRead, unknown610) == 0x610, "");
static_assert(offsetof(DrResMdoSeamParmRead, unknown618) == 0x618, "");
static_assert(offsetof(DrResMdoSeamParmRead, unknown620) == 0x620, "");
static_assert(offsetof(DrResMdoSeamParmRead, unknown628) == 0x628, "");
static_assert(offsetof(DrResMdoSeamParmRead, unknown62c) == 0x62c, "");
static_assert(offsetof(DrResMdoSeamParmRead, unknown630) == 0x630, "");

} // namespace ml
