#include "dr/dr_calc_cp_plane_obj.h"

#include "dr/dr_man.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace ml {

DrCalcCpPlaneObj::DrCalcCpPlaneObj(const void *data) : DrCalcClipMan::unknown009<DrCalcCpPlaneObj>(), unknown30(nullptr), unknown38(0), unknown40(0) {
  const unknown005 *header = static_cast<const unknown005 *>(data);
  unknown3c = header->unknown08;
  unknown10 = reinterpret_cast<const unknown006 *>(static_cast<const u8 *>(data) + header->unknown00);
  unknown18 = reinterpret_cast<const unknown007 *>(static_cast<const u8 *>(data) + header->unknown04);
  unknown30 = static_cast<unknown008 *>(mtl::MemManager::allocate(DrMan::get()->unknown14, unknown3c * sizeof(unknown008), 0x10, false, "no name", 0));
}

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
