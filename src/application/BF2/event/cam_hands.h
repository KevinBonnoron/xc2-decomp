#pragma once
#include <stddef.h>

#include "event/anm_f32.h"
#include "event/anm_vec.h"
#include "event/cam_base.h"
#include "event/cam_util.h"
#include "event/curve.h"
#include "event/pos_axis.h"
#include "event/tar_axis.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace event {

class CamHands : public CamBase {
public:
  static constexpr u32 KEY_COUNT = 16;

  enum {
    FLAG_FOLLOW_POS = 1 << 0,
    FLAG_FOLLOW_TAR = 1 << 1,
    FLAG_FOLLOW_TAR_ANGLE = 1 << 2,
  };

  CamHands(bool isFocal);
  virtual ~CamHands() {}
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
  void setFollowTarAngle(u32 axis) {
    if (axis == TarAxis::AXIS_ANGLE || axis == TarAxis::AXIS_ANGLE_GLOBAL) {
      flags |= FLAG_FOLLOW_TAR_ANGLE;
    } else {
      flags &= ~FLAG_FOLLOW_TAR_ANGLE;
    }
  }

  u32 flags;
  AnmVec posAnm;
  AnmVec tarAnm;
  AnmF32 fovAnm;
  AnmF32 rotZAnm;
  mm::mtl::FixedVector<PosAxis, KEY_COUNT> posAxes;
  mm::mtl::FixedVector<TarAxis, KEY_COUNT> tarAxes;
  mm::mtl::FixedVector<f32, KEY_COUNT> fovs;
  mm::mtl::FixedVector<f32, KEY_COUNT> rotZs;
};

static_assert(sizeof(CamHands) == 0xb00, "");

} // namespace event
