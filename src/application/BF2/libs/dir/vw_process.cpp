// No game string names this file: named after its header dir/vw_process.h.
#include "dir/vw_process.h"

namespace dir {

namespace {

// Inferred helper: destroys the processes marked deleted below a process; original name unknown.
void unknown001(VwProcess *process) {
  DoubleListNode *head = process->unknown38.unknown08;
  if (head != nullptr) {
    DoubleListNode *child = head->unknown10;
    while (child != nullptr) {
      DoubleListNode *next = nullptr;
      if (process->unknown38.unknown08 != child) {
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

} // namespace

VwProcess::VwProcess() : unknown58(0), unknown59(0), unknown5a(0), unknown5b(0), unknown60(nullptr) {}

VwProcess::~VwProcess() {
  DoubleListNode *head = unknown38.unknown08;
  if (head != nullptr) {
    DoubleListNode *child = head->unknown10;
    while (child != nullptr) {
      DoubleListNode *next = nullptr;
      if (unknown38.unknown08 != child) {
        next = child->unknown10;
      }
      delete static_cast<VwProcess *>(child);
      child = next;
    }
  }
  DoubleListHeader *header;
  if (unknown20 != nullptr) {
    header = &unknown20->unknown38;
  } else if (unknown58) {
    header = &unknown60->unknown30;
  } else {
    header = &unknown60->unknown10;
  }
  header->Remove(this);
}

void VwProcess::Remove() {
  if (unknown58) {
    while (unknown38.unknown08 != nullptr) {
      static_cast<VwProcess *>(unknown38.unknown08)->Remove();
    }
    Term();
    DoubleListHeader *header;
    if (unknown20 != nullptr) {
      header = &unknown20->unknown38;
    } else {
      header = &unknown60->unknown30;
    }
    header->Remove(this);
    unknown60->unknown10.InsertEnd(this);
    unknown20 = nullptr;
    unknown58 = 0;
  }
}

bool VwProcess::HasChild() const {
  if (unknown38.unknown08 != nullptr) {
    return unknown38.unknown08->unknown10 != nullptr;
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
    while (unknown30.unknown08 != nullptr && unknown30.unknown08->unknown10 != nullptr) {
      static_cast<VwProcess *>(unknown30.unknown08->unknown10)->Remove();
    }
    while (unknown10.unknown08 != nullptr && unknown10.unknown08->unknown10 != nullptr) {
      delete static_cast<VwProcess *>(unknown10.unknown08->unknown10);
    }
    unknown08 = 0;
  }
}

void VwProcessMan::Reset() {
  while (unknown30.unknown08 != nullptr && unknown30.unknown08->unknown10 != nullptr) {
    static_cast<VwProcess *>(unknown30.unknown08->unknown10)->Remove();
  }
  while (unknown10.unknown08 != nullptr && unknown10.unknown08->unknown10 != nullptr) {
    delete static_cast<VwProcess *>(unknown10.unknown08->unknown10);
  }
}

void VwProcessMan::Delete() {
  DoubleListNode *head = unknown10.unknown08;
  if (head != nullptr) {
    DoubleListNode *child = head->unknown10;
    while (child != nullptr) {
      DoubleListNode *next = nullptr;
      if (unknown10.unknown08 != child) {
        next = child->unknown10;
      }
      delete static_cast<ChildListNode *>(child);
      child = next;
    }
  }
  head = unknown30.unknown08;
  if (head != nullptr) {
    DoubleListNode *child = head->unknown10;
    while (child != nullptr) {
      DoubleListNode *next = nullptr;
      if (unknown30.unknown08 != child) {
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

} // namespace dir
