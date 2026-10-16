#pragma once

namespace mm {

template <typename T> struct Rect {
  Rect() {}
  Rect(const Rect &other) : x(other.x), y(other.y), width(other.width), height(other.height) {}

  T x;
  T y;
  T width;
  T height;
};

} // namespace mm
