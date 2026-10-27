#pragma once
#include <stddef.h>

#include "dr/dr_calc_clip_work_cone.h"
#include "dr/dr_pixl_shadow_obj.h"
#include "mm_math/mm_vec2.h"
#include "types.h"

namespace ml {
class DrMan;

class DrPixlShadowObjSpt : public DrPixlShadowObj {
public:
  DrPixlShadowObjSpt(DrMan *man);
  ~DrPixlShadowObjSpt() override;
  void update() override;
  void afterUpdate() override;
  bool dispChk() override;
  bool clipChk(const mm::Vec3 &position, f32 value, bool flag) override;
  int clipTypeChk(const mm::Vec3 &position, f32 value) override;
  bool setSptCalcPos(const mm::Vec3 &position, f32 value) override;
  void renderLight() override;
  void stockTile() override;
  const f32 *getParmTbl() const override;

  DrCalcClipWorkCone unknown1a0; // Inferred role: clip cone; original member name unknown.
  f32 unknown200[8];             // Inferred role: shadow parameters; original member name unknown.
  f32 unknown220[3];             // Inferred role: shadow screen range; original member name unknown.
  mm::Vec2 unknown22c;           // Inferred role: shadow screen range end and clip distance; original member name unknown.
};

static_assert(offsetof(DrPixlShadowObjSpt, unknown1a0) == 0x1a0, "");
static_assert(offsetof(DrPixlShadowObjSpt, unknown200) == 0x200, "");
static_assert(offsetof(DrPixlShadowObjSpt, unknown220) == 0x220, "");
static_assert(offsetof(DrPixlShadowObjSpt, unknown22c) == 0x22c, "");

} // namespace ml
