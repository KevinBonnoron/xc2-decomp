#include "dr/dr_global_ibl_man.h"

#include "dr/dr_man.h"

namespace ml {

void DrGlobalIBLPack::setup() {}

bool DrGlobalIBLPack::checkFileType(const void *data) {
  const u32 *header = static_cast<const u32 *>(data);
  if (header[0] == 0x4c424947) {
    return header[1] == 10100 || header[1] == 20000;
  }
  return false;
}

void DrGlobalIBLMan::releaseObj(DrGlobalIBLPack *pack) { pack->unknown50 |= DrGlobalIBLPack::FLAG_UNKNOWN_30 << DrMan::s_nDblStockIdx; }

} // namespace ml
