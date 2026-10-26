#pragma once
#include <stddef.h>

#include "mtl/mem_manager.h"
#include "types.h"

namespace ml {

template <typename T> class fixed_size_alloc {
public:
  virtual ~fixed_size_alloc() {
    if (unknown08 != nullptr) {
      mtl::MemManager::deallocate(unknown08, 0, false);
      unknown08 = nullptr;
    }
    unknown28 = 0;
    unknown18 = 0;
    unknown20 = 0;
    unknown10 = 0;
  }

  void *unknown08; // Inferred role: pool memory; original member name unknown.
  u64 unknown10;   // Inferred role: unknown; original member name unknown.
  u64 unknown18;   // Inferred role: unknown; original member name unknown.
  u64 unknown20;   // Inferred role: unknown; original member name unknown.
  u32 unknown28;   // Inferred role: unknown; original member name unknown.
};

static_assert(offsetof(fixed_size_alloc<int>, unknown08) == 0x08, "");
static_assert(offsetof(fixed_size_alloc<int>, unknown28) == 0x28, "");
static_assert(sizeof(fixed_size_alloc<int>) == 0x30, "");

template <typename T, int N> class fixed_size_alloc_inside {
public:
  virtual ~fixed_size_alloc_inside() {}
};

} // namespace ml
