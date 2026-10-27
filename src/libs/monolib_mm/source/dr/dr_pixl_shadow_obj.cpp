#include "dr/dr_pixl_shadow_obj.h"

#include "dr/dr_ap_cache.h"
#include "dr/dr_ap_gx_type.h"
#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_man.h"
#include "dr/dr_mdo_shd_pxl_wrk_tex.h"
#include "dr/dr_pixl_man.h"
#include "grlib/cglib_gpu_cache.h"

namespace ml {

void DrPixlShadowObj::afterUpdate() {}

bool DrPixlShadowObj::dispChk() { return true; }

void DrPixlShadowObj::renderLight() {}

void DrPixlShadowObj::debugInfo() {}

void DrPixlShadowObj::stockTile() {}

void DrPixlShadowObj::update() {}

bool DrPixlShadowObj::clipChk(const mm::Vec3 &position, f32 value, bool flag) { return true; }

int DrPixlShadowObj::clipTypeChk(const mm::Vec3 &position, f32 value) { return 0; }

bool DrPixlShadowObj::setSptCalcPos(const mm::Vec3 &position, f32 value) { return true; }

const f32 *DrPixlShadowObj::getParmTbl() const { return unknown60.rows[0]; }

void DrPixlShadowObj::createWork(DrLightObj *light, int index, MdoShdPxlWrkTex *work) {
  unknown40 = work;
  unknown4a = index;
  unknown198 = light;
  unknown08.release();
  if (unknown4c == 1) {
    unknown08.setup(0x50);
  } else {
    unknown08.setup(0x40);
  }
}

void DrPixlShadowObj::releaseWork() { unknown08.release(); }

void DrPixlShadowObj::setInstSelMapShadow(bool value) {
  if (value) {
    unknown50 |= 4;
  } else {
    unknown50 &= ~4;
  }
}

void DrPixlShadowObj::renderSetup() {
  if (!(unknown50 & 1)) {
    unknown40->clearDepth(false);
    unknown178->unknown5c0->shadowBegin();
    DrAPGxType::beginShadow();
    unknown178->unknown78->unknown858 = 0;
    unknown40->setRenderTarget();
    unknown178->unknown580->unknown10->shadowBegin(unknown60);
    unknown50 |= 1;
  }
}

bool DrPixlShadowObj::renderEnd() {
  if (unknown50 & 1) {
    grlib::CGLibGPUCache::depthInvalidate(*unknown40->unknown120);
    DrAPGxType::endShadow();
    unknown178->unknown580->shadowEnd();
    return true;
  }
  return false;
}

} // namespace ml
