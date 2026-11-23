#include "dr/dr_shd_lgt_hybrid.h"

#include "dr/dr_man.h"
#include "dr/dr_shd_lgt_clustered.h"
#include "dr/dr_shd_lgt_tile_based_dr.h"
#include "mtl/alloc_handle.h"

namespace ml {

DrShdLgtHybrid::DrShdLgtHybrid(DrMan *drMan) {
  unknown08 = 0;
  m_drMan = drMan;
  m_drShdLgtClustered = new (drMan->unknown0c) DrShdLgtClustered(drMan, false);
  m_drShdLgtTileBasedDr = new (drMan->unknown0c) DrShdLgtTileBasedDr(drMan);
}

DrShdLgtHybrid::~DrShdLgtHybrid() {
  if (m_drShdLgtClustered != nullptr) {
    delete m_drShdLgtClustered;
    m_drShdLgtClustered = nullptr;
  }
  if (m_drShdLgtTileBasedDr != nullptr) {
    delete m_drShdLgtTileBasedDr;
    m_drShdLgtTileBasedDr = nullptr;
  }
}

void DrShdLgtHybrid::render(DrShdLgtMan *shdLgtMan, DrLightMan *lightMan) {
  if (m_drMan->unknown1da4 != 1) {
    if (m_drMan->unknown1da4 != 0) {
      return;
    }
    m_drShdLgtTileBasedDr->render(shdLgtMan, lightMan);
    return;
  }
  if (DrMan::getIns()->unknown1d70) {
    return;
  }
  m_drShdLgtClustered->render(shdLgtMan, lightMan);
}

void DrShdLgtHybrid::stockBegin() {
  m_drShdLgtClustered->stockBegin();
  m_drShdLgtTileBasedDr->stockBegin();
}

void DrShdLgtHybrid::stockEnd() {
  m_drShdLgtClustered->stockEnd();
  m_drShdLgtTileBasedDr->stockEnd();
}

void DrShdLgtHybrid::update() {
  m_drShdLgtClustered->update();
  m_drShdLgtTileBasedDr->update();
}

void DrShdLgtHybrid::setupCate(int cate) {
  unknown08 = cate;
  m_drShdLgtClustered->setupCate(cate);
  m_drShdLgtTileBasedDr->setupCate(cate);
}

void DrShdLgtHybrid::addViewInfo(int cate) {
  m_drShdLgtClustered->addViewInfo(cate);
  m_drShdLgtTileBasedDr->addViewInfo(cate);
}

void DrShdLgtHybrid::delViewInfo(int cate) {
  m_drShdLgtClustered->delViewInfo(cate);
  m_drShdLgtTileBasedDr->delViewInfo(cate);
}

void DrShdLgtHybrid::stockPntList(DrLightObjPnt *light) {
  m_drShdLgtClustered->stockPntList(light);
  m_drShdLgtTileBasedDr->stockPntList(light);
}

void DrShdLgtHybrid::stockSptList(DrLightObjSpt *light) {
  m_drShdLgtClustered->stockSptList(light);
  m_drShdLgtTileBasedDr->stockSptList(light);
}

void DrShdLgtHybrid::debugRender() {
  switch (m_drMan->unknown1da4) {
  case unknown063_0:
    m_drShdLgtTileBasedDr->debugRender();
    break;
  case unknown063_1:
    m_drShdLgtClustered->debugRender();
    break;
  }
}

} // namespace ml
