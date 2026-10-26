#include "dr/dr_pixl_shadow_cache_obj.h"

#include "grlib/cglib_gpu_cache.h"

namespace ml {

void DrPixlShadowCacheObj::release() { CGLibDepthTarget::release(); }

void DrPixlShadowCacheObj::end() { grlib::CGLibGPUCache::depthInvalidate(*unknown120); }

void DrPixlShadowCacheObj::setClear() { unknown808 &= ~2; }

void DrPixlShadowCacheObj::setNewGrid() { unknown808 &= ~6; }

void DrPixlShadowCacheObj::setBigMode(bool isBig) {
  if (isBig) {
    unknown808 |= 8;
  } else {
    unknown808 &= ~8;
  }
}

void DrPixlShadowCacheObj::setID(int id) {
  unknown8e8 = 1ull << id;
  unknown8f2 = id;
}

} // namespace ml
