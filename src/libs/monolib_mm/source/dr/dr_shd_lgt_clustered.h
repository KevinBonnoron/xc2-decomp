#pragma once
#include <stddef.h>

#include "dr/dr_res_fetch.h"
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
  // Inferred role: cluster setting; original type name unknown.
  struct unknown001 {
    s32 unknown00; // Inferred role: div x; original member name unknown.
    s32 unknown04; // Inferred role: div y; original member name unknown.
    s32 unknown08; // Inferred role: div z; original member name unknown.
    s32 unknown0c; // Inferred role: light list entries per cluster; original member name unknown.
    s32 unknown10; // Inferred role: maximum light count; original member name unknown.
  };

  // Inferred role: view info; original type name unknown.
  struct unknown002 {
    grlib::CGLibDblUniformBlock unknown00;  // Inferred role: pnt light; original member name unknown.
    grlib::CGLibDblUniformBlock unknown38;  // Inferred role: spt light; original member name unknown.
    grlib::CGLibDblUniformBlock unknown70;  // Inferred role: pointer list; original member name unknown.
    grlib::CGLibDblUniformBlock unknowna8;  // Inferred role: light list; original member name unknown.
    grlib::CGLibDblUniformBlock unknowne0;  // Inferred role: cluster uniform; original member name unknown.
    grlib::CGLibDblUniformBlock unknown118; // Inferred role: param; original member name unknown.
    s32 unknown150;                         // Inferred role: pnt light count; original member name unknown.
    s32 unknown154;                         // Inferred role: spt light count; original member name unknown.
    s32 unknown158;                         // Inferred role: light list count; original member name unknown.
    u8 _15c[0x188 - 0x15c];
    u8 *unknown188; // Inferred role: light list data; original member name unknown.
  };

  DrShdLgtClustered(DrMan *drMan, bool isLowResolution);
  ~DrShdLgtClustered() override;
  void createWork();
  const unknown001 *getClusterSetting(u32 cate) const;
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

  static const unknown001 c_ClusterSettings[4]; // Name from the game symbol _ZN2ml17DrShdLgtClustered17c_ClusterSettingsE; also in torna and xc1de.

  bool unknown18;          // Inferred role: is low resolution; original member name unknown.
  unknown002 unknown20[4]; // Inferred role: view infos; original member name unknown.
  void *unknown660;        // Inferred role: allocated cluster work; original member name unknown.
  u32 unknown668;          // Inferred role: remaining size of the pnt light buffer; original member name unknown.
  u32 unknown66c;          // Inferred role: remaining size of the spt light buffer; original member name unknown.
  void *unknown670;        // Inferred role: pnt light buffer position; original member name unknown.
  void *unknown678;        // Inferred role: spt light buffer position; original member name unknown.
  void **unknown680;       // Inferred role: pnt light list of each cluster; original member name unknown.
  void **unknown688;       // Inferred role: spt light list of each cluster; original member name unknown.
  u32 unknown690;          // Inferred role: light list node count; original member name unknown.
  u32 unknown694;          // Inferred role: light list node maximum; original member name unknown.
  void *unknown698;        // Inferred role: light list nodes; original member name unknown.
  DrResFetch unknown6a0;   // Inferred role: light vertex fetch; original member name unknown.
};

static_assert(sizeof(DrShdLgtClustered::unknown001) == 0x14, "");
static_assert(offsetof(DrShdLgtClustered::unknown002, unknown150) == 0x150, "");
static_assert(offsetof(DrShdLgtClustered::unknown002, unknown158) == 0x158, "");
static_assert(offsetof(DrShdLgtClustered::unknown002, unknown188) == 0x188, "");
static_assert(offsetof(DrShdLgtClustered::unknown002, unknown154) == 0x154, "");
static_assert(sizeof(DrShdLgtClustered::unknown002) == 0x190, "");
static_assert(offsetof(DrShdLgtClustered, unknown18) == 0x18, "");
static_assert(offsetof(DrShdLgtClustered, unknown20) == 0x20, "");
static_assert(offsetof(DrShdLgtClustered, unknown660) == 0x660, "");
static_assert(offsetof(DrShdLgtClustered, unknown698) == 0x698, "");
static_assert(offsetof(DrShdLgtClustered, unknown6a0) == 0x6a0, "");
static_assert(sizeof(DrShdLgtClustered) == 0x6b0, "");

} // namespace ml
