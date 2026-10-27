#pragma once
#include "anm/anm_array.h"
#include "mm/mm_std_base.h"
#include "types.h"

namespace anm {

struct SerialiseArg;

template <typename T> class Array {
public:
  Array() : m_pElements(nullptr), m_size(0) {}
  explicit Array(const SerialiseArg &arg) {}

  u32 size() const { return m_size; }

  ArrayIterartor<T> begin() { return ArrayIterartor<T>(m_pElements); }
  ArrayIterartor<T> end() { return ArrayIterartor<T>(m_pElements + m_size); }
  ArrayIterartor<const T> begin() const { return ArrayIterartor<const T>(m_pElements); }
  ArrayIterartor<const T> end() const { return ArrayIterartor<const T>(m_pElements + m_size); }

  // __LINE__ must be 217 and 218 as in the original header: they are the line arguments of the asserts.
#line 216
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
