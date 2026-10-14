#pragma once
#include "types.h"

namespace gf {

struct GfSetupParam;

class GfLayerPause {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
  static void gevPause(u32 resumeBits, u32 pauseBits);
  static void destroyLayerPause();
  static bool isLayerPause(u32 layer);
};

} // namespace gf
