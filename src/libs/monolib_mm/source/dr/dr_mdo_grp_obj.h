#pragma once
#include <stddef.h>

#include "dr/dr_mdl_base.h"
#include "dr/dr_res_chank_list.h"
#include "dr/dr_res_mdo_sort.h"
#include "types.h"

namespace ml {

class DrMdlObj;

class DrMdoGrpObj : public DrMdlBase {
public:
  DrMdoGrpObj(int viewNum, u32 num);
  ~DrMdoGrpObj() override;
  void update() override;
  void dispOffUpdate() override;
  void resourceInit() override;
  void shadowRender() override;
  bool shadowCacheRender(DrPixlShadowCacheObj &cache) override;
  void shadowCacheOnlyRender() override;
  void callShadowCacheUpdate(u64 flags) override;
  void occRender() override;
  DrMdlObj *createMdl(const void *data, const char *name, u32 index);
  DrMdlObj *createInstantMdl(const void *data, const char *name, u32 index);
  void updateList();
  void callNomSetupRender();
  void callZSortNomZpreePassRender();
  void callZSortThicknessRenderFirst();
  void callZSortThicknessRenderSecond();
  void callZSortNomRender();
  void callZSortGBuffRender();
  void callZSortLightPrePassRender();
  void callZSortNomAlphaRender();
  void callZSortNomSpAlphaRender();
  void callZSortNomRefractionRender();

  DrResChankList<DrMdlBase> *unknown28;   // Inferred role: models of each group; original member name unknown.
  DrResChankList<DrMdlBase> **unknown30;  // Inferred role: lists of the groups that have models; original member name unknown.
  DrResChankList<DrMdlBase> unknown38[2]; // Inferred role: models created in each buffer, sorted into the groups by updateList; original member name unknown.
  DrResChankList<DrMdlBase> unknown58;    // Inferred role: models to delete; original member name unknown.
  s32 unknown68;                          // Inferred role: group count; original member name unknown.
  s32 unknown6c;                          // Inferred role: count of the groups that have models; original member name unknown.
  void *unknown70;                        // Inferred role: allocated work; original member name unknown.
  DrResMdoSortGrp unknown78;              // Inferred role: z sort object; original member name unknown.
};

static_assert(offsetof(DrMdoGrpObj, unknown28) == 0x28, "");
static_assert(offsetof(DrMdoGrpObj, unknown30) == 0x30, "");
static_assert(offsetof(DrMdoGrpObj, unknown38) == 0x38, "");
static_assert(offsetof(DrMdoGrpObj, unknown58) == 0x58, "");
static_assert(offsetof(DrMdoGrpObj, unknown68) == 0x68, "");
static_assert(offsetof(DrMdoGrpObj, unknown6c) == 0x6c, "");
static_assert(offsetof(DrMdoGrpObj, unknown70) == 0x70, "");
static_assert(offsetof(DrMdoGrpObj, unknown78) == 0x78, "");
static_assert(sizeof(DrMdoGrpObj) == 0x98, "");

} // namespace ml
