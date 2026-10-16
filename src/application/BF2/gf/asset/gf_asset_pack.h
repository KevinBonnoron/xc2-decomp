#pragma once
#include <stddef.h>

#include "gf/asset/gf_asset_def.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace gf {

class GfAssetFiles {
public:
  const mm::mtl::FixStr<128> &getFileName(GfFileIdx index) const;
};

class GfAssetPack {
public:
  u8 _00[0x120 - 0x00];
  GfAssetFiles files;
};

static_assert(offsetof(GfAssetPack, files) == 0x120, "");

} // namespace gf
