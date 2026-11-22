#include "dr/dr_calc_man.h"

#include "dr/dr_calc_clip_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_man.h"
#include "mm_math/mm_mat44.h"
#include "mtl/alloc_handle.h"

// The game builds the clip manager and the clip works in the same unit, in address order: the constructor and the destructor of DrCalcClipMan
// and the empty destructors of the clip works of DrCalcViewWork are inlined in DrCalcMan. Unit evidence (game 1.0.0, 0x71008a4744 to 0x71008ade6c): the
// files follow the order of their functions here, clip manager and clip objects (0x71008a4744 to 0x71008a63f0), cone (0x71008a6448 to 0x71008a6b60),
// plane (0x71008a6b64 to 0x71008a7334), view plane (0x71008a75ac to 0x71008a7f74), shadow plane (0x71008a8258 to 0x71008a8a28), sphere
// (0x71008a8be0 to 0x71008a8cc8), view poli (0x71008a8ccc to 0x71008a98b0), cp plane objects (0x71008aa06c to 0x71008aa120), the gpu cost destructor
// (0x71008aa29c), then this file's functions (from 0x71008aa530): the cone, plane, shadow plane and sphere clip works alternate with the view plane and
// view poli clip works, with no other unit between, so they are one translation unit.
// clang-format off
#include "dr_calc_clip_man.cpp"
#include "dr_calc_clip_work_cone.cpp"
#include "dr_calc_clip_work_plane.cpp"
#include "dr_calc_clip_work_view_plane.cpp"
#include "dr_calc_clip_work_shadow_plane.cpp"
#include "dr_calc_clip_work_sphere.cpp"
#include "dr_calc_clip_work_view_poli.cpp"
#include "dr_calc_cp_plane_obj.cpp"
#include "dr_calc_gpu_cost.cpp"
// clang-format on

namespace ml {

DrCalcMan::DrCalcMan(DrMan *man, int loopCount) : m_drMan(man), unknown08(loopCount) {
  m_drCalcViewWork = new (man->unknown0c) DrCalcViewWork(man);
  m_drCalcClipMan = new (m_drMan->unknown0c) DrCalcClipMan(man, m_drCalcViewWork);
}

DrCalcMan::~DrCalcMan() {
  if (m_drCalcViewWork != nullptr) {
    delete m_drCalcViewWork;
    m_drCalcViewWork = nullptr;
  }
  if (m_drCalcClipMan != nullptr) {
    delete m_drCalcClipMan;
    m_drCalcClipMan = nullptr;
  }
}

void DrCalcMan::begin() {
  m_drCalcViewWork->begin(unknown08);
  m_drCalcClipMan->update();
}

void DrCalcMan::end() { m_drCalcViewWork->end(); }

void DrCalcMan::renderEnd() {
  DrCalcViewWork *work = m_drCalcViewWork;
  if (work->unknown9ad) {
    work->unknown9ad = false;
  }
  work->unknown280 = work->unknown40;
  work->unknown100 = work->unknownc0;
}

void DrCalcMan::shadowEnd() { m_drCalcViewWork->unknownc0 = m_drCalcViewWork->unknown140; }

} // namespace ml

// The game builds the view work in this unit: the functions of DrCalcMan and DrCalcViewWork interleave in one contiguous range with no other unit between them
// (DrCalcMan::begin 0x71008aa678, DrCalcViewWork::begin 0x71008aa6a4, DrCalcMan::end 0x71008ad964, DrCalcViewWork::end 0x71008ad96c, DrCalcMan::renderEnd 0x71008adde4,
// DrCalcViewWork::renderEnd 0x71008ade28, DrCalcMan::shadowEnd 0x71008ade6c, DrCalcViewWork::shadowEnd 0x71008ade80, then the rest of the view work up to 0x71008b1f44).
// With the view work in this unit clang inlines the empty DrCalcClipWorkViewPlane and DrCalcClipWorkViewPoli destructors (0x71008a75c4, 0x71008a8ce8) into ~DrCalcViewWork
// (0x71008ae7a8), which calls only the CGLibDblUniformBlock destructors.
#include "dr_calc_view_work.cpp"
