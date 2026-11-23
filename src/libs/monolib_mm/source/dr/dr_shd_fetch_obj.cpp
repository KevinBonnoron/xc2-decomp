#include "dr/dr_shd_fetch_obj.h"

namespace ml {

DrShdFetchObj::DrShdFetchObj(u32 first, u32 second, u32 third, int num, const MdsMatVertexInfo *infos)
    : unknown00(nullptr), unknown08(nullptr), unknown10(first), unknown14(second), unknown18(third), unknown1c(1) {
  m_fetch.setMdlVertexParam(num, infos);
}

DrShdFetchObj::~DrShdFetchObj() { m_fetch.clearWork(); }

} // namespace ml
