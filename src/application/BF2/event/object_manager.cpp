#include "event/object_manager.h"

#include "event/memory_manager.h"
#include "event/object_party_list.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace event {

ObjectManager::ObjectManager() : mMode(0), flags(0), mSceneName("default") {}

void ObjectManager::init() {
  mMode = 0;
  mNextSceneName = "";
  mCurrent = nullptr;
  mSceneName = "default";
  mm::mtl::Singleton<ObjectPartyList>::getPtr()->init();
}

void ObjectManager::startPage() {
  if (mCurrent != nullptr) {
    mCurrent->startPage();
  }
}

void ObjectManager::endScene() {
  if (mCurrent != nullptr) {
    mCurrent->endScene();
  }
}

void ObjectManager::update() {
  if (mCurrent != nullptr) {
    mCurrent->update();
  }
}

void ObjectManager::tail() {
  if (mCurrent != nullptr) {
    mCurrent->tail();
  }
}

bool ObjectManager::isLoading() const {
  if (mCurrent != nullptr) {
    return mCurrent->isLoading();
  }
  return false;
}

ObjectList *ObjectManager::getCurrent() {
  updateCurrent();
  return mCurrent;
}

ObjectCamera *ObjectManager::createCamera(const char *name, u32 id) { return getCurrent()->createCamera(name, id); }

ObjectEffect *ObjectManager::createEffect(const char *name) { return getCurrent()->createEffect(name); }

ObjectLight *ObjectManager::createLight(const char *name, u32 id) { return getCurrent()->createLight(name, id); }

ObjectLight *ObjectManager::getLight(u32 index) { return getCurrent()->getLight(index); }

u32 ObjectManager::getLightCount() const {
  if (mCurrent == nullptr) {
    return 0;
  }
  return mCurrent->getLightCount();
}

void ObjectManager::setActivePath(const char *path) { getCurrent()->setActivePath(path); }

Object *ObjectManager::searchByPath(const char *path) {
  if (mCurrent == nullptr) {
    return nullptr;
  }
  return mCurrent->searchByPath(path);
}

bool ObjectManager::getPathByObj(mm::mtl::FixStr<256> &path, const Object *object) {
  if (mCurrent == nullptr) {
    return false;
  }
  return mCurrent->getPathByObj(path, object);
}

void ObjectManager::listupObject(mm::mtl::FixedVector<u32, 256> &list, u32 type, bool isAppend) {
  if (mCurrent != nullptr) {
    mCurrent->listupObject(list, type, isAppend);
  }
}

void ObjectManager::setCloneMode(bool isCloneMode) {
  if (isCloneMode) {
    mMode |= MODE_CLONE;
  } else {
    mMode &= ~MODE_CLONE;
  }
}

void ObjectManager::setDisp(bool isDisp) {
  if (isDisp) {
    flags |= FLAG_DISP;
  } else {
    flags &= ~FLAG_DISP;
  }
}

ObjectList *ObjectManager::createScene(const char *name) {
  ObjectList *scene =
      new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ObjectList(name, (mMode & MODE_CLONE) != 0);
  mScenes.push_back(scene);
  return scene;
}

} // namespace event
