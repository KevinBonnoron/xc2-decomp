#pragma once
#include "mm/mm_std_base.h"
#include "mm_mtl/construct.h"
#include "mm_mtl/type_traits.h"
#include <new>
#include <stddef.h>

namespace mm {
namespace mtl {

template <size_t ALIGN> struct FixedVectorUnit;
template <> struct FixedVectorUnit<1> {
  typedef unsigned char type;
};
template <> struct FixedVectorUnit<2> {
  typedef unsigned short type;
};
template <> struct FixedVectorUnit<4> {
  typedef unsigned int type;
};
template <> struct FixedVectorUnit<8> {
  typedef unsigned long type;
};
template <> struct FixedVectorUnit<16> {
  struct alignas(16) type {
    unsigned char bytes[16];
  };
};

template <typename T, size_t N> class FixedVector {
  typedef typename FixedVectorUnit<alignof(T)>::type Unit;

public:
  FixedVector() : mSize(0) {}
  ~FixedVector() { clear(); }

  // __LINE__ must be 170, 181 and 227 as in the original header: they are the line arguments of the asserts.
  T &operator[](size_t index) {
#line 170
    MM_ASSERT(index < size());
    return *at(index);
  }

  const T &operator[](size_t index) const {
#line 181
    MM_ASSERT(index < size());
    return *at(index);
  }

  T &front() { return *at(0); }
  const T &front() const { return *at(0); }
  T &back() { return *at(mSize - 1); }
  const T &back() const { return *at(mSize - 1); }

  size_t size() const { return mSize; }
  size_t capacity() const { return N; }
  bool empty() const { return mSize == 0; }
  T *begin() { return reinterpret_cast<T *>(mBuffer); }
  const T *begin() const { return reinterpret_cast<const T *>(mBuffer); }
  T *end() { return begin() + size(); }
  const T *end() const { return begin() + size(); }

  void clear() {
    while (mSize != 0) {
      at(--mSize)->~T();
    }
  }

  void push_back(const T &value) {
#line 227
    MM_ASSERT(size() < capacity());
    construct(at(mSize), value);
    mSize++;
  }

  bool validate_iterator(const T *it) const { return begin() <= it && it <= end(); }

  T *erase(T *it) {
    MM_ASSERT(validate_iterator(it));
    if (it == end()) {
      return it;
    }
    copy(it + 1, end(), it);
    --mSize;
    destroy(end());
    return it;
  }

  FixedVector &operator=(const FixedVector &other) {
    if (this != &other) {
      clear();
      assign(other.begin(), other.end());
    }
    return *this;
  }

  void assign(const T *first, const T *last) {
    MM_ASSERT(first <= last);
    clear();
    if (first == last) {
      return;
    }
    size_t newSize = last - first;
    MM_ASSERT(newSize <= N);
    copy_construct_n(first, newSize, begin());
    mSize = newSize;
  }

  T *at(size_t index) { return reinterpret_cast<T *>(&mBuffer[index * sizeof(T) / sizeof(Unit)]); }
  const T *at(size_t index) const { return reinterpret_cast<const T *>(&mBuffer[index * sizeof(T) / sizeof(Unit)]); }

private:
  static void copy(const T *first, const T *last, T *dest) {
    if (is_pod<T>::value) {
      size_t count = last - first;
      __builtin_memcpy(dest, first, count * sizeof(T));
    } else {
      for (; first != last; ++first, ++dest) {
        *dest = *first;
      }
    }
  }

  static void construct(T *it, const T &value) {
    if (it != nullptr) {
      new (static_cast<void *>(it)) T(value);
    }
  }

  static void destroy(T *it) {
    if (it != nullptr) {
      it->~T();
    }
  }

  Unit mBuffer[sizeof(T) * N / sizeof(Unit)];
  size_t mSize;
};

} // namespace mtl
} // namespace mm
