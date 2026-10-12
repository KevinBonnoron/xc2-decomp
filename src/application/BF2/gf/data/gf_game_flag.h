#pragma once
#include "types.h"

namespace gf {
class GfGameFlag {
public:
  static uint getLocal(uint param_1, int param_2);
  static void setLocal(uint param_1, int param_2, uint value);
};
} // namespace gf
