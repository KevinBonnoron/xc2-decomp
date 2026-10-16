#include "mm_mtl/reserved_bitflag.h"

#include "mm/mm_std_base.h"
#include "mm_mtl/allocator.h"

namespace mm {
namespace mtl {

// The assert lines of the game: their constants change the register allocation.
#line 15
void ReservedBitflag::setLocal(u32 index, bool value) {
  MM_ASSERT(m_element != 0);
  MM_ASSERT(index < m_size);
  u32 word = index >> 5;
  u64 position = index;
  u32 mask = 1UL << (position & 31);
  if (value) {
    m_element[word] |= mask;
  } else {
    m_element[word] &= ~mask;
  }
}

// The assert lines of the game: their constants change the register allocation.
#line 33
bool ReservedBitflag::getLocal(u32 index) const {
  MM_ASSERT(m_element != 0);
  u32 word = index >> 5;
  u64 position = index;
  u32 mask = 1UL << (position & 31);
  return (m_element[word] & mask) != 0;
}

// The assert lines of the game: their constants change the register allocation.
#line 47
void ReservedBitflag::flipLocal(u32 index) {
  MM_ASSERT(m_element != 0);
  u32 word = index >> 5;
  u64 position = index;
  u32 mask = 1UL << (position & 31);
  m_element[word] ^= mask;
}

void ReservedBitflag::clrLocal(u32 index) {
  u32 word = index >> 5;
  u64 position = index;
  u32 mask = 1UL << (position & 31);
  m_element[word] &= ~mask;
}

void ReservedBitflag::clrLocal() {
  if (m_element != nullptr) {
    __builtin_memset(m_element, 0, m_elementCount * sizeof(u32));
  }
}

ReservedBitflag::ReservedBitflag() : m_element(nullptr), m_size(0), m_elementCount(0), m_allocator(nullptr) {}

ReservedBitflag::~ReservedBitflag() { destroy(); }

void ReservedBitflag::destroy() {
  if (m_element != nullptr) {
    MM_ASSERT(m_allocator != 0);
    m_allocator->deallocate(m_element);
    m_element = nullptr;
    m_size = 0;
    m_elementCount = 0;
    m_allocator = nullptr;
  }
}

void ReservedBitflag::initialize(IAllocator *allocator, u32 size) {
  MM_ASSERT(size != 0);
  MM_ASSERT(m_element == 0);
  MM_ASSERT(allocator != 0);
  u32 elementCount = (size + 31UL) >> 5;

  m_element = static_cast<u32 *>(allocator->allocate(elementCount * sizeof(u32), 4));

  MM_ASSERT(m_element != 0);
  m_allocator = allocator;
  m_size = size;
  m_elementCount = elementCount;
  clrLocal();
}

bool ReservedBitflag::get(u32 start, u32 last) const {
  MM_ASSERT(start <= last);
  for (u32 index = start; index < last; index++) {
    if (getLocal(index)) {
      return true;
    }
  }
  return false;
}

void ReservedBitflag::set(u32 start, u32 last, bool value) {
  MM_ASSERT(start <= last);
  for (u32 index = start; index < last; index++) {
    setLocal(index, value);
  }
}

void ReservedBitflag::flip(u32 start, u32 last) {
  MM_ASSERT(start <= last);
  for (u32 index = start; index < last; index++) {
    flipLocal(index);
  }
}

void ReservedBitflag::clear(u32 start, u32 last) {
  MM_ASSERT(start <= last);
  for (u32 index = start; index < last; index++) {
    clrLocal(index);
  }
}

bool ReservedBitflag::test(u32 start, u32 last) const { return get(start, last); }

} // namespace mtl
} // namespace mm
