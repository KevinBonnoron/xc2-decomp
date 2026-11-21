#pragma once
#include <new>
#include <stddef.h>

#include "mm/mm_std_base.h"
#include "mm_mtl/allocator.h"
#include "mm_mtl/construct.h"
#include "types.h"

namespace mm {
namespace mtl {

template <typename T> class Queue {
public:
  template <typename V> class queue_iterator {
  public:
    queue_iterator(V *array, size_t index, size_t capacity) : _pArray(array), _index(index), unknown10(capacity) {}

    V &operator*() const { return _pArray[_index % unknown10]; }

    queue_iterator &operator++() {
      ++_index;
      return *this;
    }

    // __LINE__ must be 411 as in the original header: it is the line argument of the assert.
#line 410
    friend bool operator==(const queue_iterator &a, const queue_iterator &b) {
      MM_ASSERT(a._pArray == b._pArray);
      return a._index == b._index;
    }

    friend bool operator!=(const queue_iterator &a, const queue_iterator &b) { return !(a == b); }

    V *_pArray;
    size_t _index;
    size_t unknown10; // Inferred role: capacity of the queue; original member name unknown.
  };

  typedef queue_iterator<T> iterator;

  // Inferred role: empty queue bound to the allocator; the game constructs Hfsm::unknown38 with it and allocates on reserve.
  explicit Queue(IAllocator *allocator) : m_buffer(nullptr), m_size(0), m_front(0), m_capacity(0), m_alignment(16), m_allocator(allocator) {}

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
      m_buffer = nullptr;
    }
    m_allocator = nullptr;
    m_front = 0;
    m_capacity = 0;
    m_size = 0;
  }

  // Inferred role: element counted from the front; original name unknown (no symbol in XC2, Torna or XC1DE). The game inlines it in the dedupe loops of
  // GfMenuObjPopup::open (0x71004b3434) and GfMenuObjDamageValue::open (0x7100445578): the assertion string "index < m_capacity" at line 503, then at()'s
  // assert at line 65.
  // __LINE__ must be 503 as in the original header: it is the line argument of the assert.
#line 502
  T &operator[](size_t index) {
    MM_ASSERT(index < m_capacity);
    return at((m_front + index) % m_capacity);
  }

  // __LINE__ must be 543 as in the original header: it is the line argument of the assert.
#line 542
  void reserve(size_t capacity, size_t alignment = alignof(T)) {
    MM_ASSERT(m_allocator && "yet setAllocator");
    if (capacity <= m_capacity) {
      return;
    }

    m_alignment = alignment;
    if (m_buffer == nullptr) {
      m_buffer = static_cast<T *>(m_allocator->allocate(capacity * sizeof(T), alignment));
      m_front = 0;
      m_capacity = capacity;
    } else if (static_cast<long>(capacity - m_capacity) > 0) {
      expand(capacity, alignment);
    }
  }

  void push_back(const T &value) {
    if (m_buffer == nullptr) {
      reserve(16);
    } else {
      size_t size = m_size;
      if (size == m_capacity) {
        expand(size != 0 ? size * 2 : 16, m_alignment);
      }
    }
    new (&at((m_front + m_size) % m_capacity)) T(value);
    m_size++;
  }

  iterator begin() { return iterator(&at(0), m_front, m_capacity); }

  size_t size() const { return m_size; }
  u32 capacity() const { return m_capacity; }
  bool full() const { return m_size == m_capacity; }

  // Inferred role: enqueues a value without growing, asserting the buffer and the spare capacity; original name unknown.
  // The game inlines it in Hfsm::endSetup; the assertion strings quote "m_buffer != 0" and "!full()".
  void unknown001(const T &value) {
    MM_ASSERT(m_buffer != 0);
    MM_ASSERT(!full());
    new (&at((m_front + m_size) % m_capacity)) T(value);
    m_size++;
  }

  T &front() { return at(m_front); }

  // Inferred role: removes the front element and copies it into the argument; original name unknown (no symbol in XC2, Torna or XC1DE: the game only
  // instantiates the push_back/erase/expand members of Queue<T>). The game inlines it in GfMenuObjDamageBuff::open and openUniteCombo (0x7100443854,
  // 0x7100443bec), GfMenuObjDropItem::open (0x7100446c10), GfMenuObjDamageValue::open (0x7100445578) and GfMenuObjPopup::open (0x71004b3434): the
  // assertion strings quote "!empty()" at line 0x301 (769), then at() asserts the buffer at line 0x41, and the element is read before the front moves.
  // The destination is a reference to a record constructed before the call (its vtable pointer is stored before the assertions): a by-value return puts the
  // copy in the inlined callee's noalias result slot, which lets the second read of m_front move above the copy stores (DamageValue::open reloads it after,
  // with m_size, as one ldp).
  // __LINE__ must be 769 as in the original header: it is the line argument of the assert.
#line 768
  void unknown002(T &out) {
    MM_ASSERT(!empty());
    out = at(m_front);
    m_front = (m_front + 1) % m_capacity;
    m_size--;
  }

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

  iterator end() { return iterator(&at(0), m_front + m_size, m_capacity); }

  // __LINE__ must be 1067 as in the original header: it is the line argument of the assert.
#line 1063
  iterator erase(iterator position) {
    if (position == end()) {
      return position;
    }
    MM_ASSERT(size() != 0);
    m_size--;
    for (size_t index = position._index; index < m_front + m_size;) {
      size_t destination = index % m_capacity;
      index++;
      T &source = at(index % m_capacity);
      at(destination) = source;
    }
    // The game ends with two at() asserts (queue.h line 65) and no other effect: both elements are the vacated slot, whose
    // destructors are trivial for every element type the game instantiates. Which two slots the original touched is not
    // recoverable from the binary; the vacated end slot is the only one an erase has reason to destruct.
    size_t vacated = (m_front + m_size) % m_capacity;
    destruct(&at(vacated));
    destruct(&at(vacated));
    return position;
  }

private:
  // __LINE__ must be 65 as in the original header: it is the line argument of the assert.
#line 64
  T &at(size_t index) {
    MM_ASSERT(m_buffer != 0);
    return m_buffer[index];
  }

  // __LINE__ must be 136 and 138 as in the original header: they are the line arguments of the asserts.
#line 133
  void expand(size_t capacity, size_t alignment) {
    size_t size = m_size;
    size_t front = m_front;
    MM_ASSERT(m_allocator != 0);
    T *ptr = static_cast<T *>(m_allocator->allocate(capacity * sizeof(T), alignment));
    MM_ASSERT(ptr != 0);
    if (m_buffer != nullptr) {
      iterator it = begin();
      for (size_t i = 0; i < size; i++, ++it) {
        new (&ptr[(m_front + i) % capacity]) T(*it);
      }
      clear();
      // __LINE__ must be 154 as in the original header: it is the line argument of the assert.
#line 154
      MM_ASSERT(m_allocator);
      m_allocator->deallocate(m_buffer);
    }
    m_front = front;
    m_capacity = capacity;
    m_buffer = ptr;
    m_size = size;
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
