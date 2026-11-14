#pragma once

#include "dr/dr_mdo_ctl_seam_inst_map.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {
class DrResMdoSeamWrkMpf;

class DrMdoCtlSeamMpfMap : public DrMdoCtlSeamInstMap {
public:
  DrMdoCtlSeamMpfMap(int viewNum);
  void releaseMpfMap();
  void initMpfMapParts(DrResMdoSeamWrkMpf *mpf);
  void changeMemMpfMapParts(DrResMdoSeamWrkMpf *mpf);
  DrResMdoSeamWrkMpf *createFreeSeamMpf();
  void releaseFreeSeamMpf(DrResMdoSeamWrkMpf *mpf);
  void updateMpfMap();
  void readMpfMapCheck();
  void updateMpfMapRenderList();
  bool readMpfModelCheck(const mm::Vec3 &position);
  void createAllpfMapDisplayList();
  void renderMpfMapDisplayList();
  void createMpfMapDisplayList();
  void callRenderSeamMpfMap();
  void createMpfZPrePassDisplayList();
};

} // namespace ml
