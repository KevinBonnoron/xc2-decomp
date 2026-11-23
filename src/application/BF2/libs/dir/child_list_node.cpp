// No game string names this file: named after the class ChildListNode of dir/dir_list.h.
#include "dir/dir_list.h"

namespace dir {

ChildListNode::ChildListNode() : m_childListNode(nullptr) {}

void ChildListNode::InitVariable() {
  m_childListNode = nullptr;
  unknown38.m_doubleListNode = nullptr;
}

void ChildListNode::Reset() {
  DoubleListNode::Reset();
  InitVariable();
}

} // namespace dir
