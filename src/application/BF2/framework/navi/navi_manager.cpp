#include "framework/navi/navi_manager.h"

#include "framework/framework.h"
#include "framework/memory/framework_memory.h"
#include "mtl/alloc_handle.h"
#include "navi/nvmsh_manager.h"

namespace fw {

NaviManager::NaviManager() : naviMeshData(nullptr), manager(nullptr) {}

bool NaviManager::initialize() {
  if (manager == nullptr) {
    // __LINE__ of the game: it is the line argument of the operator new.
#line 30
    manager = new (Framework::getAllocator(), 16, __FILE__, __LINE__) navi::NvmshManager(Framework::get()->scn, FrameworkMemory::getMem(1));
  }

  return true;
}

bool NaviManager::finalize() {
  if (manager != nullptr) {
    delete manager;
    manager = nullptr;
  }

  return true;
}

bool NaviManager::createNaviMesh(void *data, const char *name) {
  if (manager == nullptr) {
    return false;
  }

  naviMeshData = data;
  manager->setupResource(data, name);
  return true;
}

void NaviManager::releaseNaviMesh() {
  if (naviMeshData != nullptr && manager != nullptr) {
    naviMeshData = nullptr;
    manager->releaseResource();
  }
}

navi::NvmshAcObj *NaviManager::createObject() {
  if (manager == nullptr) {
    return nullptr;
  }

  return manager->createObj();
}

void NaviManager::releaseObject(navi::NvmshAcObj *object) {
  if (object != nullptr && manager != nullptr) {
    manager->releaseObj(object);
  }
}

void NaviManager::tail() {
  if (isFinalized()) {
    return;
  }

  if (manager != nullptr) {
    manager->tail();
  }
}

void NaviManager::openDebugWindow() {
  if (manager != nullptr) {
    manager->openDebugWindow(Framework::get()->winProc);
  }
}

} // namespace fw
