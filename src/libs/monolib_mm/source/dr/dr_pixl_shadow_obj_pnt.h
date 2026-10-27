#pragma once
#include <stddef.h>

#include "dr/dr_calc_clip_work_sphere.h"
#include "dr/dr_pixl_shadow_obj.h"
#include "types.h"

namespace ml {
class DrMan;

class DrPixlShadowObjPnt : public DrPixlShadowObj {
public:
  DrPixlShadowObjPnt(DrMan *man, int index);
  ~DrPixlShadowObjPnt() override;
  void update() override;
  bool dispChk() override;
  bool clipChk(const mm::Vec3 &position, f32 value, bool flag) override;
  int clipTypeChk(const mm::Vec3 &position, f32 value) override;

  DrCalcClipWorkSphere unknown1a0; // Inferred role: clip sphere; original member name unknown.
};

static_assert(offsetof(DrPixlShadowObjPnt, unknown1a0) == 0x1a0, "");

} // namespace ml
