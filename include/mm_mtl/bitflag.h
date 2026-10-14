#pragma once
#include "mm/mm_std_base.h"
#include <stddef.h>

namespace mm {
namespace mtl {

template <unsigned int Size> class BitFlag {
public:
  void set(unsigned int index) {
    MM_ASSERT(index < Size);
    mBits[wordIndex(index)] |= bit(index);
  }

  bool test(unsigned int index) const {
    MM_ASSERT(index < Size);
    return (bit(index) & mBits[wordIndex(index)]) != 0;
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
