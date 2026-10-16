#pragma once
#include <stddef.h>

#include "event/anm_f32.h"
#include "event/anm_vec.h"
#include "event/cam_base.h"
#include "event/cam_util.h"
#include "event/curve.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace event {

class PosAxis;
class TarAxis;

class CamHands : public CamBase {
public:
  static constexpr u32 KEY_COUNT = 16;

  enum {
    FLAG_FOLLOW_POS = 1 << 0,
    FLAG_FOLLOW_TAR = 1 << 1,
  };

  CamHands(bool isFocal);
  virtual ~CamHands();
  virtual void update(const FrameInfo &info);
  void calcFollowPos();
  void calcFollowTar();
  virtual void render(const mm::Col4 &color);
  void setPos(const PosAxis &pos, CV_TYPE cv);
  void addAnmPos(f32 frame, const PosAxis &pos, CV_TYPE cv);
  void insertAnmPos(size_t index, const PosAxis &pos);
  void setTar(const TarAxis &tar, CV_TYPE cv);
  void addAnmTar(f32 frame, const TarAxis &tar, CV_TYPE cv);
  void insertAnmTar(size_t index, const TarAxis &tar);
  void setFov(f32 fov, CV_TYPE cv);
  void addAnmFov(f32 frame, f32 fov, CV_TYPE cv);
  void insertAnmFov(size_t index, f32 fov);
  void setRotZ(f32 rotZ, CV_TYPE cv);
  void addAnmRotZ(f32 frame, f32 rotZ, CV_TYPE cv);
  void insertAnmRotZ(size_t index, f32 rotZ);
  void replay();
  void followPos(bool isFollow);
  bool isFollowPos() const;
  void followTar(bool isFollow);
  bool isFollowTar() const;
  void setNearfar(f32 nearClip, f32 farClip);
  void setNearfar(EVT_nearfar nearfar);
  void getPosString(mm::mtl::FixStr<256> &string);
  void getTarString(mm::mtl::FixStr<256> &string);
  void getFovString(mm::mtl::FixStr<256> &string);
  void getRotZString(mm::mtl::FixStr<256> &string);

private:
  u32 flags;
  AnmVec mPosAnm;
  AnmVec mTarAnm;
  AnmF32 mFovAnm;
  AnmF32 mRotZAnm;
  u8 _650[0xa70 - 0x650];
  mm::mtl::FixedVector<f32, KEY_COUNT> mFovKeys;
  mm::mtl::FixedVector<f32, KEY_COUNT> mRotZKeys;
};

static_assert(sizeof(CamHands) == 0xb00, "");

} // namespace event
