#include "dr/dr_mdo_sml_shadow_man.h"

#include "dr/dr_man.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace ml {

DrMdoSmlShadowObj::DrMdoSmlShadowObj(int viewNum, const u8 *data, DrMan *man) {
  unknown28 = 0;
  unknown00 = nullptr;
  unknown08 = nullptr;
  unknown10 = reinterpret_cast<const unknown002 *>(data);
  unknown18 = nullptr;
  unknown2a = viewNum;
  int size = unknown10->unknown00 * 0x30;
  size += (32 - size % 32) % 32;
  unknown18 = mtl::MemManager::allocate(man->unknown14, size, 0x20, false, "no name", 0);
  unknown20 = unknown18;
}

DrMdoSmlShadowObj::~DrMdoSmlShadowObj() {
  if (unknown18 != nullptr) {
    mtl::MemManager::deallocate(unknown18, 0, false);
    unknown18 = nullptr;
  }
}

DrMdoSmlShadowMan::DrMdoSmlShadowMan(DrMan *man) : unknown00(0), unknown04(0), unknown08(man) {
  for (int i = 0; i < 4; i++) {
    unknown10[i][0] = nullptr;
    unknown10[i][1] = nullptr;
  }
  for (int i = 0; i < 2; i++) {
    unknown50[i][0] = nullptr;
    unknown50[i][1] = nullptr;
  }
  unknown70[0] = nullptr;
  unknown70[1] = nullptr;
}

// Inferred helper: deletes the objects of a list and empties it; original name unknown.
static void unknown001(DrMdoSmlShadowObj **list) {
  DrMdoSmlShadowObj *shadow = list[0];
  while (shadow != nullptr) {
    DrMdoSmlShadowObj *next = shadow->unknown08;
    delete shadow;
    shadow = next;
  }
  list[0] = nullptr;
  list[1] = nullptr;
}

DrMdoSmlShadowMan::~DrMdoSmlShadowMan() {
  for (int i = 0; i < 2; i++) {
    unknown001(unknown50[i]);
  }
  unknown001(unknown70);
  for (int i = 0; i < 4; i++) {
    unknown001(unknown10[i]);
  }
}

void DrMdoSmlShadowMan::releaseObj(DrMdoSmlShadowObj *shadow) { shadow->unknown28 |= DrMdoSmlShadowObj::FLAG_UNKNOWN_14 << DrMan::s_nDblStockIdx; }

void DrMdoSmlShadowMan::delObjList() {
  unknown50[DrMan::s_nDblIdx][0] = nullptr;
  unknown50[DrMan::s_nDblIdx][1] = nullptr;
  unknown001(unknown70);
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
