#pragma once
#include <stddef.h>

#include "dr/dr_calc_clip_work_plane.h"
#include "grlib/cglib_depth_target.h"
#include "mm_math/mm_mat44.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {

class DrPixlShadowCacheObj : public grlib::CGLibDepthTarget {
public:
  void release();
  void begin();
  bool clipTest(const mm::Vec3 &position, f32 radius);
  void end();
  void setClear();
  void setNewGrid();
  void setBigMode(bool isBig);
  void setID(int id);

  u8 _128[0x808 - 0x128];
  u32 unknown808; // Inferred role: flags; original member name unknown.
  u8 _80c[0x810 - 0x80c];
  mm::Mat44 unknown810; // Inferred role: shadow matrix; original member name unknown.
  u8 _850[0x8e8 - 0x850];
  u64 unknown8e8; // Inferred role: id mask; original member name unknown.
  u16 unknown8f0; // Inferred role: id; original member name unknown.
  u16 unknown8f2; // Inferred role: id; original member name unknown.
  u8 _8f4[0x900 - 0x8f4];
  DrCalcClipWorkPlane unknown900; // Inferred role: clip work; original member name unknown.
};

static_assert(offsetof(DrPixlShadowCacheObj, unknown808) == 0x808, "");
static_assert(offsetof(DrPixlShadowCacheObj, unknown810) == 0x810, "");
static_assert(offsetof(DrPixlShadowCacheObj, unknown8e8) == 0x8e8, "");
static_assert(offsetof(DrPixlShadowCacheObj, unknown8f2) == 0x8f2, "");
static_assert(offsetof(DrPixlShadowCacheObj, unknown900) == 0x900, "");

} // namespace ml
