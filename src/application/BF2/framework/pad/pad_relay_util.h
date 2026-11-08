#pragma once
#include "types.h"

namespace fw {

class PadRelayUtil {
public:
  static bool getFwPadKey(u32 padIndex, const char *name, u32 arg2, u32 arg3, u32 *key);
};

} // namespace fw
