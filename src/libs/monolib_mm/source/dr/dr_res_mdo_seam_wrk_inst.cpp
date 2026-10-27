#include "dr/dr_res_mdo_seam_wrk_inst.h"

namespace ml {

void DrResMdoSeamWrkInst::beginMdl() { unknown150 = 0; }

void DrResMdoSeamWrkInst::linkReadMdl() { unknown88 = 0; }

void DrResMdoSeamWrkInst::linkReadMdl(u32 index) {
  unknown88 = 0;
  unknownc8[index >> 5] |= 1 << (index & 0x1f);
}

u32 DrResMdoSeamWrkInst::isSubMdl(u32 index) {
  u32 bit = unknown20->unknown2c + index;
  return unknownd0[bit >> 5] & (1 << (bit & 0x1f));
}

} // namespace ml
