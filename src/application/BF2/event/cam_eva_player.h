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
  CamBase *unknown08;    // Inferred role: cam; original member name unknown.
  RchaCam *unknown10;    // Inferred role: rcha; original member name unknown.
  f32 unknown18;         // Inferred role: frame; original member name unknown.
  mm::Vec3 unknown20;    // Inferred role: offset; original member name unknown.
  EVT_nearfar unknown30; // Inferred role: nearfar; original member name unknown.
};

static_assert(sizeof(CamEvaPlayer) == 0x40, "");

} // namespace event
