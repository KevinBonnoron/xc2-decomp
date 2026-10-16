#include "mm_mtl/intrusive_list.h"

#include "mm/mm_std_base.h"

namespace mm {
namespace mtl {

IntrusiveListBase::IntrusiveListBase() : m_size(0) {}

int IntrusiveListBase::sizeTraverse() const {
  int count = -1;
  const IntrusiveListNodeBase *node = &m_head;
  do {
    node = node->m_next;
    count++;
  } while (node != &m_head);
  return count;
}

void IntrusiveListBase::linkNode(IntrusiveListNodeBase *node, IntrusiveListNodeBase *position) {
  MM_ASSERT(!node->intoNode());
  node->m_prev = position->m_prev;
  node->m_prev->m_next = node;
  position->m_prev = node;
  node->m_next = position;
}

void IntrusiveListBase::unlinkNode(IntrusiveListNodeBase *node) {
  MM_ASSERT(node->intoNode());
  node->m_prev->m_next = node->m_next;
  node->m_next->m_prev = node->m_prev;
  node->m_next = node;
  node->m_prev = node;
}

} // namespace mtl
} // namespace mm
