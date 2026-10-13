#pragma once
#include "types.h"

namespace gf {

class GfGameFlag {
public:
  static u32 getLocal(u32 size, int index);
  static void setLocal(u32 size, int index, u32 value);
};

} // namespace gf
