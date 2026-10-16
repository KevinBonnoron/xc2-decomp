#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {
class DrMan;
class DrPixlShadowMan;

struct DrBlurTarget {
  u8 _00[0x28 - 0x00];
  void *velocityMap;
};

static_assert(offsetof(DrBlurTarget, velocityMap) == 0x28, "");

struct DrViewBlur {
  u8 _00[0x50 - 0x00];
  DrBlurTarget *target;
};

static_assert(offsetof(DrViewBlur, target) == 0x50, "");

struct wkPixlManRes {
  u8 _000[0x178 - 0x000];
  DrPixlShadowMan *shadowMan;
  DrViewBlur *blur;
  u8 _188[0x1f8 - 0x188];
};

static_assert(offsetof(wkPixlManRes, shadowMan) == 0x178, "");
static_assert(offsetof(wkPixlManRes, blur) == 0x180, "");
static_assert(sizeof(wkPixlManRes) == 0x1f8, "");

class DrPixlMan {
public:
  void setMainRenderTarget();
  void updateShadowDisplayList();
  void callShadowCacheVariance();
  void fastRender();
  grlib::CGLibTextureBuffer *getDammyTexObj();

  u8 _00[0x08 - 0x00];
  DrMan *m_drMan;
  wkPixlManRes m_resources[4];
  wkPixlManRes *m_res;
  u8 _7f8[0x800 - 0x7f8];
  u32 *m_lightFlags;
};

static_assert(offsetof(DrPixlMan, m_resources) == 0x10, "");
static_assert(offsetof(DrPixlMan, m_res) == 0x7f0, "");
static_assert(offsetof(DrPixlMan, m_lightFlags) == 0x800, "");

} // namespace ml
