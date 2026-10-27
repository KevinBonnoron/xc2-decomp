#include "dr/dr_light_man.h"

#include "dr/dr_light_obj.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_shd_lgt_man.h"
#include "dr/dr_shd_man.h"
#include "ml/critical_section.h"

namespace ml {

void DrLightMan::render() {}

void DrLightMan::renderDir() {}

void DrLightMan::renderPnt() {}

void DrLightMan::renderSpt() {}

void DrLightMan::renderDebugDir() {}

void DrLightMan::stockBegin() {
  unknown1b8 = false;
  unknown1b9 = false;
  unknown168 = 0;
  unknowne0->unknown80->unknown18->stockBegin();
}

void DrLightMan::stockEnd() {
  updateAfterPnt();
  updateAfterSpt();
  unknowne0->unknown80->unknown18->stockEnd();
}

void DrLightMan::releaseAmbLight(DrLightObjAmb *light) {
  CS lock(DrMan::getCriticalSection());
  light->unknown1c |= DrLightObj::FLAG_UNKNOWN_16 << DrMan::s_nDblStockIdx;
  unknown100--;
  if (unknown100 < 0) {
    unknown100 = 0;
  }
}

void DrLightMan::releaseDirLight(DrLightObjDir *light) {
  CS lock(DrMan::getCriticalSection());
  light->unknown1c |= DrLightObj::FLAG_UNKNOWN_16 << DrMan::s_nDblStockIdx;
  unknown104--;
  if (unknown104 < 0) {
    unknown104 = 0;
  }
}

void DrLightMan::releasePntLight(DrLightObjPnt *light) {
  CS lock(DrMan::getCriticalSection());
  light->unknown1c |= DrLightObj::FLAG_UNKNOWN_16 << DrMan::s_nDblStockIdx;
  unknown108--;
  if (unknown108 < 0) {
    unknown108 = 0;
  }
}

void DrLightMan::releaseSptLight(DrLightObjSpt *light) {
  CS lock(DrMan::getCriticalSection());
  light->unknown1c |= DrLightObj::FLAG_UNKNOWN_16 << DrMan::s_nDblStockIdx;
  unknown10c--;
  if (unknown10c < 0) {
    unknown10c = 0;
  }
}

void DrLightMan::releaseFastLight() {
  if (unknown0f0 != nullptr) {
    releaseAmbLight(unknown0f0);
    unknown0f0 = nullptr;
  }
  if (unknown0f8 != nullptr) {
    releaseDirLight(unknown0f8);
    unknown0f8 = nullptr;
  }
}

f32 DrLightMan::getSkyLuminance() const {
  DrPixlPostParm *parm = unknowne0->unknown120[unknowne0->unknown1c98];
  f32 second = parm->unknown46c;
  f32 first = parm->unknown468;
  f32 r = second * unknown12c.r + first * unknown120.r;
  f32 g = second * unknown12c.g + first * unknown120.g;
  f32 b = second * unknown12c.b + first * unknown120.b;
  return r * 0.299f + g * 0.587f + b * 0.114f;
}

void DrLightMan::releaseInstantPntLight(DrLightObjPnt *light) {
  light->unknown1c |= DrLightObj::FLAG_UNKNOWN_16 << DrMan::s_nDblIdx;
  light->unknown1c |= DrLightObj::FLAG_UNKNOWN_16 << DrMan::s_nDblStockIdx;
  unknown108--;
  if (unknown108 < 0) {
    unknown108 = 0;
  }
}

void DrLightMan::releaseInstantSptLight(DrLightObjSpt *light) {
  light->unknown1c |= DrLightObj::FLAG_UNKNOWN_16 << DrMan::s_nDblIdx;
  light->unknown1c |= DrLightObj::FLAG_UNKNOWN_16 << DrMan::s_nDblStockIdx;
  unknown10c--;
  if (unknown10c < 0) {
    unknown10c = 0;
  }
}

} // namespace ml
