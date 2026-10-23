#pragma once
#include "event/chara_obj.h"
#include "event/object.h"
#include "event/object_tree.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
}

namespace event {

class ObjectCamera;
class ObjectEffect;
class ObjectLight;
class ObjectChara;

class ObjectList {
public:
  static const char ROOT[64];
  static const char CHR_TREE[64];
  static const char CAM_TREE[64];
  static const char EFF_TREE[64];
  static const char LGT_TREE[64];

  enum {
    FLAG_CLONE_MODE = 1 << 0,
  };

  ObjectList(const char *name, bool isCloneMode);
  virtual ~ObjectList();
  void clearSub(Object *object);
  static void clrChilds(Object *object);
  void startScene();
  void startSceneSub(Object *object);
  void startPage();
  void endScene();
  void endSceneSub(Object *object);
  void update();
  void updateSub(Object *object);
  void render();
  void renderSub(Object *object);
  void tail();
  void tailSub(Object *object);
  bool isLoading() const;
  bool isLoadingSub(Object *object) const;
  ObjectChara *createGfObjTalk(const char *name);
  ObjectChara *createGfObj(const char *name, gf::GF_OBJ_HANDLE *handle);
  ObjectChara *createGfObj(const char *name, CHARA_TYPE type, u32 id, u32 param3, u32 param4);
  void adjestDefaultPos(ObjectChara *chara, bool isForce);
  ObjectChara *createGfObjPcByWalkID(const char *name, u32 walkID, u32 param2);
  ObjectChara *createGhost(const char *name);
  ObjectChara *createGfObjPcByBladeID(const char *name, u32 bladeID, u32 param2);
  gf::GF_OBJ_HANDLE *getDriverByBlade(u32 bladeID);
  u32 getDriverIdByBlade(u32 bladeID) const;
  ObjectChara *createGfObjBlByWalkID(const char *name, u32 walkID, u32 param2);
  ObjectChara *createGfObjBladeByPcID(const char *name, u32 pcID, u32 param2);
  gf::GF_OBJ_HANDLE *getBladeByDriver(u32 driverID);
  u32 getBladeIdByDriver(u32 driverID) const;
  ObjectChara *createGfObjPartyIn(const char *name, CHARA_TYPE type, u32 id, u32 param3, u32 param4);
  ObjectChara *createModel(const char *name, const char *model, u32 param2, u32 param3);
  ObjectCamera *createCamera(const char *name, u32 id);
  static Object *getChild(Object *parent, u32 index);
  ObjectEffect *createEffect(const char *name);
  ObjectLight *createLight(const char *name, u32 id);
  ObjectChara *getChara(u32 index);
  ObjectCamera *getCamera(u32 index);
  ObjectLight *getLight(u32 index);
  bool isUsingEffect();
  void stopEffect();
  void setActivePath(const char *path);
  static Object *searchByPathSub(Object *object, const char *path);
  Object *searchByPath(const char *path) const;
  Object *searchByName(const char *name) const;
  static Object *searchByNameSub(Object *object, const char *name);
  ObjectChara *searchByHandle(gf::GF_OBJ_HANDLE *handle) const;
  ObjectChara *searchByID(u32 type, u32 id) const;
  bool getPathByObj(mm::mtl::FixStr<256> &path, const Object *object) const;
  static bool getPathByObjSub(mm::mtl::FixStr<256> &path, const char *parentPath, Object *object, const Object *target);
  void listupObject(mm::mtl::FixedVector<u32, 256> &list, u32 type, bool isAppend);
  void dump();

  const char *getName() const { return mName.c_str(); }
  Object *getActive() const { return mActive; }
  void setActive(Object *object) { mActive = object; }
  u32 getCharaCount() const { return mCharaCount; }
  u32 getCameraCount() const { return mCameraCount; }
  u32 getEffectCount() const { return mEffectCount; }
  u32 getLightCount() const { return mLightCount; }

  Object *getCharaObject(u32 index) const {
    Object *object = mCharaTree->getChild();
    for (u32 i = 0; i < index; i++) {
      object = object->getNext();
    }
    return object;
  }

  Object *getEffect(u32 index) const {
    Object *object = mEffectTree->getChild();
    for (u32 i = 0; i < index; i++) {
      object = object->getNext();
    }
    return object;
  }

private:
  // Reconstruction access for ObjectManager::searchByName; original access
  // relationship is unknown. The wrapper reads the same tree offsets.
  friend class ObjectManager;

  bool isTree(const Object *object) const {
    return object == mRoot || object == mCharaTree || object == mCameraTree || object == mEffectTree || object == mLightTree;
  }

  u32 flags;
  mm::mtl::FixStr<64> mName;
  ObjectTree *mRoot;
  ObjectTree *mCharaTree;
  ObjectTree *mCameraTree;
  ObjectTree *mEffectTree;
  ObjectTree *mLightTree;
  Object *mActive;
  ObjectChara *mFirstChara;
  u32 mCharaCount;
  u32 mCameraCount;
  u32 mEffectCount;
  u32 mLightCount;
};

static_assert(sizeof(ObjectList) == 0x98, "");

} // namespace event
