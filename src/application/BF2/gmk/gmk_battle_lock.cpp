#include "gmk/gmk_battle_lock.h"

namespace gmk {

GmkType GmkBattleLock::getGmkType() const { return GMK_TYPE; }

bool GmkBattleLock::isValid() const { return unknown08.unknown00 != nullptr && unknown20.unknown08 != nullptr; }

void GmkBattleLock::create(const CreateInfo &info) { AGmkBase::create(info); }

void GmkBattleLock::debugDraw() const { isValid(); }

} // namespace gmk
