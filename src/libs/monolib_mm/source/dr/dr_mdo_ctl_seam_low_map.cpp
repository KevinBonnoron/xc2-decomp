#include "dr/dr_mdo_ctl_seam_low_map.h"
#include "dr/dr_res_mdo_seam_wrk_low.h"

namespace ml {

void DrMdoCtlSeamLowMap::releaseLowMap() {
  DrResMdoSeamWrkLow *low = unknown2d8;
  while (low != nullptr) {
    DrResMdoSeamWrkLow *next = low->unknown08;
    releaseFreeSeamLow(low);
    low = next;
  }
  unknownc44 = 0;
}

void DrMdoCtlSeamLowMap::callRenderSeamLowMap() { renderSeamLowMap(0); }

void DrMdoCtlSeamLowMap::callGBuffRenderSeamLowMap() { renderSeamLowMap(1); }

void DrMdoCtlSeamLowMap::callLightPrePassRenderSeamLowMap() { renderSeamLowMap(3); }

void DrMdoCtlSeamLowMap::callRefractionRenderSeamLowMap() { renderSeamLowMap(2); }

void DrMdoCtlSeamLowMap::callAlphaRenderSeamLowMap() { renderSeamLowMap(4); }

void DrMdoCtlSeamLowMap::callSpAlphaRenderSeamLowMap() { renderSeamLowMap(5); }

void DrMdoCtlSeamLowMap::createLowDisplayList() {}

void DrMdoCtlSeamLowMap::updateLowMap() {
  readLowMapCheck();
  if (((unknownc7c >> 12) & 1) == 0) {
    updateLowMapRenderList();
  }
}

} // namespace ml
