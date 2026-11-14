#include "dr/dr_global_ibl_man.h"

#include "dr/dr_man.h"
#include "mtl/alloc_handle.h"

namespace ml {

DrGlobalIBLMan::DrGlobalIBLMan(DrMan *man, int index) : unknown00(man), unknown08(index) {}

DrGlobalIBLMan::~DrGlobalIBLMan() { releaseAll(); }

void DrGlobalIBLMan::releaseAll() {
  unknown10[0].unknown003();
  unknown10[1].unknown003();
  unknown40.unknown003();
  unknown30.unknown003();
}

DrGlobalIBLPack *DrGlobalIBLMan::createObj(const void *data) {
  if (!DrGlobalIBLPack::checkFileType(data)) {
    return nullptr;
  }
  DrGlobalIBLPack *pack = new (unknown00->unknown10) DrGlobalIBLPack(data, unknown08);
  unknown10[DrMan::s_nDblStockIdx].unknown002(pack);
  return pack;
}

void DrGlobalIBLMan::releaseObj(DrGlobalIBLPack *pack) { pack->unknown50 |= DrGlobalIBLPack::FLAG_UNKNOWN_30 << DrMan::s_nDblStockIdx; }

} // namespace ml
