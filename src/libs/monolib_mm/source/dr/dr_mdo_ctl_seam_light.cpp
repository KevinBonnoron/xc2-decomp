#include "dr/dr_mdo_ctl_seam_light.h"

#include "dr/dr_environment_obj.h"
#include "dr/dr_man.h"
#include "dr/dr_mdo_ctl_seam.h"
#include "dr/dr_res_mdo_seam_mem_man.h"
#include "dr/dr_res_mdo_seam_parm_read.h"
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

void DrMdoCtlSeamLight::initLightParts(DrResMdoSeamWrkLight *light) {
  const MdsSeamLgtMapData *data = reinterpret_cast<const MdsSeamLgtMapData *>(reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknown8c) + light->unknown30;
  unknownc6c += data->unknown1c;
  unknown723(unknownbc0, light->unknown30) |= 1 << (light->unknown30 & 0x1f);
  unknownc0c++;
  light->setupWork(data);
  DrEnvironmentObj *environment = light->unknown20; // The game loads the object once for the two accesses (ldr at 0x7100824464).
  environment->unknown8c |= 4;
  environment->unknown90 = unknownc88;
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

void DrMdoCtlSeamLight::readLightCheck() {
  if ((unknownc7c & 0x40) == 0) {
    DrResMdoSeamWrkLight::SEAM_LIGHT_READ_CHECK = 5.0f;
  } else {
    DrResMdoSeamWrkLight::SEAM_LIGHT_READ_CHECK = 0.5f;
  }
  bool isOpen = ((unknownc7c >> 12) & 1) != 0 || unknowncc8;
  DrResMdoSeamWrkLight *light = unknown3a8.unknown10.unknown00;
  while (light != nullptr) {
    if (light->update(&unknownd30, m_drMan->m_gblIdx, isOpen)) {
      DrResMdoSeamWrkLight *next = light->unknown08;
      releaseFreeSeamLight(light);
      light = next;
    } else {
      if (light->unknown20 != nullptr) {
        light->unknown20->unknown90 = unknownc88;
      }
      light = light->unknown08;
    }
  }
  if ((unknownc7c & 0x80000) == 0 && unknownc0c < 8 && (unknownc7c & 0x1000) == 0) {
    const MdsSeamLgtMapData *entry = reinterpret_cast<const MdsSeamLgtMapData *>(reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknown8c);
    s32 max = unknown1a8->unknown88;
    const u32 *gblIdx = m_drMan->m_gblIdx;
    for (s32 i = 0; i < max; i++, entry++) {
      if ((unknownbc0[static_cast<u32>(i) >> 5] & (1 << (i & 0x1f))) != 0) {
        continue;
      }
      if (entry->unknown20 != 0 && (gblIdx[entry->unknown20 >> 5] & (1 << (entry->unknown20 & 0x1f))) != 0) {
        continue;
      }
      bool isRead = true;
      if (entry->unknown00[0] < unknownd30.unknown50.x || entry->unknown0c[0] > unknownd30.unknown50.x || entry->unknown00[1] < unknownd30.unknown50.y ||
          entry->unknown0c[1] > unknownd30.unknown50.y || entry->unknown00[2] < unknownd30.unknown50.z || entry->unknown0c[2] > unknownd30.unknown50.z) {
        isRead = false;
        for (s32 k = 0; k < unknownd30.unknown40; k++) {
          if (readInstModelCheck(unknownd30.unknown10[k], entry->unknown00, entry->unknown0c)) {
            isRead = true;
            break;
          }
        }
      }
      if (isRead) {
        unknownd30.setStockLight(i);
      }
    }
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
