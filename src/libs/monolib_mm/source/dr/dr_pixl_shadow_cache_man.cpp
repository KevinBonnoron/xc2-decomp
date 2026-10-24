#include "dr/dr_pixl_shadow_cache_man.h"

namespace ml {

bool DrPixlShadowCacheMan::isShadowMap() const { return unknown00 & 8; }

void DrPixlShadowCacheMan::callShadowCacheUpdate(bool isAll) { unknown00 = unknown00 | (isAll ? 0x180 : 0x80); }

void DrPixlShadowCacheMan::callShadowCacheVariance() { unknown00 |= 0x400; }

void DrPixlShadowCacheMan::callFgShadowCacheUpdate() {}

void DrPixlShadowCacheMan::endMode() { unknown00 |= 0x40; }

} // namespace ml
