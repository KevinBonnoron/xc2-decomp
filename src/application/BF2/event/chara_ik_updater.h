#pragma once
#include "mm_math/mm_vec2.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/bitflag.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
class GfObj;
} // namespace gf

namespace event {

class CharaIKUpdater {
public:
  enum FOOT_TYPE {
    FOOT_TYPE_0 = 0,
    FOOT_TYPE_1 = 1,
    FOOT_TYPE_2 = 2,
  };

  enum {
    FLAG_ALL_IK = 0,
    FLAG_FOOT_IK_0 = 1,
    FLAG_FOOT_IK_1 = 2,
    FLAG_FOOT_IK_2 = 3,
    FLAG_TARGET_IK = 4,
    FLAG_TARGET_IK_NO_SPINE = 5,
    FLAG_LENS_IK = 6,
    FLAG_MAX = 32,
  };

  enum {
    REQUEST_ALL_IK = 0,
    REQUEST_FOOT_IK = 1,
    REQUEST_TARGET_IK = 2,
    REQUEST_TARGET_POS = 3,
    REQUEST_LENS_IK = 4,
    REQUEST_MAX = 32,
  };

  CharaIKUpdater();
  virtual ~CharaIKUpdater() {}
  void create(gf::GF_OBJ_HANDLE *handle);
  void destroy();
  void update(f32 delta);
  void render(const mm::Vec3 &position, f32 height);
  void setAllIK(bool isEnable);
  void setFootIK(bool isEnable, FOOT_TYPE type);
  void setTargetIK(bool isEnable, f32 frame, bool isNoSpine);
  void setTargetPos(const mm::Vec3 &position);
  void setLensIK(bool isEnable, f32 x, f32 y);
  static bool checkField(gf::GfObj *obj);

private:
  mm::mtl::BitFlag<FLAG_MAX> flags;
  mm::mtl::BitFlag<REQUEST_MAX> mRequests;
  gf::GF_OBJ_HANDLE *handle;
  f32 mTargetFrame;
  mm::Vec3 mTargetPos;
  alignas(16) mm::Vec2 mLensMove;
  alignas(16) mm::Vec2 mLensTranslateMin;
  alignas(16) mm::Vec2 mLensTranslateMax;
  alignas(16) mm::Vec2 mLensRotateMin;
  alignas(16) mm::Vec2 mLensRotateMax;
};

static_assert(sizeof(CharaIKUpdater) == 0x80, "");

} // namespace event
