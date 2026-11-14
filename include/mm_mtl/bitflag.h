#pragma once
#include "mm/mm_std_base.h"
#include "mm_mtl/algorithm.h"

namespace mm {
namespace mtl {

// Inferred role: fixed size bit flag set; original type name unknown.
template <unsigned int Size> class unknown027 {
public:
  unknown027() { clear(); }

  unknown027 &operator=(const unknown027 &other) {
    if (&other != this) {
      copy(other.mBits, unknown003, mBits);
    }
    return *this;
  }

  void clear() {
    for (unsigned int i = 0; i < unknown003; i++) {
      mBits[i] = 0;
    }
  }

  void set(unsigned int index) {
    MM_ASSERT(index < Size);
    mBits[wordIndex(index)] |= bit(index);
  }

  // The assert line of the game (169): its constant changes the instruction encoding.
#line 168
  void set(unsigned int index, bool value) {
    MM_ASSERT(index < Size);
    if (value) {
      mBits[wordIndex(index)] |= bit(index);
    } else {
      mBits[wordIndex(index)] &= ~bit(index);
    }
  }

  // Inferred role: clears one bit; original name unknown. The assert line of the game (181).
#line 180
  void unknown004(unsigned int index) {
    MM_ASSERT(index < Size);
    mBits[wordIndex(index)] &= ~bit(index);
  }

  // Inferred role: replaces the stored words with a raw value; original name unknown.
  void unknown002(unsigned int value) {
    clear();
    mBits[0] = value;
  }

  // Inferred role: writes one bit; original name unknown. The assert line of the game (89), seen in gf::GfGameFlag::setLocal (0x71002b8958) and
  // gf::GfObjUtil::setFlag, tells it apart from set(unsigned int, bool) (169).
#line 88
  void unknown006(unsigned int index, bool value) {
    MM_ASSERT(index < Size);
    unsigned int word = wordIndex(index);
    unsigned int mask = bit(index);
    if (value) {
      mBits[word] |= mask;
    } else {
      mBits[word] &= ~mask;
    }
  }

  // Inferred role: reads one bit; original name unknown. The assert line of the game (119), seen in gf::GfGameFlag::getLocal, gf::GfGameFlag::setLocal
  // (0x71002b8928) and gf::GfDataEvent::isWatchedEventFlag, tells it apart from test() (133).
#line 118
  bool unknown005(unsigned int index) const {
    MM_ASSERT(index < Size);
    return (mBits[wordIndex(index)] & bit(index)) != 0;
  }

  // The assert line of the game (133).
#line 132
  bool test(unsigned int index) const {
    MM_ASSERT(index < Size);
    if (unknown003 > 1) {
      return (mBits[wordIndex(index)] & bit(index)) != 0;
    }

    return (bit(index) & mBits[0]) != 0;
  }

  // Inferred role: one word of the bits; original name unknown.
  unsigned int unknown001(unsigned int word) const { return mBits[word]; }

private:
  static const unsigned int unknown003 = (Size + 31) / 32; // Inferred role: number of 32-bit words holding the bits; original name unknown.

  static unsigned int wordIndex(unsigned int index) { return unknown003 > 1 ? index >> 5 : 0; }

  static unsigned int bit(unsigned int index) {
    unsigned long position = index;
    return static_cast<unsigned int>(1UL << (unknown003 > 1 ? position & 31 : position));
  }

  unsigned int mBits[unknown003];
};

} // namespace mtl
} // namespace mm
