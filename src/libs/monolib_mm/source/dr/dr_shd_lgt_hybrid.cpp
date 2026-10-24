#include "dr/dr_shd_lgt_hybrid.h"

#include "dr/dr_man.h"
#include "dr/dr_shd_lgt_clustered.h"
#include "dr/dr_shd_lgt_tile_based_dr.h"
#include "mtl/alloc_handle.h"

namespace ml {

DrShdLgtHybrid::DrShdLgtHybrid(DrMan *drMan) {
  unknown08 = 0;
  unknown10 = drMan;
  unknown18 = new (drMan->unknown0c) DrShdLgtClustered(drMan, false);
  unknown20 = new (drMan->unknown0c) DrShdLgtTileBasedDr(drMan);
}

DrShdLgtHybrid::~DrShdLgtHybrid() {
  if (unknown18 != nullptr) {
    delete unknown18;
    unknown18 = nullptr;
  }
  if (unknown20 != nullptr) {
    delete unknown20;
    unknown20 = nullptr;
  }
}

void DrShdLgtHybrid::stockBegin() {
  unknown18->stockBegin();
  unknown20->stockBegin();
}

void DrShdLgtHybrid::stockEnd() {
  unknown18->stockEnd();
  unknown20->stockEnd();
}

void DrShdLgtHybrid::update() {
  unknown18->update();
  unknown20->update();
}

void DrShdLgtHybrid::setupCate(int cate) {
  unknown08 = cate;
  unknown18->setupCate(cate);
  unknown20->setupCate(cate);
}

void DrShdLgtHybrid::addViewInfo(int cate) {
  unknown18->addViewInfo(cate);
  unknown20->addViewInfo(cate);
}

void DrShdLgtHybrid::delViewInfo(int cate) {
  unknown18->delViewInfo(cate);
  unknown20->delViewInfo(cate);
}

void DrShdLgtHybrid::stockPntList(DrLightObjPnt *light) {
  unknown18->stockPntList(light);
  unknown20->stockPntList(light);
}

void DrShdLgtHybrid::stockSptList(DrLightObjSpt *light) {
  unknown18->stockSptList(light);
  unknown20->stockSptList(light);
}

void DrShdLgtHybrid::debugRender() {
  switch (unknown10->unknown1da4) {
  case DR_SHD_LGT_DYNAMIC_TILE_BASED:
    unknown20->debugRender();
    break;
  case DR_SHD_LGT_DYNAMIC_CLUSTERED:
    unknown18->debugRender();
    break;
  }
}

} // namespace ml
