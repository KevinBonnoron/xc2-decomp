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

void BitArray::SetData(int index, int value) {
  int size = bitCount;
  int bits;
  if (!isSigned) {
    bits = (value < 0 ? 0 : value) & ((1 << size) - 1);
  } else {
    int sign = 1 << (size - 1);
    bits = ((value < 0 ? -value : value) & (sign - 1)) | (value < 0 ? sign : 0);
  }

  int position = size * index;
  int byte = position >> 3;
  int bit = position & 7;
  int i = 0;
  while (true) {
    u8 mask = 1 << bit;
    data[byte] = (data[byte] & ~mask) | ((bits & (1 << (size - 1 - i))) == 0 ? 0 : mask);
    if (++i >= size) {
      break;
    }
    if (++bit >= 8) {
      bit = 0;
      byte++;
    }
  }
}

} // namespace btl
