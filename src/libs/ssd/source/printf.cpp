#include <math.h>
#include <stdarg.h>

#include "ssd/ssd_debug.h"
#include "ssd/ssd_text.h"
#include "types.h"

namespace ssd {

// Inferred role: writes the decimal digits of a non-negative value, most significant first, padding the leading zeros with the pad
// character (the integer part of ToDoubleText with a pad, and the fraction); original name unknown.
template <typename T> static inline T *unknown001(T *buffer, s64 value, int width, int pad) {
  bool started = false;
  T *p = buffer;
  for (int i = width - 1; i != -1; i--) {
    s64 divisor = static_cast<s64>(pow(10.0, i));
    s64 digit = value / divisor;
    started |= i == 0 || digit != 0;
    value -= digit * divisor;
    *p++ = started ? static_cast<T>(digit + '0') : static_cast<T>(pad);
  }
  return p;
}

// Writes a double as text: a sign, the integer part with `width` digits (20 when width is 0; padded with the pad character, ' ' by
// default, or cut to its significant digits when pad is 0) and, when precision is not 0, '.' and the fraction scaled by
// pow(10, precision) with '0' padding. The padded digit loop is a function of its own (unknown001, used for the integer part and the
// fraction); the sign and pad handling stay in this function: with them in a further inline helper around the loops the exit pointer
// of the padded loop is computed after the loop (`add x8, x20, w24, uxtw` for the game's `add x8, x20, x24`, 4 lines in each instance).
// The terminating 0 is stored after the integer part and again after the fraction (the stores at 0x71009a41d4, 0x71009a4288 and
// 0x71009a428c of the char instance; the char16_t instance 0x71009a43f8 has the same).
template <typename T> T *ToDoubleText(T *buffer, double value, int width, int precision, int pad) {
  if (value < 0.0) {
    value = -value;
    *buffer++ = '-';
  }
  s64 integer = static_cast<s64>(value);
  pad = pad == 0 && width != 0 ? ' ' : pad;
  int digits = width == 0 ? 20 : width;
  pad = width == 0 ? 0 : pad;
  width = digits;
  s64 magnitude = integer;
  if (magnitude < 0) {
    *buffer++ = '-';
    magnitude = -magnitude;
  }
  if (pad != 0) {
    buffer = unknown001(buffer, magnitude, width, pad);
  } else {
    bool started = false;
    for (int i = width - 1; i != -1; i--) {
      s64 divisor = static_cast<s64>(pow(10.0, i));
      s64 digit = magnitude / divisor;
      started |= i == 0 || digit != 0;
      if (started) {
        *buffer++ = static_cast<T>(digit + '0');
      }
      magnitude -= digit * divisor;
    }
  }
  *buffer = 0;
  if (precision != 0) {
    double fraction = value - integer;
    s64 scaled = static_cast<s64>(fraction * pow(10.0, precision) + 0.5);
    *buffer++ = '.';
    if (scaled < 0) {
      *buffer++ = '-';
      scaled = -scaled;
    }
    buffer = unknown001(buffer, scaled, precision, '0');
    *buffer = 0;
  }
  *buffer = 0;
  return buffer;
}

// Inferred role: powers of ten from 1 to 10^9 (index 0 is never read), the divisors of the 32-bit decimal conversion; original name
// unknown. Game address 0x7100f86274.
static const u32 TEXT_UNKNOWN_1[] = {0, 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

// Inferred role: names of the size units B, K, M, G, T, P, E, Z, Y, one table per character type (no terminating 0); original name
// unknown. Game addresses 0x7100f862a0 (char) and 0x7100f862ea (char16_t).
template <typename T> static const T TEXT_UNKNOWN_2[] = {'B', 'K', 'M', 'G', 'T', 'P', 'E', 'Z', 'Y'};

// Inferred role: writes a size in bytes as text (the 'h' conversion of vsprintf_impl): an integer up to 1024, otherwise the size
// divided by 1024 until it is at most 1024, written by ToDoubleText with three decimals, cut to three significant digits, and
// the unit name. Original name unknown.
template <typename T> T *ToSizeText(T *buffer, long long size) {
  if (size <= 1024) {
    int value = size;
    if (value < 0) {
      *buffer++ = '-';
      value = -value;
    }
    bool started = false;
    // The walk over the table through a pointer makes the compiler read the table again after the store to the buffer.
    const u32 *divisor = &TEXT_UNKNOWN_1[10];
    for (int i = 10; i != 0; i--) {
      u32 digit = value / *divisor;
      started |= i == 1 || *divisor <= value;
      if (started) {
        *buffer++ = static_cast<T>(digit + '0');
      }
      value -= *divisor * digit;
      divisor--;
    }
    *buffer = 0;
    return buffer;
  }
  double value = size;
  int unit = 0;
  do {
    value /= 1024.0;
    unit++;
  } while (value > 1024.0);
  ToDoubleText(buffer, value, 0, 3, 0);
  // Keeps the first four characters of the text when the '.' is among them (it ends at the end of the text if that is shorter),
  // otherwise cuts the text at the '.'; a '.' that ends the kept text is dropped.
  int i = 0;
  T *p = buffer;
  for (; *p != 0; p++, i++) {
    if (*p == '.') {
      if (i <= 3) {
        int j = i + 1;
        T c;
        // `while (c)` with `j++ > 3` keeps the character read (`ldrh w9, [x19, #0x2]!`) before the position test, as in the game;
        // with `while (c != 0)` the compiler reads it after the test and folds the `i <= 3` guard into it (15 differing lines in the
        // char instance, 14 in the char16_t instance).
        do {
          c = *++p;
          if (j++ > 3) {
            break;
          }
        } while (c);
      }
      if (p[-1] == '.') {
        p--;
      }
      break;
    }
  }
  *p = TEXT_UNKNOWN_2<T>[unit];
  *++p = 0;
  return p;
}

void printf(const char *format, ...) {
  va_list args;
  va_start(args, format);
  char text[256];
  vsprintf(text, sizeof(text), format, args);
  va_end(args);
  char16_t wide[256];
  SjisToUTF16(text, wide, 256);
  Debug::log_.m_messageMethod(static_cast<LogMessage::Type>(0), wide);
}

int vsprintf(char *buffer, unsigned long size, const char *format, va_list args) { return vsprintf_impl<char>(buffer, size, format, args) - buffer; }

void printf(const char16_t *format, ...) {
  va_list args;
  va_start(args, format);
  char16_t text[256];
  vsprintf(text, 512, format, args);
  va_end(args);
  Debug::log_.m_messageMethod(static_cast<LogMessage::Type>(0), text);
}

unsigned long vsprintf(char16_t *buffer, unsigned long size, const char16_t *format, va_list args) {
  return (reinterpret_cast<unsigned long>(vsprintf_impl<char16_t>(buffer, size, format, args)) - reinterpret_cast<unsigned long>(buffer)) / sizeof(char16_t);
}

int sprintf(char *buffer, unsigned long size, const char *format, ...) {
  va_list args;
  va_start(args, format);
  char *end = vsprintf_impl<char>(buffer, size, format, args);
  va_end(args);
  return end - buffer;
}

unsigned long sprintf(char16_t *buffer, unsigned long size, const char16_t *format, ...) {
  va_list args;
  va_start(args, format);
  char16_t *end = vsprintf_impl<char16_t>(buffer, size, format, args);
  va_end(args);
  return (reinterpret_cast<unsigned long>(end) - reinterpret_cast<unsigned long>(buffer)) / sizeof(char16_t);
}

template char *ToDoubleText<char>(char *, double, int, int, int);
template char *ToSizeText<char>(char *, long long);
template char16_t *ToDoubleText<char16_t>(char16_t *, double, int, int, int);
template char16_t *ToSizeText<char16_t>(char16_t *, long long);

} // namespace ssd
