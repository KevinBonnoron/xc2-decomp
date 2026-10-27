#pragma once
#include <iterator>
#include <type_traits>

#include "mm/mm_std_base.h"
#include "types.h"

namespace anm {

template <typename T> class ArrayIterartor {
public:
  typedef std::random_access_iterator_tag iterator_category;
  typedef typename std::remove_const<T>::type value_type;
  typedef s64 difference_type;
  typedef T *pointer;
  typedef T &reference;

  explicit ArrayIterartor(T *pData) : m_pData(pData) {}

  T *operator->() const { return m_pData; }

  // __LINE__ must be 69 as in the original header: it is the line argument of the assert.
#line 67
  ArrayIterartor &operator++() {
    MM_ASSERT(m_pData);
    ++m_pData;
    return *this;
  }

  bool operator!=(const ArrayIterartor &rhs) const { return m_pData != rhs.m_pData; }

  T *m_pData;
};

} // namespace anm
