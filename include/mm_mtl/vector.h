#pragma once
#include "mm/mm_std_base.h"
#include "mm_mtl/allocator.h"
#include "mm_mtl/construct.h"
#include <stddef.h>

namespace mm {
namespace mtl {

template <typename T> class Vector {
public:
  Vector() : m_buffer(nullptr), m_size(0), m_capacity(0), m_alignment(16), m_allocator(nullptr) {}
  ~Vector() { release(); }

  // __LINE__ must be 60 as in the original header: it is the line argument of the assert.
#line 59
  const T *begin() const {
    MM_ASSERT(m_buffer != 0);
    return m_buffer;
  }

  // __LINE__ must be 68 as in the original header: it is the line argument of the assert.
#line 67
  T *begin() {
    MM_ASSERT(m_buffer != 0);
    return m_buffer;
  }

  const T *end() const { return begin() + m_size; }
  T *end() { return begin() + m_size; }

private:
  // __LINE__ must be 92 and 94 as in the original header: they are the line arguments of the asserts.
#line 90
  void expand(size_t capacity, size_t alignment) {
    size_t size = m_size;
    MM_ASSERT(m_allocator != 0);
    T *ptr = static_cast<T *>(m_allocator->allocate(capacity * sizeof(T), alignment));
    MM_ASSERT(ptr != 0);
    if (m_buffer != nullptr) {
      copy_construct_n(m_buffer, size, ptr);
      clear();
      // __LINE__ must be 103 as in the original header: it is the line argument of the assert.
#line 103
      MM_ASSERT(m_allocator);
      m_allocator->deallocate(m_buffer);
      m_buffer = nullptr;
    }
    m_buffer = ptr;
    m_capacity = capacity;
    m_size = size;
  }

  // __LINE__ must be 154 as in the original header: it is the line argument of the assert.
#line 145
  void extend(size_t size, size_t alignment) {
    size_t oldSize = m_size;
    T *ptr = static_cast<T *>(m_allocator->allocate(size * sizeof(T), alignment));
    copy_construct_n(begin(), oldSize, ptr);
    if (oldSize < size) {
      construct_n(ptr + oldSize, size - oldSize);
    }
    clear();
    if (m_buffer != nullptr) {
      MM_ASSERT(m_allocator);
      m_allocator->deallocate(m_buffer);
      m_buffer = nullptr;
    }
    m_buffer = ptr;
    m_capacity = size;
    m_size = size;
  }

public:
  // __LINE__ must be 338 and 339 as in the original header: they are the line arguments of the asserts.
#line 337
  T &operator[](size_t index) {
    MM_ASSERT(m_buffer != 0);
    MM_ASSERT(index < size());
    return m_buffer[index];
  }

  // __LINE__ must be 345 and 346 as in the original header: they are the line arguments of the asserts.
#line 344
  const T &operator[](size_t index) const {
    MM_ASSERT(m_buffer != 0);
    MM_ASSERT(index < size());
    return m_buffer[index];
  }

  size_t size() const { return m_size; }
  size_t capacity() const { return m_capacity; }
  bool empty() const { return m_size == 0; }

  void setAllocator(IAllocator *allocator) {
    if (m_allocator != allocator) {
      release();
      m_allocator = allocator;
    }
  }

  void resize(size_t size) {
    if (m_size == size) {
      return;
    }

    m_alignment = 8;
    if (m_buffer == nullptr) {
      m_buffer = static_cast<T *>(m_allocator->allocate(size * sizeof(T), 8));
      m_capacity = size;
      construct_n(begin(), size);
      m_size += size;
    } else if (static_cast<long>(size - m_capacity) > 0) {
      extend(size, 8);
    } else {
      long count = size - m_size;
      if (count < 0) {
        for (long i = -count; i > 0; i--) {
          pop_back();
        }
      } else if (count != 0) {
        construct_n(m_buffer + m_size, count);
        m_size += count;
      }
    }
  }
  void pop_back() {
    if (m_size != 0) {
      size_t index = --m_size;
      destruct(begin() + index);
    }
  }

  void clear() {
    if (m_buffer != nullptr) {
      destruct_n(m_buffer, m_size);
    }
    m_size = 0;
  }

  // __LINE__ must be 455 as in the original header: it is the line argument of the assert.
#line 452
  void release() {
    clear();
    if (m_buffer != nullptr) {
      MM_ASSERT(m_allocator);
      m_allocator->deallocate(m_buffer);
      m_buffer = nullptr;
    }
    m_allocator = nullptr;
    m_capacity = 0;
  }

  // __LINE__ must be 483 as in the original header: it is the line argument of the assert.
#line 482
  void reserve(size_t capacity, size_t alignment = 8) {
    MM_ASSERT(m_allocator && "yet setAllocator");
    if (capacity <= m_capacity) {
      return;
    }

    m_alignment = alignment;
    if (m_buffer == nullptr) {
      m_buffer = static_cast<T *>(m_allocator->allocate(capacity * sizeof(T), alignment));
      m_capacity = capacity;
    } else if (static_cast<long>(capacity - m_capacity) > 0) {
      expand(capacity, alignment);
    }
  }

private:
  T *m_buffer;
  size_t m_size;
  size_t m_capacity;
  size_t m_alignment;
  IAllocator *m_allocator;
};

} // namespace mtl
} // namespace mm
