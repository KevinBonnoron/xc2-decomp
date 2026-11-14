// No game string names this file: named after its header dir/dir_list.h.
#include "dir/dir_list.h"

namespace dir {

SingleListNode::SingleListNode() : unknown08(nullptr), unknown10(0), unknown14(-1) {}

void SingleListNode::InitVariable() {
  unknown08 = nullptr;
  unknown10 = 0;
  unknown14 = -1;
}

void SingleListNode::Reset() { InitVariable(); }

SingleListNode *SingleListHeader::InsertTop(SingleListNode *node) {
  if (node != nullptr) {
    if (unknown08 == nullptr) {
      unknown08 = node;
      node->unknown08 = node;
      return node;
    }
    node->unknown08 = unknown08->unknown08;
    unknown08->unknown08 = node;
  }
  return node;
}

SingleListNode *SingleListHeader::InsertEnd(SingleListNode *node) {
  if (node != nullptr) {
    if (unknown08 == nullptr) {
      unknown08 = node;
      node->unknown08 = node;
    } else {
      node->unknown08 = unknown08->unknown08;
      unknown08->unknown08 = node;
    }
    unknown08 = node;
  }
  return node;
}

SingleListNode *SingleListHeader::InsertNext(SingleListNode *position, SingleListNode *node) {
  if (position != nullptr && node != nullptr) {
    SingleListNode *next = position->unknown08;
    if (next == nullptr) {
      return nullptr;
    }
    SingleListNode *head = unknown08;
    if (head == nullptr) {
      unknown08 = node;
      node->unknown08 = node;
      return nullptr;
    }
    SingleListNode *current = head->unknown08;
    SingleListNode *prev = head;
    if (current == nullptr) {
      return nullptr;
    }
    while (current != next) {
      if (head == current) {
        return nullptr;
      }
      prev = current;
      current = current->unknown08;
      if (current == nullptr) {
        return nullptr;
      }
    }
    prev->unknown08 = node;
    node->unknown08 = next;
    if (unknown08 == position) {
      unknown08 = node;
    }
    return node;
  }
  return nullptr;
}

SingleListNode *SingleListHeader::Remove(SingleListNode *node) {
  if (node != nullptr) {
    SingleListNode *head = unknown08;
    if (head != nullptr) {
      SingleListNode *first = head->unknown08;
      SingleListNode *current = first;
      if (first == node) {
        if (head == node) {
          unknown08 = nullptr;
        } else {
          head->unknown08 = node->unknown08;
        }
      } else {
        while (current->unknown08 != node) {
          current = current->unknown08;
          if (current == first) {
            return nullptr;
          }
        }
        current->unknown08 = node->unknown08;
        if (unknown08 == node) {
          unknown08 = current;
        }
      }
      node->unknown08 = nullptr;
    }
  }
  return node;
}

DoubleListNode::DoubleListNode() : unknown08(nullptr), unknown10(nullptr), unknown18(0), unknown1c(-1) {}

void DoubleListNode::InitVariable() {
  unknown18 = 0;
  unknown1c = -1;
  unknown08 = nullptr;
  unknown10 = nullptr;
}

void DoubleListNode::Reset() { InitVariable(); }

DoubleListNode *DoubleListHeader::InsertTop(DoubleListNode *node) {
  if (node != nullptr) {
    DoubleListNode *head = unknown08;
    if (head == nullptr) {
      unknown08 = node;
      node->unknown08 = node;
      node->unknown10 = node;
      return node;
    }
    DoubleListNode *tail = head->unknown10;
    node->unknown08 = head;
    node->unknown10 = tail;
    tail->unknown08 = node;
    unknown08->unknown10 = node;
  }
  return node;
}

DoubleListNode *DoubleListHeader::InsertEnd(DoubleListNode *node) {
  if (node != nullptr) {
    DoubleListNode *head = unknown08;
    if (head == nullptr) {
      unknown08 = node;
      node->unknown08 = node;
      node->unknown10 = node;
    } else {
      DoubleListNode *tail = head->unknown10;
      node->unknown08 = head;
      node->unknown10 = tail;
      tail->unknown08 = node;
      unknown08->unknown10 = node;
    }
    unknown08 = node;
  }
  return node;
}

DoubleListNode *DoubleListHeader::InsertPrev(DoubleListNode *position, DoubleListNode *node) {
  DoubleListNode *result = nullptr;
  if (position != nullptr && node != nullptr) {
    if (unknown08 == nullptr) {
      unknown08 = node;
      node->unknown08 = node;
      node->unknown10 = node;
      return node;
    }
    DoubleListNode *next = position->unknown08;
    node->unknown08 = next;
    node->unknown10 = position;
    position->unknown08 = node;
    next->unknown10 = node;
    result = node;
  }
  return result;
}

DoubleListNode *DoubleListHeader::InsertNext(DoubleListNode *position, DoubleListNode *node) {
  DoubleListNode *result = nullptr;
  if (position != nullptr && node != nullptr) {
    DoubleListNode *prev = position->unknown10;
    if (prev == nullptr) {
      return nullptr;
    }
    if (unknown08 == nullptr) {
      unknown08 = node;
      node->unknown08 = node;
      node->unknown10 = node;
    } else {
      DoubleListNode *next = prev->unknown08;
      node->unknown08 = next;
      node->unknown10 = prev;
      prev->unknown08 = node;
      next->unknown10 = node;
    }
    result = node;
    if (unknown08 == position) {
      unknown08 = node;
    }
  }
  return result;
}

DoubleListNode *DoubleListHeader::Remove(DoubleListNode *node) {
  if (node != nullptr) {
    DoubleListNode *head = unknown08;
    if (head != nullptr) {
      if (head == head->unknown10) {
        if (head != node) {
          return nullptr;
        }
        unknown08 = nullptr;
      } else {
        if (node->unknown08 != nullptr) {
          node->unknown08->unknown10 = node->unknown10;
        }
        if (node->unknown10 != nullptr) {
          node->unknown10->unknown08 = node->unknown08;
        }
        if (unknown08 == node) {
          unknown08 = node->unknown08;
        }
      }
      node->unknown08 = nullptr;
      node->unknown10 = nullptr;
    }
  }
  return node;
}

} // namespace dir
