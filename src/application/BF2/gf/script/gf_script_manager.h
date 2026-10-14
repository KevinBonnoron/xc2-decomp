#pragma once
#include "types.h"

namespace gf {

class GfScriptManager {
public:
  static bool isScriptLoadError(u32 slot);
  static bool isScriptActive(u32 slot);
};

} // namespace gf
