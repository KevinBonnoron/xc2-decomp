#include "dr/dr_man.h"
#include "dr/dr_pixl_occ_query.h"
#include "dr/dr_res_use_query_obj.h"
#include "grlib/cglib_occlusion_query.h"
#include "types.h"

namespace ml {

u32 DrResQueryObj::getOccZPassCount() {
  if (flags & (DrResUseQueryObj::QUERY_FLAG_RESULT << DrMan::s_nDblNowIdx)) {
    return query.getQueryPixel();
  }
  return 0;
}

DrResQueryObj::DrResQueryObj() : next(nullptr), prev(nullptr), user(nullptr), subNext(nullptr), flags(0) {}

DrResQueryObj::~DrResQueryObj() { query.release(); }

bool DrResQueryObj::update() {
  if (user == nullptr) {
    if (flags & DrResUseQueryObj::QUERY_FLAG_BEGIN) {
      flags &= ~3;
      return false;
    }
  } else if (flags & 2) {
    if (flags & DrResUseQueryObj::QUERY_FLAG_BEGIN) {
      flags &= ~DrResUseQueryObj::QUERY_FLAG_BEGIN;
      return false;
    }
    user->m_query = nullptr;
  } else {
    if (flags & DrResUseQueryObj::QUERY_FLAG_BEGIN) {
      flags &= ~DrResUseQueryObj::QUERY_FLAG_BEGIN;
      return false;
    }
    flags = 2;
    return false;
  }
  flags = 0;
  user = nullptr;
  subNext = nullptr;
  return true;
}

void DrResQueryObj::begin() {
  query.beginQuery();
  flags |= DrResUseQueryObj::QUERY_FLAG_RESULT << DrMan::s_nDblNowIdx;
}

void DrResQueryObj::end() { query.endQuery(); }

} // namespace ml
