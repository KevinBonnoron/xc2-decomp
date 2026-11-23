// No game string names this file: named after its header dir/dir_list.h.
#include "dir/dir_list.h"

namespace dir {

SingleListNode::SingleListNode() : m_singleListNode(nullptr), unknown10(0), unknown14(-1) {}

void SingleListNode::InitVariable() {
  m_singleListNode = nullptr;
  unknown10 = 0;
  unknown14 = -1;
}

void SingleListNode::Reset() { InitVariable(); }

SingleListNode *SingleListHeader::InsertTop(SingleListNode *node) {
  if (node != nullptr) {
    if (m_singleListNode == nullptr) {
      m_singleListNode = node;
      node->m_singleListNode = node;
      return node;
    }
    node->m_singleListNode = m_singleListNode->m_singleListNode;
    m_singleListNode->m_singleListNode = node;
  }
  return node;
}

SingleListNode *SingleListHeader::InsertEnd(SingleListNode *node) {
  if (node != nullptr) {
    if (m_singleListNode == nullptr) {
      m_singleListNode = node;
      node->m_singleListNode = node;
    } else {
      node->m_singleListNode = m_singleListNode->m_singleListNode;
      m_singleListNode->m_singleListNode = node;
    }
    m_singleListNode = node;
  }
  return node;
}

SingleListNode *SingleListHeader::InsertNext(SingleListNode *position, SingleListNode *node) {
  if (position != nullptr && node != nullptr) {
    SingleListNode *next = position->m_singleListNode;
    if (next == nullptr) {
      return nullptr;
    }
    SingleListNode *head = m_singleListNode;
    if (head == nullptr) {
      m_singleListNode = node;
      node->m_singleListNode = node;
      return nullptr;
    }
    SingleListNode *current = head->m_singleListNode;
    SingleListNode *prev = head;
    if (current == nullptr) {
      return nullptr;
    }
    while (current != next) {
      if (head == current) {
        return nullptr;
      }
      prev = current;
      current = current->m_singleListNode;
      if (current == nullptr) {
        return nullptr;
      }
    }
    prev->m_singleListNode = node;
    node->m_singleListNode = next;
    if (m_singleListNode == position) {
      m_singleListNode = node;
    }
    return node;
  }
  return nullptr;
}

SingleListNode *SingleListHeader::Remove(SingleListNode *node) {
  if (node != nullptr) {
    SingleListNode *head = m_singleListNode;
    if (head != nullptr) {
      SingleListNode *first = head->m_singleListNode;
      SingleListNode *current = first;
      if (first == node) {
        if (head == node) {
          m_singleListNode = nullptr;
        } else {
          head->m_singleListNode = node->m_singleListNode;
        }
      } else {
        while (current->m_singleListNode != node) {
          current = current->m_singleListNode;
          if (current == first) {
            return nullptr;
          }
        }
        current->m_singleListNode = node->m_singleListNode;
        if (m_singleListNode == node) {
          m_singleListNode = current;
        }
      }
      node->m_singleListNode = nullptr;
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
    DoubleListNode *head = m_doubleListNode;
    if (head == nullptr) {
      m_doubleListNode = node;
      node->unknown08 = node;
      node->unknown10 = node;
      return node;
    }
    DoubleListNode *tail = head->unknown10;
    node->unknown08 = head;
    node->unknown10 = tail;
    tail->unknown08 = node;
    m_doubleListNode->unknown10 = node;
  }
  return node;
}

DoubleListNode *DoubleListHeader::InsertEnd(DoubleListNode *node) {
  if (node != nullptr) {
    DoubleListNode *head = m_doubleListNode;
    if (head == nullptr) {
      m_doubleListNode = node;
      node->unknown08 = node;
      node->unknown10 = node;
    } else {
      DoubleListNode *tail = head->unknown10;
      node->unknown08 = head;
      node->unknown10 = tail;
      tail->unknown08 = node;
      m_doubleListNode->unknown10 = node;
    }
    m_doubleListNode = node;
  }
  return node;
}

DoubleListNode *DoubleListHeader::InsertPrev(DoubleListNode *position, DoubleListNode *node) {
  DoubleListNode *result = nullptr;
  if (position != nullptr && node != nullptr) {
    if (m_doubleListNode == nullptr) {
      m_doubleListNode = node;
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
    if (m_doubleListNode == nullptr) {
      m_doubleListNode = node;
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
    if (m_doubleListNode == position) {
      m_doubleListNode = node;
    }
  }
  return result;
}

DoubleListNode *DoubleListHeader::Remove(DoubleListNode *node) {
  if (node != nullptr) {
    DoubleListNode *head = m_doubleListNode;
    if (head != nullptr) {
      if (head == head->unknown10) {
        if (head != node) {
          return nullptr;
        }
        m_doubleListNode = nullptr;
      } else {
        if (node->unknown08 != nullptr) {
          node->unknown08->unknown10 = node->unknown10;
        }
        if (node->unknown10 != nullptr) {
          node->unknown10->unknown08 = node->unknown08;
        }
        if (m_doubleListNode == node) {
          m_doubleListNode = node->unknown08;
        }
      }
      node->unknown08 = nullptr;
      node->unknown10 = nullptr;
    }
  }
  return node;
}

} // namespace dir
