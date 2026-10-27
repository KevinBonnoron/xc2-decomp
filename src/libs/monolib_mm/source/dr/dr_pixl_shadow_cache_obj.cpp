#include "dr/dr_pixl_shadow_cache_obj.h"

#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_man.h"
#include "grlib/cglib_gpu_cache.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {

void DrPixlShadowCacheObj::release() { CGLibDepthTarget::release(); }

void DrPixlShadowCacheObj::begin() {
  setRenderTarget();
  DrMan::get()->unknown580->unknown10->shadowBegin(unknown810);
}

bool DrPixlShadowCacheObj::clipTest(const mm::Vec3 &position, f32 radius) { return unknown900.clipTest(position, radius); }

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
