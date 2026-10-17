#include "event/object_manager.h"

#include <stddef.h>

#include "event/manager.h"
#include "event/memory_manager.h"
#include "event/object_party_list.h"
#include "event/skip_manager.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace event {
class ObjectChara;

u32 ObjectManager::getCharaCount() const {
  if (mCurrent == nullptr) {
    return 0;
  }
  return mCurrent->getCharaCount();
}

ObjectChara *ObjectManager::getChara(u32 index) { return getCurrent()->getChara(index); }

u32 ObjectManager::getCameraCount() const {
  if (mCurrent == nullptr) {
    return 0;
  }
  return mCurrent->getCameraCount();
}

ObjectCamera *ObjectManager::getCamera(u32 index) { return getCurrent()->getCamera(index); }

bool ObjectManager::isDisp() const { return (flags & FLAG_DISP) != 0; }

ObjectManager::ObjectManager() : mMode(0), flags(0), mSceneName("default") {}

void ObjectManager::stopEffect() {
  for (size_t i = 0; i < mScenes.size(); i++) {
    mScenes[i]->stopEffect();
  }
}

void ObjectManager::clear() {
  for (size_t i = 0; i < mScenes.size(); i++) {
    if (mScenes[i] != nullptr) {
      delete mScenes[i];
      mScenes[i] = nullptr;
    }
  }
  mScenes.clear();
  mMode = 0;
  mSceneName = "default";
  mNextSceneName = "";
  mCurrent = nullptr;
}

void ObjectManager::init() {
  mMode = 0;
  mNextSceneName = "";
  mCurrent = nullptr;
  mSceneName = "default";
  mm::mtl::Singleton<ObjectPartyList>::getPtr()->init();
}

void ObjectManager::setupScene() {
  mSceneName = Manager::get()->getSceneName();
  updateCurrent();
}

void ObjectManager::updateCurrent() {
  if (__builtin_strcmp(mSceneName.c_str(), mNextSceneName.c_str()) == 0) {
    return;
  }
  mCurrent = searchScene(mSceneName.c_str());
  if (mCurrent == nullptr) {
    mCurrent = createScene(mSceneName.c_str());
  }
  if (mCurrent != nullptr) {
    mNextSceneName = mSceneName;
  }
}

void ObjectManager::startScene() {
  mSceneName = Manager::get()->getSceneName();
  updateCurrent();
  if (mCurrent != nullptr) {
    mCurrent->startScene();
  }
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

ObjectChara *ObjectManager::createGfObjPcByWalkID(const char *name, u32 walkID, u32 param2) {
  bool isSkipFast = mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast();
  ObjectList *current = getCurrent();
  if (isSkipFast) {
    return current->createGhost(name);
  }
  return current->createGfObjPcByWalkID(name, walkID, param2);
}

ObjectChara *ObjectManager::createGfObjPcByBladeID(const char *name, u32 bladeID, u32 param2) {
  bool isSkipFast = mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast();
  ObjectList *current = getCurrent();
  if (isSkipFast) {
    return current->createGhost(name);
  }
  return current->createGfObjPcByBladeID(name, bladeID, param2);
}

ObjectChara *ObjectManager::createGfObjBlByWalkID(const char *name, u32 walkID, u32 param2) {
  bool isSkipFast = mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast();
  ObjectList *current = getCurrent();
  if (isSkipFast) {
    return current->createGhost(name);
  }
  return current->createGfObjBlByWalkID(name, walkID, param2);
}

ObjectChara *ObjectManager::createGfObjBladeByPcID(const char *name, u32 pcID, u32 param2) {
  bool isSkipFast = mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast();
  ObjectList *current = getCurrent();
  if (isSkipFast) {
    return current->createGhost(name);
  }
  return current->createGfObjBladeByPcID(name, pcID, param2);
}

ObjectChara *ObjectManager::createGfObjPartyIn(const char *name, CHARA_TYPE type, u32 id, u32 param3, u32 param4) {
  bool isSkipFast = mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast();
  ObjectList *current = getCurrent();
  if (isSkipFast) {
    return current->createGhost(name);
  }
  return current->createGfObjPartyIn(name, type, id, param3, param4);
}

ObjectChara *ObjectManager::createGfObj(const char *name, CHARA_TYPE type, u32 id, u32 param3, u32 param4) {
  bool isSkipFast = mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast();
  ObjectList *current = getCurrent();
  if (isSkipFast) {
    return current->createGhost(name);
  }
  return current->createGfObj(name, type, id, param3, param4);
}

ObjectChara *ObjectManager::createModel(const char *name, const char *model, u32 param2, u32 param3) {
  bool isSkipFast = mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast();
  ObjectList *current = getCurrent();
  if (isSkipFast) {
    return current->createGhost(name);
  }
  return current->createModel(name, model, param2, param3);
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

bool ObjectManager::isUsingEffect() {
  if (mCurrent == nullptr) {
    return false;
  }
  return mCurrent->isUsingEffect();
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

void ObjectManager::dump() { getCurrent()->dump(); }

ObjectList *ObjectManager::searchScene(const char *name) const {
  for (size_t i = 0; i < mScenes.size(); i++) {
    if (__builtin_strcmp(name, mScenes[i]->getName()) == 0) {
      return mScenes[i];
    }
  }
  return nullptr;
}

ObjectList *ObjectManager::createScene(const char *name) {
  ObjectList *scene =
      new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ObjectList(name, (mMode & MODE_CLONE) != 0);
  mScenes.push_back(scene);
  return scene;
}

} // namespace event
