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

// Layout from gf::_gfdac::s_accbuf (.data: bitmap pointer at 0x4020 = s_accbuf + 0x4008, element pointer at 0x4028 = s_accbuf + 0x08,
// word count 4 at 0x4030 for 128 elements) and from the GfMenuReference constructor (512 elements of 0x20 bytes: memset of 0x4044 bytes
// at +0x08, word count 0x10).
template <typename T, int N> class fixed_size_alloc_inside {
public:
  fixed_size_alloc_inside() : unknown08(), unknown005() {
    unknown008 = N / 32;
    unknown007 = reinterpret_cast<T *>(unknown08);
    unknown006 = unknown005;
    unknown009 = 0;
  }

  virtual ~fixed_size_alloc_inside() {}

  // Inferred role: takes the first free element and marks it used, storing its index when asked; original name unknown.
  T *unknown003(u32 *index = nullptr) {
    if (unknown009 < N) {
      u32 *bits = unknown006;
      for (u32 word = 0; word < unknown008; word++, bits++) {
        if (*bits != 0xffffffff) {
          u32 bit = (*bits & 0xffff) == 0xffff ? 16 : 0;
          for (u32 mask = 1 << bit; bit < 32; bit++, mask <<= 1) {
            if ((*bits & mask) == 0) {
              unknown009++;
              *bits |= mask;
              if (index != nullptr) {
                *index = word * 32 + bit;
              }
              return unknown007 + (word * 32 + bit);
            }
          }
        }
      }
    }
    return nullptr;
  }

  // Inferred role: marks the element at address p free; original name unknown.
  void unknown004(void *p) { unknown011((static_cast<u8 *>(p) - reinterpret_cast<u8 *>(unknown007)) / sizeof(T)); }

  // Inferred role: marks the element at index free; original name unknown.
  void unknown011(u32 index) {
    u32 word = index / 32;
    u32 bit = 1 << (index % 32);
    if ((unknown006[word] & bit) != 0) {
      unknown006[word] &= ~bit;
      unknown009--;
    }
  }

  // Inferred role: tells whether the element at index is used; original name unknown.
  bool unknown010(u32 index) const {
    u32 word = index / 32;
    u32 bit = 1 << (index % 32);
    return (unknown006[word] & bit) != 0;
  }

  u8 unknown08[sizeof(T) * N]; // Inferred role: element storage, not aligned to T (GfGameSearchObj::GFSEARCH_INFO pool at 0x08); original member name unknown.
  u32 unknown005[N / 32 + 1];  // Inferred role: usage bitmap storage; original member name unknown (offset depends on N).
  u32 *unknown006;             // Inferred role: usage bitmap; original member name unknown (offset depends on N).
  T *unknown007;               // Inferred role: elements; original member name unknown (offset depends on N).
  u32 unknown008;              // Inferred role: usage bitmap word count; original member name unknown (offset depends on N).
  u32 unknown009;              // Inferred role: used element count; original member name unknown (offset depends on N).
};

} // namespace ml
