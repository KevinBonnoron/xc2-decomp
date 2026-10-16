#include "dr/dr_res_use_query_obj.h"

#include "dr/dr_man.h"
#include "dr/dr_pixl_occ_query.h"
#include "grlib/cglib_occlusion_query.h"

namespace ml {

DrResUseQueryObj::DrResUseQueryObj() : m_query(nullptr), m_pixel(0) {}

DrResUseQueryObj::~DrResUseQueryObj() {
  if (m_query != nullptr) {
    m_query->user = nullptr;
    m_query = nullptr;
  }
}

void DrResUseQueryObj::update() {
  if (m_query == nullptr) {
    m_pixel = 0;
    return;
  }
  m_pixel = (m_query->flags & (QUERY_FLAG_RESULT << DrMan::s_nDblNowIdx)) ? m_query->query.getQueryPixel() : 0;
}

void DrResUseQueryObj::begin(DrPixlOccQuery *occQuery) {
  DrResQueryObj *query = m_query;
  if (query == nullptr) {
    query = occQuery->createObj();
    if (query == nullptr) {
      return;
    }
    m_query = query;
    query->user = this;
  }
  query->flags |= QUERY_FLAG_BEGIN;
  query->query.beginQuery();
  query->flags |= QUERY_FLAG_RESULT << DrMan::s_nDblNowIdx;
}

void DrResUseQueryObj::end() {
  if (m_query != nullptr) {
    m_query->query.endQuery();
  }
}

} // namespace ml
