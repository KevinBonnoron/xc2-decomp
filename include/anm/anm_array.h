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

  // Written out, with += built on +, the std::__lower_bound instantiations of the game match; the implicit versions do not.
  ArrayIterartor &operator=(const ArrayIterartor &rhs) {
    m_pData = rhs.m_pData;
    return *this;
  }

  // __LINE__ must be 58 as in the original header: it is the line argument of the assert.
#line 57
  T &operator*() const {
    MM_ASSERT(m_pData);
    return *m_pData;
  }

  T *operator->() const { return m_pData; }

  // __LINE__ must be 69 as in the original header: it is the line argument of the assert.
#line 67
  ArrayIterartor &operator++() {
    MM_ASSERT(m_pData);
    ++m_pData;
    return *this;
  }

  // __LINE__ must be 83 as in the original header: it is the line argument of the assert.
#line 81
  ArrayIterartor operator-(difference_type n) const {
    ArrayIterartor result(*this);
    MM_ASSERT(m_pData);
    result.m_pData -= n;
    return result;
  }

  // __LINE__ must be 97 as in the original header: it is the line argument of the assert.
#line 95
  ArrayIterartor operator+(difference_type n) const {
    ArrayIterartor result(*this);
    MM_ASSERT(m_pData);
    result.m_pData += n;
    return result;
  }

  ArrayIterartor &operator+=(difference_type n) {
    *this = *this + n;
    return *this;
  }

  // __LINE__ must be 123 and 124 as in the original header: they are the line arguments of the asserts.
#line 122
  difference_type operator-(const ArrayIterartor &rhs) const {
    MM_ASSERT(m_pData);
    MM_ASSERT(rhs.m_pData);
    return m_pData - rhs.m_pData;
  }

  bool operator==(const ArrayIterartor &rhs) const { return m_pData == rhs.m_pData; }
  bool operator!=(const ArrayIterartor &rhs) const { return m_pData != rhs.m_pData; }

  T *m_pData;
};

} // namespace anm
