#pragma once
#include <new>

#include "mm/mm_std_base.h"
#include "mm_mtl/allocator.h"
#include "mm_mtl/construct.h"

namespace mm {
namespace mtl {

// Layout from the assembly of the instantiations for Set<anm::StringPtr> and Map<anm::StringPtr, ...> (insert, rebalance, free_node and
// the code of anm::StateMachine): a node is the left child at 0x00, the parent at 0x08, the right child at 0x10, the value at 0x18 and the
// color after it; the tree is the root at 0x00, m_size at 0x08 and m_allocator at 0x10. The assertion strings give m_size, m_allocator,
// m_sentinel, nodePtr, m_root and the color name "red".
template <typename Traits> class RedBlackTreeBase {
public:
  typedef typename Traits::key_type key_type;
  typedef typename Traits::value_type value_type;

  // The node colors; the name of the enum and of the second enumerator are unknown, only "red" appears in an assertion.
  enum unknown001 { red, unknown001_UNKNOWN_1 };

  struct node {
    node() {}
    explicit node(node *sentinel) : unknown00(sentinel), unknown08(sentinel), unknown10(sentinel), unknown18(), color(unknown001_UNKNOWN_1) {}

    node *unknown00; // Inferred role: left child; original member name unknown.
    node *unknown08; // Inferred role: parent; original member name unknown.
    node *unknown10; // Inferred role: right child; original member name unknown.
    value_type unknown18;
    unknown001 color;
  };

  class iterator {
  public:
    iterator(RedBlackTreeBase *tree, node *node) : m_tree(tree), nodePtr(node) {}

    value_type &operator*() const { return nodePtr->unknown18; }
    value_type *operator->() const { return &nodePtr->unknown18; }

    iterator &operator++() {
      nodePtr = m_tree->unknown004(nodePtr);
      return *this;
    }

    bool operator==(const iterator &rhs) const { return nodePtr == rhs.nodePtr; }
    bool operator!=(const iterator &rhs) const { return nodePtr != rhs.nodePtr; }

    RedBlackTreeBase *m_tree;
    node *nodePtr;
  };

  iterator begin() {
    node *current = m_root;
    if (current == &m_sentinel) {
      return iterator(this, nullptr);
    }
    while (current->unknown00 != &m_sentinel) {
      current = current->unknown00;
    }
    return iterator(this, current);
  }

  iterator end() { return iterator(this, nullptr); }

  iterator find(const key_type &key) {
    node *current = m_root;
    while (current != &m_sentinel) {
      if (Traits::get_key(current->unknown18) < key) {
        current = current->unknown10;
      } else if (!(key < Traits::get_key(current->unknown18))) {
        return iterator(this, current);
      } else {
        current = current->unknown00;
      }
    }
    return iterator(this, nullptr);
  }

  RedBlackTreeBase() : m_size(0), m_allocator(nullptr) { unknown003(); }
  ~RedBlackTreeBase() {
    clear();
    m_allocator = nullptr;
  }

  void clear() {
    if (m_size != 0) {
      free_node(m_root, true);
      m_root = &m_sentinel;
      m_size = 0;
    }
  }

  void setAllocator(IAllocator *allocator) {
    if (m_allocator != allocator) {
      clear();
      m_allocator = allocator;
      unknown003();
    }
  }

  // __LINE__ must be 636 and 639 as in the original header: they are the line arguments of the asserts.
#line 630
  node *insert(const value_type &value) {
    node *parent = &m_sentinel;
    node *current = m_root;
    while (current != &m_sentinel) {
      parent = current;
      if (Traits::get_key(current->unknown18) < Traits::get_key(value)) {
        current = current->unknown10;
      } else if (!(Traits::get_key(value) < Traits::get_key(current->unknown18))) {
        return current;
      } else {
        current = current->unknown00;
      }
    }
    MM_ASSERT(m_allocator != 0);
    void *mem = m_allocator->allocate(sizeof(node), alignof(node));
    node *new_node = static_cast<node *>(mem);
    if (new_node != nullptr) {
      new (new_node) node();
    }
    MM_ASSERT(mem != 0);
    new_node->color = red;
    new_node->unknown18 = value;
    new_node->unknown10 = &m_sentinel;
    new_node->unknown08 = parent;
    new_node->unknown00 = &m_sentinel;
    if (parent == &m_sentinel) {
      m_root = new_node;
    } else if (Traits::get_key(value) < Traits::get_key(parent->unknown18)) {
      parent->unknown00 = new_node;
    } else {
      parent->unknown10 = new_node;
    }
    rebalance(new_node);
    m_size++;
    return new_node;
  }

  // __LINE__ must be 661 as in the original header: it is the line argument of the assert.
#line 650
  void free_node(node *target, bool recursive) {
    if (recursive) {
      if (target->unknown00 != &m_sentinel) {
        free_node(target->unknown00, true);
      }
      if (target->unknown10 != &m_sentinel) {
        free_node(target->unknown10, true);
      }
    }
    if (target != &m_sentinel) {
      MM_ASSERT(m_allocator != 0);
      destruct(target);
      m_allocator->deallocate(target);
    }
  }

  // Matches the instantiation for Map<anm::StringPtr, anm::AdditiveInfo> (1.0.0: 0x71009682cc), called by anm::StateMachine::update.
  // __LINE__ must be 231 as in the original header: it is the line argument of the assert.
#line 230
  void erase(node *nodePtr) {
    MM_ASSERT(m_size > 0);
    node *target;
    if (nodePtr->unknown00 == &m_sentinel || nodePtr->unknown10 == &m_sentinel) {
      target = nodePtr;
    } else {
      target = nodePtr->unknown10;
      while (target->unknown00 != &m_sentinel) {
        target = target->unknown00;
      }
    }
    node *&childLink = target->unknown00 == &m_sentinel ? target->unknown10 : target->unknown00;
    node *child = childLink;
    child->unknown08 = target->unknown08;
    if (target->unknown08 == &m_sentinel) {
      m_root = child;
    } else if (target == target->unknown08->unknown00) {
      target->unknown08->unknown00 = child;
    } else {
      target->unknown08->unknown10 = child;
    }
    nodePtr->unknown18 = target->unknown18;
    if (target->color == unknown001_UNKNOWN_1) {
      rebalance_after_erase(child);
    }
    free_node(target, false);
    m_size--;
  }

  node *m_root;
  int m_size;
  IAllocator *m_allocator;
  static node m_sentinel;

private:
  // Inferred helper: resets the sentinel node and empties the root; original name unknown.
  void unknown003() {
    m_sentinel.color = unknown001_UNKNOWN_1;
    m_sentinel.unknown10 = &m_sentinel;
    m_sentinel.unknown08 = &m_sentinel;
    m_sentinel.unknown00 = &m_sentinel;
    m_root = &m_sentinel;
  }

  // Inferred helper: finds the node that follows another one in order, null after the last; original name unknown.
  // __LINE__ must be 363 as in the original header: it is the line argument of the assert.
#line 345
  node *unknown004(node *nodePtr) {
    if (nodePtr->unknown10 == &m_sentinel) {
      node *parent = nodePtr->unknown08;
      if (parent == &m_sentinel) {
        MM_ASSERT(nodePtr == m_root);
        return nullptr;
      }
      if (parent->unknown00 == nodePtr) {
        return parent;
      }
      while (nodePtr == parent->unknown10) {
        nodePtr = parent;
        parent = nodePtr->unknown08;
        if (parent == &m_sentinel) {
          return nullptr;
        }
      }
      return parent;
    }
    nodePtr = nodePtr->unknown10;
    while (nodePtr->unknown00 != &m_sentinel) {
      nodePtr = nodePtr->unknown00;
    }
    return nodePtr;
  }

  // Inferred helper: rotates the subtree at a node to the left; original name unknown.
  void unknown001(node *pivot) {
    node *child = pivot->unknown10;
    node *inner = child->unknown00;
    pivot->unknown10 = inner;
    if (inner != &m_sentinel) {
      inner->unknown08 = pivot;
    }
    child->unknown08 = pivot->unknown08;
    if (pivot->unknown08 == &m_sentinel) {
      m_root = child;
    } else if (pivot == pivot->unknown08->unknown00) {
      pivot->unknown08->unknown00 = child;
    } else {
      pivot->unknown08->unknown10 = child;
    }
    child->unknown00 = pivot;
    pivot->unknown08 = child;
  }

  // Inferred helper: rotates the subtree at a node to the right; original name unknown.
  void unknown002(node *pivot) {
    node *child = pivot->unknown00;
    node *inner = child->unknown10;
    pivot->unknown00 = inner;
    if (inner != &m_sentinel) {
      inner->unknown08 = pivot;
    }
    child->unknown08 = pivot->unknown08;
    if (pivot->unknown08 == &m_sentinel) {
      m_root = child;
    } else if (pivot == pivot->unknown08->unknown00) {
      pivot->unknown08->unknown00 = child;
    } else {
      pivot->unknown08->unknown10 = child;
    }
    child->unknown10 = pivot;
    pivot->unknown08 = child;
  }

  // Inferred helper: restores the red black properties after a black node was removed; original name unknown.
  void rebalance_after_erase(node *current) {
    while (current != m_root && current->color == unknown001_UNKNOWN_1) {
      if (current == current->unknown08->unknown00) {
        node *sibling = current->unknown08->unknown10;
        if (sibling->color == red) {
          sibling->color = unknown001_UNKNOWN_1;
          current->unknown08->color = red;
          unknown001(current->unknown08);
          sibling = current->unknown08->unknown10;
        }
        if (sibling->unknown00->color == unknown001_UNKNOWN_1 && sibling->unknown10->color == unknown001_UNKNOWN_1) {
          sibling->color = red;
          current = current->unknown08;
        } else {
          if (sibling->unknown10->color == unknown001_UNKNOWN_1) {
            sibling->unknown00->color = unknown001_UNKNOWN_1;
            sibling->color = red;
            unknown002(sibling);
            sibling = current->unknown08->unknown10;
          }
          sibling->color = current->unknown08->color;
          current->unknown08->color = unknown001_UNKNOWN_1;
          sibling->unknown10->color = unknown001_UNKNOWN_1;
          unknown001(current->unknown08);
          current = m_root;
        }
      } else {
        node *sibling = current->unknown08->unknown00;
        if (sibling->color == red) {
          sibling->color = unknown001_UNKNOWN_1;
          current->unknown08->color = red;
          unknown002(current->unknown08);
          sibling = current->unknown08->unknown00;
        }
        if (sibling->unknown00->color == unknown001_UNKNOWN_1 && sibling->unknown10->color == unknown001_UNKNOWN_1) {
          sibling->color = red;
          current = current->unknown08;
        } else {
          if (sibling->unknown00->color == unknown001_UNKNOWN_1) {
            sibling->unknown10->color = unknown001_UNKNOWN_1;
            sibling->color = red;
            unknown001(sibling);
            sibling = current->unknown08->unknown00;
          }
          sibling->color = current->unknown08->color;
          current->unknown08->color = unknown001_UNKNOWN_1;
          sibling->unknown00->color = unknown001_UNKNOWN_1;
          unknown002(current->unknown08);
          current = m_root;
        }
      }
    }
    current->color = unknown001_UNKNOWN_1;
  }

  // __LINE__ must be 419 as in the original header: it is the line argument of the assert.
#line 418
  void rebalance(node *new_node) {
    MM_ASSERT(new_node->color == red);
    node *current = new_node;
    node *parent = current->unknown08;
    while (parent->color == red) {
      node *grandparent = parent->unknown08;
      if (parent == grandparent->unknown00) {
        node *uncle = grandparent->unknown10;
        if (uncle->color == red) {
          parent->color = unknown001_UNKNOWN_1;
          uncle->color = unknown001_UNKNOWN_1;
          grandparent->color = red;
          current = grandparent;
        } else {
          if (current == parent->unknown10) {
            current = parent;
            unknown001(current);
            parent = current->unknown08;
            grandparent = parent->unknown08;
          }
          parent->color = unknown001_UNKNOWN_1;
          grandparent->color = red;
          unknown002(grandparent);
        }
      } else {
        node *uncle = grandparent->unknown00;
        if (uncle->color == red) {
          grandparent->color = red;
          current->unknown08->color = unknown001_UNKNOWN_1;
          uncle->color = unknown001_UNKNOWN_1;
          current = grandparent;
        } else {
          if (current == parent->unknown00) {
            current = parent;
            unknown002(current);
            parent = current->unknown08;
            grandparent = parent->unknown08;
          }
          parent->color = unknown001_UNKNOWN_1;
          grandparent->color = red;
          unknown001(grandparent);
        }
      }
      parent = current->unknown08;
    }
    m_root->color = unknown001_UNKNOWN_1;
  }
};

template <typename Traits> typename RedBlackTreeBase<Traits>::node RedBlackTreeBase<Traits>::m_sentinel(&RedBlackTreeBase<Traits>::m_sentinel);

} // namespace mtl
} // namespace mm
