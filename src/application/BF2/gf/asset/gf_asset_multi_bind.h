#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_list.h"
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;

class GfAssetMultiBind {
public:
  GfAssetMultiBind(u32 uniqueId, bool flag);
  virtual ~GfAssetMultiBind() {}
  bool isValid() const;
  bool bind(GF_OBJ_HANDLE *handle);
  bool unbind(GF_OBJ_HANDLE *handle);
  bool loadedAsset(GF_OBJ_HANDLE *handle);
  bool unloadedAsset(GF_OBJ_HANDLE *handle);
  void checkObject();

  mm::mtl::FixedList<GF_OBJ_HANDLE *, 32> unknown08;  // Inferred role: bound objects; original member name unknown.
  mm::mtl::FixedList<GF_OBJ_HANDLE *, 32> unknown248; // Inferred role: bound objects with a loaded asset; original member name unknown.
  u32 unknown488;                                     // Inferred role: unique id; original member name unknown.
  u32 unknown48c;                                     // Inferred role: expected number of bound objects; original member name unknown.
  u32 unknown490;                                     // Inferred role: number of loaded objects; original member name unknown.
  bool unknown494;                                    // Role and original member name unknown.
};

static_assert(offsetof(GfAssetMultiBind, unknown08) == 0x08, "");
static_assert(offsetof(GfAssetMultiBind, unknown248) == 0x248, "");
static_assert(offsetof(GfAssetMultiBind, unknown488) == 0x488, "");
static_assert(offsetof(GfAssetMultiBind, unknown48c) == 0x48c, "");
static_assert(offsetof(GfAssetMultiBind, unknown490) == 0x490, "");
static_assert(offsetof(GfAssetMultiBind, unknown494) == 0x494, "");
static_assert(sizeof(GfAssetMultiBind) == 0x498, "");

} // namespace gf
