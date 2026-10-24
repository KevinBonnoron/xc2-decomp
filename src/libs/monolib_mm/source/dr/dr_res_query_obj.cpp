#include "dr/dr_man.h"
#include "dr/dr_pixl_occ_query.h"
#include "dr/dr_res_use_query_obj.h"
#include "grlib/cglib_occlusion_query.h"
#include "types.h"

namespace ml {

u32 DrResQueryObj::getOccZPassCount() {
  if (unknown38 & (DrResUseQueryObj::QUERY_FLAG_RESULT << DrMan::s_nDblNowIdx)) {
    return unknown10.getQueryPixel();
  }
  return 0;
}

DrResQueryObj::DrResQueryObj() : unknown00(nullptr), unknown08(nullptr), unknown28(nullptr), unknown30(nullptr), unknown38(0) {}

DrResQueryObj::~DrResQueryObj() { unknown10.release(); }

bool DrResQueryObj::update() {
  if (unknown28 == nullptr) {
    if (unknown38 & DrResUseQueryObj::QUERY_FLAG_BEGIN) {
      unknown38 &= ~3;
      return false;
    }
  } else if (unknown38 & 2) {
    if (unknown38 & DrResUseQueryObj::QUERY_FLAG_BEGIN) {
      unknown38 &= ~DrResUseQueryObj::QUERY_FLAG_BEGIN;
      return false;
    }
    unknown28->m_query = nullptr;
  } else {
    if (unknown38 & DrResUseQueryObj::QUERY_FLAG_BEGIN) {
      unknown38 &= ~DrResUseQueryObj::QUERY_FLAG_BEGIN;
      return false;
    }
    unknown38 = 2;
    return false;
  }
  unknown38 = 0;
  unknown28 = nullptr;
  unknown30 = nullptr;
  return true;
}

void DrResQueryObj::begin() {
  unknown10.beginQuery();
  unknown38 |= DrResUseQueryObj::QUERY_FLAG_RESULT << DrMan::s_nDblNowIdx;
}

void DrResQueryObj::end() { unknown10.endQuery(); }

} // namespace ml
