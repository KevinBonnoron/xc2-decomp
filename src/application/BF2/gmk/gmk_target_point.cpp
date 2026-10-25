#include "gmk/gmk_target_point.h"

namespace gmk {

GmkType GmkTargetPoint::getGmkType() const { return GMK_TYPE; }

bool GmkTargetPoint::isValid() const { return unknown08.unknown00 != nullptr && unknown20.unknown08 != nullptr; }

} // namespace gmk
