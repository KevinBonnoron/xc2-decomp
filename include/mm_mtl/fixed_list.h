#pragma once
#include "mm/mm_std_base.h"
#include "types.h"
#include <new>
#include <stddef.h>

namespace mm {
namespace mtl {

template <size_t N, bool IsSmall = (N < 256)> struct FixedListIndex {
  typedef u16 Type;
};

template <size_t N> struct FixedListIndex<N, true> {
  typedef u8 Type;
};

template <typename T, size_t N> class FixedList {
  typedef typename FixedListIndex<N>::Type Index;

public:
  struct ListNode {
    bool in_list() const { return mIndex != mNext; }

    T mValue;
    Index mIndex;
    Index mNext;
    Index mPrev;
  };

  template <typename V, typename NodePtr> class node_iterator {
  public:
    node_iterator(NodePtr node, FixedList *list) : m_node(node), mList(list) {}

    V &operator*() const {
      MM_ASSERT(m_node != 0);
      return m_node->mValue;
    }

    node_iterator &operator++() {
      m_node = mList->node(m_node->mNext);
      return *this;
    }

    bool operator==(const node_iterator &other) const { return m_node == other.m_node; }
    bool operator!=(const node_iterator &other) const { return m_node != other.m_node; }

    NodePtr node() const { return m_node; }
    FixedList *list() const { return mList; }

  private:
    NodePtr m_node;
    FixedList *mList;
  };

  typedef node_iterator<T, ListNode *> iterator;
  typedef node_iterator<const T, const ListNode *> const_iterator;

  FixedList() {
    m_num_nodes = 0;
    for (int i = 0; i < N + 1; i++) {
      mFreeIndices[i] = i;
    }
    m_free_index_top = N;
    head()->mPrev = 0;
    head()->mNext = 0;
    head()->mIndex = 0;
  }
  ~FixedList() { clear(); }

  iterator begin() { return iterator(node(head()->mNext), this); }
  const_iterator begin() const { return const_iterator(node(head()->mNext), const_cast<FixedList *>(this)); }
  iterator end() { return iterator(head(), this); }
  const_iterator end() const { return const_iterator(head(), const_cast<FixedList *>(this)); }

  size_t size() const { return m_num_nodes; }
  bool empty() const { return m_num_nodes == 0; }

  void clear() {
    for (ListNode *current = node(head()->mNext); current != head(); current = node(current->mNext)) {
      current->mValue.~T();
    }
    head()->mPrev = 0;
    head()->mNext = 0;
    head()->mIndex = 0;
    m_num_nodes = 0;
    for (int i = 0; i < N + 1; i++) {
      mFreeIndices[i] = i;
    }
    m_free_index_top = N;
  }

  void push_back(const T &value) {
    MM_ASSERT(m_free_index_top > 0);
    Index index = mFreeIndices[m_free_index_top--];
    ListNode *added = node(index);
    new (&added->mValue) T(value);
    added->mIndex = index;
    m_num_nodes++;
    MM_ASSERT(m_num_nodes <= N + 1);
    Index last = head()->mPrev;
    added->mPrev = last;
    node(last)->mNext = added->mIndex;
    head()->mPrev = added->mIndex;
    added->mNext = head()->mIndex;
  }

  iterator erase(iterator it) {
    MM_ASSERT(!empty());
    MM_ASSERT(it.node()->in_list());
    MM_ASSERT(it.list() == this);
    ListNode *removed = it.node();
    iterator next(it.list()->node(removed->mNext), it.list());
    mFreeIndices[++m_free_index_top] = removed->mIndex;
    node(removed->mPrev)->mNext = removed->mNext;
    node(removed->mNext)->mPrev = removed->mPrev;
    removed->mPrev = removed->mIndex;
    removed->mNext = removed->mIndex;
    m_num_nodes--;
    return next;
  }

private:
  ListNode *node(int index) { return reinterpret_cast<ListNode *>(mBuffer) + index; }
  const ListNode *node(int index) const { return reinterpret_cast<const ListNode *>(mBuffer) + index; }
  ListNode *head() { return node(0); }
  const ListNode *head() const { return node(0); }

  alignas(ListNode) unsigned char mBuffer[sizeof(ListNode) * (N + 1)];
  Index mFreeIndices[N + 1];
  int m_free_index_top;
  int m_num_nodes;
};

static_assert(sizeof(FixedList<u32, 3>::ListNode) == 0x8, "");
static_assert(sizeof(FixedList<u32, 3>) == 0x2c, "");
static_assert(sizeof(FixedList<void *, 16>::ListNode) == 0x10, "");
static_assert(sizeof(FixedList<void *, 16>) == 0x130, "");
static_assert(sizeof(FixedList<u32, 512>::ListNode) == 0xc, "");
static_assert(sizeof(FixedList<u32, 512>) == 0x1c18, "");
static_assert(sizeof(FixedList<void *, 1024>) == 0x4820, "");

} // namespace mtl
} // namespace mm
