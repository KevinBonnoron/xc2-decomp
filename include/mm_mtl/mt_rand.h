#pragma once
#include <stddef.h>

#include "types.h"

namespace mm {
namespace mtl {

class MTRand {
public:
  static const int STATE_UNKNOWN_624 = 624;               // Inferred role: size of the generator state; original name unknown.
  static const int SHIFT_UNKNOWN_397 = 397;               // Inferred role: state offset of the twist; original name unknown.
  static const u32 DEFAULT_SEED_UNKNOWN_5489 = 5489;      // Inferred role: seed used when none was set; original name unknown.
  static const u32 ZERO_SEED_UNKNOWN_19650218 = 19650218; // Inferred role: seed of the state initialization; original name unknown.

  explicit MTRand(u32 seed) { init(seed); }

  void init(u32 seed) {
    if (seed == 0) {
      seed = ZERO_SEED_UNKNOWN_19650218;
    }
    unknown9d0 = seed;
    unknown00[0] = seed;
    for (int i = 1; i < STATE_UNKNOWN_624; i++) {
      unknown00[i] = 1812433253 * (unknown00[i - 1] ^ (unknown00[i - 1] >> 30)) + i;
    }
    unknown9c0 = 1;
    unknown9c4 = 1;
  }

  void nextMt() {
    u32 *p = unknown00;
    if (unknown9c4 == 0) {
      init(DEFAULT_SEED_UNKNOWN_5489);
    }
    unknown9c0 = STATE_UNKNOWN_624;
    unknown9c8 = unknown00;
    for (int i = STATE_UNKNOWN_624 - SHIFT_UNKNOWN_397 + 1; --i; p++) {
      *p = p[SHIFT_UNKNOWN_397] ^ twist(p[0], p[1]);
    }
    for (int i = SHIFT_UNKNOWN_397; --i; p++) {
      *p = p[SHIFT_UNKNOWN_397 - STATE_UNKNOWN_624] ^ twist(p[0], p[1]);
    }
    *p = p[SHIFT_UNKNOWN_397 - STATE_UNKNOWN_624] ^ twist(p[0], unknown00[0]);
  }

  u32 generate() {
    if (--unknown9c0 <= 0) {
      nextMt();
    }
    u32 value = *unknown9c8++;
    value ^= value >> 11;
    value ^= (value << 7) & 0x9d2c5680;
    value ^= (value << 15) & 0xefc60000;
    value ^= value >> 18;
    return value;
  }

  static u32 twist(u32 upper, u32 lower) { return (((upper & 0x80000000) | (lower & 0x7fffffff)) >> 1) ^ ((lower & 1) != 0 ? 0x9908b0df : 0); }

  u32 unknown00[STATE_UNKNOWN_624]; // Inferred role: state; original member name unknown.
  int unknown9c0;                   // Inferred role: left; original member name unknown.
  int unknown9c4;                   // Inferred role: initialized; original member name unknown.
  u32 *unknown9c8;                  // Inferred role: next; original member name unknown.
  u32 unknown9d0;                   // Inferred role: seed; original member name unknown.
};

static_assert(offsetof(MTRand, unknown9c0) == 0x9c0, "");
static_assert(offsetof(MTRand, unknown9c8) == 0x9c8, "");
static_assert(offsetof(MTRand, unknown9d0) == 0x9d0, "");

} // namespace mtl
} // namespace mm
