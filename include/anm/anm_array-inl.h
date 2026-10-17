#pragma once
#include "mm/mm_std_base.h"
#include "types.h"

namespace anm {

template <typename T> class Array {
public:
  u32 size() const { return m_size; }

  T &operator[](u32 index) {
    MM_ASSERT(m_pElements);
    MM_ASSERT(index < m_size);
    return m_pElements[index];
  }

  // __LINE__ must be 231 and 232 as in the original header: they are the line arguments of the asserts.
#line 230
  const T &operator[](u32 index) const {
    MM_ASSERT(m_pElements);
    MM_ASSERT(index < m_size);
    return m_pElements[index];
  }

  T *m_pElements;
  u32 m_size;
};

} // namespace anm
