#pragma once
#include "types.h"

namespace gf {

class GfMenuSoundManager {
public:
  static u32 playJingle(u32 id);
  bool isSpecInJingle(u32 id);
  bool isSpecOutJingle(u32 id);
};

} // namespace gf
