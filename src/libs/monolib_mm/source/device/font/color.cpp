#include "font/color.h"

#include "types.h"

// Inferred helper: clamps a sum or product of two components to 255; original name unknown.
static u8 unknown001(u32 value) {
  if (value > 255) {
    return 255;
  }
  return value;
}

// Inferred helper: clamps a difference of two components to 0; original name unknown.
static u8 unknown002(int value) {
  if (value < 0) {
    return 0;
  }
  return value;
}

// Inferred helper: product of two components saturated to 255 (an unsigned multiply with overflow check on bytes);
// original name unknown.
static u8 unknown003(u8 left, u8 right) {
  u8 product;
  if (__builtin_mul_overflow(left, right, &product)) {
    product = 255;
  }
  return product;
}

Color::Color() {
  unknown00 = 255;
  unknown01 = 255;
  unknown02 = 255;
  unknown03 = 255;
}

Color::Color(const Color &color) : unknown00(color.unknown00), unknown01(color.unknown01), unknown02(color.unknown02), unknown03(color.unknown03) {}

Color::Color(u32 color) {
  unknown00 = color >> 24;
  unknown01 = color >> 16;
  unknown02 = color >> 8;
  unknown03 = color;
}

Color::Color(u8 first, u8 second, u8 third, u8 fourth) {
  unknown00 = first;
  unknown01 = second;
  unknown02 = third;
  unknown03 = fourth;
}

Color::~Color() {}

u32 Color::to_u32() const { return unknown00 << 24 | unknown01 << 16 | unknown02 << 8 | unknown03; }

void Color::set(u8 first, u8 second, u8 third, u8 fourth) {
  unknown00 = first;
  unknown01 = second;
  unknown02 = third;
  unknown03 = fourth;
}

Color &Color::operator=(u32 color) {
  unknown00 = color >> 24;
  unknown01 = color >> 16;
  unknown02 = color >> 8;
  unknown03 = color;
  return *this;
}

Color &Color::operator=(const Color &color) = default;

Color::operator u32() const { return to_u32(); }

Color Color::operator+(u32 color) const { return *this + Color(color); }

Color &Color::operator+=(u32 color) { return *this += Color(color); }

Color Color::operator+(const Color &color) const {
  Color result(*this);
  result += color;
  return result;
}

Color &Color::operator+=(const Color &color) {
  unknown00 = unknown001(unknown00 + color.unknown00);
  unknown01 = unknown001(unknown01 + color.unknown01);
  unknown02 = unknown001(unknown02 + color.unknown02);
  unknown03 = unknown001(unknown03 + color.unknown03);
  return *this;
}

Color Color::operator-(u32 color) const { return *this - Color(color); }

Color &Color::operator-=(u32 color) { return *this -= Color(color); }

Color Color::operator-(const Color &color) const {
  Color result(*this);
  result -= color;
  return result;
}

Color &Color::operator-=(const Color &color) {
  unknown00 = unknown002(unknown00 - color.unknown00);
  unknown01 = unknown002(unknown01 - color.unknown01);
  unknown02 = unknown002(unknown02 - color.unknown02);
  unknown03 = unknown002(unknown03 - color.unknown03);
  return *this;
}

Color &Color::operator*=(u32 color) {
  unknown00 = unknown001(unknown00 * (color >> 24));
  unknown01 = unknown001(unknown01 * (color >> 16 & 0xff));
  unknown02 = unknown001(unknown02 * (color >> 8 & 0xff));
  unknown03 = unknown001(unknown03 * (color & 0xff));
  return *this;
}

Color Color::operator*(const Color &color) const {
  Color result(*this);
  result *= color;
  return result;
}

Color &Color::operator*=(const Color &color) {
  unknown00 = unknown003(unknown00, color.unknown00);
  unknown01 = unknown003(unknown01, color.unknown01);
  unknown02 = unknown003(unknown02, color.unknown02);
  unknown03 = unknown003(unknown03, color.unknown03);
  return *this;
}

Color Color::operator/(u32 color) const {
  Color result(*this);
  result /= color;
  return result;
}

Color &Color::operator/=(u32 color) {
  unknown00 = unknown00 / (color >> 24);
  unknown01 = unknown01 / (color >> 16 & 0xff);
  unknown02 = unknown02 / (color >> 8 & 0xff);
  unknown03 = unknown03 / (color & 0xff);
  return *this;
}

Color Color::operator/(const Color &color) const {
  Color result(*this);
  result /= color;
  return result;
}

Color &Color::operator/=(const Color &color) {
  unknown00 = unknown00 / color.unknown00;
  unknown01 = unknown01 / color.unknown01;
  unknown02 = unknown02 / color.unknown02;
  unknown03 = unknown03 / color.unknown03;
  return *this;
}

Color Color::operator++() {
  unknown00++;
  unknown01++;
  unknown02++;
  unknown03++;
  return *this;
}

Color Color::operator++(int) {
  Color result(*this);
  unknown00++;
  unknown01++;
  unknown02++;
  unknown03++;
  return result;
}

Color Color::operator--() {
  unknown00--;
  unknown01--;
  unknown02--;
  unknown03--;
  return *this;
}

Color Color::operator--(int) {
  Color result(*this);
  unknown00--;
  unknown01--;
  unknown02--;
  unknown03--;
  return result;
}
