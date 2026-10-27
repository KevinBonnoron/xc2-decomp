#pragma once
#include <stddef.h>

#include "dr/dr_shd_lgt_dynamic.h"
#include "grlib/cglib_dbl_uniform_block.h"
#include "types.h"

namespace grlib {
class CGLibTexture;
} // namespace grlib

namespace mm {
struct Vec2;
struct Vec3;
} // namespace mm

namespace ml {
class DrMan;

class DrShdLgtClustered : public DrShdLgtDynamic {
public:
  struct ClusterSetting {
    s32 unknown00; // Inferred role: div x; original member name unknown.
    s32 unknown04; // Inferred role: div y; original member name unknown.
    s32 unknown08; // Inferred role: div z; original member name unknown.
    u8 _0c[0x14 - 0xc];
  };

  struct ViewInfo {
    grlib::CGLibDblUniformBlock unknown00; // Inferred role: pnt light; original member name unknown.
    grlib::CGLibDblUniformBlock unknown38; // Inferred role: spt light; original member name unknown.
    grlib::CGLibDblUniformBlock unknown70; // Inferred role: pointer list; original member name unknown.
    grlib::CGLibDblUniformBlock unknowna8; // Inferred role: light list; original member name unknown.
    u8 _e0[0x118 - 0xe0];
    grlib::CGLibDblUniformBlock unknown118; // Inferred role: param; original member name unknown.
    s32 unknown150;                         // Inferred role: pnt light count; original member name unknown.
    s32 unknown154;                         // Inferred role: spt light count; original member name unknown.
    u8 _158[0x188 - 0x158];
    u8 *unknown188; // Inferred role: light list data; original member name unknown.
  };

  DrShdLgtClustered(DrMan *drMan, bool isLowResolution);
  ~DrShdLgtClustered() override;
  const ClusterSetting *getClusterSetting(u32 cate) const;
  void stockBegin() override;
  void stockEnd() override;
  void update() override;
  void addViewInfo(int cate) override;
  void delViewInfo(int cate) override;
  void stockPntList(DrLightObjPnt *light) override;
  void stockSptList(DrLightObjSpt *light) override;
  void setPntLightUniformBlock(u32 cate, u32 index);
  void setSptLightUniformBlock(u32 cate, u32 index);
  void setPointerListUniformBlock(u32 cate, u32 index);
  void setLightListUniformBlock(u32 cate, u32 index);
  void setParamUniformBlock(u32 cate, u32 index);
  void setPntLightStorageBuffer(u32 cate, u32 index);
  void setSptLightStorageBuffer(u32 cate, u32 index);
  void setPointerListStorageBuffer(u32 cate, u32 index);
  void setLightListStorageBuffer(u32 cate, u32 index);
  void setParamStorageBuffer(u32 cate, u32 index);
  grlib::CGLibTexture *getLightListTexture(u32 cate) const;
  void beginLightList();
  void setLightListData(u32 index, int data);
  u8 getLightListData(u32 index);
  void endLightList();
  void render(DrShdLgtMan *shdLgtMan, DrLightMan *lightMan) override;
  void debugRender() override;
  void ssboBiteSwap();
  void convertToViewProj(mm::Vec3 &result, const mm::Vec2 &position);

  static const ClusterSetting c_ClusterSettings[4];

  bool unknown18;        // Inferred role: is low resolution; original member name unknown.
  ViewInfo unknown20[3]; // Inferred role: view infos; original member name unknown.
  u8 _4d0[0x6b0 - 0x4d0];
};

static_assert(offsetof(DrShdLgtClustered::ViewInfo, unknown150) == 0x150, "");
static_assert(offsetof(DrShdLgtClustered::ViewInfo, unknown154) == 0x154, "");
static_assert(sizeof(DrShdLgtClustered::ViewInfo) == 0x190, "");
static_assert(offsetof(DrShdLgtClustered, unknown18) == 0x18, "");
static_assert(offsetof(DrShdLgtClustered, unknown20) == 0x20, "");
static_assert(sizeof(DrShdLgtClustered) == 0x6b0, "");

} // namespace ml
