#include "battle/bit_array.h"

#include "gf/gf_allocator.h"

namespace btl {

BitArray::BitArray() : unknown08(nullptr) {}

BitArray::BitArray(int bitCount, int count, bool isSigned) : unknown08(nullptr) { Initialize(bitCount, count, isSigned); }

void BitArray::Initialize(int bitCount, int count, bool isSigned) {
  if (unknown08 != nullptr) {
    gf::getAllocator(gf::ALLOCATOR_DEFAULT)->deallocate(unknown08);
  }

  int size = (bitCount * count + 7) / 8;
  unknown08 = static_cast<u8 *>(gf::getAllocator(gf::ALLOCATOR_DEFAULT)->allocate(size, 4));
  __builtin_memset(unknown08, 0, size);
  this->unknown10 = count;
  this->unknown12 = bitCount;
  this->unknown13 = isSigned;
}

BitArray::~BitArray() {
  if (unknown08 != nullptr) {
    gf::getAllocator(gf::ALLOCATOR_DEFAULT)->deallocate(unknown08);
  }
}

void BitArray::SetData(int index, int value) {
  int size = unknown12;
  int bits;
  if (!unknown13) {
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
    unknown08[byte] = (unknown08[byte] & ~mask) | ((bits & (1 << (size - 1 - i))) == 0 ? 0 : mask);
    if (++i >= size) {
      break;
    }
    if (++bit >= 8) {
      bit = 0;
      byte++;
    }
  }
}

int BitArray::GetData(int index) const {
  int size = unknown12;
  int position = size * index;
  int byte = position >> 3;
  int bit = position & 7;
  int bits = 0;
  int i = 0;
  while (true) {
    if ((unknown08[byte] & (1 << bit)) != 0) {
      bits |= 1 << (size - 1 - i);
    }
    if (++i >= size) {
      break;
    }
    if (++bit >= 8) {
      bit = 0;
      byte++;
    }
  }

  int sign = 1 << (size - 1);
  int value = (bits & sign) != 0 ? -(bits & (sign - 1)) : bits;
  if (unknown13) {
    return value;
  }
  return bits;
}

} // namespace btl
