#include "dr/dr_calc_man.h"

#include "dr/dr_calc_clip_man.h"
#include "dr/dr_calc_view_work.h"
#include "mm_math/mm_mat44.h"

namespace ml {

void DrCalcMan::begin() {
  unknown10->begin(unknown08);
  unknown18->update();
}

void DrCalcMan::end() { unknown10->end(); }

void DrCalcMan::renderEnd() {
  DrCalcViewWork *work = unknown10;
  if (work->unknown9ad) {
    work->unknown9ad = false;
  }
  work->unknown280 = work->unknown40;
  work->unknown100 = work->unknownc0;
}

void DrCalcMan::shadowEnd() { unknown10->unknownc0 = unknown10->unknown140; }

} // namespace ml
