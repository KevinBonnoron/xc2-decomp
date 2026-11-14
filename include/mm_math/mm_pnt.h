#pragma once

namespace mm {

template <typename T> struct Pnt {
  Pnt() {}
  Pnt(T x, T y) : x(x), y(y) {}
  Pnt(const Pnt &other) : x(other.x), y(other.y) {}

  static const Pnt zero; // Name from the game symbol _ZN2mm3PntIiE4zeroE; also in torna and xc1de.

  T x;
  T y;
};

} // namespace mm
