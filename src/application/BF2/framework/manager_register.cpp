#include "framework/manager_register.h"

#include "framework/manager_object.h"
#include "mm_mtl/algorithm.h"
#include "types.h"

namespace fw {

ManagerRegister::ManagerRegister() {}

ManagerRegister::~ManagerRegister() {}

void ManagerRegister::regist(ManagerObject *manager) {
  if (manager == nullptr) {
    return;
  }

  if (mm::mtl::find(unknown08.begin(), unknown08.end(), manager) != unknown08.end()) {
    return;
  }

  unknown08.push_back(manager);
}

void ManagerRegister::remove(ManagerObject *manager) {
  if (manager == nullptr) {
    return;
  }

  ManagerObject **found = mm::mtl::find(unknown08.begin(), unknown08.end(), manager);
  if (found != unknown08.end()) {
    unknown08.erase(found);
  }
}

bool ManagerRegister::initialize() {
  bool isInitialized = true;
  for (ManagerObject **it = unknown08.begin(); it != unknown08.end(); it++) {
    ManagerObject *manager = *it;
    if (!manager->isInitialized()) {
      if (manager->initialize()) {
        manager->unknown08 |= ManagerObject::FLAG_UNKNOWN_0;
      }
      isInitialized = false;
    }
  }

  return isInitialized;
}

bool ManagerRegister::finalize() {
  // The early return is the game's size test before the loop (cbz x24 at 0x710018c8cc); without it the loop gives 52 instructions against 55.
  if (unknown08.empty()) {
    return true;
  }

  // A u8 flag: the game (0x710018c8ac) returns it through tst w25, #0xff / cset, and a bool flag gives and #1 instead
  // (P1, decision of 2026-11-14).
  u8 isFinalized = 1;
  for (int i = unknown08.size(); i > 0;) {
    ManagerObject *manager = unknown08[--i];
    if (!manager->isFinalized()) {
      if (manager->finalize()) {
        manager->unknown08 |= ManagerObject::FLAG_UNKNOWN_1;
      }
      isFinalized = 0;
    }
  }

  return isFinalized;
}

void ManagerRegister::enterFinalizeApplet() {
  for (ManagerObject **it = unknown08.begin(); it != unknown08.end(); it++) {
    (*it)->enterFinalizeApplet();
  }
}

} // namespace fw
