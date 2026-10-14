#pragma once
#include "mm/mm_std_base.h"
#include <stddef.h>

namespace mm {
namespace mtl {

template <unsigned int Size> class BitFlag {
public:
  void set(unsigned int index) {
    MM_ASSERT(index < Size);
    mBits |= static_cast<unsigned int>(1UL << index);
  }

  bool test(unsigned int index) const {
    MM_ASSERT(index < Size);
    return (static_cast<unsigned int>(1UL << index) & mBits) != 0;
  }

private:
  unsigned int mBits;
};

} // namespace mtl
} // namespace mm
