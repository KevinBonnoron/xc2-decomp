#pragma once
#include "types.h"

namespace grlib {

class CGLibTexSwizzle;
class CGLibTextureBuffer;

class CGLibTexture {
public:
  static void get1PixelTextureInfo(f32 *info, CGLibTextureBuffer &texture);
  static bool createTextureImagePtrs(CGLibTextureBuffer &texture, const void *data, u32 size, bool, const CGLibTexSwizzle *swizzle, bool);
  static bool createMixTextureImagePtrs(CGLibTextureBuffer &texture, const void *data, u32 size, u32 mixSize, bool, const CGLibTexSwizzle *swizzle,
                                        bool);
  static bool changeTextureImagePtrs(CGLibTextureBuffer &texture, const void *data, u32 size);
  static bool changeMixTextureImagePtrs(CGLibTextureBuffer &texture, const void *data, u32 size, u32 mixSize);
};

} // namespace grlib
