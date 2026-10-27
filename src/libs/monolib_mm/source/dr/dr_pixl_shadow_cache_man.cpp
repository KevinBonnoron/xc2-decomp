#include "dr/dr_pixl_shadow_cache_man.h"

#include "dr/dr_man.h"
#include "grlib/cglib_dbl_uniform_block.h"
#include "grlib/cglib_depth_target.h"

namespace ml {

void DrPixlShadowCacheMan::createShadowTemp() {
  DrMan::get();
  if (unknown00 & 2) {
    for (int i = 0; i < 4; i++) {
      unknown0010[i].unknown5940.release();
    }
    unknown00 &= ~2;
  }
  unknown00 |= 2;
  resetColorBuff();
}

void DrPixlShadowCacheMan::buffUpdate() {
  createCacheBuff();
  createShadowTemp();
}

bool DrPixlShadowCacheMan::isShadowMap() const { return unknown00 & 8; }

void DrPixlShadowCacheMan::callShadowCacheUpdate(bool isAll) { unknown00 = unknown00 | (isAll ? 0x180 : 0x80); }

void DrPixlShadowCacheMan::callShadowCacheVariance() { unknown00 |= 0x400; }

void DrPixlShadowCacheMan::callFgShadowCacheUpdate() {}

void DrPixlShadowCacheMan::endMode() { unknown00 |= 0x40; }

void DrPixlShadowCacheMan::debugInfoRender() {}

void DrPixlShadowCacheMan::setShadowDirRenderTarget(int index) { unknown0010[index].unknown5940.setRenderTarget(); }

void DrPixlShadowCacheMan::setupDirRenderTarget(int index) { unknown0010[index].unknown5940.setRenderTarget(); }

void *DrPixlShadowCacheMan::getShadowDirUniform(int index) { return &m_shadowDirUniform[index]; }

void DrPixlShadowCacheMan::clearShadowMap() {
  unknown0010[0].unknown5940.clearDepth(false);
  unknown0010[1].unknown5940.clearDepth(false);
  unknown0010[2].unknown5940.clearDepth(false);
  unknown0010[3].unknown5940.clearDepth(false);
}

void DrPixlShadowCacheMan::clearZeroShadowMap() {
  unknown0010[0].unknown5940.clearValDepth(0.0f, false);
  unknown0010[1].unknown5940.clearValDepth(0.0f, false);
  unknown0010[2].unknown5940.clearValDepth(0.0f, false);
  unknown0010[3].unknown5940.clearValDepth(0.0f, false);
}

void DrPixlShadowCacheMan::addShadowCacheUpdate(bool) {
  unknown187ac++;
  unknown00 |= 0x80;
}

void DrPixlShadowCacheMan::delShadowCacheUpdate() {
  unknown187ac--;
  if (unknown187ac < 0) {
    unknown187ac = 0;
  }
  unknown00 |= 0x180;
}

void DrPixlShadowCacheMan::callSelectShadowCacheUpdate(u64 mask) { unknown187b0 &= ~mask; }

bool DrPixlShadowCacheMan::isShadowCache() const { return unknown187ac != 0 && isShadowMap(); }

} // namespace ml
