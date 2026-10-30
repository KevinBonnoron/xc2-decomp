#pragma once
#include <stddef.h>

#include "grlib/cglib_depth_target.h"
#include "grlib/cglib_uniform_array.h"
#include "types.h"

namespace grlib {
class CGLibDblUniformBlock;
} // namespace grlib

namespace ml {
class DrPixlMan;

class DrPixlShadowCacheMan {
public:
  class SHCACHE_WORK_TBL {
  public:
    u8 _000[0x5940 - 0x000];
    grlib::CGLibDepthTarget unknown5940; // Inferred role: shadow direction depth target; original member name unknown.
  };

  static_assert(offsetof(SHCACHE_WORK_TBL, unknown5940) == 0x5940, "");
  static_assert(sizeof(SHCACHE_WORK_TBL) == 0x6140, "");

  bool isShadowMap() const;
  void callShadowCacheUpdate(bool isAll);
  void callShadowCacheVariance();
  void callFgShadowCacheUpdate();
  void shadowCacheRender();
  void fastRender();
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
  void debugInfoRender();
  void createCacheBuff();
  void resetColorBuff();
  void createShadowTemp();
  void buffUpdate();

  u32 unknown00;                   // Inferred role: flags; original member name unknown.
  DrPixlMan *unknown08;            // Inferred role: pixl man; original member name unknown.
  SHCACHE_WORK_TBL unknown0010[4]; // Inferred role: shadow cache works; original member name unknown.
  grlib::CGLibUniformArray<grlib::CGLibDblUniformBlock> m_shadowDirUniform;
  u8 _18538[0x187ac - 0x18538];
  s32 unknown187ac; // Inferred role: shadow cache update count; original member name unknown.
  u64 unknown187b0; // Inferred role: shadow cache select mask; original member name unknown.
};

static_assert(offsetof(DrPixlShadowCacheMan, unknown08) == 0x8, "");
static_assert(offsetof(DrPixlShadowCacheMan, unknown0010) == 0x10, "");
static_assert(offsetof(DrPixlShadowCacheMan, m_shadowDirUniform) == 0x18510, "");
static_assert(offsetof(DrPixlShadowCacheMan, unknown187ac) == 0x187ac, "");
static_assert(offsetof(DrPixlShadowCacheMan, unknown187b0) == 0x187b0, "");

} // namespace ml
