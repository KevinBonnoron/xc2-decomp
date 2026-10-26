#include "gmk/gmk_battle_lock.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep

namespace gmk {

template bool TGmkList<GmkBattleLock, GmkBattleLock::BdatInfo, 1129075778u, 3u, GmkBattleLockGob>::initGmkBdatInfo(GmkBattleLock::BdatInfo &, int &, const AGmkBase &);

GmkType GmkBattleLock::getGmkType() const { return GMK_TYPE; }

bool GmkBattleLock::isValid() const { return unknown08.unknown00 != nullptr && unknown20.unknown08 != nullptr; }

void GmkBattleLock::create(const CreateInfo &info) { AGmkBase::create(info); }

void GmkBattleLock::debugDraw() const { isValid(); }

} // namespace gmk
