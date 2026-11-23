#include "dr/dr_global_ibl_man.h"

#include "dr/dr_man.h"
#include "mtl/alloc_handle.h"

namespace ml {

DrGlobalIBLMan::DrGlobalIBLMan(DrMan *man, int index) : m_drMan(man), unknown08(index) {}

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
  DrGlobalIBLPack *pack = new (m_drMan->unknown10) DrGlobalIBLPack(data, unknown08);
  unknown10[DrMan::s_nDblStockIdx].unknown002(pack);
  return pack;
}

void DrGlobalIBLMan::releaseObj(DrGlobalIBLPack *pack) { pack->unknown50 |= DrGlobalIBLPack::FLAG_UNKNOWN_30 << DrMan::s_nDblStockIdx; }

void DrGlobalIBLMan::update() {
  unknown40.unknown003();
  s32 index = DrMan::s_nDblIdx;
  for (DrGlobalIBLPack *pack = unknown10[index].unknown00; pack != nullptr;) {
    pack->resourceInit();
    DrGlobalIBLPack *next = pack->unknown10;
    unknown30.unknown002(pack);
    pack = next;
  }
  unknown10[index].unknown00 = nullptr;
  unknown10[index].unknown08 = nullptr;
  DrGlobalIBLPack *pack = unknown30.unknown00;
  while (pack != nullptr) {
    if (pack->unknown50 & (DrGlobalIBLPack::FLAG_UNKNOWN_30 << index)) {
      DrGlobalIBLPack *next = pack->unknown10;
      unknown30.unlink(pack);
      pack->release();
      unknown40.unknown002(pack);
      pack = next;
    } else {
      pack->update();
      pack = pack->unknown10;
    }
  }
}

} // namespace ml
