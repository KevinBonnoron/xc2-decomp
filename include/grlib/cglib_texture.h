#pragma once
#include "types.h"

namespace grlib {

class CGLibTextureBuffer;

class CGLibTexture {
public:
  static void get1PixelTextureInfo(f32 *info, CGLibTextureBuffer &texture);
};

} // namespace grlib
