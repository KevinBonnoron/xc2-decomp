#pragma once

#include "dr/dr_mdo_ctl_seam.h"

namespace ml {

class DrMdoCtlSeamMpfMap : public DrMdoCtlSeam {
public:
  void updateMpfMap();
  void readMpfMapCheck();
  void updateMpfMapRenderList();
  void createAllpfMapDisplayList();
  void renderMpfMapDisplayList();
  void createMpfMapDisplayList();
};

} // namespace ml
