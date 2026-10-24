#include "event/object_manager.h"

#include <stddef.h>

#include "event/manager.h"
#include "event/memory_manager.h"
#include "event/object_party_list.h"
#include "event/object_tree.h"
#include "event/skip_manager.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace event {
class ObjectChara;

u32 ObjectManager::getCharaCount() const {
  if (unknown128 == nullptr) {
    return 0;
  }
  return unknown128->getCharaCount();
}

ObjectChara *ObjectManager::getChara(u32 index) { return getCurrent()->getChara(index); }

u32 ObjectManager::getCameraCount() const {
  if (unknown128 == nullptr) {
    return 0;
  }
  return unknown128->getCameraCount();
}

ObjectCamera *ObjectManager::getCamera(u32 index) { return getCurrent()->getCamera(index); }

ObjectChara *ObjectManager::searchByHandle(gf::GF_OBJ_HANDLE *handle) {
  if (unknown128 == nullptr)
    return nullptr;
  return unknown128->searchByHandle(handle);
}

ObjectChara *ObjectManager::searchByID(u32 type, u32 id) {
  if (unknown128 == nullptr)
    return nullptr;
  return unknown128->searchByID(type, id);
}

Object *ObjectManager::searchByName(const char *name) {
  ObjectList *current = unknown128;
  if (current == nullptr)
    return nullptr;
  Object *root = current->unknown50;
  if (root == nullptr)
    return nullptr;
  Object *found = ObjectList::searchByNameSub(root, name);
  if (found == nullptr || found == root || found == current->unknown58 || found == current->unknown60 || found == current->unknown68 || found == current->unknown70)
    return nullptr;
  return found;
}

bool ObjectManager::isDisp() const { return (unknown14 & FLAG_DISP) != 0; }

ObjectManager::ObjectManager() : unknown10(0), unknown14(0), unknowna0("default") {}

void ObjectManager::stopEffect() {
  for (size_t i = 0; i < unknown18.size(); i++) {
    unknown18[i]->stopEffect();
  }
}

void ObjectManager::clear() {
  for (size_t i = 0; i < unknown18.size(); i++) {
    if (unknown18[i] != nullptr) {
      delete unknown18[i];
      unknown18[i] = nullptr;
    }
  }
  unknown18.clear();
  unknown10 = 0;
  unknowna0 = "default";
  unknowne4 = "";
  unknown128 = nullptr;
}

void ObjectManager::init() {
  unknown10 = 0;
  unknowne4 = "";
  unknown128 = nullptr;
  unknowna0 = "default";
  mm::mtl::Singleton<ObjectPartyList>::getPtr()->init();
}

void ObjectManager::setupScene() {
  unknowna0 = Manager::get()->getSceneName();
  updateCurrent();
}

void ObjectManager::updateCurrent() {
  if (__builtin_strcmp(unknowna0.c_str(), unknowne4.c_str()) == 0) {
    return;
  }
  unknown128 = searchScene(unknowna0.c_str());
  if (unknown128 == nullptr) {
    unknown128 = createScene(unknowna0.c_str());
  }
  if (unknown128 != nullptr) {
    unknowne4 = unknowna0;
  }
}

void ObjectManager::startScene() {
  unknowna0 = Manager::get()->getSceneName();
  updateCurrent();
  if (unknown128 != nullptr) {
    unknown128->startScene();
  }
}

void ObjectManager::startPage() {
  if (unknown128 != nullptr) {
    unknown128->startPage();
  }
}

void ObjectManager::endScene() {
  if (unknown128 != nullptr) {
    unknown128->endScene();
  }
}

void ObjectManager::update() {
  if (unknown128 != nullptr) {
    unknown128->update();
  }
}

void ObjectManager::tail() {
  if (unknown128 != nullptr) {
    unknown128->tail();
  }
}

bool ObjectManager::isLoading() const {
  if (unknown128 != nullptr) {
    return unknown128->isLoading();
  }
  return false;
}

ObjectList *ObjectManager::getCurrent() {
  updateCurrent();
  return unknown128;
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
  if (unknown128 == nullptr) {
    return 0;
  }
  return unknown128->getLightCount();
}

bool ObjectManager::isUsingEffect() {
  if (unknown128 == nullptr) {
    return false;
  }
  return unknown128->isUsingEffect();
}

void ObjectManager::setActivePath(const char *path) { getCurrent()->setActivePath(path); }

Object *ObjectManager::searchByPath(const char *path) {
  if (unknown128 == nullptr) {
    return nullptr;
  }
  return unknown128->searchByPath(path);
}

bool ObjectManager::getPathByObj(mm::mtl::FixStr<256> &path, const Object *object) {
  if (unknown128 == nullptr) {
    return false;
  }
  return unknown128->getPathByObj(path, object);
}

void ObjectManager::listupObject(mm::mtl::FixedVector<u32, 256> &list, u32 type, bool isAppend) {
  if (unknown128 != nullptr) {
    unknown128->listupObject(list, type, isAppend);
  }
}

void ObjectManager::setCloneMode(bool isCloneMode) {
  if (isCloneMode) {
    unknown10 |= MODE_CLONE;
  } else {
    unknown10 &= ~MODE_CLONE;
  }
}

void ObjectManager::setDisp(bool isDisp) {
  if (isDisp) {
    unknown14 |= FLAG_DISP;
  } else {
    unknown14 &= ~FLAG_DISP;
  }
}

void ObjectManager::dump() { getCurrent()->dump(); }

ObjectList *ObjectManager::searchScene(const char *name) const {
  for (size_t i = 0; i < unknown18.size(); i++) {
    if (__builtin_strcmp(name, unknown18[i]->getName()) == 0) {
      return unknown18[i];
    }
  }
  return nullptr;
}

ObjectList *ObjectManager::createScene(const char *name) {
  ObjectList *scene = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ObjectList(name, (unknown10 & MODE_CLONE) != 0);
  unknown18.push_back(scene);
  return scene;
}

} // namespace event
