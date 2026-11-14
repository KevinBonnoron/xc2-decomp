#pragma once
#include <stddef.h>

#include "types.h"

// Layout evidence: Color::Color(unsigned int) 0x710078df18 and Color::to_u32 0x710078df50 pack the four bytes
// big endian (byte 0 is the most significant byte of the packed value).
class Color {
public:
  Color();
  Color(const Color &color);
  Color(u32 color);
  Color(u8 first, u8 second, u8 third, u8 fourth);
  ~Color();
  u32 to_u32() const;
  void set(u8 first, u8 second, u8 third, u8 fourth);
  Color &operator=(u32 color);
  Color &operator=(const Color &color);
  operator u32() const;
  Color operator+(u32 color) const;
  Color &operator+=(u32 color);
  Color operator+(const Color &color) const;
  Color &operator+=(const Color &color);
  Color operator-(u32 color) const;
  Color &operator-=(u32 color);
  Color operator-(const Color &color) const;
  Color &operator-=(const Color &color);
  Color operator*(u32 color) const;
  Color &operator*=(u32 color);
  Color operator*(const Color &color) const;
  Color &operator*=(const Color &color);
  Color operator/(u32 color) const;
  Color &operator/=(u32 color);
  Color operator/(const Color &color) const;
  Color &operator/=(const Color &color);
  Color operator++();
  Color operator++(int);
  Color operator--();
  Color operator--(int);

private:
  u8 unknown00; // Inferred role: first component, the most significant byte of the packed value; original member name unknown.
  u8 unknown01; // Inferred role: second component; original member name unknown.
  u8 unknown02; // Inferred role: third component; original member name unknown.
  u8 unknown03; // Inferred role: fourth component, the least significant byte of the packed value; original member name unknown.

  friend struct ColorLayout;
};

struct ColorLayout {
  static_assert(offsetof(Color, unknown00) == 0x00, "");
  static_assert(offsetof(Color, unknown03) == 0x03, "");
  static_assert(sizeof(Color) == 0x4, "");
};
