#pragma once
#include "types.h"

namespace ml {

class DrMdlMan {
public:
  static void getTextureStreamInfo(u32 &size, u32 &count, const void *data, bool isMiddle);
};

} // namespace ml
