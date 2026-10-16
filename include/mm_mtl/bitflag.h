#pragma once
#include "mm/mm_std_base.h"
#include "mm_mtl/algorithm.h"

namespace mm {
namespace mtl {

template <unsigned int Size> class BitFlag {
public:
  BitFlag &operator=(const BitFlag &other) {
    if (&other != this) {
      copy_n(other.mBits, WORD_COUNT, mBits);
    }
    return *this;
  }

  void clear() {
    for (unsigned int i = 0; i < WORD_COUNT; i++) {
      mBits[i] = 0;
    }
  }

  void set(unsigned int index) {
    MM_ASSERT(index < Size);
    mBits[wordIndex(index)] |= bit(index);
  }

  void set(unsigned int index, bool value) {
    MM_ASSERT(index < Size);
    if (value) {
      mBits[wordIndex(index)] |= bit(index);
    } else {
      mBits[wordIndex(index)] &= ~bit(index);
    }
  }

  bool test(unsigned int index) const {
    MM_ASSERT(index < Size);
    if (WORD_COUNT > 1) {
      return (mBits[wordIndex(index)] & bit(index)) != 0;
    }

    return (bit(index) & mBits[0]) != 0;
  }

private:
  static const unsigned int WORD_COUNT = (Size + 31) / 32;

  static unsigned int wordIndex(unsigned int index) { return WORD_COUNT > 1 ? index >> 5 : 0; }

  static unsigned int bit(unsigned int index) {
    unsigned long position = index;
    return static_cast<unsigned int>(1UL << (WORD_COUNT > 1 ? position & 31 : position));
  }

  unsigned int mBits[WORD_COUNT];
};

} // namespace mtl
} // namespace mm
