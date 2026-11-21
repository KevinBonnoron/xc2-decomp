#include "dr/dr_calc_man.h"

#include "dr/dr_calc_clip_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_man.h"
#include "mm_math/mm_mat44.h"
#include "mtl/alloc_handle.h"

// The game builds the clip manager and the clip works in the same unit, in address order: the constructor and the destructor of DrCalcClipMan
// and the empty destructors of the clip works of DrCalcViewWork are inlined in DrCalcMan. Unit evidence (game 1.0.0, 0x71008a4744 to 0x71008ade6c): the
// files follow the order of their last functions defined here, clip manager (to 0x71008a5778), clip objects (0x71008a63f0), view plane (0x71008a7f74),
// view poli (0x71008a98b0), cp plane objects (0x71008aa06c to 0x71008aa120), then this file's functions (from 0x71008aa530).
#include "dr_calc_clip_man.cpp"
#include "dr_calc_clip_work_view_plane.cpp"
#include "dr_calc_clip_work_view_poli.cpp"
#include "dr_calc_cp_plane_obj.cpp"

namespace ml {

DrCalcMan::DrCalcMan(DrMan *man, int loopCount) : unknown00(man), unknown08(loopCount) {
  unknown10 = new (man->unknown0c) DrCalcViewWork(man);
  unknown18 = new (unknown00->unknown0c) DrCalcClipMan(man, unknown10);
}

DrCalcMan::~DrCalcMan() {
  if (unknown10 != nullptr) {
    delete unknown10;
    unknown10 = nullptr;
  }
  if (unknown18 != nullptr) {
    delete unknown18;
    unknown18 = nullptr;
  }
}

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
