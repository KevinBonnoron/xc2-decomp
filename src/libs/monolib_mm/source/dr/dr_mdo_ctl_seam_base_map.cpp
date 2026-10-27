#include "dr/dr_mdo_ctl_seam_base_map.h"
#include "dr/dr_res_mdo_seam_wrk_base.h"

namespace ml {

void DrMdoCtlSeamBaseMap::releaseBaseMap() {
  DrResMdoSeamWrkBase *base = unknown2a0;
  while (base != nullptr) {
    DrResMdoSeamWrkBase *next = base->unknown08;
    releaseFreeSeamBase(base);
    base = next;
  }
  unknownc40 = 0;
}

DrResMdoSeamWrkBase *DrMdoCtlSeamBaseMap::seachBaseIdx(int index) {
  DrResMdoSeamWrkBase *base = unknown2a0;
  while (base != nullptr && (base->unknown68 == nullptr || base->unknown84 != index)) {
    base = base->unknown08;
  }
  return base;
}

void DrMdoCtlSeamBaseMap::callRenderSeamBaseMap() { renderSeamBaseMap(0); }

void DrMdoCtlSeamBaseMap::callGBuffRenderSeamBaseMap() { renderSeamBaseMap(1); }

void DrMdoCtlSeamBaseMap::callLightPrePassRenderSeamBaseMap() { renderSeamBaseMap(3); }

void DrMdoCtlSeamBaseMap::callRefractionRenderSeamBaseMap() { renderSeamBaseMap(2); }

void DrMdoCtlSeamBaseMap::callAlphaRenderSeamBaseMap() { renderSeamBaseMap(4); }

void DrMdoCtlSeamBaseMap::callSpAlphaRenderSeamBaseMap() { renderSeamBaseMap(5); }

void DrMdoCtlSeamBaseMap::createBaseMapDisplayList() {}

void DrMdoCtlSeamBaseMap::updateBaseMap() {
  readBaseMapCheck();
  if (((unknownc7c >> 12) & 1) == 0) {
    updateBaseMapRenderList();
  }
}

} // namespace ml
