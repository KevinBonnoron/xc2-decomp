#pragma once
#include <stddef.h>

#include "mm/mm_std_base.h"
#include "mm_mtl/allocator.h"
#include "mm_mtl/construct.h"
#include "types.h"

namespace mm {
namespace mtl {

template <typename T> class Queue {
public:
  Queue(IAllocator *allocator, size_t capacity) : m_buffer(nullptr), m_size(0), m_front(0), m_capacity(0), m_alignment(8), m_allocator(allocator) {
    m_buffer = static_cast<T *>(m_allocator->allocate(capacity * sizeof(T), m_alignment));
    m_front = 0;
    m_capacity = capacity;
  }

  ~Queue() {
    clear();
    if (m_buffer != nullptr) {
      // __LINE__ must be 835 as in the original header: it is the line argument of the assert.
#line 835
      MM_ASSERT(m_allocator);
      m_allocator->deallocate(m_buffer);
    }
  }

  void push_back(const T &value);

  u32 size() const { return m_size; }

  T &front() { return at(m_front); }

  // __LINE__ must be 782 as in the original header: it is the line argument of the assert.
#line 781
  void pop_front() {
    MM_ASSERT(!empty());
    size_t index = m_front;
    m_front = (m_front + 1) % m_capacity;
    m_size--;
    destruct(&at(index));
  }

  bool empty() const { return m_size == 0; }

  void clear() {
    while (m_size != 0) {
      pop_back();
    }

    m_size = 0;
    m_front = 0;
  }

private:
  // __LINE__ must be 65 as in the original header: it is the line argument of the assert.
#line 64
  T &at(size_t index) {
    MM_ASSERT(m_buffer != 0);
    return m_buffer[index];
  }

  void pop_back() {
    size_t index = (m_front + m_size - 1) % m_capacity;
    m_size--;
    destruct(&at(index));
  }

  T *m_buffer;
  size_t m_size;
  size_t m_front;
  size_t m_capacity;
  size_t m_alignment;
  IAllocator *m_allocator;
};

} // namespace mtl
} // namespace mm
