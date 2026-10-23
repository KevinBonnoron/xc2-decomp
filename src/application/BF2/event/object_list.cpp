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
    : flags(0), mName(name), mRoot(nullptr), mCharaTree(nullptr), mCameraTree(nullptr), mEffectTree(nullptr), mLightTree(nullptr), mActive(nullptr),
      mFirstChara(nullptr), mCharaCount(0), mCameraCount(0), mEffectCount(0), mLightCount(0) {
  if (isCloneMode) {
    flags |= FLAG_CLONE_MODE;
  } else {
    flags &= ~FLAG_CLONE_MODE;
  }
  mRoot = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ObjectTree(ROOT);
  mCharaTree = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ObjectTree(CHR_TREE);
  mRoot->addChild(mCharaTree);
  mCharaCount = 0;
  mCameraTree = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ObjectTree(CAM_TREE);
  mRoot->addChild(mCameraTree);
  mCameraCount = 0;
  mEffectTree = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ObjectTree(EFF_TREE);
  mRoot->addChild(mEffectTree);
  mEffectCount = 0;
  mLightTree = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ObjectTree(LGT_TREE);
  mRoot->addChild(mLightTree);
  mLightCount = 0;
  mActive = nullptr;
  mFirstChara = nullptr;
}

ObjectList::~ObjectList() {
  for (Object *object = mCharaTree->getChild(); object != nullptr; object = object->getNext()) {
  }
  for (Object *object = mCameraTree->getChild(); object != nullptr; object = object->getNext()) {
  }
  for (Object *object = mEffectTree->getChild(); object != nullptr; object = object->getNext()) {
  }
  if (mRoot != nullptr) {
    clearSub(mRoot);
  }
  if (mEffectTree != nullptr) {
    clrChilds(mEffectTree);
  }
  mEffectCount = 0;
  if (mCharaTree != nullptr) {
    clrChilds(mCharaTree);
  }
  mCharaCount = 0;
  if (mCameraTree != nullptr) {
    clrChilds(mCameraTree);
  }
  mCameraCount = 0;
  if (mLightTree != nullptr) {
    clrChilds(mLightTree);
  }
  mLightCount = 0;
  if (mRoot != nullptr) {
    mRoot->setChild(nullptr);
  }
  if (mLightTree != nullptr) {
    delete mLightTree;
    mLightTree = nullptr;
  }
  if (mEffectTree != nullptr) {
    delete mEffectTree;
    mEffectTree = nullptr;
  }
  if (mCameraTree != nullptr) {
    delete mCameraTree;
    mCameraTree = nullptr;
  }
  if (mCharaTree != nullptr) {
    delete mCharaTree;
    mCharaTree = nullptr;
  }
  if (mRoot != nullptr) {
    delete mRoot;
    mRoot = nullptr;
  }
  flags = 0;
  mActive = nullptr;
  mFirstChara = nullptr;
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
  if (mRoot != nullptr) {
    startSceneSub(mRoot);
  }
}

void ObjectList::startSceneSub(Object *object) {
  object->start();
  for (Object *child = object->getChild(); child != nullptr; child = child->getNext()) {
    startSceneSub(child);
  }
}

void ObjectList::startPage() {
  for (Object *object = mEffectTree->getChild(); object != nullptr; object = object->getNext()) {
    mm::mtl::Singleton<BouManager>::getPtr()->pop(static_cast<ObjectEffect *>(object));
  }
  ObjectTree *tree = mEffectTree;
  for (Object *object = tree->getChild(); object != nullptr; object = object->getNext()) {
  }
  if (tree != nullptr) {
    clrChilds(tree);
  }
  mEffectCount = 0;
  mActive = nullptr;
}

void ObjectList::endScene() {
  if (mRoot != nullptr) {
    endSceneSub(mRoot);
  }
}

void ObjectList::endSceneSub(Object *object) {
  object->end();
  for (Object *child = object->getChild(); child != nullptr; child = child->getNext()) {
    endSceneSub(child);
  }
}

void ObjectList::update() {
  if (mRoot != nullptr) {
    updateSub(mRoot);
  }
}

void ObjectList::updateSub(Object *object) {
  object->update();
  for (Object *child = object->getChild(); child != nullptr; child = child->getNext()) {
    updateSub(child);
  }
}

void ObjectList::render() {
  if (mRoot != nullptr) {
    renderSub(mRoot);
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
  if (mRoot != nullptr) {
    tailSub(mRoot);
  }
}

void ObjectList::tailSub(Object *object) {
  object->tail();
  for (Object *child = object->getChild(); child != nullptr; child = child->getNext()) {
    tailSub(child);
  }
}

bool ObjectList::isLoading() const {
  if (mRoot != nullptr) {
    return isLoadingSub(mRoot);
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
  mCharaTree->addChild(chara);
  mCharaCount++;
  mm::mtl::Singleton<BouManager>::getPtr()->push(chara);
  mActive = chara;
  if (mFirstChara == nullptr) {
    mFirstChara = chara;
  }
  return chara;
}

ObjectChara *ObjectList::createGfObjPcByBladeID(const char *name, u32 bladeID, u32 param2) {
  if ((flags & FLAG_CLONE_MODE) == 0) {
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
  if ((flags & FLAG_CLONE_MODE) == 0) {
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
  if (id < mCameraCount) {
    return static_cast<ObjectCamera *>(getChild(mCameraTree, id));
  }
  ObjectCamera *camera = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ObjectCamera(name, id);
  mCameraTree->addChild(camera);
  mCameraCount++;
  mm::mtl::Singleton<BouManager>::getPtr()->push(camera);
  mActive = camera;
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
  mEffectTree->addChild(effect);
  mEffectCount++;
  mm::mtl::Singleton<BouManager>::getPtr()->push(effect);
  mActive = effect;
  return effect;
}

ObjectLight *ObjectList::createLight(const char *name, u32 id) {
  if (id < mLightCount) {
    return static_cast<ObjectLight *>(getChild(mLightTree, id));
  }
  ObjectLight *light = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ObjectLight(name, id);
  mLightTree->addChild(light);
  mLightCount++;
  mActive = light;
  return light;
}

ObjectChara *ObjectList::getChara(u32 index) {
  if (mCharaTree == nullptr) {
    return nullptr;
  }
  return static_cast<ObjectChara *>(getChild(mCharaTree, index));
}

ObjectCamera *ObjectList::getCamera(u32 index) {
  if (mCameraTree == nullptr) {
    return nullptr;
  }
  return static_cast<ObjectCamera *>(getChild(mCameraTree, index));
}

ObjectLight *ObjectList::getLight(u32 index) {
  if (mLightTree == nullptr) {
    return nullptr;
  }
  return static_cast<ObjectLight *>(getChild(mLightTree, index));
}

bool ObjectList::isUsingEffect() {
  for (u32 i = 0; i < mEffectCount; i++) {
    if (static_cast<ObjectEffect *>(getEffect(i))->getEffCount() != 0) {
      return true;
    }
  }
  return false;
}

void ObjectList::stopEffect() {
  for (u32 i = 0; i < mEffectCount; i++) {
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
  Object *root = mRoot;
  if (root == nullptr)
    return nullptr;
  Object *found = searchByNameSub(root, name);
  if (found == nullptr || found == root || found == mCharaTree || found == mCameraTree || found == mEffectTree || found == mLightTree)
    return nullptr;
  return found;
}

ObjectChara *ObjectList::searchByHandle(gf::GF_OBJ_HANDLE *handle) const {
  if (mCharaTree == nullptr) {
    return nullptr;
  }
  for (Object *object = mCharaTree->getChild(); object != nullptr; object = object->getNext()) {
    if (object->getType() == OBJTYPE_CHARA && static_cast<ObjectChara *>(object)->getCharaObj()->getHandle() == handle) {
      return static_cast<ObjectChara *>(object);
    }
  }
  return nullptr;
}

ObjectChara *ObjectList::searchByID(u32 type, u32 id) const {
  if (mCharaTree != nullptr) {
    for (Object *object = mCharaTree->getChild(); object != nullptr; object = object->getNext()) {
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
  if (mRoot == nullptr) {
    return false;
  }
  for (Object *child = mRoot->getChild(); child != nullptr; child = child->getNext()) {
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
  if (mCharaTree == nullptr) {
    return;
  }
  for (Object *object = mCharaTree->getChild(); object != nullptr && list.size() < list.capacity(); object = object->getNext()) {
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
  if (mCharaTree == nullptr) {
    return;
  }
  for (Object *object = mCharaTree->getChild(); object != nullptr; object = object->getNext()) {
    if (object->getType() == OBJTYPE_CHARA) {
      gf::GfObjAcc acc(static_cast<ObjectChara *>(object)->getCharaObj()->getHandle());
    }
  }
}

} // namespace event
