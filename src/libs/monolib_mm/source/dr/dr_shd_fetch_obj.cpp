#include "dr/dr_shd_fetch_obj.h"

namespace ml {

DrShdFetchObj::DrShdFetchObj(u32 first, u32 second, u32 third, int num, const MdsMatVertexInfo *infos)
    : unknown00(0), unknown08(0), unknown10(first), unknown14(second), unknown18(third), unknown1c(1) {
  unknown20.setMdlVertexParam(num, infos);
}

DrShdFetchObj::~DrShdFetchObj() { unknown20.clearWork(); }

} // namespace ml
