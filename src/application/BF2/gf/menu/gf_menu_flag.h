#pragma once
#include "types.h"

namespace gf {

class GfMenuFlag {
public:
  static void set1(int index, u32 value);
  static u32 get1(int index);
  static void set2(int index, u32 value);
  static u32 get2(int index);
  static void set4(int index, u32 value);
  static u32 get4(int index);
};

} // namespace gf
