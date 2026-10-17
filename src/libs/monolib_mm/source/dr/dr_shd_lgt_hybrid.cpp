#include "dr/dr_shd_lgt_hybrid.h"

#include "dr/dr_man.h"
#include "dr/dr_shd_lgt_clustered.h"
#include "dr/dr_shd_lgt_tile_based_dr.h"
#include "mtl/alloc_handle.h"

namespace ml {

DrShdLgtHybrid::DrShdLgtHybrid(DrMan *drMan) {
  m_cate = 0;
  m_drMan = drMan;
  m_clustered = new (drMan->memSys) DrShdLgtClustered(drMan, false);
  m_tileBasedDr = new (drMan->memSys) DrShdLgtTileBasedDr(drMan);
}

DrShdLgtHybrid::~DrShdLgtHybrid() {
  if (m_clustered != nullptr) {
    delete m_clustered;
    m_clustered = nullptr;
  }
  if (m_tileBasedDr != nullptr) {
    delete m_tileBasedDr;
    m_tileBasedDr = nullptr;
  }
}

void DrShdLgtHybrid::stockBegin() {
  m_clustered->stockBegin();
  m_tileBasedDr->stockBegin();
}

void DrShdLgtHybrid::stockEnd() {
  m_clustered->stockEnd();
  m_tileBasedDr->stockEnd();
}

void DrShdLgtHybrid::update() {
  m_clustered->update();
  m_tileBasedDr->update();
}

void DrShdLgtHybrid::setupCate(int cate) {
  m_cate = cate;
  m_clustered->setupCate(cate);
  m_tileBasedDr->setupCate(cate);
}

void DrShdLgtHybrid::addViewInfo(int cate) {
  m_clustered->addViewInfo(cate);
  m_tileBasedDr->addViewInfo(cate);
}

void DrShdLgtHybrid::delViewInfo(int cate) {
  m_clustered->delViewInfo(cate);
  m_tileBasedDr->delViewInfo(cate);
}

void DrShdLgtHybrid::stockPntList(DrLightObjPnt *light) {
  m_clustered->stockPntList(light);
  m_tileBasedDr->stockPntList(light);
}

void DrShdLgtHybrid::stockSptList(DrLightObjSpt *light) {
  m_clustered->stockSptList(light);
  m_tileBasedDr->stockSptList(light);
}

void DrShdLgtHybrid::debugRender() {
  switch (m_drMan->dynamicLightType) {
  case DR_SHD_LGT_DYNAMIC_TILE_BASED:
    m_tileBasedDr->debugRender();
    break;
  case DR_SHD_LGT_DYNAMIC_CLUSTERED:
    m_clustered->debugRender();
    break;
  }
}

} // namespace ml
