#include "framework/navi/navi_manager.h"

#include "framework/framework.h"
#include "framework/memory/framework_memory.h"
#include "mtl/alloc_handle.h"
#include "navi/nvmsh_manager.h"

namespace fw {

NaviManager::NaviManager() : unknown18(nullptr), unknown20(nullptr) {}

bool NaviManager::initialize() {
  if (unknown20 == nullptr) {
    // __LINE__ of the game: it is the line argument of the operator new.
#line 30
    unknown20 = new (Framework::getAllocator(), 16, __FILE__, __LINE__) navi::NvmshManager(Framework::get()->unknown58, FrameworkMemory::getMem(1));
  }

  return true;
}

bool NaviManager::finalize() {
  if (unknown20 != nullptr) {
    delete unknown20;
    unknown20 = nullptr;
  }

  return true;
}

bool NaviManager::createNaviMesh(void *data, const char *name) {
  if (unknown20 == nullptr) {
    return false;
  }

  unknown18 = data;
  unknown20->setupResource(data, name);
  return true;
}

void NaviManager::releaseNaviMesh() {
  if (unknown18 != nullptr && unknown20 != nullptr) {
    unknown18 = nullptr;
    unknown20->releaseResource();
  }
}

navi::NvmshAcObj *NaviManager::createObject() {
  if (unknown20 == nullptr) {
    return nullptr;
  }

  return unknown20->createObj();
}

void NaviManager::releaseObject(navi::NvmshAcObj *object) {
  if (object != nullptr && unknown20 != nullptr) {
    unknown20->releaseObj(object);
  }
}

void NaviManager::tail() {
  if (isFinalized()) {
    return;
  }

  if (unknown20 != nullptr) {
    unknown20->tail();
  }
}

void NaviManager::openDebugWindow() {
  if (unknown20 != nullptr) {
    unknown20->openDebugWindow(Framework::get()->unknown50);
  }
}

} // namespace fw
