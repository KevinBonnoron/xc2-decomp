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

  if (mm::mtl::find(managers.begin(), managers.end(), manager) != managers.end()) {
    return;
  }

  managers.push_back(manager);
}

void ManagerRegister::remove(ManagerObject *manager) {
  if (manager == nullptr) {
    return;
  }

  ManagerObject **found = mm::mtl::find(managers.begin(), managers.end(), manager);
  if (found != managers.end()) {
    managers.erase(found);
  }
}

bool ManagerRegister::initialize() {
  bool isInitialized = true;
  for (ManagerObject **it = managers.begin(); it != managers.end(); it++) {
    ManagerObject *manager = *it;
    if (!manager->isInitialized()) {
      if (manager->initialize()) {
        manager->flags |= ManagerObject::FLAG_INITIALIZED;
      }
      isInitialized = false;
    }
  }

  return isInitialized;
}

void ManagerRegister::enterFinalizeApplet() {
  for (ManagerObject **it = managers.begin(); it != managers.end(); it++) {
    (*it)->enterFinalizeApplet();
  }
}

} // namespace fw
