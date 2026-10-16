#include "battle/bit_array.h"

#include "gf/gf_allocator.h"

namespace btl {

BitArray::BitArray() : data(nullptr) {}

BitArray::BitArray(int bitCount, int count, bool isSigned) : data(nullptr) { Initialize(bitCount, count, isSigned); }

void BitArray::Initialize(int bitCount, int count, bool isSigned) {
  if (data != nullptr) {
    gf::getAllocator(gf::ALLOCATOR_DEFAULT)->deallocate(data);
  }

  int size = (bitCount * count + 7) / 8;
  data = static_cast<u8 *>(gf::getAllocator(gf::ALLOCATOR_DEFAULT)->allocate(size, 4));
  __builtin_memset(data, 0, size);
  this->count = count;
  this->bitCount = bitCount;
  this->isSigned = isSigned;
}

BitArray::~BitArray() {
  if (data != nullptr) {
    gf::getAllocator(gf::ALLOCATOR_DEFAULT)->deallocate(data);
  }
}

} // namespace btl
