#include "dr/dr_pixl_shadow_cache_man.h"

#include "dr/dr_man.h"
#include "dr/dr_pixl_format.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_mem_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "grlib/cglib_dbl_uniform_block.h"
#include "grlib/cglib_depth_target.h"
#include "mm_mtl/fixed_array.h"

namespace ml {

DrPixlShadowCacheMan::~DrPixlShadowCacheMan() {
  m_shadowDirUniform.unknown001();
  if (unknown00 & 2) {
    for (int i = 0; i < 4; i++) {
      unknown0010[i].unknown5940.release();
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < unknown187a4; j++) {
      unknown0010[i].unknown0000[j].release();
    }
  }
}

void DrPixlShadowCacheMan::createCacheBuff() {
  m_shadowDirUniform.unknown001();
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < unknown187a4; j++) {
      unknown0010[i].unknown0000[j].release();
      unknown0010[i].unknown0000[j].unknown8f0 = i;
    }
  }
  DrPixlMemMan *memMan = DrPixlMemMan::get();
  u32 resArea = memMan->unknown010[DrMan::getIns()->unknown1c98].unknown1e8;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < unknown187a4; j++) {
      unknown0010[i].unknown0000[j].createShadow(unknown0010[i].unknown5854, resArea);
      unknown0010[i].unknown0000[j].setID(j + i * unknown187a4);
      resArea += memMan->unknown010[DrMan::getIns()->unknown1c98].unknown1f0;
    }
  }
  resArea = memMan->unknown010[DrMan::getIns()->unknown1c98].unknown1f4;
  for (int j = 0; j < unknown187a4; j++) {
    unknown0010[3].unknown0000[j].createShadow(unknown0010[3].unknown5854, resArea);
    unknown0010[3].unknown0000[j].setID(j + 3 * unknown187a4);
    unknown0010[3].unknown0000[j].unknown808 |= 0x10;
    resArea += memMan->unknown010[DrMan::getIns()->unknown1c98].unknown1fc;
  }
  m_shadowDirUniform.setupArray(4);
  m_shadowDirUniform.unknown0c = 0x800;
  m_shadowDirUniform.unknown002();
  for (int i = 0; i < 4; i++) {
    m_shadowDirUniform.unknown0c += m_shadowDirUniform[i].setupArray(0x40, m_shadowDirUniform.unknown18, m_shadowDirUniform.unknown0c);
  }
  unknown00 |= 1;
}

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

void DrPixlShadowCacheMan::resetColorBuff() {
  DrPixlMemMan *memMan = DrPixlMemMan::get();
  u32 resArea = memMan->unknown010[DrMan::getIns()->unknown1c98].unknown1ec;
  unknown0010[0].unknown5940.setTextureInfo(unknown0010[0].unknown5854, unknown0010[0].unknown5854, DrPixlFormat::s_ShadowFormat, true, resArea);
  resArea += memMan->unknown010[DrMan::getIns()->unknown1c98].unknown1f0;
  unknown0010[1].unknown5940.setTextureInfo(unknown0010[1].unknown5854, unknown0010[1].unknown5854, DrPixlFormat::s_ShadowFormat, true, resArea);
  resArea += memMan->unknown010[DrMan::getIns()->unknown1c98].unknown1f0;
  unknown0010[2].unknown5940.setTextureInfo(unknown0010[2].unknown5854, unknown0010[2].unknown5854, DrPixlFormat::s_ShadowFormat, true, resArea);
  DrMan::getIns();
  resArea = memMan->unknown010[DrMan::getIns()->unknown1c98].unknown1f8;
  unknown0010[3].unknown5940.setTextureInfo(unknown0010[3].unknown5854, unknown0010[3].unknown5854, DrPixlFormat::s_ShadowFormat, true, resArea);
  DrMan::getIns();
}

void DrPixlShadowCacheMan::buffUpdate() {
  createCacheBuff();
  createShadowTemp();
}

bool DrPixlShadowCacheMan::isShadowMap() const { return unknown00 & 8; }

void DrPixlShadowCacheMan::callShadowCacheUpdate(bool isAll) { unknown00 = unknown00 | (isAll ? 0x180 : 0x80); }

void DrPixlShadowCacheMan::callShadowCacheVariance() { unknown00 |= 0x400; }

void DrPixlShadowCacheMan::callFgShadowCacheUpdate() {}

void DrPixlShadowCacheMan::fastRender() {
  if (unknown00 & 0x28) {
    if (!isShadowMap() || unknown187ac == 0 || DrMan::get()->unknown1d7a) {
      clearShadowMap();
    } else {
      shadowmapRender(0);
      shadowmapRender(1);
      shadowmapRender(2);
    }
    shadowmapRender(3);
    unknown00 &= ~0x20;
  }
}

void DrPixlShadowCacheMan::debugShadowCacheRender() {
  DrMan *man = DrMan::get();
  int index = static_cast<int>(man->unknown120[man->unknown1c98]->unknown102c - 1.0f);
  if (index < 0) {
    index = 0;
  }
  if (index > 3) {
    index = 3;
  }
  int size = DrMan::get()->unknown5b8->unknown18 / 8;
  int x = 0;
  int y = 0;
  int column = 0;
  for (int i = 0; i < unknown187a4; i++) {
    DrMan::get()->unknown78->debugRender(*unknown0010[index].unknown0000[i].unknown128, x, y, size, size, false, false, 1.0f, true);
    column++;
    if (column >= unknown187a0) {
      x = 0;
      y += size;
      column = 0;
    } else {
      x += size;
    }
  }
  unknown08->debugRender(*unknown0010[index].unknown5940.unknown128, x, y, size, size, false, false, 1.0f, true);
}

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
