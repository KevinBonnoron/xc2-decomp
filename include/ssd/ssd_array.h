#pragma once
#include <stddef.h>

#include "ssd/ssd_allocator.h"

namespace ssd {

template <typename T> class Array {
public:
  Array() : unknown08(0), unknown0c(0), unknown10(nullptr) {}

  virtual ~Array();
  void SetArraySize(int size);
  void SetSize(int size);
  // Inferred role: release the element buffer and reset the counts; original name unknown.
  void unknown001() {
    if (unknown10 != nullptr) {
      SoundMemory::allocator_->unknown001(unknown10);
    }
    unknown08 = 0;
    unknown0c = 0;
    unknown10 = nullptr;
  }

  int unknown08; // Inferred role: element count; original member name unknown.
  int unknown0c; // Inferred role: capacity; original member name unknown.
  T *unknown10;  // Inferred role: elements; original member name unknown.
};

static_assert(offsetof(Array<int>, unknown10) == 0x10, "");

} // namespace ssd
