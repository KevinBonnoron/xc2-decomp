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

  const char *getName() const { return unknown0c.c_str(); }
  Object *getActive() const { return unknown78; }
  void setActive(Object *object) { unknown78 = object; }
  u32 getCharaCount() const { return unknown88; }
  u32 getCameraCount() const { return unknown8c; }
  u32 getEffectCount() const { return unknown90; }
  u32 getLightCount() const { return unknown94; }

  Object *getCharaObject(u32 index) const {
    Object *object = unknown58->getChild();
    for (u32 i = 0; i < index; i++) {
      object = object->getNext();
    }
    return object;
  }

  Object *getEffect(u32 index) const {
    Object *object = unknown68->getChild();
    for (u32 i = 0; i < index; i++) {
      object = object->getNext();
    }
    return object;
  }

private:
  // Reconstruction access for ObjectManager::searchByName; original access
  // relationship is unknown. The wrapper reads the same tree offsets.
  friend class ObjectManager;

  bool isTree(const Object *object) const { return object == unknown50 || object == unknown58 || object == unknown60 || object == unknown68 || object == unknown70; }

  u32 unknown08;                 // Inferred role: flags; original member name unknown.
  mm::mtl::FixStr<64> unknown0c; // Inferred role: name; original member name unknown.
  ObjectTree *unknown50;         // Inferred role: root; original member name unknown.
  ObjectTree *unknown58;         // Inferred role: chara tree; original member name unknown.
  ObjectTree *unknown60;         // Inferred role: camera tree; original member name unknown.
  ObjectTree *unknown68;         // Inferred role: effect tree; original member name unknown.
  ObjectTree *unknown70;         // Inferred role: light tree; original member name unknown.
  Object *unknown78;             // Inferred role: active; original member name unknown.
  ObjectChara *unknown80;        // Inferred role: first chara; original member name unknown.
  u32 unknown88;                 // Inferred role: chara count; original member name unknown.
  u32 unknown8c;                 // Inferred role: camera count; original member name unknown.
  u32 unknown90;                 // Inferred role: effect count; original member name unknown.
  u32 unknown94;                 // Inferred role: light count; original member name unknown.
};

static_assert(sizeof(ObjectList) == 0x98, "");

} // namespace event
