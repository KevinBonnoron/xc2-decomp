#pragma once
#include "types.h"

namespace gf {

struct GfSetupParam;

class GfGameFlag {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
  static void clear();

  static u32 getLocal(u32 size, int index);
  static void setLocal(u32 size, int index, u32 value);
};

} // namespace gf
