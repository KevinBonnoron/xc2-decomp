#include "dr/dr_light_man.h"

#include "dr/dr_light_obj.h"
#include "dr/dr_man.h"
#include "dr/dr_shd_lgt_man.h"
#include "dr/dr_shd_man.h"

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
