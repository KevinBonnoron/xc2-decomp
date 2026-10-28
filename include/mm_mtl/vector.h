#pragma once
#include <new>
#include <stddef.h>

#include "mm/mm_std_base.h"
#include "mm_mtl/allocator.h"
#include "mm_mtl/construct.h"
#include "mm_mtl/type_traits.h"

namespace mm {
namespace mtl {

template <typename T> class Vector {
public:
  Vector() : m_buffer(nullptr), m_size(0), m_capacity(0), m_alignment(16), m_allocator(nullptr) {}
  explicit Vector(IAllocator *allocator) : m_buffer(nullptr), m_size(0), m_capacity(0), m_alignment(16), m_allocator(allocator) {}
  Vector(const Vector &other) : m_buffer(nullptr), m_size(0), m_capacity(0), m_alignment(16), m_allocator(other.m_allocator) {
    if (this != &other) {
      assign(other);
    }
  }
  ~Vector() { destroy(); }

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
  // Inferred helper: allocation alignment of the element type, at least 8; original name unknown.
  static size_t unknown001() { return alignof(T) < 8 ? 8 : alignof(T); }

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
      size_t count = size - oldSize;
      construct_n(ptr + oldSize, count);
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

  void extend(size_t size, size_t alignment, const T &value) {
    size_t oldSize = m_size;
    T *ptr = static_cast<T *>(m_allocator->allocate(size * sizeof(T), alignment));
    copy_construct_n(begin(), oldSize, ptr);
    if (oldSize < size) {
      T *position = ptr + oldSize;
      for (size_t i = 0; i < size - oldSize; i++, position++) {
        if (position != nullptr) {
          new (position) T(value);
        }
      }
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
      destroy();
      m_allocator = allocator;
    }
  }

  void resize(size_t size) {
    if (m_size == size) {
      return;
    }

    m_alignment = unknown001();
    if (m_buffer == nullptr) {
      m_buffer = static_cast<T *>(m_allocator->allocate(size * sizeof(T), unknown001()));
      m_capacity = size;
      construct_n(begin(), size);
      m_size += size;
    } else if (static_cast<long>(size - m_capacity) > 0) {
      extend(size, unknown001());
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
  void resize(size_t size, const T &value) {
    if (m_size == size) {
      return;
    }

    m_alignment = unknown001();
    if (m_buffer == nullptr) {
      T *ptr = static_cast<T *>(m_allocator->allocate(size * sizeof(T), unknown001()));
      m_capacity = size;
      m_size = size;
      m_buffer = ptr;
      size_t i = 0;
      while (i < size) {
        T *position = begin() + i++;
        if (position != nullptr) {
          new (position) T(value);
        }
      }
    } else if (static_cast<long>(size - m_capacity) > 0) {
      extend(size, unknown001(), value);
    } else {
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
  void destroy() {
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

  bool valid_iterator(const T *it) const { return begin() <= it && it <= end(); }

  // __LINE__ must be 385 as in the original header: it is the line argument of the assert.
#line 380
  void push_back(const T &value) {
    size_t size = m_size;
    if (size == m_capacity) {
      expand(size != 0 ? size * 2 : 16, m_alignment);
    }
    MM_ASSERT(m_buffer);
    size = m_size;
    T *position = begin() + size;
    if (position != nullptr) {
      new (position) T(value);
    }
    m_size++;
  }

  void assign(const Vector &other) {
    m_allocator = other.m_allocator;
    m_alignment = other.m_alignment;
    m_capacity = other.m_capacity;
    if (m_capacity != 0 && m_allocator != nullptr) {
      m_buffer = static_cast<T *>(m_allocator->allocate(other.m_capacity * sizeof(T), m_alignment));
      const T *source = other.begin();
      if (source != other.end()) {
        copy_construct_n(source, other.m_capacity, begin());
        m_size = other.m_size;
      }
    }
  }

#line 512

  T *insert(T *it, const T &value);

  T *erase(T *it);

private:
  static void copy(const T *first, const T *last, T *result);

public:
  T *m_buffer;
  size_t m_size;
  size_t m_capacity;
  size_t m_alignment;
  IAllocator *m_allocator;
};

template <typename T> void Vector<T>::copy(const T *first, const T *last, T *result) {
  if (is_pod<T>::value) {
    __builtin_memcpy(result, first, (last - first) * sizeof(T));
  } else {
    while (first != last) {
      *result++ = *first++;
    }
  }
}

template <typename T> T *Vector<T>::erase(T *it) {
  MM_ASSERT(valid_iterator(it));
  T *last = end();
  if (it != last) {
    copy(it + 1, last, it);
    m_size--;
    destruct(end());
  }
  return it;
}

} // namespace mtl
} // namespace mm
