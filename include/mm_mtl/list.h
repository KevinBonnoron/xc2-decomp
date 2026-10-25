#pragma once
#include <new>
#include <stddef.h>

#include "mm/mm_std_base.h"
#include "mm_mtl/allocator.h"

namespace mm {
namespace mtl {

template <typename T> class _ReslistBase {
public:
  struct Node {
    Node *m_next;
    Node *m_prev;
    T m_value;
  };

  class iterator {
  public:
    iterator(Node *node, _ReslistBase *list) : m_node(node), m_list(list) {}

    T &operator*() const { return m_node->m_value; }

    iterator &operator++() {
      m_node = m_node->m_next;
      return *this;
    }

    bool operator==(const iterator &other) const { return m_node == other.m_node; }
    bool operator!=(const iterator &other) const { return m_node != other.m_node; }

    Node *m_node;
    _ReslistBase *m_list;
  };

  class const_iterator {
  public:
    const_iterator(Node *node, const _ReslistBase *list) : m_node(node), m_list(list) {}

    const T &operator*() const { return m_node->m_value; }

    const_iterator &operator++() {
      m_node = m_node->m_next;
      return *this;
    }

    bool operator==(const const_iterator &other) const { return m_node == other.m_node; }
    bool operator!=(const const_iterator &other) const { return m_node != other.m_node; }

    Node *m_node;
    const _ReslistBase *m_list;
  };

  explicit _ReslistBase(IAllocator *allocator = nullptr) : m_capacity(0), m_size(0), m_alignment(alignof(Node)), m_allocator(allocator) {
    m_head = &m_terminator;
    m_head->m_next = m_head;
    m_head->m_prev = m_head;
  }
  virtual ~_ReslistBase() { clear(); }

  iterator begin() { return iterator(m_head->m_next, this); }
  iterator end() { return iterator(m_head, this); }
  const_iterator begin() const { return const_iterator(m_head->m_next, this); }
  const_iterator end() const { return const_iterator(m_head, this); }

  int size() const { return m_size; }
  bool empty() const { return m_size == 0; }

  void clear() {
    Node *node = begin().m_node;
    while (node != m_head) {
      Node *next = node->m_next;
      destroyNode(node);
      node = next;
    }
    m_head->m_next = m_head;
    m_head->m_prev = m_head;
    m_capacity = 0;
    m_size = 0;
  }

  void setAllocator(IAllocator *allocator) {
    if (m_allocator != allocator) {
      clear();
      m_allocator = allocator;
    }
  }

  // __LINE__ must be 169 as in the original header: it is the line argument of the assert.
#line 167
  void reserve(int capacity) {
    MM_ASSERT(m_allocator && "yet setAllocator");
    if (m_capacity < capacity) {
      m_alignment = alignof(Node);
      m_capacity = capacity;
    }
  }

  void push_back(const T &value) {
    Node *position = m_head;
    Node *node = static_cast<Node *>(m_allocator->allocate(sizeof(Node), m_alignment));
    new (&node->m_value) T(value);
    node->m_next = position;
    node->m_prev = position->m_prev;
    position->m_prev->m_next = node;
    position->m_prev = node;
    m_size++;
    if (m_capacity < m_size) {
      m_capacity = m_size;
    }
  }

  iterator erase(const iterator &it) {
    if (it == end()) {
      return end();
    }

    Node *node = it.m_node;
    Node *next = node->m_next;
    Node *prev = node->m_prev;
    prev->m_next = next;
    next->m_prev = prev;
    destroyNode(node);
    m_size--;
    return iterator(next, this);
  }

private:
  void destroyNode(Node *node) {
    node->m_value.~T();
    freeNode(node);
  }

  void freeNode(Node *node) {
    if (node != nullptr && node != m_head) {
      m_allocator->deallocate(node);
    }
  }

  Node *m_head;
  Node m_terminator;
  int m_capacity;
  int m_size;
  size_t m_alignment;
  IAllocator *m_allocator;
};

template <typename T> class List : public _ReslistBase<T> {
public:
  explicit List(IAllocator *allocator = nullptr) : _ReslistBase<T>(allocator) {}
};

static_assert(sizeof(List<void *>) == 0x40, "");

} // namespace mtl
} // namespace mm
