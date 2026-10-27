#include "dr/dr_res_mdo_light.h"

#include "dr/dr_res_etc_params.h"

namespace ml {

DrResMdoLight::DrResMdoLight() : unknown00(nullptr), unknown18(0), unknown1a(2) {}

int DrResMdoLight::calcWorkSize(const u8 *resource) {
  const unknown001 *header = reinterpret_cast<const unknown001 *>(resource);
  const unknown002 *table = reinterpret_cast<const unknown002 *>(resource + header->unknown2c);
  return table->unknown00 * 8 + sizeof(DrResMdoLight);
}

void DrResMdoLight::setDisp(bool isDisp) {
  if (isDisp) {
    unknown1a |= 2;
  } else {
    unknown1a &= ~2;
  }
}

void DrResMdoLight::lgtCall_col_r(f32 *color, DrResEtcParams *params) { color[0] = params->unknown14; }

void DrResMdoLight::lgtCall_col_g(f32 *color, DrResEtcParams *params) { color[1] = params->unknown14; }

void DrResMdoLight::lgtCall_col_b(f32 *color, DrResEtcParams *params) { color[2] = params->unknown14; }

void DrResMdoLight::lgtCall_col_inv(f32 *color, DrResEtcParams *params) { color[3] = params->unknown14; }

} // namespace ml
