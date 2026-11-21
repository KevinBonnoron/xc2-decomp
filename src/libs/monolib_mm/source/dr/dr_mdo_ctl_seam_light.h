#pragma once

#include "dr/dr_mdo_ctl_seam_env_map.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {
class DrResMdoSeamWrkLight;

class DrMdoCtlSeamLight : public DrMdoCtlSeamEnvMap {
public:
  DrMdoCtlSeamLight(int viewNum);
  void releaseLight();
  void initLightParts(DrResMdoSeamWrkLight *light);
  DrResMdoSeamWrkLight *createFreeSeamLight();
  void releaseFreeSeamLight(DrResMdoSeamWrkLight *light);
  bool readInstModelCheck(const mm::Vec3 &position, const f32 *max, const f32 *min);
  void readLightCheck();
  void updateLight();
};

} // namespace ml
