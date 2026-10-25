#include "gmk/gmk_mob/gmk_mob.h"

namespace gmk {

GmkType GmkMob::getGmkType() const { return GMK_TYPE; }

void GmkMob::debugDraw() const { isValid(); }

} // namespace gmk
