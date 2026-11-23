#include "dr/dr_man.h"
#include "dr/dr_pixl_occ_query.h"
#include "dr/dr_res_use_query_obj.h"
#include "grlib/cglib_occlusion_query.h"
#include "types.h"

namespace ml {

u32 DrResQueryObj::getOccZPassCount() {
  if (unknown38 & (DrResUseQueryObj::unknown001_4 << DrMan::s_nDblNowIdx)) {
    return m_cGLibOcclusionQuery.getQueryPixel();
  }
  return 0;
}

DrResQueryObj::DrResQueryObj() : unknown00(nullptr), unknown08(nullptr), m_drResUseQueryObj(nullptr), unknown30(nullptr), unknown38(0) {}

DrResQueryObj::~DrResQueryObj() { m_cGLibOcclusionQuery.release(); }

bool DrResQueryObj::update() {
  if (m_drResUseQueryObj == nullptr) {
    if (unknown38 & DrResUseQueryObj::unknown001_1) {
      unknown38 &= ~3;
      return false;
    }
  } else if (unknown38 & 2) {
    if (unknown38 & DrResUseQueryObj::unknown001_1) {
      unknown38 &= ~DrResUseQueryObj::unknown001_1;
      return false;
    }
    m_drResUseQueryObj->m_query = nullptr;
  } else {
    if (unknown38 & DrResUseQueryObj::unknown001_1) {
      unknown38 &= ~DrResUseQueryObj::unknown001_1;
      return false;
    }
    unknown38 = 2;
    return false;
  }
  unknown38 = 0;
  m_drResUseQueryObj = nullptr;
  unknown30 = nullptr;
  return true;
}

void DrResQueryObj::begin() {
  m_cGLibOcclusionQuery.beginQuery();
  unknown38 |= DrResUseQueryObj::unknown001_4 << DrMan::s_nDblNowIdx;
}

void DrResQueryObj::end() { m_cGLibOcclusionQuery.endQuery(); }

} // namespace ml
