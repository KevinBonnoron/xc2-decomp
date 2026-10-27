#include "ptlib/math/particle_keyframe_ip.h"

#include <string.h>

namespace ptlib {
namespace math {

namespace {

// Inferred role: next value in [-1, 1) of the random sequence of a key; original name unknown.
inline f32 unknown001(u32 &seed) {
  seed = seed * 0x41c64e6d + 0x3039;
  u32 bits = seed & 0x7fffff | 0x40000000;
  f32 value;
  memcpy(&value, &bits, sizeof(value));
  return value - 3.0f;
}

// Inferred role: value of a key with the random range applied; original name unknown.
inline f32 unknown002(const f32 *key, u32 &seed) { return key[0] + key[1] * unknown001(seed); }

} // namespace

f32 KeyFrameIP::get_ip1(int index) {
  f32 start = unknown002(unknown00 + index, unknown14);
  f32 end = unknown002(unknown08 + index, unknown18);
  return unknown10 * end + (1.0f - unknown10) * start;
}

void KeyFrameIP::setup_keyrand(EPkey *epkey, int count, u32 &rand) {
  u16 startId = static_cast<int>(unknown00[-1]);
  u16 endId = static_cast<int>(unknown08[-1]);
  if (epkey->unknown00 != startId) {
    u16 previousEndId = epkey->unknown02;
    epkey->unknown00 = startId;
    if (previousEndId == startId) {
      epkey->unknown04 = epkey->unknown08;
    } else {
      rand = rand * 0x41c64e6d + 0x3039;
      epkey->unknown04 = rand;
      for (int i = 1; i < count; i++) {
        rand = rand * 0x41c64e6d + 0x3039;
      }
    }
  }
  if (epkey->unknown02 != endId) {
    epkey->unknown02 = endId;
    rand = rand * 0x41c64e6d + 0x3039;
    epkey->unknown08 = rand;
    for (int i = 1; i < count; i++) {
      rand = rand * 0x41c64e6d + 0x3039;
    }
  }
  unknown14 = epkey->unknown04;
  unknown18 = epkey->unknown08;
}

f32 KeyFrameIP::keyrand_get_ip1(EPkey *epkey, u32 &rand) {
  setup_keyrand(epkey, 1, rand);
  return get_ip1(0);
}

} // namespace math
} // namespace ptlib
