#include "grlib/cglib_util_pixel.h"

namespace grlib {

f32 CGLibUtilPixel::convF16toF32(u16 value) {
  u32 exponent = (value >> 10) & 0x1f;
  u32 bits;
  if (exponent == 0x1f) {
    bits = 0x7f800000;
  } else if (exponent == 0) {
    bits = 0;
  } else {
    bits = exponent * 0x800000 + 0x38000000;
  }
  bits |= ((value & 0x8000) << 16) | ((value & 0x3ff) << 13);
  return *reinterpret_cast<f32 *>(&bits);
}

} // namespace grlib
