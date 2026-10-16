#pragma once
#include "mm/mm_std_base.h"

namespace mm {
namespace mtl {

class IntrusiveListNodeBase {
public:
  IntrusiveListNodeBase() : m_next(this), m_prev(this) {}

  bool intoNode() const { return m_next != this; }

  IntrusiveListNodeBase *m_next;
  IntrusiveListNodeBase *m_prev;
};

template <typename T> class IntrusiveListNode : public IntrusiveListNodeBase {};

class IntrusiveListBase {
public:
  IntrusiveListBase();
  int sizeTraverse() const;
  static void linkNode(IntrusiveListNodeBase *node, IntrusiveListNodeBase *position);
  static void unlinkNode(IntrusiveListNodeBase *node);

protected:
  IntrusiveListNodeBase m_head;
  int m_size;
};

template <typename T> class IntrusiveList : public IntrusiveListBase {
public:
  void push_back(T *ptr) {
    MM_ASSERT(ptr);
    linkNode(ptr, &m_head);
    m_size++;
  }

  void erase(T *ptr) {
    unlinkNode(ptr);
    m_size--;
    MM_ASSERT(m_size >= 0);
  }
};

} // namespace mtl
} // namespace mm
