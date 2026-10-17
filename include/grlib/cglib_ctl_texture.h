#pragma once
#include "types.h"

namespace grlib {
class CGLibSampler;
class CGLibTextureBuffer;

class CGLibCtlTexture {
public:
  static void setTexture(const CGLibTextureBuffer &texture, const CGLibSampler &sampler, u32 location);
  static void setUAVTexture(const CGLibTextureBuffer &texture, u32 location, u32 level, u32 layer);
};

} // namespace grlib
