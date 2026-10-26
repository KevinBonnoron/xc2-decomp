#include "gmk/gmk_target_point.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep

namespace gmk {

template bool TGmkList<GmkTargetPoint, GmkTargetPoint::BdatInfo, 1414547284u, 1u, GmkTargetPointGob>::initGmkBdatInfo(GmkTargetPoint::BdatInfo &, int &, const AGmkBase &);

GmkType GmkTargetPoint::getGmkType() const { return GMK_TYPE; }

bool GmkTargetPoint::isValid() const { return unknown08.unknown00 != nullptr && unknown20.unknown08 != nullptr; }

} // namespace gmk
