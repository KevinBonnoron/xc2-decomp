#include "gmk/gmk_mob/gmk_mob.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep

namespace gmk {

template bool TGmkList<GmkMob, GmkMob::BdatInfo, 4345677u, 2u, GmkMobGob>::initGmkBdatInfo(GmkMob::BdatInfo &, int &, const AGmkBase &);

GmkType GmkMob::getGmkType() const { return GMK_TYPE; }

void GmkMob::debugDraw() const { isValid(); }

} // namespace gmk
