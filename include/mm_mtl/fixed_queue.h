#pragma once
#include "mm/mm_std_base.h"
#include "types.h"
#include <stddef.h>

namespace mm {
namespace mtl {

template <typename T, size_t N> class FixedQueue {
  template <size_t Align, typename Dummy = void> struct Storage {
    typedef u8 Unit;
  };

  template <typename Dummy> struct Storage<2, Dummy> {
    typedef u16 Unit;
  };

  template <typename Dummy> struct Storage<4, Dummy> {
    struct Unit {
      u32 unknown00; // Inferred role: storage word; original member name unknown.
    };
  };

  template <typename Dummy> struct Storage<8, Dummy> {
    typedef u64 Unit;
  };

  typedef typename Storage<alignof(T)>::Unit Unit;

  T *buffer() { return reinterpret_cast<T *>(mBuffer); }
  const T *buffer() const { return reinterpret_cast<const T *>(mBuffer); }
  T &element(size_t index) { return *reinterpret_cast<T *>(&mBuffer[index * (sizeof(T) / sizeof(Unit))]); }

  // __LINE__ must be 110 as in the original header: it is the line argument of the assert.
#line 109
  T &at(size_t index) {
    MM_ASSERT(index < N);
    return element(index);
  }

public:
  template <typename V, size_t M> class fixed_queue_iterator {
  public:
    fixed_queue_iterator(V *array, size_t index) : _pArray(array), _index(index) {}

    V &operator*() const { return _pArray[_index % M]; }

    fixed_queue_iterator &operator++() {
      ++_index;
      return *this;
    }

    fixed_queue_iterator &operator--() {
      --_index;
      return *this;
    }

    // __LINE__ must be 230 as in the original header: it is the line argument of the assert.
#line 229
    friend bool operator==(const fixed_queue_iterator &a, const fixed_queue_iterator &b) {
      MM_ASSERT(a._pArray == b._pArray);
      return a._index == b._index;
    }

    friend bool operator!=(const fixed_queue_iterator &a, const fixed_queue_iterator &b) { return !(a == b); }

    V *_pArray;
    size_t _index;
  };

  typedef fixed_queue_iterator<T, N> iterator;
  typedef fixed_queue_iterator<const T, N> const_iterator;

  FixedQueue() : mSize(0), mFront(0) {}

  FixedQueue(const FixedQueue &other) : mSize(0), mFront(0) { *this = other; }

  FixedQueue &operator=(const FixedQueue &other) {
    if (this != &other) {
      clear();
      for (size_t i = 0; i < other.size(); i++) {
        push(other[i]);
      }
    }
    return *this;
  }

  size_t size() const { return mSize; }
  bool empty() const { return mSize == 0; }
  bool full() const { return mSize == N; }

  iterator begin() { return iterator(buffer(), mFront); }
  iterator end() { return iterator(buffer(), mFront + mSize); }
  const_iterator begin() const { return const_iterator(buffer(), mFront); }
  const_iterator end() const { return const_iterator(buffer(), mFront + mSize); }

  // __LINE__ must be 368 as in the original header: it is the line argument of the assert.
#line 367
  T &operator[](size_t index) {
    MM_ASSERT(index < N);
    return buffer()[(mFront + index) % N];
  }

  // __LINE__ must be 376 as in the original header: it is the line argument of the assert.
#line 375
  const T &operator[](size_t index) const {
    MM_ASSERT(index < N);
    return reinterpret_cast<const T *>(mBuffer)[(mFront + index) % N];
  }

  T &front() {
    MM_ASSERT(!empty());
    return buffer()[mFront];
  }

  // __LINE__ must be 400 as in the original header: it is the line argument of the assert.
#line 399
  T &back() {
    MM_ASSERT(!empty());
    return buffer()[(mFront + mSize - 1) % N];
  }

  void clear() {
    if (mSize != 0) {
      mSize = 0;
    }
    mSize = 0;
    mFront = 0;
  }

  // __LINE__ must be 470 as in the original header: it is the line argument of the assert.
#line 469
  T pop_front() {
    MM_ASSERT(!empty());
    size_t index = mFront;
    mFront = (mFront + 1) % N;
    --mSize;
    return at(index);
  }

  // Inferred role: copies the front element into out before removing it; original name unknown.
  void unknown002(T &out) {
    out = at(mFront);
    mFront = (mFront + 1) % N;
    --mSize;
  }

  // __LINE__ must be 485 as in the original header: it is the line argument of the assert.
#line 484
  T pop_back() {
    MM_ASSERT(!empty());
    size_t index = (mFront + mSize - 1) % N;
    --mSize;
    return element(index);
  }

  // __LINE__ must be 633 as in the original header: it is the line argument of the assert.
#line 632
  void push(const T &value) {
    MM_ASSERT(!full());
    T &slot = element((mFront + mSize) % N);
    slot = value;
    mSize++;
  }

  // The position runs from mFront to mFront + mSize, with the modulo and the increment in separate statements: counting from zero or
  // incrementing in the modulo statement changes the width of the index add (pointer queues) or the register assignment (scalar queues).
  iterator find(const T &value) {
    iterator found = end();
    if (!empty()) {
      for (size_t i = mFront; i != mFront + mSize;) {
        size_t index = i % N;
        i++;
        if (buffer()[index] == value) {
          found = iterator(buffer(), index);
          break;
        }
      }
    }
    return found;
  }

  // __LINE__ must be 625 as in the original header: it is the line argument of the assert.
#line 624
  void push_front(const T &value) {
    MM_ASSERT(!full());
    mFront = (mFront + N - 1) % N;
    element(mFront) = value;
    mSize++;
  }

  // Inferred role: push_front variant indexing through at(), as AIAgentField::procMsgPcFieldNotifyWall (1.0.0: 0x7100542514)
  // uses it; original name unknown.
  void unknown001(const T &value) {
    MM_ASSERT(!full());
    mFront += static_cast<s64>(mFront) <= 0 ? N - 1 : -1;
    at(mFront) = value;
    mSize++;
  }

  void remove(const T &value) {
    iterator it = find(value);
    while (it != end()) {
      erase(it);
      it = find(value);
    }
  }

  // __LINE__ must be 683 as in the original header: it is the line argument of the assert.
#line 682
  iterator erase(iterator position) {
    MM_ASSERT(size() != 0);
    --mSize;
    for (size_t index = position._index; index < mFront + mSize;) {
      size_t destination = index % N;
      index++;
      T &source = element(index % N);
      element(destination) = source;
    }
    return position;
  }

  // __LINE__ must be 854 as in the original header: it is the line argument of the assert.
#line 853
  iterator insert(iterator position, const T &value) {
    MM_ASSERT(!full());
    if (position == end()) {
      push(value);
      return position;
    }

    *end() = T();
    if (!empty()) {
      for (iterator it = end(); it != position; --it) {
        int index = it._index;
        size_t previous = it._index - 1;
        if (index - 1 < 0) {
          previous += N;
        }
        T &source = element(static_cast<int>(previous) % N);
        element(index % N) = source;
      }
    }
    *position = value;
    ++mSize;
    return position;
  }

private:
  Unit mBuffer[N * sizeof(T) / sizeof(Unit)];
  size_t mSize;
  size_t mFront;
};

} // namespace mtl
} // namespace mm
