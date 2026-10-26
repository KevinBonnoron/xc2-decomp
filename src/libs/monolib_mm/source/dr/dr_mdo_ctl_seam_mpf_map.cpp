#include "dr/dr_mdo_ctl_seam_mpf_map.h"

namespace ml {

void DrMdoCtlSeamMpfMap::createAllpfMapDisplayList() {}

void DrMdoCtlSeamMpfMap::renderMpfMapDisplayList() { createMpfMapDisplayList(); }

void DrMdoCtlSeamMpfMap::updateMpfMap() {
  readMpfMapCheck();
  if (((unknownc7c >> 12) & 1) == 0) {
    updateMpfMapRenderList();
  }
}

} // namespace ml
