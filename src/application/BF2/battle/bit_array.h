#pragma once
#include "types.h"
#include <stddef.h>

namespace btl {

class BitArray {
public:
  BitArray();
  BitArray(int bitCount, int count, bool isSigned);
  void Initialize(int bitCount, int count, bool isSigned);
  virtual ~BitArray();
  void SetData(int index, int value);
  int GetData(int index) const;

  u8 *data;
  u16 count;
  u8 bitCount;
  bool isSigned;
};

static_assert(offsetof(BitArray, data) == 0x08, "");
static_assert(offsetof(BitArray, count) == 0x10, "");
static_assert(offsetof(BitArray, bitCount) == 0x12, "");
static_assert(offsetof(BitArray, isSigned) == 0x13, "");
static_assert(sizeof(BitArray) == 0x18, "");

} // namespace btl
