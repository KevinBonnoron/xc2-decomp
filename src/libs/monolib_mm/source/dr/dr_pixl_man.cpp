#include "dr/dr_pixl_man.h"

#include "dr/dr_ap_cache.h"
#include "dr/dr_ap_gx_type.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_deferred.h"
#include "dr/dr_pixl_post_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_pixl_render_target.h"
#include "dr/dr_pixl_shadow_cache_man.h"
#include "grlib/cglib_color_ctl.h"
#include "grlib/cglib_depth_target.h"
#include "grlib/cglib_render_target.h"
#include "grlib/cglib_state.h"

namespace ml {

static const s32 s_gbuffPixlObjs[] = {0, 1, 2, 3, 4, 8, 5, 6, 7, 15, 18};

static bool isDblPixlObj(int type) { return (0x27200ULL >> type) & 1; }

void DrPixlMan::endDeferredRenderTarget() { unknown7f0->unknown00[5][0]->setColorInvalidate(); }

void DrPixlMan::setMainViewPort() {
  grlib::LibMainStateViewPort viewPort(0.0f, 0.0f, static_cast<f32>(unknown08->unknown5b8->unknown18), static_cast<f32>(unknown08->unknown5b8->unknown1c), 0.0f, 1.0f);
  grlib::CGLibState::setViewport(viewPort);
}

void DrPixlMan::resetRenderTarget() { unknown858 = 0; }

void DrPixlMan::endGBuffTexture() {
  if (unknown08->unknown120[unknown08->unknown1c98]->m_toneMapOn) {
    unknown7f0->unknown00[6][0]->setColorInvalidate();
  }
}

void DrPixlMan::setMainRenderTarget() {
  if (unknown7f0->unknown1d0 == nullptr) {
    grlib::CGLibState::setMainFrameBuffer();
  } else {
    grlib::CGLibState::beginRegisterRenderTarget();
    grlib::CGLibState::setRegisterRenderTarget(*unknown7f0->unknown1d0, grlib::GRL_MRT_TYPE_0);
    grlib::CGLibState::endRegisterRenderTarget();
  }
  setFinalViewPort();
}

void DrPixlMan::selectOpcaityBlmRenderTarget() {
  unknown858 = 6;
  grlib::CGLibState::beginRegisterRenderTarget();
  grlib::CGLibState::setRegisterRenderTarget(*getPixlObj(5), grlib::GRL_MRT_TYPE_0);
  grlib::CGLibState::setRegisterRenderTarget(*getPixlObj(6), grlib::GRL_MRT_TYPE_1);
  grlib::CGLibState::setRegisterRenderTarget(*getPixlObj(9), grlib::GRL_MRT_TYPE_2);
  grlib::CGLibState::setRegisterDepthTarget(*getDepthObj()->unknown120);
  grlib::CGLibState::endRegisterRenderTarget();
}

void DrPixlMan::selectOpcaityRenderTarget() {
  grlib::CGLibState::beginRegisterRenderTarget();
  grlib::CGLibState::setRegisterRenderTarget(*getPixlObj(5), grlib::GRL_MRT_TYPE_0);
  grlib::CGLibState::setRegisterDepthTarget(*getDepthObj()->unknown120);
  grlib::CGLibState::endRegisterRenderTarget();
}

DrPixlRenderTarget *DrPixlMan::getPixlObj(int type) {
  if (isDblPixlObj(type)) {
    return unknown7f0->unknown00[type][DrMan::s_nDblIdx];
  }
  return unknown7f0->unknown00[type][0];
}

grlib::CGLibDepthTarget *DrPixlMan::getDepthObj() { return unknown7f0->unknown1a0[DrMan::s_nDblIdx]; }

grlib::CGLibTextureBuffer *DrPixlMan::getDammyWhiteTexObj() { return unknown838->unknown70; }

DrPixlMan::~DrPixlMan() { releaseColorBuffer(); }

void DrPixlMan::resetLightBuffOnly() {}

void DrPixlMan::createShadowParmDisplayList(wkPixlManRes *res) { res->unknown1d8 &= ~RES_FLAG_SHADOW_DISPLAY_LIST; }

void DrPixlMan::setupCate(int cate) {
  unknown7f0 = &unknown10[cate];
  unknown860 = cate;
}

void DrPixlMan::updateShadowDisplayList() {
  if (unknown7f0->unknown1d8 & RES_FLAG_SHADOW_DISPLAY_LIST) {
    createShadowParmDisplayList(unknown7f0);
  }
}

DrPixlRenderTarget *DrPixlMan::getResponsiveAAMask() { return unknown7f0->unknown00[18][0]; }

grlib::CGLibDepthTarget *DrPixlMan::getSeparateTransDepthObj() {
  if (unknown08->unknown120[unknown08->unknown1c98]->unknownfb4) {
    return unknown7f0->unknown1b0;
  }
  return getDepthObj();
}

void DrPixlMan::displayUpdate() { unknown7f0->unknown170->displayUpdate(); }

void DrPixlMan::renderEnd(int loop) {
  if (unknown7f0->unknown1d0 != nullptr) {
    unknown7f0->unknown1d0->setColorInvalidate();
  }
}

void DrPixlMan::selectZprepassRenderTarget() {
  unknown858 = 1;
  unknown85c = 0;
  grlib::CGLibState::beginRegisterRenderTarget();
  grlib::CGLibState::setRegisterDepthTarget(*getDepthObj()->unknown120);
  grlib::CGLibState::endRegisterRenderTarget();
}

void DrPixlMan::selectGBuffRenderTarget() { selectGBuffRenderTarget(0xff); }

bool DrPixlMan::selectGBuffRenderTarget(u32 mask) {
  if (unknown858 == 2 && unknown85c == mask) {
    return false;
  }
  unknown858 = 2;
  unknown85c = mask;
  grlib::CGLibState::beginRegisterRenderTarget();
  int mrt = 0;
  for (int i = 0; i < 11; i++) {
    if (mask & (1 << i)) {
      grlib::CGLibState::setRegisterRenderTarget(*getPixlObj(s_gbuffPixlObjs[i]), static_cast<grlib::GrlMrtType>(mrt));
      mrt++;
    }
  }
  grlib::CGLibState::setRegisterDepthTarget(*getDepthObj()->unknown120);
  grlib::CGLibState::endRegisterRenderTarget();
  return true;
}

void DrPixlMan::refractionGBuffInvalidate() {
  unknown7f0->unknown00[0][0]->setColorInvalidate();
  unknown7f0->unknown00[1][0]->setColorInvalidate();
  unknown7f0->unknown00[2][0]->setColorInvalidate();
  unknown7f0->unknown00[3][0]->setColorInvalidate();
  unknown7f0->unknown00[4][0]->setColorInvalidate();
}

void DrPixlMan::endGBuffRenderTarget() {
  unknown7f0->unknown00[0][0]->setColorInvalidate();
  unknown7f0->unknown00[1][0]->setColorInvalidate();
  unknown7f0->unknown00[2][0]->setColorInvalidate();
  unknown7f0->unknown00[3][0]->setColorInvalidate();
  unknown7f0->unknown00[4][0]->setColorInvalidate();
  unknown7f0->unknown00[8][0]->setColorInvalidate();
  unknown7f0->unknown00[5][0]->setColorInvalidate();
  unknown7f0->unknown00[6][0]->setColorInvalidate();
}

void DrPixlMan::selectDeferredRenderTarget() {
  if (unknown858 == 4) {
    return;
  }
  unknown858 = 4;
  grlib::CGLibState::beginRegisterRenderTarget();
  grlib::CGLibState::setRegisterRenderTarget(*getPixlObj(5), grlib::GRL_MRT_TYPE_0);
  grlib::CGLibState::setRegisterDepthTarget(*getDepthObj()->unknown120);
  grlib::CGLibState::endRegisterRenderTarget();
}

void DrPixlMan::selectRefractRenderTarget() {
  unknown858 = 5;
  grlib::CGLibState::beginRegisterRenderTarget();
  grlib::CGLibState::setRegisterDepthTarget(*getDepthObj()->unknown120);
  grlib::CGLibState::endRegisterRenderTarget();
}

void DrPixlMan::selectPrePassWrkClearRenderTarget() {
  unknown858 = 0;
  grlib::CGLibState::beginRegisterRenderTarget();
  grlib::CGLibState::setRegisterRenderTarget(*getPixlObj(5), grlib::GRL_MRT_TYPE_0);
  grlib::CGLibState::setRegisterDepthTarget(*getDepthObj()->unknown120);
  grlib::CGLibState::endRegisterRenderTarget();
  setMainViewPort();
}

void DrPixlMan::selectGlobalIBLIndexRenderTarget() {
  if (unknown858 == 11) {
    return;
  }
  unknown858 = 11;
  grlib::CGLibState::beginRegisterRenderTarget();
  grlib::CGLibState::setRegisterRenderTarget(*getPixlObj(3), grlib::GRL_MRT_TYPE_0);
  grlib::CGLibState::setRegisterDepthTarget(*getDepthObj()->unknown120);
  grlib::CGLibState::endRegisterRenderTarget();
}

void DrPixlMan::endGlobalIBLIndexRenderTarget() { unknown7f0->unknown00[3][0]->setColorInvalidate(); }

void DrPixlMan::alphaRenderTarget() {
  if (selectGBuffRenderTarget(0x1c0)) {
    setMainViewPort();
  }
}

void DrPixlMan::skyVisibilityRenderTarget() {}

void DrPixlMan::skyGodRayRenderTarget() {
  if (selectGBuffRenderTarget(0x100)) {
    setMainViewPort();
  }
}

void DrPixlMan::renderRefractionMap(bool isRefractionMap, bool isHalfMap) { unknown7f0->unknown180->renderRefractionMap(isRefractionMap, isHalfMap); }

void DrPixlMan::renderSkyDome() { unknown7f0->unknown180->renderSkyDome(); }

void DrPixlMan::renderSkyGodRay() { unknown7f0->unknown180->renderSkyGodRay(); }

void DrPixlMan::renderRainDrop() { unknown7f0->unknown180->renderRainDrop(); }

void DrPixlMan::renderTMAA() { unknown7f0->unknown180->renderTMAA(); }

bool DrPixlMan::isRefractionMap() { return unknown7f0->unknown180->unknownd0 != nullptr; }

void DrPixlMan::thicknessFirstBegin() {
  unknown858 = 13;
  grlib::CGLibState::beginRegisterRenderTarget();
  grlib::CGLibState::setRegisterRenderTarget(*unknown7f0->unknown148, grlib::GRL_MRT_TYPE_0);
  grlib::CGLibState::setRegisterDepthTarget(*getDepthObj()->unknown120);
  grlib::CGLibState::endRegisterRenderTarget();
}

DrPixlRenderTarget *DrPixlMan::getBackFaceDepthTexture() { return unknown7f0->unknown148; }

void DrPixlMan::thicknessFirstEnd() { unknown7f0->unknown148->setColorInvalidate(); }

void DrPixlMan::lastDeferredRender() { unknown7f0->unknown170->lastDeferredRender(); }

void DrPixlMan::occRenderEnd() { DrAPGxType::endOccQuery(); }

void DrPixlMan::depCheckEnd() { grlib::CGLibColorCtl::setColorBufferOn(); }

void DrPixlMan::shadowCallDirBegin() {
  unknown08->unknown5c0->shadowBegin();
  DrAPGxType::beginShadow();
}

void DrPixlMan::shadowCallDirEnd() {
  DrAPGxType::endShadow();
  resetRenderTarget();
  selectGBuffRenderTarget();
  setMainViewPort();
}

void DrPixlMan::shadowDirBegin() {
  unknown08->unknown5c0->shadowBegin();
  DrAPGxType::beginShadow();
}

void DrPixlMan::shadowDirEnd() {
  DrAPGxType::endShadow();
  resetRenderTarget();
  selectGBuffRenderTarget();
  setMainViewPort();
}

void DrPixlMan::callShadowCacheUpdate(bool isAll) { unknown800->callShadowCacheUpdate(isAll); }

void DrPixlMan::callShadowCacheVariance() { unknown800->callShadowCacheVariance(); }

void DrPixlMan::callFgShadowCacheUpdate() { unknown800->callFgShadowCacheUpdate(); }

void DrPixlMan::fastRender() {
  unknown7f0->unknown180->fastRender();
  if (unknown860 == 0) {
    unknown800->shadowCacheRender();
    unknown800->fastRender();
  }
}

void DrPixlMan::lastCapRender() { unknown7f0->unknown180->capRender(); }

void DrPixlMan::setFinalViewPort() {
  grlib::LibMainStateViewPort viewPort(0.0f, 0.0f, static_cast<f32>(unknown08->unknown5b8->unknown20), static_cast<f32>(unknown08->unknown5b8->unknown24), 0.0f, 1.0f);
  grlib::CGLibState::setViewport(viewPort);
}

void DrPixlMan::setMainSRGBRenderTarget() { grlib::CGLibState::setMainFrameBuffer(); }

void DrPixlMan::setMainSRGBAfterRenderTarget() {}

void DrPixlMan::changeColorBuff() {
  unknown7f0->unknown138->setColorInvalidate();
  if (unknown7f0->unknown138 == unknown7f0->unknown130) {
    unknown7f0->unknown138 = unknown7f0->unknown140;
  }
}

void DrPixlMan::changeHDRBuff(DrPixlRenderTarget *hdrBuff) {
  if (unknown7f0->unknown138 == unknown7f0->unknown140) {
    unknown7f0->unknown138 = hdrBuff;
  }
  unknown7f0->unknown140 = hdrBuff;
}

void DrPixlMan::setTempColorBuff() { getTempColorBuff()->setRenderTarget(); }

DrPixlRenderTarget *DrPixlMan::getTempColorBuff() {
  if (unknown7f0->unknown138 != unknown7f0->unknown130) {
    return unknown7f0->unknown130;
  }
  return unknown7f0->unknown140;
}

void DrPixlMan::pixelEndMode() { unknown800->endMode(); }

void DrPixlMan::setToneAveRange(f32 min, f32 max) {
  unknown7f0->unknown194 = min;
  unknown7f0->unknown198 = max;
}

grlib::CGLibTextureBuffer *DrPixlMan::getDammyTexObj() { return unknown830->unknown70; }

void DrPixlMan::offScreenAlphaEnd() { DrAPGxType::setupAlphaChanel(true); }

void DrPixlMan::debugDeferredRenderAlbedoAndFogRatio(int x, int y, int width, int height) {}

DrPixlRenderTarget *DrPixlMan::getDeactivePixlObj(int type) {
  if (!isDblPixlObj(type)) {
    return nullptr;
  }
  return unknown7f0->unknown00[type][DrMan::s_nDblIdx ^ 1];
}

grlib::CGLibDepthTarget *DrPixlMan::getDeactiveDepthObj() { return unknown7f0->unknown1a0[DrMan::s_nDblStockIdx]; }

void DrPixlMan::swapPixlObj(int type) {
  if (isDblPixlObj(type)) {
    DrPixlRenderTarget *deactive = unknown7f0->unknown00[type][DrMan::s_nDblIdx ^ 1];
    unknown7f0->unknown00[type][DrMan::s_nDblIdx ^ 1] = unknown7f0->unknown00[type][DrMan::s_nDblIdx];
    unknown7f0->unknown00[type][DrMan::s_nDblIdx] = deactive;
  }
}

DrPixlRenderTarget *DrPixlMan::getBackFaceDepthTexture() const { return unknown7f0->unknown148; }

} // namespace ml
