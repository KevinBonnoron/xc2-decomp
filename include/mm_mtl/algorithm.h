#pragma once
#include "mm/mm_std_base.h"
#include <stddef.h>

namespace mm {
namespace mtl {

template <typename InputIterator, typename Function> Function for_each(InputIterator first, InputIterator last, Function function) {
  for (; first != last; ++first) {
    function(*first);
  }
  return function;
}

template <typename InputIterator, typename T> InputIterator find(InputIterator first, InputIterator last, const T &value) {
  for (; first != last; ++first) {
    if (*first == value) {
      break;
    }
  }
  return first;
}

template <typename InputIterator, typename Predicate> InputIterator find_if(InputIterator first, InputIterator last, Predicate predicate) {
  for (; first != last; ++first) {
    if (predicate(*first)) {
      break;
    }
  }
  return first;
}

// __LINE__ must be 224 as in the original header: it is the line argument of the assert.
#line 223
template <typename T> T *copy_n(const T *first, size_t n, T *result) {
  MM_ASSERT((first + n <= result) || result < first);
  __builtin_memcpy(result, first, n * sizeof(T));
  return result + n;
}

template <typename T> void move_n(T *first, size_t n, T *result) {
  if (__is_pod(T)) {
    __builtin_memcpy(result, first, n * sizeof(T));
  } else {
    for (size_t i = 0; i < n; i++) {
      result[i] = first[i];
    }
  }
}

} // namespace mtl
} // namespace mm
