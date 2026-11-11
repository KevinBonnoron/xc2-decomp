#pragma once
#include <new>
#include <stddef.h>

#include "mm/mm_std_base.h"
#include "mm_mtl/bitflag.h"
#include "mm_mtl/construct.h"
#include "types.h"

namespace mm {
namespace mtl {

template <typename T, size_t N> class FixedObjectAllocator {
public:
  FixedObjectAllocator() : m_allocated(0), m_capacity(N) {}

  ~FixedObjectAllocator() {
    for (u32 i = 0; i < m_capacity; i++) {
      if (unknown001.test(i)) {
        unknown001.unknown004(i);
      }
    }
    m_allocated = 0;
  }

  // The assert lines of the game: their constants change the instruction encoding.
#line 82
  bool valid_pointer(const T *p) const { return reinterpret_cast<const u8 *>(p) <= unknown00 + sizeof(unknown00) && unknown00 <= reinterpret_cast<const u8 *>(p); }

  // Inferred role: slot index of an object; original name unknown.
  u32 unknown003(const T *p) const {
    MM_ASSERT(valid_pointer(p));
    u32 offset = reinterpret_cast<const u8 *>(p) - unknown00;
    return offset / static_cast<u32>(sizeof(T));
  }

#line 117
  T *allocate() {
    MM_ASSERT(m_allocated <= m_capacity);
    if (m_allocated != N) {
      for (u32 word = 0; word < (N + 31) / 32; word++) {
        if (unknown001.unknown001(word) != 0xffffffff) {
          u32 last = word * 32 + 32;
          if (last > m_capacity) {
            last = m_capacity;
          }
          for (u32 i = word * 32; i < last; i++) {
            if (!unknown001.test(i)) {
              T *object = unknown002() + i;
              if (object != nullptr) {
                new (object) T;
                unknown001.set(i);
                m_allocated++;
#line 193
                MM_ASSERT(m_allocated <= m_capacity);
                return object;
              }
            }
          }
        }
      }
    }
    return nullptr;
  }

#line 209
  void deallocate(T *p) {
    if (p != nullptr) {
      MM_ASSERT(m_allocated > 0);
      u32 index = unknown003(p);
      destruct(p);
      unknown001.set(index, false);
      m_allocated--;
    }
  }

  // Inferred role: first slot of the storage; original name unknown.
  T *unknown002() { return reinterpret_cast<T *>(unknown00); }
  const T *unknown002() const { return reinterpret_cast<const T *>(unknown00); }

  alignas(T) u8 unknown00[sizeof(T) * N]; // Inferred role: object storage; original member name unknown.
  unknown027<N> unknown001;               // Inferred role: used-slot bitflag; original member name unknown (offset depends on N).
  u32 m_allocated;
  u32 m_capacity;
};

// __builtin_offsetof: the comma of the template arguments would split the arguments of the offsetof macro.
static_assert(__builtin_offsetof(FixedObjectAllocator<u32, 16>, unknown001) == 0x40, "");
static_assert(__builtin_offsetof(FixedObjectAllocator<u32, 16>, m_allocated) == 0x44, "");
static_assert(__builtin_offsetof(FixedObjectAllocator<u32, 16>, m_capacity) == 0x48, "");
static_assert(sizeof(FixedObjectAllocator<u32, 16>) == 0x4c, "");

} // namespace mtl
} // namespace mm
