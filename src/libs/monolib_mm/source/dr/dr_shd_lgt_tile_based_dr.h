#pragma once
#include "dr/dr_shd_lgt_dynamic.h"
#include "types.h"

namespace ml {
class DrMan;

class DrShdLgtTileBasedDr : public DrShdLgtDynamic {
public:
  DrShdLgtTileBasedDr(DrMan *drMan);
  ~DrShdLgtTileBasedDr() override;
  void stockBegin() override;
  void update() override;
  void addViewInfo(int cate) override;
  void delViewInfo(int cate) override;
  void stockPntList(DrLightObjPnt *light) override;
  void stockSptList(DrLightObjSpt *light) override;
  void render(DrShdLgtMan *shdLgtMan, DrLightMan *lightMan) override;
  void debugRender() override;
  void stockEnd() override;

  u8 _18[0x398 - 0x18];
};

static_assert(sizeof(DrShdLgtTileBasedDr) == 0x398, "");

} // namespace ml
