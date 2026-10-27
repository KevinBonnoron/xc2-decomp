#pragma once
#include <stddef.h>

#include "dr/dr_calc_clip_work_plane.h"
#include "dr/dr_pixl_shadow_obj.h"
#include "mm_math/mm_vec2.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ml {

class DrPixlShadowObjDir : public DrPixlShadowObj {
public:
  ~DrPixlShadowObjDir() override;
  void update() override;
  bool dispChk() override;
  bool clipChk(const mm::Vec3 &position, f32 value, bool flag) override;
  int clipTypeChk(const mm::Vec3 &position, f32 value) override;
  void debugInfo() override;
  void calcLgtMat();
  bool setAddObjPos(const mm::Vec3 &position, f32 value);

  DrCalcClipWorkPlane unknown1a0; // Inferred role: clip planes; original member name unknown.
  u8 _270[0x2b0 - 0x270];
  f32 unknown2b0; // Inferred role: scale; original member name unknown.
  u8 _2b4[0x300 - 0x2b4];
  mm::Vec3 unknown300; // Inferred role: clip line start; original member name unknown.
  u8 _310[0x338 - 0x310];
  mm::Vec2 unknown338; // Inferred role: clip distances; original member name unknown.
  f32 unknown340;      // Inferred role: scale; original member name unknown.
};

static_assert(offsetof(DrPixlShadowObjDir, unknown1a0) == 0x1a0, "");
static_assert(offsetof(DrPixlShadowObjDir, unknown2b0) == 0x2b0, "");
static_assert(offsetof(DrPixlShadowObjDir, unknown300) == 0x300, "");
static_assert(offsetof(DrPixlShadowObjDir, unknown338) == 0x338, "");
static_assert(offsetof(DrPixlShadowObjDir, unknown340) == 0x340, "");

} // namespace ml
