#include "dr/dr_calc_clip_obj.h"

#include "dr/dr_man.h"

namespace ml {

void DrCalcClipObj::release() { unknown3c |= 1 << DrMan::s_nDblStockIdx; }

} // namespace ml
