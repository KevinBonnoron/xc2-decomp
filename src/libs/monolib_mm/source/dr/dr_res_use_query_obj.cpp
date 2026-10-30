#include "dr/dr_res_use_query_obj.h"

#include "dr/dr_man.h"
#include "dr/dr_pixl_occ_query.h"
#include "grlib/cglib_occlusion_query.h"

namespace ml {

DrResUseQueryObj::DrResUseQueryObj() : m_query(nullptr), m_pixel(0) {}

DrResUseQueryObj::~DrResUseQueryObj() {
  if (m_query != nullptr) {
    m_query->unknown28 = nullptr;
    m_query = nullptr;
  }
}

void DrResUseQueryObj::update() {
  if (m_query == nullptr) {
    m_pixel = 0;
    return;
  }
  m_pixel = (m_query->unknown38 & (unknown001_4 << DrMan::s_nDblNowIdx)) ? m_query->unknown10.getQueryPixel() : 0;
}

void DrResUseQueryObj::begin(DrPixlOccQuery *occQuery) {
  DrResQueryObj *query = m_query;
  if (query == nullptr) {
    query = occQuery->createObj();
    if (query == nullptr) {
      return;
    }
    m_query = query;
    query->unknown28 = this;
  }
  query->unknown38 |= unknown001_1;
  query->unknown10.beginQuery();
  query->unknown38 |= unknown001_4 << DrMan::s_nDblNowIdx;
}

void DrResUseQueryObj::end() {
  if (m_query != nullptr) {
    m_query->unknown10.endQuery();
  }
}

} // namespace ml
