#pragma once

#include <stddef.h>

#include "dr/dr_mdo_ctl_seam.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {
class DrPixlShadowCacheObj;
class DrPixlShadowObj;
class DrResMdoSeamWrkBase;

// Inferred role: base map data of the seam resource; original type name unknown.
struct unknown700 {
  f32 unknown00[3]; // Inferred role: maximum position of the area; original member name unknown.
  f32 unknown0c[3]; // Inferred role: minimum position of the area; original member name unknown.
  u8 _18[0x28 - 0x18];
  u32 unknown28; // Inferred role: flags; original member name unknown.
  u8 _2c[0x34 - 0x2c];
  u32 unknown34; // Inferred role: data offset; original member name unknown.
  s32 unknown38; // Inferred role: memory size; original member name unknown.
  u8 _3c[0x4c - 0x3c];
};

static_assert(offsetof(unknown700, unknown0c) == 0x0c, "");
static_assert(offsetof(unknown700, unknown28) == 0x28, "");
static_assert(offsetof(unknown700, unknown34) == 0x34, "");
static_assert(offsetof(unknown700, unknown38) == 0x38, "");
static_assert(sizeof(unknown700) == 0x4c, "");

class DrMdoCtlSeamBaseMap : public DrMdoCtlSeam {
public:
  DrMdoCtlSeamBaseMap(int viewNum);
  void updateBaseMap();
  void readBaseMapCheck();
  void updateBaseMapRenderList();
  bool readBaseModelCheck(bool &isRead, const mm::Vec3 &position, bool isFirst);
  void basemapReadCheck();
  void checkBaseMapMode();
  void initBaseMapParts(DrResMdoSeamWrkBase *base);
  void changeMemBaseMapParts(DrResMdoSeamWrkBase *base);
  void callRenderSeamBaseMap();
  void callGBuffRenderSeamBaseMap();
  void callLightPrePassRenderSeamBaseMap();
  void callRefractionRenderSeamBaseMap();
  void callAlphaRenderSeamBaseMap();
  void callSpAlphaRenderSeamBaseMap();
  void renderSeamBaseMap(int renderType);
  void createBaseMapDisplayList();
  void releaseBaseMap();
  DrResMdoSeamWrkBase *seachBaseIdx(int index);
  void releaseFreeSeamBase(DrResMdoSeamWrkBase *base);
  DrResMdoSeamWrkBase *createFreeSeamBase();
  void callShadowCacheBaseUpdate(u64 flags);
  void createBaseZPrePassDisplayList();
  void createBaseThicknesPassDisplayList(bool isFirst);
  void callShadowMapRenderSeamBaseMap(DrPixlShadowObj *shadow);
  void callBaseShadowCacheRender(DrPixlShadowCacheObj &cache);

  // Names from the game symbols _ZN2ml19DrMdoCtlSeamBaseMap27SEAM_BASEMAP_READ_DEN_CHECKE (0x71011b3148) and ...26SEAM_BASEMAP_READ_IN_CHECKE
  // (0x71011b314c); writable data, initial values read from the game's .data (100.0f, 5.0f).
  static f32 SEAM_BASEMAP_READ_DEN_CHECK;
  static f32 SEAM_BASEMAP_READ_IN_CHECK;
};

} // namespace ml
