#include "gmk/gmk_area_bgm.h"

#include "gf/data/gf_bdat_wrapper.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

void GmkAreaBgm::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  dispose();
  unknown00 = bdat.getValCheck("bgmCondition", id, BDAT_TYPE_U16);
}

} // namespace gmk
