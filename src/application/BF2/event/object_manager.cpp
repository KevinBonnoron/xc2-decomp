#include "event/object_manager.h"

#include <stddef.h>

#include "event/chara_manager.h"
#include "event/effect_manager.h"
#include "event/light_manager.h"
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
  if (m_objectList == nullptr) {
    return 0;
  }
  return m_objectList->getCharaCount();
}

ObjectChara *ObjectManager::getChara(u32 index) { return getCurrent()->getChara(index); }

u32 ObjectManager::getCameraCount() const {
  if (m_objectList == nullptr) {
    return 0;
  }
  return m_objectList->getCameraCount();
}

ObjectCamera *ObjectManager::getCamera(u32 index) { return getCurrent()->getCamera(index); }

ObjectChara *ObjectManager::searchByHandle(gf::GF_OBJ_HANDLE *handle) {
  if (m_objectList == nullptr)
    return nullptr;
  return m_objectList->searchByHandle(handle);
}

ObjectChara *ObjectManager::searchByID(u32 type, u32 id) {
  if (m_objectList == nullptr)
    return nullptr;
  return m_objectList->searchByID(type, id);
}

Object *ObjectManager::searchByName(const char *name) {
  ObjectList *current = m_objectList;
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

bool ObjectManager::isDisp() const { return (unknown14 & FLAG_UNKNOWN_0) != 0; }

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
  m_objectList = nullptr;
}

void ObjectManager::init() {
  unknown10 = 0;
  unknowne4 = "";
  m_objectList = nullptr;
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
  m_objectList = searchScene(unknowna0.c_str());
  if (m_objectList == nullptr) {
    m_objectList = createScene(unknowna0.c_str());
  }
  if (m_objectList != nullptr) {
    unknowne4 = unknowna0;
  }
}

void ObjectManager::startScene() {
  unknowna0 = Manager::get()->getSceneName();
  updateCurrent();
  if (m_objectList != nullptr) {
    m_objectList->startScene();
  }
}

void ObjectManager::startPage() {
  if (m_objectList != nullptr) {
    m_objectList->startPage();
  }
}

void ObjectManager::endScene() {
  if (m_objectList != nullptr) {
    m_objectList->endScene();
  }
}

void ObjectManager::update() {
  if (m_objectList != nullptr) {
    m_objectList->update();
  }
}

void ObjectManager::render() {
  if (!isDisp() && !mm::mtl::Singleton<CharaManager>::getPtr()->isCharaDisp() && !mm::mtl::Singleton<CharaManager>::getPtr()->isFacialDisp() &&
      !mm::mtl::Singleton<CharaManager>::getPtr()->isBoneDisp() && !mm::mtl::Singleton<EffectManager>::getPtr()->isEffectDisp() && !mm::mtl::Singleton<LightManager>::getPtr()->isLightDisp()) {
    return;
  }
  if (m_objectList != nullptr) {
    m_objectList->render();
  }
}

void ObjectManager::tail() {
  if (m_objectList != nullptr) {
    m_objectList->tail();
  }
}

bool ObjectManager::isLoading() const {
  if (m_objectList != nullptr) {
    return m_objectList->isLoading();
  }
  return false;
}

ObjectList *ObjectManager::getCurrent() {
  updateCurrent();
  return m_objectList;
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
  if (m_objectList == nullptr) {
    return 0;
  }
  return m_objectList->getLightCount();
}

bool ObjectManager::isUsingEffect() {
  if (m_objectList == nullptr) {
    return false;
  }
  return m_objectList->isUsingEffect();
}

void ObjectManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_UNKNOWN_4:
    unknown10 = 0;
    unknowna0 = "default";
    unknowne4 = "";
    m_objectList = nullptr;
    mm::mtl::Singleton<ObjectPartyList>::getPtr()->init();
    break;
  case MSG_TYPE_UNKNOWN_5:
    setupScene();
    break;
  case MSG_TYPE_UNKNOWN_7:
    startScene();
    break;
  case MSG_TYPE_UNKNOWN_8:
    startPage();
    break;
  case MSG_TYPE_UNKNOWN_10:
    endScene();
    break;
  case MSG_TYPE_UNKNOWN_12:
    clear();
    break;
  case MSG_TYPE_UNKNOWN_14:
    update();
    break;
  case MSG_TYPE_UNKNOWN_16:
    render();
    break;
  case MSG_TYPE_UNKNOWN_18:
    tail();
    break;
  default:
    break;
  }
}

void ObjectManager::setActivePath(const char *path) { getCurrent()->setActivePath(path); }

Object *ObjectManager::searchByPath(const char *path) {
  if (m_objectList == nullptr) {
    return nullptr;
  }
  return m_objectList->searchByPath(path);
}

bool ObjectManager::getPathByObj(mm::mtl::FixStr<256> &path, const Object *object) {
  if (m_objectList == nullptr) {
    return false;
  }
  return m_objectList->getPathByObj(path, object);
}

void ObjectManager::listupObject(mm::mtl::FixedVector<u32, 256> &list, u32 type, bool isAppend) {
  if (m_objectList != nullptr) {
    m_objectList->listupObject(list, type, isAppend);
  }
}

void ObjectManager::setCloneMode(bool isCloneMode) {
  if (isCloneMode) {
    unknown10 |= MODE_UNKNOWN_0;
  } else {
    unknown10 &= ~MODE_UNKNOWN_0;
  }
}

void ObjectManager::setDisp(bool isDisp) {
  if (isDisp) {
    unknown14 |= FLAG_UNKNOWN_0;
  } else {
    unknown14 &= ~FLAG_UNKNOWN_0;
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
  ObjectList *scene = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ObjectList(name, (unknown10 & MODE_UNKNOWN_0) != 0);
  unknown18.push_back(scene);
  return scene;
}

} // namespace event
