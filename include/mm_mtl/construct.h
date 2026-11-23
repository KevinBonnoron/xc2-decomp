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

// One memcpy of the range for a type with a trivial copy and a trivial destructor, or declared plain old data through is_pod (arc::CArcData: its destructor is user-provided, yet the game copies
// Vector<CArcData>::extend, 0x710014e68c, with one memcpy; the element loop gives 89 instructions against 72). A type with a user destructor is copied element by element, a memcpy of one element per
// iteration unrolled by two (Vector<GmkNpcIdInfo>::expand 0x710068e2b4, Vector<GfFieldLod::BdatInfo>::expand 0x71002e7014): testing has_trivial_copy alone gives the memcpy of the range there (81
// instructions against 99, and 101 against 123).
template <typename T> void copy_construct_n(const T *source, size_t count, T *destination) {
  mtl_detail::copy_construct_n(source, count, destination, int_to_type<(__has_trivial_copy(T) && __has_trivial_destructor(T)) || is_pod<T>::unknown001>());
}

template <typename T> void destruct_n(T *buffer, size_t count) { mtl_detail::destruct_n(buffer, count, int_to_type<__has_trivial_destructor(T)>()); }

template <typename T> void destruct(T *object) {
  if (object != nullptr) {
    object->~T();
  }
}

} // namespace mtl
} // namespace mm
