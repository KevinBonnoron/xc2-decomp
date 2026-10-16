#include "framework/coli/coli_manager.h"

#include "framework/coli/coli_object.h"
#include "framework/framework.h"
#include "framework/memory/framework_memory.h"
#include "idcoli/idcoli.h"
#include "ml/work_cpu.h"
#include "mtl/alloc_handle.h"

namespace fw {

bool ColiManager::Impl::initialize() {
  if (manager == nullptr) {
    // __LINE__ of the game: it is the line argument of the operator new.
#line 247
    manager =
        new (Framework::getAllocator(), 16, __FILE__, __LINE__) idcoli::IDColiManager(Framework::get()->scn, FrameworkMemory::getMem(5), 0x80000);
  }

  return true;
}

bool ColiManager::Impl::finalize() {
  destroyContactTable();
  updateRelease();
  groundObject = nullptr;
  if (manager != nullptr) {
    delete manager;
    manager = nullptr;
  }

  return true;
}

void ColiManager::Impl::finalizeContact() { destroyContactTable(); }

void ColiManager::Impl::updateRelease() {
  for (mm::mtl::IntrusiveList<ColiObject>::iterator it = objects.begin(); it != objects.end();) {
    ColiObject *object = it.get();
    ++it;
    if (object != nullptr && object->getRefCount() == 1) {
      object->release();
    }
  }
}

void ColiManager::Impl::update() {
  if (manager != nullptr) {
    manager->update();
    frameCount++;
    updateContact();
    sendContactEvent();
  }

  for (mm::mtl::IntrusiveList<ColiObject>::iterator it = objects.begin(); it != objects.end(); ++it) {
    (*it).update();
  }
}

void ColiManager::Impl::postUpdate() {
  updateRelease();
  for (mm::mtl::IntrusiveList<ColiObject>::iterator it = objects.begin(); it != objects.end(); ++it) {
    (*it).postUpdate();
  }

  if (manager != nullptr) {
    manager->consistentUpdate();
  }
}

void ColiManager::Impl::tail() {
  if (manager != nullptr) {
    manager->tail();
  }
}

u32 ColiManager::Impl::getFrameCount() const { return ml::WorkCpu::getFrameCount(); }

ColiObject *ColiManager::Impl::getObject(u32 handle, bool isCheck) const {
  if (isCheck && !objectMap.isValid(handle)) {
    return nullptr;
  }

  return static_cast<ColiObject *>(objectMap.getPtr(handle));
}

bool ColiManager::Impl::isValidObject(u32 handle) { return objectMap.isValid(handle); }

void ColiManager::Impl::cleanupObject(ColiObject *object) { sendRemoveEvent(object->userData.handle); }

void ColiManager::Impl::openDebugWindow() {
  if (manager != nullptr) {
    manager->openDebugWindow(Framework::get()->winProc);
  }
}

bool ColiManager::Impl::isGblId(u32 id) {
  if (manager == nullptr) {
    return false;
  }

  return manager->isGblId(id) == 0;
}

void ColiManager::Impl::setGblId(u32 id, bool isGlobal) {
  if (manager != nullptr) {
    manager->setGblId(id, isGlobal);
  }
}

void *ColiManager::Impl::getGblIdTbl() {
  if (manager != nullptr) {
    return manager->getGblIdTbl();
  }

  return nullptr;
}

bool ColiManager::initialize() { return impl->initialize(); }

bool ColiManager::finalize() { return impl->finalize(); }

void ColiManager::update() {
  if (isFinalized()) {
    return;
  }

  impl->update();
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

  impl->tail();
}

void ColiManager::registObject(ColiObject *object) { impl->registObject(object); }

void ColiManager::removeObject(ColiObject *object) { impl->removeObject(object); }

void ColiManager::cleanupObject(ColiObject *object) { impl->cleanupObject(object); }

const idcoli::IDColiManager *ColiManager::getInterface() const { return impl->manager; }

idcoli::IDColiManager *ColiManager::getInterface() { return impl->manager; }

void ColiManager::openDebugWindow() { impl->openDebugWindow(); }

ColiObject *ColiManager::getGroundObject() { return impl->groundObject; }

ColiObject *ColiManager::getObject(u32 handle) const {
  const PointerMap &objectMap = impl->objectMap;
  if (objectMap.isValid(handle)) {
    return static_cast<ColiObject *>(objectMap.getPtr(handle));
  }

  return nullptr;
}

bool ColiManager::isGblId(u32 id) { return impl->isGblId(id); }

void ColiManager::setGblId(u32 id, bool isGlobal) { impl->setGblId(id, isGlobal); }

void *ColiManager::getGblIdTbl() { return impl->getGblIdTbl(); }

} // namespace fw
