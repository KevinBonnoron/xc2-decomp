#pragma once
#include "mm_mtl/algorithm.h"
#include <new>
#include <stddef.h>

namespace mm {
namespace mtl {

template <int N> struct int_to_type {
  enum { value = N };
};

namespace mtl_detail {

template <typename T> void construct_n(T *buffer, size_t count, int_to_type<0>) {
  for (size_t i = 0; i < count; i++) {
    new (&buffer[i]) T;
  }
}

template <typename T> void construct_n(T *, size_t, int_to_type<1>) {}

template <typename T> void copy_construct_n(const T *source, size_t count, T *destination, int_to_type<0>) {
  for (size_t i = 0; i < count; i++) {
    new (&destination[i]) T(source[i]);
  }
}

template <typename T> void copy_construct_n(const T *source, size_t count, T *destination, int_to_type<1>) { copy_n(source, count, destination); }

template <typename T> void destruct_n(T *buffer, size_t count, int_to_type<0>) {
  for (; count != 0; count--, buffer++) {
    buffer->~T();
  }
}

template <typename T> void destruct_n(T *, size_t, int_to_type<1>) {}

} // namespace mtl_detail

template <typename T> void construct_n(T *buffer, size_t count) {
  mtl_detail::construct_n(buffer, count, int_to_type<__has_trivial_constructor(T)>());
}

template <typename T> void copy_construct_n(const T *source, size_t count, T *destination) {
  mtl_detail::copy_construct_n(source, count, destination, int_to_type<__has_trivial_copy(T)>());
}

template <typename T> void destruct_n(T *buffer, size_t count) { mtl_detail::destruct_n(buffer, count, int_to_type<__has_trivial_destructor(T)>()); }

template <typename T> void destruct(T *object) {
  if (object != nullptr) {
    object->~T();
  }
}

} // namespace mtl
} // namespace mm
