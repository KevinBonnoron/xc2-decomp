#include "dr/dr_res_mdo_light.h"

#include <new>

#include "dr/dr_light_man.h"
#include "dr/dr_light_obj.h"
#include "dr/dr_man.h"
#include "dr/dr_res_etc_params.h"

namespace ml {

DrResMdoLight::DrResMdoLight() : unknown00(nullptr), unknown18(0), unknown1a(2) {}

DrResMdoLight::~DrResMdoLight() { release(); }

void DrResMdoLight::release(DrResMdoLight *&light) {
  if (light != nullptr) {
    light->~DrResMdoLight();
    light = nullptr;
  }
}

void DrResMdoLight::release() {
  if (unknown00 != nullptr) {
    DrMan *man = DrMan::getIns();
    if (unknown18 > 0) {
      DrLightMan *lightMan = man->unknown588;
      for (s32 i = 0; i < unknown18; i++) {
        DrLightObj *light = unknown00[i];
        if (light != nullptr) {
          if (light->isPnt()) {
            lightMan->releasePntLight(static_cast<DrLightObjPnt *>(unknown00[i]));
          } else {
            lightMan->releaseSptLight(static_cast<DrLightObjSpt *>(unknown00[i]));
          }
        }
      }
    }
    unknown18 = 0;
    unknown00 = nullptr;
  }
}

int DrResMdoLight::setup(u8 *work, const u8 *resource, const u8 *lightResource) {
  const unknown001 *header = reinterpret_cast<const unknown001 *>(resource);
  const unknown003 *lightHeader = reinterpret_cast<const unknown003 *>(lightResource);
  unknown08 = reinterpret_cast<const unknown002 *>(resource + header->unknown2c);
  unknown10 = lightResource + lightHeader->unknown30;
  unknown00 = reinterpret_cast<DrLightObj **>(work);
  unknown18 = 0;
  return unknown08->unknown00 * 8 + sizeof(DrResMdoLight);
}

int DrResMdoLight::calcWorkSize(const u8 *resource) {
  const unknown001 *header = reinterpret_cast<const unknown001 *>(resource);
  const unknown002 *table = reinterpret_cast<const unknown002 *>(resource + header->unknown2c);
  return table->unknown00 * 8 + sizeof(DrResMdoLight);
}

int DrResMdoLight::create(u8 *work, const u8 *resource, const u8 *lightResource) {
  DrResMdoLight *light = new (work) DrResMdoLight();
  return light->setup(work + sizeof(DrResMdoLight), resource, lightResource);
}

void DrResMdoLight::setDisp(bool isDisp) {
  if (isDisp) {
    unknown1a |= 2;
  } else {
    unknown1a &= ~2;
  }
}

void DrResMdoLight::lgtCall_col_r(f32 *color, DrResEtcParams *params) { color[0] = params->m_params; }

void DrResMdoLight::lgtCall_col_g(f32 *color, DrResEtcParams *params) { color[1] = params->m_params; }

void DrResMdoLight::lgtCall_col_b(f32 *color, DrResEtcParams *params) { color[2] = params->m_params; }

void DrResMdoLight::lgtCall_col_inv(f32 *color, DrResEtcParams *params) { color[3] = params->m_params; }

} // namespace ml
