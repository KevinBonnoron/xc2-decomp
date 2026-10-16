#pragma once
#include "mm/mm_std_base.h"

namespace mm {
namespace mtl {

class IntrusiveListNodeBase {
public:
  IntrusiveListNodeBase() {
    m_prev = this;
    m_next = this;
  }

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
  class iterator {
  public:
    explicit iterator(T *node) : m_node(node) {}

    T &operator*() const {
      MM_ASSERT(m_node);
      return *m_node;
    }

    T *operator->() const {
      MM_ASSERT(m_node);
      return m_node;
    }

    iterator &operator++() {
      m_node = static_cast<T *>(m_node->m_next);
      return *this;
    }

    bool operator==(const iterator &other) const { return m_node == other.m_node; }
    bool operator!=(const iterator &other) const { return m_node != other.m_node; }

  private:
    T *m_node;
  };

  iterator begin() { return iterator(static_cast<T *>(m_head.m_next)); }
  iterator end() { return iterator(static_cast<T *>(&m_head)); }

  int size() const { return m_size; }

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
