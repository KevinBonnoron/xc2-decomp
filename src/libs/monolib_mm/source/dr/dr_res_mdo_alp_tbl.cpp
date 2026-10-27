#include "dr/dr_res_mdo_alp_tbl.h"

namespace ml {

DrResMdoAlpTbl::DrResMdoAlpTbl() {}

int DrResMdoAlpTbl::calcCntWorkSize(u32 count) {
  u32 aligned = count + (-count & 3);
  u32 words = count >> 5;
  if ((count & 0x1f) != 0) {
    words++;
  }
  return (aligned + words) * 4 + 0x50;
}

} // namespace ml
