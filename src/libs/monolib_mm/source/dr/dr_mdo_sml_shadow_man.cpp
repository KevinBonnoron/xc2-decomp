#include "dr/dr_mdo_sml_shadow_man.h"

#include "dr/dr_man.h"

namespace ml {

void DrMdoSmlShadowMan::releaseObj(DrMdoSmlShadowObj *shadow) { shadow->unknown28 |= DrMdoSmlShadowObj::FLAG_UNKNOWN_14 << DrMan::s_nDblStockIdx; }

bool DrMdoSmlShadowMan::checkDisp() {
  for (DrMdoSmlShadowObj *shadow = unknown10[unknown04][0]; shadow != nullptr; shadow = shadow->unknown08) {
    if (shadow->unknown28 & DrMdoSmlShadowObj::FLAG_UNKNOWN_0) {
      return true;
    }
  }
  return false;
}

} // namespace ml
