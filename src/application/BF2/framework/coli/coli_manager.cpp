#include "framework/coli/coli_manager.h"

#include "framework/coli/coli_object.h"
#include "framework/framework.h"
#include "framework/memory/framework_memory.h"
#include "idcoli/idcoli.h"
#include "mtl/alloc_handle.h"

namespace fw {

bool ColiManager::initialize() {
  Impl *colliders = &*impl;
  if (colliders->manager == nullptr) {
    // __LINE__ of the game: it is the line argument of the operator new.
#line 247
    colliders->manager =
        new (Framework::getAllocator(), 16, __FILE__, __LINE__) idcoli::IDColiManager(Framework::get()->scn, FrameworkMemory::getMem(5), 0x80000);
  }

  return true;
}

void ColiManager::postUpdate() {
  if (isFinalized()) {
    return;
  }

  impl->postUpdate();
}

void ColiManager::tail() {
  if (isFinalized()) {
    return;
  }

  idcoli::IDColiManager *manager = impl->manager;
  if (manager != nullptr) {
    manager->tail();
  }
}

void ColiManager::registObject(ColiObject *object) { impl->registObject(object); }

void ColiManager::removeObject(ColiObject *object) { impl->removeObject(object); }

void ColiManager::cleanupObject(ColiObject *object) { impl->sendRemoveEvent(object->userData.handle); }

const idcoli::IDColiManager *ColiManager::getInterface() const { return impl->manager; }

idcoli::IDColiManager *ColiManager::getInterface() { return impl->manager; }

void ColiManager::openDebugWindow() {
  idcoli::IDColiManager *manager = impl->manager;
  if (manager != nullptr) {
    manager->openDebugWindow(Framework::get()->winProc);
  }
}

ColiObject *ColiManager::getGroundObject() { return impl->groundObject; }

ColiObject *ColiManager::getObject(u32 handle) const {
  const PointerMap &objectMap = impl->objectMap;
  if (objectMap.isValid(handle)) {
    return static_cast<ColiObject *>(objectMap.getPtr(handle));
  }

  return nullptr;
}

bool ColiManager::isGblId(u32 id) {
  idcoli::IDColiManager *manager = impl->manager;
  if (manager == nullptr) {
    return false;
  }

  return manager->isGblId(id) == 0;
}

void ColiManager::setGblId(u32 id, bool isGlobal) {
  idcoli::IDColiManager *manager = impl->manager;
  if (manager != nullptr) {
    manager->setGblId(id, isGlobal);
  }
}

void *ColiManager::getGblIdTbl() {
  idcoli::IDColiManager *manager = impl->manager;
  if (manager != nullptr) {
    return manager->getGblIdTbl();
  }

  return nullptr;
}

} // namespace fw
