#pragma once

namespace mm {

template <typename T> struct Rect {
  Rect() {}
  Rect(T x, T y, T width, T height) : x(x), y(y), width(width), height(height) {}
  Rect(const Rect &other) : x(other.x), y(other.y), width(other.width), height(other.height) {}

  static const Rect &zero() {
    static Rect r(0, 0, 0, 0);
    return r;
  }

  T x;
  T y;
  T width;
  T height;
};

} // namespace mm
