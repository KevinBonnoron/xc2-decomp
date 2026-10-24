#include "event/object_list.h"

#include <string.h>

#include "event/bou_manager.h"
#include "event/memory_manager.h"
#include "event/object_camera.h"
#include "event/object_chara.h"
#include "event/object_effect.h"
#include "event/object_light.h"
#include "event/object_party_list.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_driver.h"
#include "gf/game/gf_game_manager.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "mm_math/mm_col4.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace event {

const char ObjectList::ROOT[64] = "\x83\x8b\x81\x5b\x83\x67";
const char ObjectList::CHR_TREE[64] = "\x83\x4c\x83\x83\x83\x89\x83\x63\x83\x8a\x81\x5b";
const char ObjectList::CAM_TREE[64] = "\x83\x4a\x83\x81\x83\x89\x83\x63\x83\x8a\x81\x5b";
const char ObjectList::EFF_TREE[64] = "\x83\x47\x83\x74\x83\x46\x83\x4e\x83\x67\x83\x63\x83\x8a\x81\x5b";
const char ObjectList::LGT_TREE[64] = "\x83\x89\x83\x43\x83\x67\x83\x63\x83\x8a\x81\x5b";

ObjectList::ObjectList(const char *name, bool isCloneMode)
    : unknown08(0), unknown0c(name), unknown50(nullptr), unknown58(nullptr), unknown60(nullptr), unknown68(nullptr), unknown70(nullptr), unknown78(nullptr), unknown80(nullptr), unknown88(0),
      unknown8c(0), unknown90(0), unknown94(0) {
  if (isCloneMode) {
    unknown08 |= FLAG_CLONE_MODE;
  } else {
    unknown08 &= ~FLAG_CLONE_MODE;
  }
  unknown50 = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ObjectTree(ROOT);
  unknown58 = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ObjectTree(CHR_TREE);
  unknown50->addChild(unknown58);
  unknown88 = 0;
  unknown60 = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ObjectTree(CAM_TREE);
  unknown50->addChild(unknown60);
  unknown8c = 0;
  unknown68 = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ObjectTree(EFF_TREE);
  unknown50->addChild(unknown68);
  unknown90 = 0;
  unknown70 = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ObjectTree(LGT_TREE);
  unknown50->addChild(unknown70);
  unknown94 = 0;
  unknown78 = nullptr;
  unknown80 = nullptr;
}

ObjectList::~ObjectList() {
  for (Object *object = unknown58->getChild(); object != nullptr; object = object->getNext()) {
  }
  for (Object *object = unknown60->getChild(); object != nullptr; object = object->getNext()) {
  }
  for (Object *object = unknown68->getChild(); object != nullptr; object = object->getNext()) {
  }
  if (unknown50 != nullptr) {
    clearSub(unknown50);
  }
  if (unknown68 != nullptr) {
    clrChilds(unknown68);
  }
  unknown90 = 0;
  if (unknown58 != nullptr) {
    clrChilds(unknown58);
  }
  unknown88 = 0;
  if (unknown60 != nullptr) {
    clrChilds(unknown60);
  }
  unknown8c = 0;
  if (unknown70 != nullptr) {
    clrChilds(unknown70);
  }
  unknown94 = 0;
  if (unknown50 != nullptr) {
    unknown50->setChild(nullptr);
  }
  if (unknown70 != nullptr) {
    delete unknown70;
    unknown70 = nullptr;
  }
  if (unknown68 != nullptr) {
    delete unknown68;
    unknown68 = nullptr;
  }
  if (unknown60 != nullptr) {
    delete unknown60;
    unknown60 = nullptr;
  }
  if (unknown58 != nullptr) {
    delete unknown58;
    unknown58 = nullptr;
  }
  if (unknown50 != nullptr) {
    delete unknown50;
    unknown50 = nullptr;
  }
  unknown08 = 0;
  unknown78 = nullptr;
  unknown80 = nullptr;
}

void ObjectList::clearSub(Object *object) {
  object->clear();
  for (Object *child = object->getChild(); child != nullptr; child = child->getNext()) {
    clearSub(child);
  }
}

void ObjectList::clrChilds(Object *object) {
  Object *child = object->getChild();
  while (child != nullptr) {
    Object *next = child->getNext();
    delete child;
    child = next;
  }
  object->setChild(nullptr);
}

void ObjectList::startScene() {
  if (unknown50 != nullptr) {
    startSceneSub(unknown50);
  }
}

void ObjectList::startSceneSub(Object *object) {
  object->start();
  for (Object *child = object->getChild(); child != nullptr; child = child->getNext()) {
    startSceneSub(child);
  }
}

void ObjectList::startPage() {
  for (Object *object = unknown68->getChild(); object != nullptr; object = object->getNext()) {
    mm::mtl::Singleton<BouManager>::getPtr()->pop(static_cast<ObjectEffect *>(object));
  }
  ObjectTree *tree = unknown68;
  for (Object *object = tree->getChild(); object != nullptr; object = object->getNext()) {
  }
  if (tree != nullptr) {
    clrChilds(tree);
  }
  unknown90 = 0;
  unknown78 = nullptr;
}

void ObjectList::endScene() {
  if (unknown50 != nullptr) {
    endSceneSub(unknown50);
  }
}

void ObjectList::endSceneSub(Object *object) {
  object->end();
  for (Object *child = object->getChild(); child != nullptr; child = child->getNext()) {
    endSceneSub(child);
  }
}

void ObjectList::update() {
  if (unknown50 != nullptr) {
    updateSub(unknown50);
  }
}

void ObjectList::updateSub(Object *object) {
  object->update();
  for (Object *child = object->getChild(); child != nullptr; child = child->getNext()) {
    updateSub(child);
  }
}

void ObjectList::render() {
  if (unknown50 != nullptr) {
    renderSub(unknown50);
  }
}

void ObjectList::renderSub(Object *object) {
  if (object->isLoading()) {
    object->render(mm::Col4(0.5f, 0.5f, 0.5f, 0.5f));
  } else {
    object->render(mm::Col4(1.0f, 1.0f, 1.0f, 0.5f));
  }
  for (Object *child = object->getChild(); child != nullptr; child = child->getNext()) {
    renderSub(child);
  }
}

void ObjectList::tail() {
  if (unknown50 != nullptr) {
    tailSub(unknown50);
  }
}

void ObjectList::tailSub(Object *object) {
  object->tail();
  for (Object *child = object->getChild(); child != nullptr; child = child->getNext()) {
    tailSub(child);
  }
}

bool ObjectList::isLoading() const {
  if (unknown50 != nullptr) {
    return isLoadingSub(unknown50);
  }
  return false;
}

bool ObjectList::isLoadingSub(Object *object) const {
  if (object->isLoading()) {
    return true;
  }
  for (Object *child = object->getChild(); child != nullptr; child = child->getNext()) {
    if (isLoadingSub(child)) {
      return true;
    }
  }
  return false;
}

ObjectChara *ObjectList::createGfObj(const char *name, gf::GF_OBJ_HANDLE *handle) {
  ObjectChara *chara = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ObjectChara(name);
  chara->createGfObj(handle);
  unknown58->addChild(chara);
  unknown88++;
  mm::mtl::Singleton<BouManager>::getPtr()->push(chara);
  unknown78 = chara;
  if (unknown80 == nullptr) {
    unknown80 = chara;
  }
  return chara;
}

ObjectChara *ObjectList::createGfObjPcByBladeID(const char *name, u32 bladeID, u32 param2) {
  if ((unknown08 & FLAG_CLONE_MODE) == 0) {
    return createGfObj(name, getDriverByBlade(bladeID));
  }
  return createGfObj(name, CHARA_TYPE_DRIVER, getDriverIdByBlade(bladeID), param2, 0);
}

gf::GF_OBJ_HANDLE *ObjectList::getDriverByBlade(u32 bladeID) {
  for (u32 i = 1; i <= ObjectPartyList::MEMBER_COUNT; i++) {
    gf::GF_OBJ_HANDLE *driver = mm::mtl::Singleton<ObjectPartyList>::getPtr()->getDriver(i);
    gf::GF_OBJ_HANDLE *blade = mm::mtl::Singleton<ObjectPartyList>::getPtr()->getBlade(i);
    if (gf::GfObjAcc(blade).getBdatId() == bladeID) {
      return driver;
    }
  }
  return gf::GfGameManager::getPartyLeaderDriver();
}

u32 ObjectList::getDriverIdByBlade(u32 bladeID) const {
  u32 driverID = gf::GfDataBlade::getCreator(bladeID);
  return driverID == 0 ? 3 : driverID;
}

ObjectChara *ObjectList::createGfObjBladeByPcID(const char *name, u32 pcID, u32 param2) {
  if ((unknown08 & FLAG_CLONE_MODE) == 0) {
    return createGfObj(name, getBladeByDriver(pcID));
  }
  return createGfObj(name, CHARA_TYPE_BLADE, getBladeIdByDriver(pcID), param2, 0);
}

gf::GF_OBJ_HANDLE *ObjectList::getBladeByDriver(u32 driverID) {
  for (u32 i = 1; i <= ObjectPartyList::MEMBER_COUNT; i++) {
    gf::GF_OBJ_HANDLE *driver = mm::mtl::Singleton<ObjectPartyList>::getPtr()->getDriver(i);
    gf::GF_OBJ_HANDLE *blade = mm::mtl::Singleton<ObjectPartyList>::getPtr()->getBlade(i);
    if (gf::GfObjAcc(driver).getBdatId() == driverID) {
      return blade;
    }
  }
  return gf::INVALID_HANDLE;
}

u32 ObjectList::getBladeIdByDriver(u32 driverID) const {
  u32 bladeID = gf::GfDataDriver::getBlade(driverID, -1);
  return bladeID == 0 ? 1001 : bladeID;
}

ObjectCamera *ObjectList::createCamera(const char *name, u32 id) {
  if (id < unknown8c) {
    return static_cast<ObjectCamera *>(getChild(unknown60, id));
  }
  ObjectCamera *camera = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ObjectCamera(name, id);
  unknown60->addChild(camera);
  unknown8c++;
  mm::mtl::Singleton<BouManager>::getPtr()->push(camera);
  unknown78 = camera;
  return camera;
}

Object *ObjectList::getChild(Object *parent, u32 index) {
  for (Object *child = parent->getChild(); child != nullptr; child = child->getNext()) {
    if (index-- == 0) {
      return child;
    }
  }
  return nullptr;
}

ObjectEffect *ObjectList::createEffect(const char *name) {
  ObjectEffect *effect = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ObjectEffect(name);
  unknown68->addChild(effect);
  unknown90++;
  mm::mtl::Singleton<BouManager>::getPtr()->push(effect);
  unknown78 = effect;
  return effect;
}

ObjectLight *ObjectList::createLight(const char *name, u32 id) {
  if (id < unknown94) {
    return static_cast<ObjectLight *>(getChild(unknown70, id));
  }
  ObjectLight *light = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ObjectLight(name, id);
  unknown70->addChild(light);
  unknown94++;
  unknown78 = light;
  return light;
}

ObjectChara *ObjectList::getChara(u32 index) {
  if (unknown58 == nullptr) {
    return nullptr;
  }
  return static_cast<ObjectChara *>(getChild(unknown58, index));
}

ObjectCamera *ObjectList::getCamera(u32 index) {
  if (unknown60 == nullptr) {
    return nullptr;
  }
  return static_cast<ObjectCamera *>(getChild(unknown60, index));
}

ObjectLight *ObjectList::getLight(u32 index) {
  if (unknown70 == nullptr) {
    return nullptr;
  }
  return static_cast<ObjectLight *>(getChild(unknown70, index));
}

bool ObjectList::isUsingEffect() {
  for (u32 i = 0; i < unknown90; i++) {
    if (static_cast<ObjectEffect *>(getEffect(i))->getEffCount() != 0) {
      return true;
    }
  }
  return false;
}

void ObjectList::stopEffect() {
  for (u32 i = 0; i < unknown90; i++) {
    static_cast<ObjectEffect *>(getEffect(i))->stop();
  }
}

Object *ObjectList::searchByPathSub(Object *object, const char *path) {
  char buffer[512];
  char *rest = nullptr;
  __builtin_strcpy(buffer, path);
  strtok_r(buffer, "/", &rest);
  for (Object *child = object->getChild(); child != nullptr; child = child->getNext()) {
    if (__builtin_strcmp(buffer, child->getName()) == 0) {
      return child->searchByPath(path);
    }
  }
  return nullptr;
}

Object *ObjectList::searchByNameSub(Object *object, const char *name) {
  if (__builtin_strcmp(name, object->getName()) == 0) {
    return object;
  }
  for (Object *child = object->getChild(); child != nullptr; child = child->getNext()) {
    Object *found = searchByNameSub(child, name);
    if (found != nullptr) {
      return found;
    }
  }
  return nullptr;
}

Object *ObjectList::searchByName(const char *name) const {
  Object *root = unknown50;
  if (root == nullptr)
    return nullptr;
  Object *found = searchByNameSub(root, name);
  if (found == nullptr || found == root || found == unknown58 || found == unknown60 || found == unknown68 || found == unknown70)
    return nullptr;
  return found;
}

ObjectChara *ObjectList::searchByHandle(gf::GF_OBJ_HANDLE *handle) const {
  if (unknown58 == nullptr) {
    return nullptr;
  }
  for (Object *object = unknown58->getChild(); object != nullptr; object = object->getNext()) {
    if (object->getType() == OBJTYPE_CHARA && static_cast<ObjectChara *>(object)->getCharaObj()->getHandle() == handle) {
      return static_cast<ObjectChara *>(object);
    }
  }
  return nullptr;
}

ObjectChara *ObjectList::searchByID(u32 type, u32 id) const {
  if (unknown58 != nullptr) {
    for (Object *object = unknown58->getChild(); object != nullptr; object = object->getNext()) {
      if (object->getType() == OBJTYPE_CHARA) {
        gf::GfObjAcc acc(static_cast<ObjectChara *>(object)->getCharaObj()->getHandle());
        if (acc.getType() == type && acc.getBdatId() == id) {
          return static_cast<ObjectChara *>(object);
        }
      }
    }
  }
  return nullptr;
}

bool ObjectList::getPathByObj(mm::mtl::FixStr<256> &path, const Object *object) const {
  if (unknown50 == nullptr) {
    return false;
  }
  for (Object *child = unknown50->getChild(); child != nullptr; child = child->getNext()) {
    if (getPathByObjSub(path, "", child, object)) {
      return true;
    }
  }
  return false;
}

bool ObjectList::getPathByObjSub(mm::mtl::FixStr<256> &path, const char *parentPath, Object *object, const Object *target) {
  mm::mtl::FixStr<256> objectPath;
  objectPath = parentPath;
  if (*objectPath.c_str() != '\0') {
    objectPath += "/";
  }
  objectPath += object->getName();
  if (object == target) {
    path = objectPath.c_str();
    return true;
  }
  for (Object *child = object->getChild(); child != nullptr; child = child->getNext()) {
    if (getPathByObjSub(path, objectPath.c_str(), child, target)) {
      return true;
    }
  }
  return false;
}

void ObjectList::listupObject(mm::mtl::FixedVector<u32, 256> &list, u32 type, bool isAppend) {
  if (!isAppend) {
    list.clear();
  }
  if (unknown58 == nullptr) {
    return;
  }
  for (Object *object = unknown58->getChild(); object != nullptr && list.size() < list.capacity(); object = object->getNext()) {
    if (object->getType() != OBJTYPE_CHARA) {
      continue;
    }
    gf::GF_OBJ_HANDLE *handle = static_cast<ObjectChara *>(object)->getCharaObj()->getHandle();
    if (handle == gf::INVALID_HANDLE) {
      continue;
    }
    gf::GfObjAcc acc(handle);
    if (acc.getType() == type) {
      list.push_back(acc.getBdatId());
    }
  }
}

void ObjectList::dump() {
  if (unknown58 == nullptr) {
    return;
  }
  for (Object *object = unknown58->getChild(); object != nullptr; object = object->getNext()) {
    if (object->getType() == OBJTYPE_CHARA) {
      gf::GfObjAcc acc(static_cast<ObjectChara *>(object)->getCharaObj()->getHandle());
    }
  }
}

} // namespace event
