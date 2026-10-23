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

  u8 *unknown08;  // Inferred role: bit data buffer; original member name unknown.
  u16 unknown10;  // Inferred role: count; original member name unknown.
  u8 unknown12;   // Inferred role: bit count; original member name unknown.
  bool unknown13; // Inferred role: signed flag; original member name unknown.
};

static_assert(offsetof(BitArray, unknown08) == 0x08, "");
static_assert(offsetof(BitArray, unknown10) == 0x10, "");
static_assert(offsetof(BitArray, unknown12) == 0x12, "");
static_assert(offsetof(BitArray, unknown13) == 0x13, "");
static_assert(sizeof(BitArray) == 0x18, "");

} // namespace btl
