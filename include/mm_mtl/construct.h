#pragma once
#include "mm_mtl/algorithm.h"
#include "mm_mtl/type_traits.h"
#include <new>
#include <stddef.h>

namespace mm {
namespace mtl {

namespace mtl_detail {

// The element loops are declared inline: the game inlines them into construct_n, copy_construct_n and destruct_n, which then stay out of line in their callers
// when the element type is heavy (the inline hint of the loops outweighs the threshold of the wrappers; for example 0x71002da30c destruct_n<GfGmkLocators>).

// Value-initialization: the game zero-fills (memset) elements of class types whose default constructor is not user-provided.
template <typename T> inline void construct_n(T *buffer, size_t count, int_to_type<0>) {
  for (size_t i = 0; i < count; i++) {
    new (&buffer[i]) T();
  }
}

template <typename T> void construct_n(T *, size_t, int_to_type<1>) {}

template <typename T> inline void copy_construct_n(const T *source, size_t count, T *destination, int_to_type<0>) {
  for (size_t i = 0; i < count; i++) {
    new (&destination[i]) T(source[i]);
  }
}

template <typename T> void copy_construct_n(const T *source, size_t count, T *destination, int_to_type<1>) { mtl::copy_n(source, count, destination); }

template <typename T> inline void destruct_n(T *buffer, size_t count, int_to_type<0>) {
  for (size_t i = 0; i < count; i++) {
    buffer[i].~T();
  }
}

template <typename T> void destruct_n(T *, size_t, int_to_type<1>) {}

} // namespace mtl_detail

template <typename T> void construct_n(T *buffer, size_t count) { mtl_detail::construct_n(buffer, count, int_to_type<__is_scalar(T)>()); }

template <typename T> void copy_construct_n(const T *source, size_t count, T *destination) { mtl_detail::copy_construct_n(source, count, destination, int_to_type<__has_trivial_copy(T)>()); }

template <typename T> void destruct_n(T *buffer, size_t count) { mtl_detail::destruct_n(buffer, count, int_to_type<__has_trivial_destructor(T)>()); }

template <typename T> void destruct(T *object) {
  if (object != nullptr) {
    object->~T();
  }
}

} // namespace mtl
} // namespace mm
