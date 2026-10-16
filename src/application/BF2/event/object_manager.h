#pragma once
#include "event/i_manager.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/noncopyable.h"
#include "types.h"

namespace event {

class ObjectList;

class ObjectManager : public IManager, public mm::mtl::NoncopyableBase {
public:
  static constexpr u32 SCENE_COUNT = 16;

  ObjectManager();
  virtual ~ObjectManager() {}
  u32 getCharaCount() const;
  u32 getCameraCount() const;
  bool isDisp() const;
  void updateCurrent();
  void startPage();
  void endScene();
  void update();
  void tail();
  bool isLoading() const;
  ObjectList *getCurrent();
  virtual void OnEventProc(MSG_TYPE type);

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
