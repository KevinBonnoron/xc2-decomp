#pragma once
#include <stddef.h>

#include "dr/dr_mdo_shd_pxl_wrk_tex.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {
class DrLightObj;
class DrMan;
class DrPixlShadowObj;
class DrPixlShadowObjDir;

class DrPixlShadowMan {
public:
  void releaseShadow(DrPixlShadowObj *shadow);
  DrPixlShadowObj *createDirCacheShadow(DrLightObj *light, int index);
  void setAddShadowObj(DrPixlShadowObjDir *shadow);
  f32 getShadowTexSize(int index);
  void beforUpdate();
  void afterUpdate();
  bool setAddObjPos(const mm::Vec3 &position, f32 value);
  bool setSptCalcPos(const mm::Vec3 &position, f32 value);
  MdoShdPxlWrkTex *createShdTexWrk(int index, int type);
  void releaseTexWorkOne(MdoShdPxlWrkTex *work);
  void releaseTexWork();

  DrPixlShadowObj *unknown0000[256]; // Inferred role: shadow objects; original member name unknown.
  MdoShdPxlWrkTex unknown0800[16];   // Inferred role: shadow textures; original member name unknown.
  s32 unknown8900;                   // Inferred role: shadow object count; original member name unknown.
  u8 _8904[0x8908 - 0x8904];
  DrMan *unknown8908; // Inferred role: driver manager; original member name unknown.
  u8 _8910[0x8918 - 0x8910];
  DrPixlShadowObjDir *unknown8918; // Inferred role: additional shadow object; original member name unknown.
};

static_assert(offsetof(DrPixlShadowMan, unknown0800) == 0x0800, "");
static_assert(offsetof(DrPixlShadowMan, unknown8900) == 0x8900, "");
static_assert(offsetof(DrPixlShadowMan, unknown8908) == 0x8908, "");
static_assert(offsetof(DrPixlShadowMan, unknown8918) == 0x8918, "");

} // namespace ml
