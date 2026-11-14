#pragma once
#include <stddef.h>

#include "dr/dr_calc_clip_work_shadow_plane.h"
#include "dr/dr_pixl_shadow_cache_obj.h"
#include "grlib/cglib_depth_target.h"
#include "grlib/cglib_uniform_array.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace grlib {
class CGLibDblUniformBlock;
} // namespace grlib

namespace ml {
class DrPixlMan;

class DrPixlShadowCacheMan {
public:
  class SHCACHE_WORK_TBL {
  public:
    DrPixlShadowCacheObj unknown0000[9]; // Inferred role: shadow cache objects; original member name unknown.
    u8 _5850[0x5854 - 0x5850];
    s32 unknown5854; // Inferred role: shadow map size; original member name unknown.
    u8 _5858[0x5940 - 0x5858];
    grlib::CGLibDepthTarget unknown5940; // Inferred role: shadow direction depth target; original member name unknown.
  };

  static_assert(offsetof(SHCACHE_WORK_TBL, unknown5854) == 0x5854, "");
  static_assert(offsetof(SHCACHE_WORK_TBL, unknown5940) == 0x5940, "");
  static_assert(sizeof(SHCACHE_WORK_TBL) == 0x6140, "");

  explicit DrPixlShadowCacheMan(DrPixlMan *pixlMan);
  ~DrPixlShadowCacheMan();
  bool isShadowMap() const;
  void callShadowCacheUpdate(bool isAll);
  void callShadowCacheVariance();
  void callFgShadowCacheUpdate();
  void update();
  void shadowCacheRender();
  void fastRender();
  void shadowmapRender(int index);
  void endMode();
  void setShadowDirRenderTarget(int index);
  void setupDirRenderTarget(int index);
  void *getShadowDirUniform(int index);
  void clearShadowMap();
  void clearZeroShadowMap();
  void addShadowCacheUpdate(bool isUpdate);
  void delShadowCacheUpdate();
  void callSelectShadowCacheUpdate(u64 mask);
  bool isShadowCache() const;
  u32 clipDirShadowChk(const mm::Vec3 &position, f32 radius, bool isFirst);
  void debugInfoRender();
  void debugShadowCacheRender();
  void createCacheBuff();
  void resetColorBuff();
  void createShadowTemp();
  void buffUpdate();

  u32 unknown00;                   // Inferred role: flags; original member name unknown.
  DrPixlMan *unknown08;            // Inferred role: pixl man; original member name unknown.
  SHCACHE_WORK_TBL unknown0010[4]; // Inferred role: shadow cache works; original member name unknown.
  grlib::CGLibUniformArray<grlib::CGLibDblUniformBlock> m_shadowDirUniform;
  u8 _18538[0x18540 - 0x18538];
  DrCalcClipWorkShadowPlane unknown18540[4]; // Inferred role: clip planes per shadow cascade, destroyed by the destructor; original member name unknown.
  u8 _18780[0x187a0 - 0x18780];
  s32 unknown187a0; // Inferred role: shadow map count per row; original member name unknown.
  s32 unknown187a4; // Inferred role: shadow cache objects per work table; original member name unknown.
  u8 _187a8[0x187ac - 0x187a8];
  s32 unknown187ac; // Inferred role: shadow cache update count; original member name unknown.
  u64 unknown187b0; // Inferred role: shadow cache select mask; original member name unknown.
};

static_assert(offsetof(DrPixlShadowCacheMan, unknown08) == 0x8, "");
static_assert(offsetof(DrPixlShadowCacheMan, unknown0010) == 0x10, "");
static_assert(offsetof(DrPixlShadowCacheMan, m_shadowDirUniform) == 0x18510, "");
static_assert(offsetof(DrPixlShadowCacheMan, unknown18540) == 0x18540, "");
static_assert(offsetof(DrPixlShadowCacheMan, unknown187a0) == 0x187a0, "");
static_assert(offsetof(DrPixlShadowCacheMan, unknown187a4) == 0x187a4, "");
static_assert(offsetof(DrPixlShadowCacheMan, unknown187ac) == 0x187ac, "");
static_assert(offsetof(DrPixlShadowCacheMan, unknown187b0) == 0x187b0, "");

} // namespace ml
