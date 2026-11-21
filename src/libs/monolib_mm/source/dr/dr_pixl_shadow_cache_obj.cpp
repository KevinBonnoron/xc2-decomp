#include "dr/dr_pixl_shadow_cache_obj.h"

#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_format.h"
#include "dr/dr_pixl_man.h"
#include "grlib/cglib_gpu_cache.h"

namespace ml {

void DrPixlShadowCacheObj::createShadow(int size, u32 resArea) {
  unknown80c = size;
  release();
  setClear();
  setTextureInfo(unknown80c, unknown80c, DrPixlFormat::s_ShadowFormat, true, resArea);
}

void DrPixlShadowCacheObj::release() { CGLibDepthTarget::release(); }

void DrPixlShadowCacheObj::begin() {
  setRenderTarget();
  DrMan::get()->unknown580->unknown10->shadowBegin(unknown810);
}

void DrPixlShadowCacheObj::debugRender(int x, int y, int size) { DrMan::get()->unknown78->debugRender(*unknown128, x, y, size, size, false, false, 1.0f, true); }

DrPixlShadowCacheObj::DrPixlShadowCacheObj() : unknown800(0), unknown808(0), unknown80c(0), unknown8d0(0.0f, 0.0f, 0.0f), unknown8e0(0), unknown8e4(0), unknown8e8(1), unknown8f0(0), unknown8f2(0) {}

DrPixlShadowCacheObj::~DrPixlShadowCacheObj() { release(); }

bool DrPixlShadowCacheObj::clipTest(const mm::Vec3 &position, f32 radius) { return unknown900.clipTest(position, radius); }

void DrPixlShadowCacheObj::end() { grlib::CGLibGPUCache::depthInvalidate(*unknown120); }

void DrPixlShadowCacheObj::depthClear() {
  if (!(unknown808 & 2)) {
    clearDepth(false);
    unknown808 |= 2;
  }
}

void DrPixlShadowCacheObj::setClear() { unknown808 &= ~2; }

void DrPixlShadowCacheObj::setNewGrid() { unknown808 &= ~6; }

void DrPixlShadowCacheObj::update(const mm::Mat44 &view, const mm::Mat44 &projection, const mm::Vec3 &center, int gridX, int gridY) {
  unknown810 = view;
  unknown890 = projection;
  unknown850 = view;
  unknown850.unknown002(unknown850, projection);
  unknown8e0 = gridX;
  unknown8e4 = gridY;
  unknown808 |= 4;
  unknown8d0 = center;
  unknown900.setMatrix(unknown850);
}

bool DrPixlShadowCacheObj::checkGrid(int gridX, int gridY) const {
  if (unknown8e0 <= gridX + 2 && unknown8e0 >= gridX && unknown8e4 <= gridY + 2 && unknown8e4 >= gridY) {
    return false;
  }
  return true;
}

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
