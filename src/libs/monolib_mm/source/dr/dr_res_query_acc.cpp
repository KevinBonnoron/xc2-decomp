#include "dr/dr_res_query_acc.h"

#include "dr/dr_man.h"
#include "dr/dr_pixl_occ_query.h"
#include "grlib/cglib_occlusion_query.h"

namespace ml {

DrResQueryAcc::DrResQueryAcc() : unknown00(nullptr) {}

void DrResQueryAcc::releaseQuery() {
  if (unknown00 != nullptr) {
    unknown00->unknown28 = nullptr;
    unknown00 = nullptr;
  }
}

u32 DrResQueryAcc::getOccPixel() {
  if (unknown00 != nullptr && (unknown00->unknown38 & (4 << DrMan::s_nDblNowIdx))) {
    return unknown00->unknown10.getQueryPixel();
  }
  return 0;
}

} // namespace ml
