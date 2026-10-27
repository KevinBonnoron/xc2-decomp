#include "dr/dr_global_ibl_man.h"

#include "dr/dr_man.h"

namespace ml {

void DrGlobalIBLPack::setup() {}

void DrGlobalIBLMan::releaseObj(DrGlobalIBLPack *pack) { pack->unknown50 |= DrGlobalIBLPack::FLAG_UNKNOWN_30 << DrMan::s_nDblStockIdx; }

} // namespace ml
