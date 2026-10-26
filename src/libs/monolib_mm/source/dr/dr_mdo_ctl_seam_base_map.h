#pragma once

#include "dr/dr_mdo_ctl_seam.h"

namespace ml {

class DrMdoCtlSeamBaseMap : public DrMdoCtlSeam {
public:
  void callRenderSeamBaseMap();
  void callGBuffRenderSeamBaseMap();
  void callLightPrePassRenderSeamBaseMap();
  void callRefractionRenderSeamBaseMap();
  void callAlphaRenderSeamBaseMap();
  void callSpAlphaRenderSeamBaseMap();
  void renderSeamBaseMap(int renderType);
  void createBaseMapDisplayList();
};

} // namespace ml
