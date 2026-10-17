#pragma once
#include "event/chara_obj.h"
#include "event/i_manager.h"
#include "event/object_list.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

class Object;
class ObjectCamera;
class ObjectEffect;
class ObjectLight;
class ObjectChara;

class ObjectManager : public IManager, public mm::mtl::Singleton<ObjectManager> {
public:
  static constexpr u32 SCENE_COUNT = 16;

  enum {
    MODE_CLONE = 1 << 0,
  };

  enum {
    FLAG_DISP = 1 << 0,
  };

  u32 getCharaCount() const;
  ObjectChara *getChara(u32 index);
  u32 getCameraCount() const;
  ObjectCamera *getCamera(u32 index);
  bool isDisp() const;
  ObjectManager();
  virtual ~ObjectManager() {}
  void stopEffect();
  void clear();
  void init();
  void setupScene();
  void updateCurrent();
  void startScene();
  void startPage();
  void endScene();
  void update();
  void render();
  void tail();
  bool isLoading() const;
  ObjectChara *createGfObjTalk(const char *name);
  ObjectList *getCurrent();
  ObjectChara *createGfObjPcByWalkID(const char *name, u32 walkID, u32 param2);
  ObjectChara *createGfObjPcByBladeID(const char *name, u32 bladeID, u32 param2);
  ObjectChara *createGfObjBlByWalkID(const char *name, u32 walkID, u32 param2);
  ObjectChara *createGfObjBladeByPcID(const char *name, u32 pcID, u32 param2);
  ObjectChara *createGfObjPartyIn(const char *name, CHARA_TYPE type, u32 id, u32 param3, u32 param4);
  ObjectChara *createGfObj(const char *name, CHARA_TYPE type, u32 id, u32 param3, u32 param4);
  ObjectChara *createModel(const char *name, const char *model, u32 param2, u32 param3);
  ObjectCamera *createCamera(const char *name, u32 id);
  ObjectEffect *createEffect(const char *name);
  ObjectLight *createLight(const char *name, u32 id);
  ObjectLight *getLight(u32 index);
  u32 getLightCount() const;
  bool isUsingEffect();
  void setActivePath(const char *path);
  Object *searchByPath(const char *path);
  Object *searchByName(const char *name);
  bool getPathByObj(mm::mtl::FixStr<256> &path, const Object *object);
  void listupObject(mm::mtl::FixedVector<u32, 256> &list, u32 type, bool isAppend);
  void setCloneMode(bool isCloneMode);
  void setDisp(bool isDisp);
  void dump();
  ObjectList *searchScene(const char *name) const;
  ObjectList *createScene(const char *name);
  virtual void OnEventProc(MSG_TYPE type);

  ObjectChara *searchByHandle(gf::GF_OBJ_HANDLE *handle) {
    if (mCurrent == nullptr) {
      return nullptr;
    }
    return mCurrent->searchByHandle(handle);
  }

  ObjectChara *searchByID(u32 type, u32 id) {
    if (mCurrent == nullptr) {
      return nullptr;
    }
    return mCurrent->searchByID(type, id);
  }

  Object *getActive() const {
    if (mCurrent == nullptr) {
      return nullptr;
    }
    return mCurrent->getActive();
  }

private:
  u32 mMode;
  u32 flags;
  mm::mtl::FixedVector<ObjectList *, SCENE_COUNT> mScenes;
  mm::mtl::FixStr<64> mSceneName;
  mm::mtl::FixStr<64> mNextSceneName;
  ObjectList *mCurrent;
};

static_assert(sizeof(ObjectManager) == 0x130, "");

} // namespace event
