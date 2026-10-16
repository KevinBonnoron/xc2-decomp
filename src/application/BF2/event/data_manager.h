#pragma once
#include "event/i_manager.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/noncopyable.h"
#include "types.h"

namespace event {

class DataManager : public IManager, public mm::mtl::NoncopyableBase {
public:
  static constexpr u32 SCENE_COUNT = 16;

  struct OfsInfo {
    OfsInfo(const char *name);

    mm::mtl::FixStr<64> name;
    mm::Mat44 srcMatrix;
    mm::Mat44 desMatrix;
    mm::Mat44 offsetMatrix;
    mm::Vec3 offsetVector;
    mm::Mat44 keepMatrix;
    mm::Vec3 keepVector;
  };

  DataManager();
  virtual ~DataManager();
  void clear();
  void setupScene();
  void updateCurrent();
  void startScene();
  OfsInfo *getCurrent();
  OfsInfo *searchScene(const char *name) const;
  OfsInfo *createScene(const char *name);
  u32 getCharaNum() const;
  bool checkRadianTar(u32 axis);
  mm::Vec3 axis2pos(u32 axis, f32 x, f32 y, f32 z);
  mm::Vec3 axis2rot(u32 axis, f32 x, f32 y, f32 z, const mm::Vec3 &rot);
  mm::Vec3 axis2tar(u32 axis, f32 x, f32 y, f32 z, const mm::Vec3 &pos);
  const char *getPosName(u32 axis);
  const char *getRotName(u32 axis);
  const char *getTarName(u32 axis);
  void setOffsetSrc(const mm::Vec3 &pos, f32 rotY, bool isKeep);
  void setOffsetDes(const mm::Vec3 &pos, f32 rotY, bool isKeep);
  virtual void OnEventProc(MSG_TYPE type);

private:
  mm::mtl::FixedVector<OfsInfo *, SCENE_COUNT> mScenes;
  mm::mtl::FixStr<64> mSceneName;
  mm::mtl::FixStr<64> mCurrentSceneName;
  OfsInfo *mCurrent;
};

static_assert(sizeof(DataManager::OfsInfo) == 0x170, "");
static_assert(sizeof(DataManager) == 0x128, "");

} // namespace event
