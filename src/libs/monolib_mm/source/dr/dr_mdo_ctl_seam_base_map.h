#pragma once

#include "dr/dr_mdo_ctl_seam.h"

namespace ml {
class DrResMdoSeamWrkBase;

class DrMdoCtlSeamBaseMap : public DrMdoCtlSeam {
public:
  void updateBaseMap();
  void readBaseMapCheck();
  void updateBaseMapRenderList();
  void callRenderSeamBaseMap();
  void callGBuffRenderSeamBaseMap();
  void callLightPrePassRenderSeamBaseMap();
  void callRefractionRenderSeamBaseMap();
  void callAlphaRenderSeamBaseMap();
  void callSpAlphaRenderSeamBaseMap();
  void renderSeamBaseMap(int renderType);
  void createBaseMapDisplayList();
  void releaseBaseMap();
  void releaseFreeSeamBase(DrResMdoSeamWrkBase *base);
};

} // namespace ml
