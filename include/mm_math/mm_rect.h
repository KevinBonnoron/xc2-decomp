#pragma once

#include <stddef.h>

#include "mm_math/mm_pnt.h"

namespace mm {

template <typename T> struct Rect {
  Rect() {}
  Rect(T x, T y, T width, T height) : x(x), y(y), width(width), height(height) {}
  Rect(const Pnt<T> &pos, const Pnt<T> &size) : x(pos.x), y(pos.y), width(size.x), height(size.y) {}
  Rect(const Rect &other) : x(other.x), y(other.y), width(other.width), height(other.height) {}

  static const Rect &zero() {
    static Rect r(0, 0, 0, 0);
    return r;
  }

  // The game reads the position and the size as one mm::Pnt<T> each (a single 64-bit load for T = int, see
  // ml::WinView::updateViewPort, and fw::debug::DebugInputKeyboard::renderImpl passing the rect and its size to
  // fw::debug::drawLineSquare2D(Pnt, Pnt)). The Pnt views have no game symbol: unknown00 is the position and unknown08
  // the size for T = int; original member names unknown.
  union {
    struct {
      T x;
      T y;
    };
    Pnt<T> unknown00;
  };
  union {
    struct {
      T width;
      T height;
    };
    Pnt<T> unknown08;
  };
};

static_assert(offsetof(Rect<int>, unknown08) == 0x08, "");
static_assert(sizeof(Rect<int>) == 0x10, "");
static_assert(offsetof(Rect<short>, unknown08) == 0x04, "");
static_assert(sizeof(Rect<short>) == 0x08, "");

} // namespace mm
