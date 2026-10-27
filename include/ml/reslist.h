#pragma once
#include "mtl/alloc_handle.h"

namespace ml {

template <typename T> class _reslist_base {
public:
  struct NodeBase {
    NodeBase *next;
    NodeBase *prev;
  };

  struct Node : NodeBase {
    Node *getNext() const { return static_cast<Node *>(this->next); }
    Node *getPrev() const { return static_cast<Node *>(this->prev); }

    T value;
  };

  _reslist_base() : m_pool(nullptr), m_capacity(0), m_size(0), m_isExternal(false) {
    m_root.next = &m_root;
    m_root.prev = &m_root;
    m_end = &m_root;
  }

  virtual ~_reslist_base() {
    clear();
    if (!m_isExternal && m_pool != nullptr) {
      delete[] m_pool;
      m_pool = nullptr;
    }
  }

  Node *begin() const { return static_cast<Node *>(m_end->next); }
  Node *end() const { return static_cast<Node *>(m_end); }
  int size() const { return m_size; }

  void release() {
    clear();
    if (!m_isExternal && m_pool != nullptr) {
      delete[] m_pool;
      m_pool = nullptr;
    }
    m_capacity = 0;
  }

  void create(int capacity, mtl::ALLOC_HANDLE handle) {
    m_pool = new (handle) Node[capacity];
    for (int i = 0; i < capacity; i++) {
      m_pool[i].next = nullptr;
    }
    m_capacity = capacity;
  }

  void push_back(const T &value) {
    NodeBase *last = end();
    int index = 0;
    while (index < m_capacity && m_pool[index].next != nullptr) {
      index++;
    }
    Node *node = &m_pool[index];
    node->value = value;
    node->next = last;
    node->prev = last->prev;
    last->prev->next = node;
    last->prev = node;
    m_size++;
  }

  void erase(Node *node) {
    NodeBase *next = node->next;
    NodeBase *prev = node->prev;
    prev->next = next;
    next->prev = prev;
    node->next = nullptr;
    m_size--;
  }

  void clear() {
    Node *node = begin();
    while (node != end()) {
      Node *next = node->getNext();
      node->next = nullptr;
      node = next;
    }
    node->next = node;
    m_end->prev = m_end;
    m_size = 0;
  }

  NodeBase *m_end;
  Node m_root;
  Node *m_pool;
  int m_capacity;
  int m_size;
  bool m_isExternal;
};

template <typename T> class reslist : public _reslist_base<T> {};

} // namespace ml
