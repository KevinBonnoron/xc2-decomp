#pragma once
#include "types.h"

namespace mm {

// 16 bytes wide and 16 byte aligned in the game (the Vec2::zero, unit, unitX and unitY symbols have size 0x10 and
// are 16 byte aligned with a zero second half, FixedQueue<Vec2, 2> elements are 16 bytes apart). A copy moves only
// the 8 bytes of x and y (ldr x/str x), which a class with user constructors does: its implicit copy skips the tail padding.
struct alignas(16) Vec2 {
  static const Vec2 zero; // Name from the game symbol _ZN2mm4Vec24zeroE; also in torna and xc1de.

  Vec2() {}
  Vec2(f32 x, f32 y) : x(x), y(y) {}
  Vec2(const Vec2 &vector) {
    x = vector.x;
    y = vector.y;
  }

  f32 x;
  f32 y;
};

static_assert(alignof(Vec2) == 16, "");
static_assert(sizeof(Vec2) == 0x10, "");

} // namespace mm
