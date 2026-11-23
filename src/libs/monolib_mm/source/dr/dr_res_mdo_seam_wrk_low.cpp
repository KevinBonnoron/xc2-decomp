#include "dr/dr_res_mdo_seam_wrk_low.h"

#include "dr/dr_res_mdo_alp_tbl.h"
#include "dr/dr_res_mdo_seam_res.h"
#include "grlib/cglib_vtx_instans.h"
#include "mtl/mem_manager.h"

namespace ml {

f32 DrResMdoSeamWrkLow::SEAM_LOWEMAP_READ_CHECK = 4000.0f;

DrResMdoSeamWrkLow::DrResMdoSeamWrkLow()
    : m_mdoWrkMatRes(nullptr), m_drResMdoSeamMemObj(nullptr), m_drResMdoAlpTbl(nullptr), unknown88(nullptr), unknown9c(0), unknowna0(0), unknowna4(0), unknowna8(0), unknownac(0), unknownb0(0),
      unknownb4(0) {}

DrResMdoSeamWrkLow::~DrResMdoSeamWrkLow() { release(); }

void DrResMdoSeamWrkLow::release() {
  grlib::CGLibVtxInstans *instans = m_drResMdoAlpTbl;
  if (instans != nullptr) {
    instans->release();
    instans->~CGLibVtxInstans();
    m_drResMdoAlpTbl = nullptr;
  }
  if (m_mdoWrkMatRes != nullptr) {
    mtl::MemManager::deallocate(m_mdoWrkMatRes, 0, false);
    m_mdoWrkMatRes = nullptr;
  }
  if (unknown88 != nullptr) {
    mtl::MemManager::deallocate(unknown88, 0, false);
    unknown88 = nullptr;
  }
  unknown9c = 0;
  m_drResMdoSeamMemObj = nullptr;
}

void DrResMdoSeamWrkLow::changeMemCall() {
  m_mdsSeamLowMapHead = reinterpret_cast<const MdsSeamLowMapHead *>(m_drResMdoSeamMemObj->m_buffer);
  unknown9c |= 0x60;
}

} // namespace ml
