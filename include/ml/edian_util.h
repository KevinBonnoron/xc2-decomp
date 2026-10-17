#pragma once
#include "types.h"

namespace ml {

class EdianUtil {
public:
  static int read(const int &value);
  static u32 read(const u32 &value);
  static u64 read(const u64 &value);
  static f32 read(const f32 &value);
  static s16 read(const s16 &value);
  static u16 read(const u16 &value);
  static void write(s16 &destination, s16 value);
  static void write(u16 &destination, u16 value);
};

} // namespace ml
