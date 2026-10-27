#pragma once

#include "dr/dr_mdo_ctl_seam.h"

namespace ml {

class DrResMdoSeamWrkEnv;

class DrMdoCtlSeamEnvMap : public DrMdoCtlSeam {
public:
  void releaseEnvMap();
  void releaseFreeSeamEnvMap(DrResMdoSeamWrkEnv *env);
  void updateEnvMap();
  void readEnvMapCheck();
  void updateEnvMapRenderList();
  void createEnvDisplayList(DrResMdoSeamWrkEnv *wrk);
};

} // namespace ml
