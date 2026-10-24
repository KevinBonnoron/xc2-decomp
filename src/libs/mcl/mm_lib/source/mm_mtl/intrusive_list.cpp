#include "mm_mtl/intrusive_list.h"

#include "mm/mm_std_base.h"

namespace mm {
namespace mtl {

IntrusiveListBase::IntrusiveListBase() : m_size(0) {}

int IntrusiveListBase::sizeTraverse() const {
  int count = -1;
  const IntrusiveListNodeBase *node = &m_head;
  do {
    node = node->unknown00;
    count++;
  } while (node != &m_head);
  return count;
}

void IntrusiveListBase::linkNode(IntrusiveListNodeBase *node, IntrusiveListNodeBase *position) {
  MM_ASSERT(!node->intoNode());
  node->unknown08 = position->unknown08;
  node->unknown08->unknown00 = node;
  position->unknown08 = node;
  node->unknown00 = position;
}

void IntrusiveListBase::unlinkNode(IntrusiveListNodeBase *node) {
  MM_ASSERT(node->intoNode());
  node->unknown08->unknown00 = node->unknown00;
  node->unknown00->unknown08 = node->unknown08;
  node->unknown00 = node;
  node->unknown08 = node;
}

} // namespace mtl
} // namespace mm
