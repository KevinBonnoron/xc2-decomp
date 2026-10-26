#pragma once

#include "dr/dr_mdo_ctl_seam.h"

namespace ml {

class DrMdoCtlSeamLowMap : public DrMdoCtlSeam {
public:
  void callRenderSeamLowMap();
  void callGBuffRenderSeamLowMap();
  void callLightPrePassRenderSeamLowMap();
  void callRefractionRenderSeamLowMap();
  void callAlphaRenderSeamLowMap();
  void callSpAlphaRenderSeamLowMap();
  void renderSeamLowMap(int renderType);
  void createLowDisplayList();
};

} // namespace ml
