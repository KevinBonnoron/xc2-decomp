#pragma once

namespace mm {

template <typename T> struct Pnt {
  Pnt() {}
  Pnt(T x, T y) : x(x), y(y) {}

  T x;
  T y;
};

} // namespace mm
