#pragma once
#include <stddef.h>

#include "mm/mm_std_base.h"
#include "types.h"

namespace wnd {

// Array of pointers with the assertions of the original wnd_array-inl.h. Only the const accessor is evidenced.
template <typename T> class Array {
public:
  // __LINE__ must be 231 and 232 as in the original header: they are the line arguments of the asserts.
#line 230
  const T &operator[](size_t index) const {
    MM_ASSERT(m_pElements);
    MM_ASSERT(index < m_size);
    return m_pElements[index];
  }

  u32 size() const { return m_size; }

  T *m_pElements;
  u32 m_size;
};

} // namespace wnd
