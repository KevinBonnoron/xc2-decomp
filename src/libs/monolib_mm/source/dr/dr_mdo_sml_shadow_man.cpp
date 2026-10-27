#include "dr/dr_mdo_sml_shadow_man.h"

#include "dr/dr_man.h"
#include "mtl/mem_manager.h"

namespace ml {

DrMdoSmlShadowObj::~DrMdoSmlShadowObj() {
  if (unknown18 != nullptr) {
    mtl::MemManager::deallocate(unknown18, 0, false);
    unknown18 = nullptr;
  }
}

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
