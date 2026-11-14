#pragma once
#include <stddef.h>

#include "dr/dr_calc_clip_work_plane.h"
#include "grlib/cglib_depth_target.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ml {

class DrPixlShadowCacheObj : public grlib::CGLibDepthTarget {
public:
  DrPixlShadowCacheObj();
  ~DrPixlShadowCacheObj();
  void createShadow(int size, u32 resArea);
  void release();
  void begin();
  bool clipTest(const mm::Vec3 &position, f32 radius);
  void end();
  void setClear();
  void setNewGrid();
  void update(const mm::Mat44 &view, const mm::Mat44 &projection, const mm::Vec3 &center, int gridX, int gridY);
  void setBigMode(bool isBig);
  void setID(int id);
  void depthClear();
  void debugRender(int x, int y, int size);

  u64 unknown800;       // Inferred role: cleared by the constructor; original member name unknown.
  u32 unknown808;       // Inferred role: flags; original member name unknown.
  s32 unknown80c;       // Inferred role: shadow size; original member name unknown.
  mm::Mat44 unknown810; // Inferred role: shadow matrix; original member name unknown.
  mm::Mat44 unknown850; // Inferred role: shadow view projection matrix; original member name unknown.
  mm::Mat44 unknown890; // Inferred role: shadow projection matrix; original member name unknown.
  mm::Vec3 unknown8d0;  // Inferred role: shadow center; original member name unknown.
  s32 unknown8e0;       // Inferred role: grid x; original member name unknown.
  s32 unknown8e4;       // Inferred role: grid y; original member name unknown.
  u64 unknown8e8;       // Inferred role: id mask; original member name unknown.
  u16 unknown8f0;       // Inferred role: id; original member name unknown.
  s16 unknown8f2;       // Inferred role: id; original member name unknown.
  u8 _8f4[0x900 - 0x8f4];
  DrCalcClipWorkPlane unknown900; // Inferred role: clip work; original member name unknown.
};

static_assert(offsetof(DrPixlShadowCacheObj, unknown800) == 0x800, "");
static_assert(offsetof(DrPixlShadowCacheObj, unknown808) == 0x808, "");
static_assert(offsetof(DrPixlShadowCacheObj, unknown80c) == 0x80c, "");
static_assert(offsetof(DrPixlShadowCacheObj, unknown810) == 0x810, "");
static_assert(offsetof(DrPixlShadowCacheObj, unknown850) == 0x850, "");
static_assert(offsetof(DrPixlShadowCacheObj, unknown8d0) == 0x8d0, "");
static_assert(offsetof(DrPixlShadowCacheObj, unknown8e0) == 0x8e0, "");
static_assert(offsetof(DrPixlShadowCacheObj, unknown8e4) == 0x8e4, "");
static_assert(offsetof(DrPixlShadowCacheObj, unknown8e8) == 0x8e8, "");
static_assert(offsetof(DrPixlShadowCacheObj, unknown8f2) == 0x8f2, "");
static_assert(offsetof(DrPixlShadowCacheObj, unknown900) == 0x900, "");

} // namespace ml
