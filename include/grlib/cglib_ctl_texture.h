#pragma once
#include "types.h"

namespace grlib {
class CGLibSampler;
class CGLibTextureBuffer;

class CGLibCtlTexture {
public:
  static void setTexture(const CGLibTextureBuffer &texture, const CGLibSampler &sampler, u32 location);
};

} // namespace grlib
