#pragma once
#include <stddef.h>

#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;

class GfAssetMultiBind {
public:
  bool isValid() const;
  void loadedAsset(GF_OBJ_HANDLE *handle);
  void unloadedAsset(GF_OBJ_HANDLE *handle);

  u8 _00[0x488];
  u32 unknown488; // Inferred role: unique id; original member name unknown.
};

static_assert(offsetof(GfAssetMultiBind, unknown488) == 0x488, "");

} // namespace gf
