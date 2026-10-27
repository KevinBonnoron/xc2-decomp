#pragma once
#include <stddef.h>

#include "mm/mm_std_base.h"

namespace ptlib {

struct IntrusiveListNode {
  bool intoNode() const { return unknown00 != this; }

  IntrusiveListNode *unknown00; // Inferred role: next node; original member name unknown.
  IntrusiveListNode *unknown08; // Inferred role: previous node; original member name unknown.
};

static_assert(offsetof(IntrusiveListNode, unknown08) == 0x08, "");
static_assert(sizeof(IntrusiveListNode) == 0x10, "");

class IntrusiveListBase : public IntrusiveListNode {
public:
  IntrusiveListBase();
  int sizeTraverse() const;
  static void linkNode(IntrusiveListNode *node, IntrusiveListNode *next);
  static void unlinkNode(IntrusiveListNode *node);

  int m_size;
};

static_assert(offsetof(IntrusiveListBase, m_size) == 0x10, "");

template <typename Ptr, typename Ref, typename T> class IntrusiveListIterator {
public:
  explicit IntrusiveListIterator(T *node) : m_node(node) {}

  Ref operator*() const {
#line 55
    MM_ASSERT(m_node);
    return *m_node;
  }

  Ptr operator->() const { return m_node; }

  IntrusiveListIterator &operator++() {
    m_node = static_cast<T *>(m_node->unknown00);
    return *this;
  }

  bool operator==(const IntrusiveListIterator &other) const { return m_node == other.m_node; }
  bool operator!=(const IntrusiveListIterator &other) const { return m_node != other.m_node; }
  T *get() const { return m_node; }

private:
  T *m_node;
};

template <typename T> class IntrusiveList : public IntrusiveListBase {
public:
  typedef IntrusiveListIterator<T *, T &, T> iterator;

  iterator begin() { return iterator(static_cast<T *>(unknown00)); }
  iterator end() { return iterator(static_cast<T *>(static_cast<IntrusiveListNode *>(this))); }

  bool empty() const { return unknown00 == this; }

  void erase(T *node) {
    unlinkNode(node);
    m_size--;
#line 154
    MM_ASSERT(m_size >= 0);
  }

  iterator erase(iterator it) {
#line 246
    MM_ASSERT(!empty());
    MM_ASSERT(it != end());
    T *next = static_cast<T *>(it.get()->unknown00);
    erase(it.get());
    return iterator(next);
  }

  iterator find(T *ptr) {
    iterator it = begin();
#line 295
    MM_ASSERT(ptr);
    for (; it != end(); ++it) {
      if (it.get() == ptr) {
        return it;
      }
    }
    return end();
  }

  void push_back(T *ptr) {
#line 209
    MM_ASSERT(ptr);
    linkNode(ptr, this);
    m_size++;
  }

  void push_front(T *ptr) {
#line 221
    MM_ASSERT(ptr);
    linkNode(ptr, unknown00);
    m_size++;
  }
};

} // namespace ptlib
