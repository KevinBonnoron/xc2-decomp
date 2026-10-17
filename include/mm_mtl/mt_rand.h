#pragma once
#include <stddef.h>

#include "types.h"

namespace mm {
namespace mtl {

class MTRand {
public:
  static const int STATE_SIZE = 624;
  static const int SHIFT_SIZE = 397;
  static const u32 DEFAULT_SEED = 5489;
  static const u32 ZERO_SEED = 19650218;

  explicit MTRand(u32 seed) { init(seed); }

  void init(u32 seed) {
    if (seed == 0) {
      seed = ZERO_SEED;
    }
    m_seed = seed;
    m_state[0] = seed;
    for (int i = 1; i < STATE_SIZE; i++) {
      m_state[i] = 1812433253 * (m_state[i - 1] ^ (m_state[i - 1] >> 30)) + i;
    }
    m_left = 1;
    m_initialized = 1;
  }

  void nextMt() {
    u32 *p = m_state;
    if (m_initialized == 0) {
      init(DEFAULT_SEED);
    }
    m_left = STATE_SIZE;
    m_next = m_state;
    for (int i = STATE_SIZE - SHIFT_SIZE + 1; --i; p++) {
      *p = p[SHIFT_SIZE] ^ twist(p[0], p[1]);
    }
    for (int i = SHIFT_SIZE; --i; p++) {
      *p = p[SHIFT_SIZE - STATE_SIZE] ^ twist(p[0], p[1]);
    }
    *p = p[SHIFT_SIZE - STATE_SIZE] ^ twist(p[0], m_state[0]);
  }

  u32 generate() {
    if (--m_left <= 0) {
      nextMt();
    }
    u32 value = *m_next++;
    value ^= value >> 11;
    value ^= (value << 7) & 0x9d2c5680;
    value ^= (value << 15) & 0xefc60000;
    value ^= value >> 18;
    return value;
  }

  static u32 twist(u32 upper, u32 lower) { return (((upper & 0x80000000) | (lower & 0x7fffffff)) >> 1) ^ ((lower & 1) != 0 ? 0x9908b0df : 0); }

  u32 m_state[STATE_SIZE];
  int m_left;
  int m_initialized;
  u32 *m_next;
  u32 m_seed;
};

static_assert(offsetof(MTRand, m_left) == 0x9c0, "");
static_assert(offsetof(MTRand, m_next) == 0x9c8, "");
static_assert(offsetof(MTRand, m_seed) == 0x9d0, "");

} // namespace mtl
} // namespace mm
