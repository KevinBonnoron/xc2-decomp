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

void DrMdoSmlShadowMan::delObjList() {
  unknown50[DrMan::s_nDblIdx][0] = nullptr;
  unknown50[DrMan::s_nDblIdx][1] = nullptr;
  DrMdoSmlShadowObj *shadow = unknown70[0];
  while (shadow != nullptr) {
    DrMdoSmlShadowObj *next = shadow->unknown08;
    delete shadow;
    shadow = next;
  }
  unknown70[0] = nullptr;
  unknown70[1] = nullptr;
}

bool DrMdoSmlShadowMan::checkDisp() {
  for (DrMdoSmlShadowObj *shadow = unknown10[unknown04][0]; shadow != nullptr; shadow = shadow->unknown08) {
    if (shadow->unknown28 & DrMdoSmlShadowObj::FLAG_UNKNOWN_0) {
      return true;
    }
  }
  return false;
}

} // namespace ml
