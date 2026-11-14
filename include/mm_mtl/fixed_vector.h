#pragma once
#include "mm/mm_std_base.h"
#include "mm_mtl/algorithm.h"
#include "mm_mtl/construct.h"
#include <new>
#include <stddef.h>

namespace mm {
namespace mtl {

template <size_t ALIGN> struct FixedVectorUnit;
template <> struct FixedVectorUnit<1> {
  typedef unsigned char type;
};
template <> struct FixedVectorUnit<2> {
  // A struct unit keeps the buffer address apart from the element addresses, as in the game (gf::GfUnpopBladeIds).
  struct type {
    unsigned short unknown00; // Inferred role: storage halfword; original member name unknown.
  };
};
template <> struct FixedVectorUnit<4> {
  // A struct unit makes the element pointers casts of the buffer address, so begin() and end() share their base and
  // the game's index compares come out (gf::GfMenuSequence::wait erasing from a FixedVector<int>).
  struct type {
    unsigned int unknown00; // Inferred role: storage word; original member name unknown.
  };
};
template <> struct FixedVectorUnit<8> {
  typedef unsigned long type;
};
template <> struct FixedVectorUnit<16> {
  // Two 8-byte words: a byte array lets the compiler fold element member addresses differently from the game.
  struct alignas(16) type {
    unsigned long unknown00[2]; // Inferred role: storage words; original member name unknown.
  };
};

template <typename T, size_t N> class FixedVector {
  typedef typename FixedVectorUnit<alignof(T)>::type Unit;
  typedef size_t size_type;

public:
  FixedVector() : m_size(0) {}
  FixedVector(const FixedVector &other) : m_size(0) { *this = other; }
  ~FixedVector() { clear(); }

  T &front() { return *at(0); }
  // __LINE__ must be 163 as in the original header: it is the line argument of the assert.
  const T &front() const {
#line 163
    MM_ASSERT(0 < m_size);
    return *at(0);
  }

  // __LINE__ must be 165, 166, 170, 181, 192, 203 and 227 as in the original header: they are the line arguments of the asserts.
  T &back() {
#line 165
    MM_ASSERT(0 < m_size);
    return unknown001(m_size - 1);
  }

  const T &back() const {
#line 166
    MM_ASSERT(0 < m_size);
    return unknown001(m_size - 1);
  }

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

  // Inferred role: element access checked against the size, as back() uses it; original name unknown.
  T &unknown001(size_t index) {
#line 192
    MM_ASSERT(index < size());
    return *at(index);
  }

  // Inferred role: element access checked against the size, as back() const uses it; original name unknown.
  const T &unknown001(size_t index) const {
#line 203
    MM_ASSERT(index < size());
    return *at(index);
  }

  size_t size() const { return m_size; }
  size_t capacity() const { return N; }
  bool empty() const { return m_size == 0; }
  T *begin() { return reinterpret_cast<T *>(mBuffer); }
  const T *begin() const { return reinterpret_cast<const T *>(mBuffer); }
  T *end() { return begin() + size(); }
  const T *end() const { return begin() + size(); }

  void clear() {
    while (m_size != 0) {
      at(--m_size)->~T();
    }
  }

  void push_back(const T &value) {
#line 227
    MM_ASSERT(size() < capacity());
    construct(at(m_size), value);
    m_size++;
  }

  void pop_back() {
#line 253
    MM_ASSERT(m_size > size_type(0U));
    if (m_size != 0) {
      --m_size;
      destroy(end());
    }
  }

  void resize(size_t size, const T &value) {
    long count = size - m_size;
    if (count < 0) {
      for (long i = -count; i > 0; i--) {
        pop_back();
      }
    } else if (count != 0) {
      for (long i = count; i > 0; i--) {
        push_back(value);
      }
    }
  }

  bool validate_iterator(const T *it) const { return begin() <= it && it <= end(); }

  // __LINE__ must be 307 and 311 as in the original header: they are the line arguments of the asserts.
  T *insert(T *it, const T &value) {
#line 307
    MM_ASSERT(validate_iterator(it));
    size_t prevSize = m_size;
    size_t index = it - begin();
#line 311
    MM_ASSERT(prevSize < N);
    T *position = end();
    if (position != nullptr) {
      construct_n(position, 1);
    }
    if (it != end()) {
      move(it, prevSize - index, it + 1);
    }
    *it = value;
    m_size++;
    return it;
  }

  T *erase(T *it) {
#line 345
    MM_ASSERT(validate_iterator(it));
    if (it == end()) {
      return it;
    }
    copy(it + 1, end(), it);
    --m_size;
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

  // __LINE__ must be 270 and 275 as in the original header: they are the line arguments of the asserts.
  void assign(const T *first, const T *last) {
#line 270
    MM_ASSERT(first <= last);
    clear();
    if (first == last) {
      return;
    }
    size_t newSize = last - first;
#line 275
    MM_ASSERT(newSize <= N);
    copy_construct_n(first, newSize, begin());
    m_size = newSize;
  }

  T *at(size_t index) { return reinterpret_cast<T *>(&mBuffer[index * sizeof(T) / sizeof(Unit)]); }
  const T *at(size_t index) const { return reinterpret_cast<const T *>(&mBuffer[index * sizeof(T) / sizeof(Unit)]); }

private:
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
  // Name from the assertion "m_size > size_type(0U)" of the original header (line 253).
  size_t m_size;
};

} // namespace mtl
} // namespace mm
