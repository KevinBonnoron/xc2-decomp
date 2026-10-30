#pragma once
#include <stddef.h>
#include <string.h>

#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"
#include "types.h"

namespace ml {

template <typename T> class fixed_size_alloc {
public:
  fixed_size_alloc() : unknown08(nullptr), unknown10(nullptr), unknown18(nullptr), unknown20(0), unknown24(0) {}

  virtual ~fixed_size_alloc() { unknown002(); }

  // Inferred role: allocates the pool of count elements followed by its usage bitmap; original name unknown.
  void unknown001(mtl::ALLOC_HANDLE handle, u32 count) {
    unknown002();
    unknown28 = count;
    unknown20 = count / 32;
    unknown08 = mtl::MemManager::allocate(handle, count * sizeof(T) + count / 8, 4, false, "no name", 0);
    memset(unknown08, 0, count * sizeof(T) + count / 8);
    unknown24 = 0;
    unknown18 = static_cast<T *>(unknown08);
    unknown10 = reinterpret_cast<u32 *>(unknown18 + count);
  }

  // Inferred role: frees the pool; original name unknown.
  void unknown002() {
    if (unknown08 != nullptr) {
      mtl::MemManager::deallocate(unknown08, 0, false);
      unknown08 = nullptr;
    }
    unknown28 = 0;
    unknown18 = nullptr;
    unknown20 = 0;
    unknown24 = 0;
    unknown10 = nullptr;
  }

  void *unknown08; // Inferred role: pool memory; original member name unknown.
  u32 *unknown10;  // Inferred role: usage bitmap, after the elements; original member name unknown.
  T *unknown18;    // Inferred role: elements; original member name unknown.
  u32 unknown20;   // Inferred role: usage bitmap word count; original member name unknown.
  u32 unknown24;   // Inferred role: allocation state, reset with the pool; original member name unknown.
  u32 unknown28;   // Inferred role: element count; original member name unknown.
};

static_assert(offsetof(fixed_size_alloc<int>, unknown08) == 0x08, "");
static_assert(offsetof(fixed_size_alloc<int>, unknown20) == 0x20, "");
static_assert(offsetof(fixed_size_alloc<int>, unknown24) == 0x24, "");
static_assert(offsetof(fixed_size_alloc<int>, unknown28) == 0x28, "");
static_assert(sizeof(fixed_size_alloc<int>) == 0x30, "");

template <typename T, int N> class fixed_size_alloc_inside {
public:
  virtual ~fixed_size_alloc_inside() {}
};

} // namespace ml
