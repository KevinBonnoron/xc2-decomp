#pragma once
#include "types.h"

namespace gf {

class GfAssetResource {
public:
  static GfAssetResource *create(const char *assetName, const char *name, void *data, u32 size);
  static void checkMemoryForDebug();
};

} // namespace gf
