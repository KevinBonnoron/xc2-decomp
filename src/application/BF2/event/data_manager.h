#pragma once
#include <stddef.h>

#include "event/i_manager.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class DataManager : public IManager, public mm::mtl::Singleton<DataManager> {
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
  size_t getCharaNum() const;
  bool checkRadianTar(u32 axis);
  mm::Vec3 axis2pos(u32 axis, f32 x, f32 y, f32 z);
  mm::Mat44 getPosAxis(u32 axis);
  f32 getRotOfsY(u32 axis, const mm::Vec3 &rot);
  mm::Mat44 getTarAxis(u32 axis);
  mm::Vec3 axis2rot(u32 axis, f32 x, f32 y, f32 z, const mm::Vec3 &rot);
  mm::Vec3 axis2tar(u32 axis, f32 x, f32 y, f32 z, const mm::Vec3 &pos);
  const char *getPosName(u32 axis);
  const char *getRotName(u32 axis);
  const char *getTarName(u32 axis);
  void setOffsetSrc(const mm::Vec3 &pos, f32 rotY, bool isKeep);
  void setOffsetDes(const mm::Vec3 &pos, f32 rotY, bool isKeep);
  virtual void OnEventProc(MSG_TYPE type);

private:
  static mm::Vec3 transformPos(mm::Mat44 mat, f32 x, f32 y, f32 z) {
    return mm::Vec3(mat.rows[0][0] * x + mat.rows[1][0] * y + mat.rows[2][0] * z + mat.rows[3][0],
                    mat.rows[0][1] * x + mat.rows[1][1] * y + mat.rows[2][1] * z + mat.rows[3][1],
                    mat.rows[0][2] * x + mat.rows[1][2] * y + mat.rows[2][2] * z + mat.rows[3][2]);
  }

  mm::mtl::FixedVector<OfsInfo *, SCENE_COUNT> mScenes;
  mm::mtl::FixStr<64> mSceneName;
  mm::mtl::FixStr<64> mCurrentSceneName;
  OfsInfo *mCurrent;
};

static_assert(sizeof(DataManager::OfsInfo) == 0x170, "");
static_assert(sizeof(DataManager) == 0x128, "");

} // namespace event
