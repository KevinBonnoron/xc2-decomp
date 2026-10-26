#pragma once

#include "dr/dr_mdo_ctl_seam.h"

namespace ml {

class DrMdoCtlSeamMpfMap : public DrMdoCtlSeam {
public:
  void createAllpfMapDisplayList();
  void renderMpfMapDisplayList();
  void createMpfMapDisplayList();
};

} // namespace ml
