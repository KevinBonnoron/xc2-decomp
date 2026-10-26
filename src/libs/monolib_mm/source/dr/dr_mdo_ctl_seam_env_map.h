#pragma once

#include "dr/dr_mdo_ctl_seam.h"

namespace ml {

class DrResMdoSeamWrkEnv;

class DrMdoCtlSeamEnvMap : public DrMdoCtlSeam {
public:
  void createEnvDisplayList(DrResMdoSeamWrkEnv *wrk);
};

} // namespace ml
