#pragma once
#include <stddef.h>

#include "dr/dr_calc_clip_work_plane.h"
#include "dr/dr_pixl_shadow_obj.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ml {
class DrMan;

class DrPixlShadowObjDir : public DrPixlShadowObj {
public:
  DrPixlShadowObjDir(DrMan *man);
  ~DrPixlShadowObjDir() override;
  void update() override;
  bool dispChk() override;
  bool clipChk(const mm::Vec3 &position, f32 value, bool flag) override;
  int clipTypeChk(const mm::Vec3 &position, f32 value) override;
  void debugInfo() override;
  void calcLgtMat();
  bool setAddObjPos(const mm::Vec3 &position, f32 value);
  bool clipAddTypeChk(const mm::Vec3 &position, f32 value);

  DrCalcClipWorkPlane unknown1a0; // Inferred role: clip planes; original member name unknown.
  u8 _270[0x2b0 - 0x270];
  f32 unknown2b0; // Inferred role: scale; original member name unknown.
  u8 _2b4[0x300 - 0x2b4];
  mm::Vec3 unknown300; // Inferred role: clip line start; original member name unknown.
  u8 _310[0x338 - 0x310];
  // Decision 2026-11-14 #4: two scalars, not a mm::Pnt<f32>. The game's constructor stores 5.0f and 30.0f here with one merged 64-bit
  // `str x9, [x20, #0x338]` (0x7100863534) and every reader (clipChk, clipTypeChk, setAddObjPos, clipAddTypeChk, update, calcLgtMat)
  // loads one float at a time; a Pnt<f32> member gives two 32-bit stores (40 instructions instead of 38).
  f32 unknown338; // Inferred role: clip distance; original member name unknown.
  f32 unknown33c; // Inferred role: second clip distance; original member name unknown.
  f32 unknown340; // Inferred role: scale; original member name unknown.
};

static_assert(offsetof(DrPixlShadowObjDir, unknown1a0) == 0x1a0, "");
static_assert(offsetof(DrPixlShadowObjDir, unknown2b0) == 0x2b0, "");
static_assert(offsetof(DrPixlShadowObjDir, unknown300) == 0x300, "");
static_assert(offsetof(DrPixlShadowObjDir, unknown338) == 0x338, "");
static_assert(offsetof(DrPixlShadowObjDir, unknown33c) == 0x33c, "");
static_assert(offsetof(DrPixlShadowObjDir, unknown340) == 0x340, "");
static_assert(sizeof(DrPixlShadowObjDir) == 0x350, "");

} // namespace ml
