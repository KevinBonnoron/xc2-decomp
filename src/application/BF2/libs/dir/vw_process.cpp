// No game string names this file: named after its header dir/vw_process.h.
#include "dir/vw_process.h"

namespace dir {

namespace {

// Inferred helper: destroys the processes marked deleted below a process; original name unknown.
void unknown001(VwProcess *process) {
  DoubleListNode *head = process->unknown38.m_doubleListNode;
  if (head != nullptr) {
    DoubleListNode *child = head->unknown10;
    while (child != nullptr) {
      DoubleListNode *next = nullptr;
      if (process->unknown38.m_doubleListNode != child) {
        next = child->unknown10;
      }
      VwProcess *childProcess = static_cast<VwProcess *>(child);
      if (childProcess->unknown59) {
        delete childProcess;
      } else {
        unknown001(childProcess);
      }
      child = next;
    }
  }
}

// Inferred helper: runs one step (Move or Draw) on a process and, recursively, on its children unless a skip flag or the deleted flag
// is set; original name unknown. The game has two separate functions (0x7100141ab4 for Move, 0x7100141b64 for Draw), the two
// instantiations; the copies written out twice match as well.
template <u8 VwProcess::*Skip, void (VwProcess::*Step)()> void unknown002(VwProcess *process) {
  if (!(process->*Skip) && !process->unknown59) {
    (process->*Step)();
    DoubleListNode *head = process->unknown38.m_doubleListNode;
    if (head != nullptr) {
      DoubleListNode *child = head->unknown10;
      while (child != nullptr) {
        unknown002<Skip, Step>(static_cast<VwProcess *>(child));
        DoubleListNode *next = nullptr;
        if (process->unknown38.m_doubleListNode != child) {
          next = child->unknown10;
        }
        child = next;
      }
    }
  }
}

} // namespace

VwProcess::VwProcess() : unknown58(0), unknown59(0), unknown5a(0), unknown5b(0), m_vwProcessMan(nullptr) {}

VwProcess::~VwProcess() {
  DoubleListNode *head = unknown38.m_doubleListNode;
  if (head != nullptr) {
    DoubleListNode *child = head->unknown10;
    while (child != nullptr) {
      DoubleListNode *next = nullptr;
      if (unknown38.m_doubleListNode != child) {
        next = child->unknown10;
      }
      delete static_cast<VwProcess *>(child);
      child = next;
    }
  }
  DoubleListHeader *header;
  if (m_childListNode != nullptr) {
    header = &m_childListNode->unknown38;
  } else if (unknown58) {
    header = &m_vwProcessMan->unknown30;
  } else {
    header = &m_vwProcessMan->unknown10;
  }
  header->Remove(this);
}

void VwProcess::Remove() {
  if (unknown58) {
    while (unknown38.m_doubleListNode != nullptr) {
      static_cast<VwProcess *>(unknown38.m_doubleListNode)->Remove();
    }
    Term();
    DoubleListHeader *header;
    if (m_childListNode != nullptr) {
      header = &m_childListNode->unknown38;
    } else {
      header = &m_vwProcessMan->unknown30;
    }
    header->Remove(this);
    m_vwProcessMan->unknown10.InsertEnd(this);
    m_childListNode = nullptr;
    unknown58 = 0;
  }
}

bool VwProcess::HasChild() const {
  if (unknown38.m_doubleListNode != nullptr) {
    return unknown38.m_doubleListNode->unknown10 != nullptr;
  }
  return false;
}

void VwProcess::Delete() { unknown59 = 1; }

VwProcessMan::VwProcessMan() : unknown08(0) {}

VwProcessMan::~VwProcessMan() { ; }

void VwProcessMan::Init() {
  if (!unknown08) {
    unknown08 = 1;
  }
}

void VwProcessMan::Term() {
  if (unknown08) {
    while (unknown30.m_doubleListNode != nullptr && unknown30.m_doubleListNode->unknown10 != nullptr) {
      static_cast<VwProcess *>(unknown30.m_doubleListNode->unknown10)->Remove();
    }
    while (unknown10.m_doubleListNode != nullptr && unknown10.m_doubleListNode->unknown10 != nullptr) {
      delete static_cast<VwProcess *>(unknown10.m_doubleListNode->unknown10);
    }
    unknown08 = 0;
  }
}

void VwProcessMan::Reset() {
  while (unknown30.m_doubleListNode != nullptr && unknown30.m_doubleListNode->unknown10 != nullptr) {
    static_cast<VwProcess *>(unknown30.m_doubleListNode->unknown10)->Remove();
  }
  while (unknown10.m_doubleListNode != nullptr && unknown10.m_doubleListNode->unknown10 != nullptr) {
    delete static_cast<VwProcess *>(unknown10.m_doubleListNode->unknown10);
  }
}

void VwProcessMan::Delete() {
  DoubleListNode *head = unknown10.m_doubleListNode;
  if (head != nullptr) {
    DoubleListNode *child = head->unknown10;
    while (child != nullptr) {
      DoubleListNode *next = nullptr;
      if (unknown10.m_doubleListNode != child) {
        next = child->unknown10;
      }
      delete static_cast<ChildListNode *>(child);
      child = next;
    }
  }
  head = unknown30.m_doubleListNode;
  if (head != nullptr) {
    DoubleListNode *child = head->unknown10;
    while (child != nullptr) {
      DoubleListNode *next = nullptr;
      if (unknown30.m_doubleListNode != child) {
        next = child->unknown10;
      }
      VwProcess *process = static_cast<VwProcess *>(child);
      if (process->unknown59) {
        delete process;
      } else {
        unknown001(process);
      }
      child = next;
    }
  }
}

// The loop over the registered root processes is written out in Delete, Move and Draw, as in the game (three loops, 0x71001419c0,
// 0x7100141a6c and 0x7100141b1c): a helper taking the list header (also as a template over the step) is not inlined, so Move
// becomes a 2 instruction tail call of it.
void VwProcessMan::Move() {
  DoubleListNode *head = unknown30.m_doubleListNode;
  if (head != nullptr) {
    DoubleListNode *child = head->unknown10;
    while (child != nullptr) {
      unknown002<&VwProcess::unknown5a, &VwProcess::Move>(static_cast<VwProcess *>(child));
      DoubleListNode *next = nullptr;
      if (unknown30.m_doubleListNode != child) {
        next = child->unknown10;
      }
      child = next;
    }
  }
}

void VwProcessMan::Draw() {
  DoubleListNode *head = unknown30.m_doubleListNode;
  if (head != nullptr) {
    DoubleListNode *child = head->unknown10;
    while (child != nullptr) {
      unknown002<&VwProcess::unknown5b, &VwProcess::Draw>(static_cast<VwProcess *>(child));
      DoubleListNode *next = nullptr;
      if (unknown30.m_doubleListNode != child) {
        next = child->unknown10;
      }
      child = next;
    }
  }
}

} // namespace dir
