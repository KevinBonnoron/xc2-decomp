#include "dr/dr_calc_cp_plane_obj.h"

#include "dr/dr_man.h"
#include "mtl/mem_manager.h"

namespace ml {

DrCalcCpPlaneObj::~DrCalcCpPlaneObj() {
  if (unknown30 != nullptr) {
    mtl::MemManager::deallocate(unknown30, 0, false);
    unknown30 = nullptr;
  }
}

void DrCalcCpPlaneObj::release() {
  int index = DrMan::s_nDblStockIdx;
  unknown3c = 0;
  unknown40 |= 1 << index;
}

} // namespace ml
