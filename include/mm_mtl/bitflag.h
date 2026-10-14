#pragma once
#include "mm/mm_std_base.h"
#include <stddef.h>

namespace mm {
namespace mtl {

template <unsigned int Size> class BitFlag {
public:
  void set(unsigned int index) {
    MM_ASSERT(index < Size);
    if (WORD_COUNT == 1) {
      mBits[0] |= static_cast<unsigned int>(1UL << index);
    } else {
      mBits[index / 32] |= static_cast<unsigned int>(1UL << (index % 32));
    }
  }

  bool test(unsigned int index) const {
    MM_ASSERT(index < Size);
    if (WORD_COUNT == 1) {
      return (static_cast<unsigned int>(1UL << index) & mBits[0]) != 0;
    }

    return (mBits[index / 32] & static_cast<unsigned int>(1UL << (index % 32))) != 0;
  }

private:
  static const unsigned int WORD_COUNT = (Size + 31) / 32;

  unsigned int mBits[WORD_COUNT];
};

} // namespace mtl
} // namespace mm
