// No game string names this file: named after the class ChildListNode of dir/dir_list.h.
#include "dir/dir_list.h"

namespace dir {

ChildListNode::ChildListNode() : unknown20(nullptr) {}

void ChildListNode::InitVariable() {
  unknown20 = nullptr;
  unknown38.unknown08 = nullptr;
}

void ChildListNode::Reset() {
  DoubleListNode::Reset();
  InitVariable();
}

} // namespace dir
