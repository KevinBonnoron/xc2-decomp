#include "ptlib/particle_intrusive_list.h"

#include "mm/mm_std_base.h"

namespace ptlib {

IntrusiveListBase::IntrusiveListBase() {
  unknown00 = this;
  unknown08 = this;
  m_size = 0;
}

int IntrusiveListBase::sizeTraverse() const {
  int count = -1;
  const IntrusiveListNode *node = this;
  do {
    node = node->unknown00;
    count++;
  } while (node != this);
  return count;
}

void IntrusiveListBase::linkNode(IntrusiveListNode *node, IntrusiveListNode *next) {
#line 34
  MM_ASSERT(!node->intoNode());
  IntrusiveListNode *prev = next->unknown08;
  node->unknown08 = prev;
  prev->unknown00 = node;
  next->unknown08 = node;
  node->unknown00 = next;
}

void IntrusiveListBase::unlinkNode(IntrusiveListNode *node) {
#line 43
  MM_ASSERT(node->intoNode());
  node->unknown08->unknown00 = node->unknown00;
  node->unknown00->unknown08 = node->unknown08;
  node->unknown00 = node;
  node->unknown08 = node;
}

} // namespace ptlib
