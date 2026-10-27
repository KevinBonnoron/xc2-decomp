#pragma once
#include <stddef.h>

#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;
struct GF_SEARCH_OBJ;

static GF_SEARCH_OBJ *const INVALID_SEARCH_OBJ = reinterpret_cast<GF_SEARCH_OBJ *>(-1);

struct GfSearchInfo {
  u8 _00[0x78];
  GF_OBJ_HANDLE *unknown78; // Inferred role: searched object; original member name unknown.
  u32 unknown80;            // Inferred role: flags, bit 0 disables the search; original member name unknown.
  u8 _84[0x90 - 0x84];
};

static_assert(offsetof(GfSearchInfo, unknown78) == 0x78, "");
static_assert(offsetof(GfSearchInfo, unknown80) == 0x80, "");
static_assert(sizeof(GfSearchInfo) == 0x90, "");

class GfGameSearchObj : public mm::mtl::PtrSingleton<GfGameSearchObj> {
public:
  static void destroyObj(GF_SEARCH_OBJ *searchObj);
  static void setEnable(GF_SEARCH_OBJ *searchObj, bool isEnable);
  static bool isEnable(GF_SEARCH_OBJ *searchObj);
  static bool isInitialized();
  static GfSearchInfo *getInfo(GF_SEARCH_OBJ *searchObj);
  static GF_OBJ_HANDLE *getObj(GF_SEARCH_OBJ *searchObj);
  u64 createHandle(u32 index);

  u8 _08[0x2428 - 0x08];
  GfSearchInfo *unknown2428; // Inferred role: search infos; original member name unknown.
  u8 _2430[0x90978 - 0x2430];
  u32 unknown90978;  // Inferred role: handle serial; original member name unknown.
  bool unknown9097c; // Inferred role: initialized; original member name unknown.
};

static_assert(offsetof(GfGameSearchObj, unknown2428) == 0x2428, "");
static_assert(offsetof(GfGameSearchObj, unknown90978) == 0x90978, "");
static_assert(offsetof(GfGameSearchObj, unknown9097c) == 0x9097c, "");

} // namespace gf
