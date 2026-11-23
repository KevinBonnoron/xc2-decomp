#include "dr/dr_res_query_acc.h"

#include "dr/dr_man.h"
#include "dr/dr_pixl_occ_query.h"
#include "grlib/cglib_occlusion_query.h"

namespace ml {

DrResQueryAcc::DrResQueryAcc() : m_drResQueryObj(nullptr) {}

void DrResQueryAcc::releaseQuery() {
  if (m_drResQueryObj != nullptr) {
    m_drResQueryObj->m_drResUseQueryObj = nullptr;
    m_drResQueryObj = nullptr;
  }
}

u32 DrResQueryAcc::getOccPixel() {
  if (m_drResQueryObj != nullptr && (m_drResQueryObj->unknown38 & (4 << DrMan::s_nDblNowIdx))) {
    return m_drResQueryObj->m_cGLibOcclusionQuery.getQueryPixel();
  }
  return 0;
}

} // namespace ml
