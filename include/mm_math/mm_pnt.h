#pragma once

namespace mm {

template <typename T> struct Pnt {
  Pnt() {}
  Pnt(T x, T y) : x(x), y(y) {}
  Pnt(const Pnt &other) : x(other.x), y(other.y) {}

  static const Pnt zero;

  T x;
  T y;
};

} // namespace mm
