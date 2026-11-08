#pragma once
#include "mm/mm_std_base.h"
#include "mm_mtl/type_traits.h"
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
      return first;
    }
  }
  return last;
}

template <typename InputIterator, typename Predicate> InputIterator find_if(InputIterator first, InputIterator last, Predicate predicate) {
  for (; first != last; ++first) {
    if (predicate(*first)) {
      break;
    }
  }
  return first;
}

template <typename T> void fill_n(T *first, size_t n, const T &value) {
  T *last = first + n;
  // Unrolled by hand in the original (Duff's device: the game switches on n & 7 into a loop of eight stores).
  switch (n & 7) {
  case 0:
    while (first != last) {
      *first++ = value;
    case 7:
      *first++ = value;
    case 6:
      *first++ = value;
    case 5:
      *first++ = value;
    case 4:
      *first++ = value;
    case 3:
      *first++ = value;
    case 2:
      *first++ = value;
    case 1:
      *first++ = value;
    }
  }
}

// __LINE__ must be 224 as in the original header: it is the line argument of the assert.
#line 223
template <typename T> T *copy_n(const T *first, size_t n, T *result) {
  MM_ASSERT((first + n <= result) || result < first);
  __builtin_memcpy(result, first, n * sizeof(T));
  return result + n;
}

// __LINE__ must be 264 as in the original header: it is the line argument of the assert.
#line 262
template <typename T> T *copy(const T *first, size_t n, T *result) {
  MM_ASSERT(result >= first + n || result < first);
  __builtin_memcpy(result, first, n * sizeof(T));
  return result + n;
}

namespace mtl_detail {

template <typename T> void copy_n(const T *first, size_t n, T *result, int_to_type<0>) {
  const T *last = first + n;
  // Unrolled by hand in the original (Duff's device: the game switches on n & 3 into a loop of four element copies).
  switch (n & 3) {
  case 0:
    while (first != last) {
      *result++ = *first++;
    case 3:
      *result++ = *first++;
    case 2:
      *result++ = *first++;
    case 1:
      *result++ = *first++;
    }
  }
}

template <typename T> void copy_n(const T *first, size_t n, T *result, int_to_type<1>) { copy(first, n, result); }

} // namespace mtl_detail

// __LINE__ must be 393 as in the original header: it is the line argument of the assert.
#line 392
template <typename T> void move(const T *from, size_t n, T *result) {
  MM_ASSERT(from != result || n == 0);
  if (from < result && result < from + n) {
    if (__has_trivial_assign(T)) {
      __builtin_memmove(result, from, n * sizeof(T));
    } else {
      for (int i = n; i > 0; i--) {
        result[i - 1] = from[i - 1];
      }
    }
  } else {
    mtl_detail::copy_n(from, n, result, int_to_type<__has_trivial_assign(T)>());
  }
}

} // namespace mtl
} // namespace mm
