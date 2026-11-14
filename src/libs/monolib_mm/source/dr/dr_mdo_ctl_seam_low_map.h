#pragma once

#include "dr/dr_mdo_ctl_seam_base_map.h"

namespace ml {
class DrResMdoSeamWrkLow;

class DrMdoCtlSeamLowMap : public DrMdoCtlSeamBaseMap {
public:
  DrMdoCtlSeamLowMap(int viewNum);
  void releaseLowMap();
  void releaseFreeSeamLow(DrResMdoSeamWrkLow *low);
  void initLowMapParts(DrResMdoSeamWrkLow *low);
  DrResMdoSeamWrkLow *createFreeSeamLow();
  void updateLowMap();
  void readLowMapCheck();
  void updateLowMapRenderList();
  void callRenderSeamLowMap();
  void callGBuffRenderSeamLowMap();
  void callLightPrePassRenderSeamLowMap();
  void callRefractionRenderSeamLowMap();
  void callAlphaRenderSeamLowMap();
  void callSpAlphaRenderSeamLowMap();
  void renderSeamLowMap(int renderType);
  void createLowDisplayList();
  void createLowZPrePassDisplayList();
};

} // namespace ml
