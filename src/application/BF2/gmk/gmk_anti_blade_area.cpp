#include "gmk/gmk_anti_blade_area.h"

#include "gf/data/gf_bdat_wrapper.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

void GmkAntiBladeArea::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  dispose();
  unknown00 = bdat.getValCheck("BTL_MapRevId", id, BDAT_TYPE_U16);
}

} // namespace gmk
