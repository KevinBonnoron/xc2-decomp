#include "framework/manager_register.h"

#include "framework/manager_object.h"
#include "mm_mtl/algorithm.h"

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
        manager->unknown08 |= ManagerObject::FLAG_INITIALIZED;
      }
      isInitialized = false;
    }
  }

  return isInitialized;
}

void ManagerRegister::enterFinalizeApplet() {
  for (ManagerObject **it = unknown08.begin(); it != unknown08.end(); it++) {
    (*it)->enterFinalizeApplet();
  }
}

} // namespace fw
