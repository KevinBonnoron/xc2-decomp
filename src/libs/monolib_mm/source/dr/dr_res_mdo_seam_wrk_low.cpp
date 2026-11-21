#include "dr/dr_res_mdo_seam_wrk_low.h"

#include "dr/dr_res_mdo_alp_tbl.h"
#include "dr/dr_res_mdo_seam_res.h"
#include "grlib/cglib_vtx_instans.h"
#include "mtl/mem_manager.h"

namespace ml {

f32 DrResMdoSeamWrkLow::SEAM_LOWEMAP_READ_CHECK = 4000.0f;

DrResMdoSeamWrkLow::DrResMdoSeamWrkLow()
    : unknown28(nullptr), unknown30(nullptr), unknown40(nullptr), unknown88(nullptr), unknown9c(0), unknowna0(0), unknowna4(0), unknowna8(0), unknownac(0), unknownb0(0), unknownb4(0) {}

DrResMdoSeamWrkLow::~DrResMdoSeamWrkLow() { release(); }

void DrResMdoSeamWrkLow::release() {
  grlib::CGLibVtxInstans *instans = unknown40;
  if (instans != nullptr) {
    instans->release();
    instans->~CGLibVtxInstans();
    unknown40 = nullptr;
  }
  if (unknown28 != nullptr) {
    mtl::MemManager::deallocate(unknown28, 0, false);
    unknown28 = nullptr;
  }
  if (unknown88 != nullptr) {
    mtl::MemManager::deallocate(unknown88, 0, false);
    unknown88 = nullptr;
  }
  unknown9c = 0;
  unknown30 = nullptr;
}

void DrResMdoSeamWrkLow::changeMemCall() {
  unknown18 = reinterpret_cast<const MdsSeamLowMapHead *>(unknown30->m_buffer);
  unknown9c |= 0x60;
}

} // namespace ml
