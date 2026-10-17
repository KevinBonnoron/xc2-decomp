#include "dr/dr_pixl_shadow_cache_man.h"

namespace ml {

bool DrPixlShadowCacheMan::isShadowMap() const { return m_flags & 8; }

void DrPixlShadowCacheMan::callShadowCacheUpdate(bool isAll) { m_flags = m_flags | (isAll ? 0x180 : 0x80); }

void DrPixlShadowCacheMan::callShadowCacheVariance() { m_flags |= 0x400; }

void DrPixlShadowCacheMan::callFgShadowCacheUpdate() {}

void DrPixlShadowCacheMan::endMode() { m_flags |= 0x40; }

} // namespace ml
