#pragma once
#include "types.h"

namespace gf {

class GfAssetName {
public:
  GfAssetName(const char *name);
  const char *getName();

  u8 _00[0x7c - 0x00];
};

static_assert(sizeof(GfAssetName) == 0x7c, "");

} // namespace gf
