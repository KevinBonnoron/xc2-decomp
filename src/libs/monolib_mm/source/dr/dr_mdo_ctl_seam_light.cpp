#include "dr/dr_mdo_ctl_seam_light.h"

#include "dr/dr_mdo_ctl_seam.h"
#include "dr/dr_res_mdo_seam_mem_man.h"
#include "dr/dr_res_mdo_seam_wrk_light.h"
#include "mm_math/mm_vec3.h"

namespace ml {
class DrResMdoSeamMemObj;

DrMdoCtlSeamLight::DrMdoCtlSeamLight(int viewNum) : DrMdoCtlSeamEnvMap(viewNum) {}

void DrMdoCtlSeamLight::releaseLight() {
  DrResMdoSeamWrkLight *light = unknown3a8.unknown10.unknown00;
  while (light != nullptr) {
    DrResMdoSeamWrkLight *next = light->unknown08;
    releaseFreeSeamLight(light);
    light = next;
  }
  unknownc6c = 0;
  unknownc0c = 0;
}

DrResMdoSeamWrkLight *DrMdoCtlSeamLight::createFreeSeamLight() { return unknown3a8.unknown001(); }

void DrMdoCtlSeamLight::releaseFreeSeamLight(DrResMdoSeamWrkLight *light) {
  DrResMdoSeamMemObj *mem = light->unknown28;
  if (mem != nullptr) {
    unknownc6c -= light->unknown34;
    unknown723(unknownbc0, light->unknown30) &= ~(1 << (light->unknown30 & 0x1f));
    unknownc0c--;
    light->release();
  }
  unknown3a8.unknown002(light);
  if (mem != nullptr) {
    light->unknown28 = nullptr;
    unknown6e0.releaseFreeObj(mem);
  }
}

bool DrMdoCtlSeamLight::readInstModelCheck(const mm::Vec3 &position, const f32 *max, const f32 *min) {
  if (!(max[0] < position.x) && !(min[0] > position.x) && !(max[1] < position.y) && !(min[1] > position.y) && !(max[2] < position.z) && !(min[2] > position.z)) {
    return true;
  }
  return false;
}

void DrMdoCtlSeamLight::updateLight() { readLightCheck(); }

} // namespace ml
