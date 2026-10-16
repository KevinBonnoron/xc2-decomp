#pragma once
#include "event/cam_util.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

class RchaCam;

namespace event {

class CamBase;

class CamEvaPlayer {
public:
  CamEvaPlayer();
  virtual ~CamEvaPlayer();
  void stop();
  void update(f32 deltaFrame);
  bool getCamLook_roll(const mm::Vec3 &pos, const mm::Vec3 &target, u32 rotOrder, mm::Vec3 &look, f32 &roll) const;
  void setNearfar(EVT_nearfar nearfar);
  void play(CamBase *cam, void *data, const mm::Vec3 &offset);

private:
  CamBase *mCam;
  RchaCam *mRcha;
  f32 frame;
  mm::Vec3 mOffset;
  EVT_nearfar mNearfar;
};

static_assert(sizeof(CamEvaPlayer) == 0x40, "");

} // namespace event
