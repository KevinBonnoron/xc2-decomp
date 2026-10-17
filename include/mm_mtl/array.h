#pragma once
#include <new>
#include <stddef.h>

#include "mm/mm_std_base.h"
#include "mm_mtl/allocator.h"

namespace mm {
namespace mtl {

template <typename T> class Array {
public:
  Array() : m_element(nullptr), m_size(0), m_allocator(nullptr) {}
  ~Array() { destroy(); }

  T *begin() const {
    MM_ASSERT(m_element);
    return m_element;
  }

  T *end() const {
    MM_ASSERT(m_element);
    return m_element + m_size;
  }

  // The assertion lines of the game change the register allocation of the loops writing an array.
#line 89
  T &operator[](size_t index) {
    MM_ASSERT(m_element);
    return m_element[index];
  }

  // The assertion line of the game changes the register allocation of the loops reading an array.
#line 101
  const T &operator[](size_t index) const {
    MM_ASSERT(m_element);
    return m_element[index];
  }

  size_t size() const { return m_size; }

  void fill(const T &value) {
    MM_ASSERT(m_element);
    for (size_t i = 0; i < m_size; i++) {
      m_element[i] = value;
    }
  }

  void setAllocator(IAllocator *allocator) {
    if (m_allocator != allocator) {
      destroy();
      m_allocator = allocator;
    }
  }

  void reserve(size_t size);

  void destroy() {
    if (m_element != nullptr) {
      m_allocator->deallocate(m_element);
      m_element = nullptr;
      m_size = 0;
      m_allocator = nullptr;
    }
  }

private:
  T *m_element;
  size_t m_size;
  IAllocator *m_allocator;
};

// __LINE__ must be 161 to 163 and 167 as in the original header: they are the line arguments of the asserts.
#line 160
template <typename T> void Array<T>::reserve(size_t size) {
  MM_ASSERT(size != 0);
  MM_ASSERT(m_element == 0);
  MM_ASSERT(m_allocator != 0);
  m_element = static_cast<T *>(m_allocator->allocate(size * sizeof(T), 8));
#line 167
  MM_ASSERT(m_element != 0);
  m_size = size;
  for (size_t i = 0; i < m_size; i++) {
    T *element = &m_element[i];
    if (element != nullptr) {
      new (element) T;
    }
  }
}

} // namespace mtl
} // namespace mm
