#pragma once
#include <stddef.h>

#include "dr/dr_shd_lgt_dynamic.h"

namespace ml {
class DrShdLgtClustered;
class DrShdLgtTileBasedDr;
class DrMan;

class DrShdLgtHybrid : public DrShdLgtDynamic {
public:
  DrShdLgtHybrid(DrMan *drMan);
  ~DrShdLgtHybrid() override;
  void stockBegin() override;
  void stockEnd() override;
  void update() override;
  void setupCate(int cate) override;
  void addViewInfo(int cate) override;
  void delViewInfo(int cate) override;
  void stockPntList(DrLightObjPnt *light) override;
  void stockSptList(DrLightObjSpt *light) override;
  void render(DrShdLgtMan *shdLgtMan, DrLightMan *lightMan) override;
  void debugRender() override;

  DrShdLgtClustered *unknown18;   // Inferred role: clustered; original member name unknown.
  DrShdLgtTileBasedDr *unknown20; // Inferred role: tile based dr; original member name unknown.
};

static_assert(offsetof(DrShdLgtHybrid, unknown10) == 0x10, "");
static_assert(offsetof(DrShdLgtHybrid, unknown18) == 0x18, "");
static_assert(offsetof(DrShdLgtHybrid, unknown20) == 0x20, "");

} // namespace ml
