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

void DrPixlMan::endDeferredRenderTarget() { m_res->pixlObjs[5][0]->setColorInvalidate(); }

void DrPixlMan::setMainViewPort() {
  grlib::LibMainStateViewPort viewPort(
      0.0f, 0.0f, static_cast<f32>(m_drMan->screenInfo->width), static_cast<f32>(m_drMan->screenInfo->height), 0.0f, 1.0f);
  grlib::CGLibState::setViewport(viewPort);
}

void DrPixlMan::resetRenderTarget() { m_renderTarget = 0; }

void DrPixlMan::endGBuffTexture() {
  if (m_drMan->postParms[m_drMan->viewIndex]->toneMap) {
    m_res->pixlObjs[6][0]->setColorInvalidate();
  }
}

void DrPixlMan::setMainRenderTarget() {
  if (m_res->mainRenderTarget == nullptr) {
    grlib::CGLibState::setMainFrameBuffer();
  } else {
    grlib::CGLibState::beginRegisterRenderTarget();
    grlib::CGLibState::setRegisterRenderTarget(*m_res->mainRenderTarget, grlib::GRL_MRT_TYPE_0);
    grlib::CGLibState::endRegisterRenderTarget();
  }
  setFinalViewPort();
}

void DrPixlMan::selectOpcaityBlmRenderTarget() {
  m_renderTarget = 6;
  grlib::CGLibState::beginRegisterRenderTarget();
  grlib::CGLibState::setRegisterRenderTarget(*getPixlObj(5), grlib::GRL_MRT_TYPE_0);
  grlib::CGLibState::setRegisterRenderTarget(*getPixlObj(6), grlib::GRL_MRT_TYPE_1);
  grlib::CGLibState::setRegisterRenderTarget(*getPixlObj(9), grlib::GRL_MRT_TYPE_2);
  grlib::CGLibState::setRegisterDepthTarget(*getDepthObj()->m_depthBuffer);
  grlib::CGLibState::endRegisterRenderTarget();
}

void DrPixlMan::selectOpcaityRenderTarget() {
  grlib::CGLibState::beginRegisterRenderTarget();
  grlib::CGLibState::setRegisterRenderTarget(*getPixlObj(5), grlib::GRL_MRT_TYPE_0);
  grlib::CGLibState::setRegisterDepthTarget(*getDepthObj()->m_depthBuffer);
  grlib::CGLibState::endRegisterRenderTarget();
}

DrPixlRenderTarget *DrPixlMan::getPixlObj(int type) {
  if (isDblPixlObj(type)) {
    return m_res->pixlObjs[type][DrMan::s_nDblIdx];
  }
  return m_res->pixlObjs[type][0];
}

grlib::CGLibDepthTarget *DrPixlMan::getDepthObj() { return m_res->depthObjs[DrMan::s_nDblIdx]; }

grlib::CGLibTextureBuffer *DrPixlMan::getDammyWhiteTexObj() { return m_dammyWhiteTex->m_texture; }

DrPixlMan::~DrPixlMan() { releaseColorBuffer(); }

void DrPixlMan::resetLightBuffOnly() {}

void DrPixlMan::createShadowParmDisplayList(wkPixlManRes *res) { res->flags &= ~RES_FLAG_SHADOW_DISPLAY_LIST; }

void DrPixlMan::setupCate(int cate) {
  m_res = &m_resources[cate];
  m_cate = cate;
}

void DrPixlMan::updateShadowDisplayList() {
  if (m_res->flags & RES_FLAG_SHADOW_DISPLAY_LIST) {
    createShadowParmDisplayList(m_res);
  }
}

DrPixlRenderTarget *DrPixlMan::getResponsiveAAMask() { return m_res->pixlObjs[18][0]; }

grlib::CGLibDepthTarget *DrPixlMan::getSeparateTransDepthObj() {
  if (m_drMan->postParms[m_drMan->viewIndex]->separateTrans) {
    return m_res->separateTransDepthObj;
  }
  return getDepthObj();
}

void DrPixlMan::displayUpdate() { m_res->deferred->displayUpdate(); }

void DrPixlMan::renderEnd(int loop) {
  if (m_res->mainRenderTarget != nullptr) {
    m_res->mainRenderTarget->setColorInvalidate();
  }
}

void DrPixlMan::selectZprepassRenderTarget() {
  m_renderTarget = 1;
  m_gbuffMask = 0;
  grlib::CGLibState::beginRegisterRenderTarget();
  grlib::CGLibState::setRegisterDepthTarget(*getDepthObj()->m_depthBuffer);
  grlib::CGLibState::endRegisterRenderTarget();
}

void DrPixlMan::selectGBuffRenderTarget() { selectGBuffRenderTarget(0xff); }

bool DrPixlMan::selectGBuffRenderTarget(u32 mask) {
  if (m_renderTarget == 2 && m_gbuffMask == mask) {
    return false;
  }
  m_renderTarget = 2;
  m_gbuffMask = mask;
  grlib::CGLibState::beginRegisterRenderTarget();
  int mrt = 0;
  for (int i = 0; i < 11; i++) {
    if (mask & (1 << i)) {
      grlib::CGLibState::setRegisterRenderTarget(*getPixlObj(s_gbuffPixlObjs[i]), static_cast<grlib::GrlMrtType>(mrt));
      mrt++;
    }
  }
  grlib::CGLibState::setRegisterDepthTarget(*getDepthObj()->m_depthBuffer);
  grlib::CGLibState::endRegisterRenderTarget();
  return true;
}

void DrPixlMan::refractionGBuffInvalidate() {
  m_res->pixlObjs[0][0]->setColorInvalidate();
  m_res->pixlObjs[1][0]->setColorInvalidate();
  m_res->pixlObjs[2][0]->setColorInvalidate();
  m_res->pixlObjs[3][0]->setColorInvalidate();
  m_res->pixlObjs[4][0]->setColorInvalidate();
}

void DrPixlMan::endGBuffRenderTarget() {
  m_res->pixlObjs[0][0]->setColorInvalidate();
  m_res->pixlObjs[1][0]->setColorInvalidate();
  m_res->pixlObjs[2][0]->setColorInvalidate();
  m_res->pixlObjs[3][0]->setColorInvalidate();
  m_res->pixlObjs[4][0]->setColorInvalidate();
  m_res->pixlObjs[8][0]->setColorInvalidate();
  m_res->pixlObjs[5][0]->setColorInvalidate();
  m_res->pixlObjs[6][0]->setColorInvalidate();
}

void DrPixlMan::selectDeferredRenderTarget() {
  if (m_renderTarget == 4) {
    return;
  }
  m_renderTarget = 4;
  grlib::CGLibState::beginRegisterRenderTarget();
  grlib::CGLibState::setRegisterRenderTarget(*getPixlObj(5), grlib::GRL_MRT_TYPE_0);
  grlib::CGLibState::setRegisterDepthTarget(*getDepthObj()->m_depthBuffer);
  grlib::CGLibState::endRegisterRenderTarget();
}

void DrPixlMan::selectRefractRenderTarget() {
  m_renderTarget = 5;
  grlib::CGLibState::beginRegisterRenderTarget();
  grlib::CGLibState::setRegisterDepthTarget(*getDepthObj()->m_depthBuffer);
  grlib::CGLibState::endRegisterRenderTarget();
}

void DrPixlMan::selectPrePassWrkClearRenderTarget() {
  m_renderTarget = 0;
  grlib::CGLibState::beginRegisterRenderTarget();
  grlib::CGLibState::setRegisterRenderTarget(*getPixlObj(5), grlib::GRL_MRT_TYPE_0);
  grlib::CGLibState::setRegisterDepthTarget(*getDepthObj()->m_depthBuffer);
  grlib::CGLibState::endRegisterRenderTarget();
  setMainViewPort();
}

void DrPixlMan::selectGlobalIBLIndexRenderTarget() {
  if (m_renderTarget == 11) {
    return;
  }
  m_renderTarget = 11;
  grlib::CGLibState::beginRegisterRenderTarget();
  grlib::CGLibState::setRegisterRenderTarget(*getPixlObj(3), grlib::GRL_MRT_TYPE_0);
  grlib::CGLibState::setRegisterDepthTarget(*getDepthObj()->m_depthBuffer);
  grlib::CGLibState::endRegisterRenderTarget();
}

void DrPixlMan::endGlobalIBLIndexRenderTarget() { m_res->pixlObjs[3][0]->setColorInvalidate(); }

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

void DrPixlMan::renderRefractionMap(bool isRefractionMap, bool isHalfMap) { m_res->postMan->renderRefractionMap(isRefractionMap, isHalfMap); }

void DrPixlMan::renderSkyDome() { m_res->postMan->renderSkyDome(); }

void DrPixlMan::renderSkyGodRay() { m_res->postMan->renderSkyGodRay(); }

void DrPixlMan::renderRainDrop() { m_res->postMan->renderRainDrop(); }

void DrPixlMan::renderTMAA() { m_res->postMan->renderTMAA(); }

bool DrPixlMan::isRefractionMap() { return m_res->postMan->m_refractionMap != nullptr; }

void DrPixlMan::thicknessFirstBegin() {
  m_renderTarget = 13;
  grlib::CGLibState::beginRegisterRenderTarget();
  grlib::CGLibState::setRegisterRenderTarget(*m_res->backFaceDepthTexture, grlib::GRL_MRT_TYPE_0);
  grlib::CGLibState::setRegisterDepthTarget(*getDepthObj()->m_depthBuffer);
  grlib::CGLibState::endRegisterRenderTarget();
}

DrPixlRenderTarget *DrPixlMan::getBackFaceDepthTexture() { return m_res->backFaceDepthTexture; }

void DrPixlMan::thicknessFirstEnd() { m_res->backFaceDepthTexture->setColorInvalidate(); }

void DrPixlMan::lastDeferredRender() { m_res->deferred->lastDeferredRender(); }

void DrPixlMan::occRenderEnd() { DrAPGxType::endOccQuery(); }

void DrPixlMan::depCheckEnd() { grlib::CGLibColorCtl::setColorBufferOn(); }

void DrPixlMan::shadowCallDirBegin() {
  m_drMan->apCache->shadowBegin();
  DrAPGxType::beginShadow();
}

void DrPixlMan::shadowCallDirEnd() {
  DrAPGxType::endShadow();
  resetRenderTarget();
  selectGBuffRenderTarget();
  setMainViewPort();
}

void DrPixlMan::shadowDirBegin() {
  m_drMan->apCache->shadowBegin();
  DrAPGxType::beginShadow();
}

void DrPixlMan::shadowDirEnd() {
  DrAPGxType::endShadow();
  resetRenderTarget();
  selectGBuffRenderTarget();
  setMainViewPort();
}

void DrPixlMan::callShadowCacheUpdate(bool isAll) { m_shadowCacheMan->callShadowCacheUpdate(isAll); }

void DrPixlMan::callShadowCacheVariance() { m_shadowCacheMan->callShadowCacheVariance(); }

void DrPixlMan::callFgShadowCacheUpdate() { m_shadowCacheMan->callFgShadowCacheUpdate(); }

void DrPixlMan::fastRender() {
  m_res->postMan->fastRender();
  if (m_cate == 0) {
    m_shadowCacheMan->shadowCacheRender();
    m_shadowCacheMan->fastRender();
  }
}

void DrPixlMan::lastCapRender() { m_res->postMan->capRender(); }

void DrPixlMan::setFinalViewPort() {
  grlib::LibMainStateViewPort viewPort(
      0.0f, 0.0f, static_cast<f32>(m_drMan->screenInfo->renderWidth), static_cast<f32>(m_drMan->screenInfo->renderHeight), 0.0f, 1.0f);
  grlib::CGLibState::setViewport(viewPort);
}

void DrPixlMan::setMainSRGBRenderTarget() { grlib::CGLibState::setMainFrameBuffer(); }

void DrPixlMan::setMainSRGBAfterRenderTarget() {}

void DrPixlMan::changeColorBuff() {
  m_res->activeColorBuff->setColorInvalidate();
  if (m_res->activeColorBuff == m_res->colorBuff) {
    m_res->activeColorBuff = m_res->hdrBuff;
  }
}

void DrPixlMan::changeHDRBuff(DrPixlRenderTarget *hdrBuff) {
  if (m_res->activeColorBuff == m_res->hdrBuff) {
    m_res->activeColorBuff = hdrBuff;
  }
  m_res->hdrBuff = hdrBuff;
}

void DrPixlMan::setTempColorBuff() { getTempColorBuff()->setRenderTarget(); }

DrPixlRenderTarget *DrPixlMan::getTempColorBuff() {
  if (m_res->activeColorBuff != m_res->colorBuff) {
    return m_res->colorBuff;
  }
  return m_res->hdrBuff;
}

void DrPixlMan::pixelEndMode() { m_shadowCacheMan->endMode(); }

void DrPixlMan::setToneAveRange(f32 min, f32 max) {
  m_res->toneAveMin = min;
  m_res->toneAveMax = max;
}

grlib::CGLibTextureBuffer *DrPixlMan::getDammyTexObj() { return m_dammyTex->m_texture; }

void DrPixlMan::offScreenAlphaEnd() { DrAPGxType::setupAlphaChanel(true); }

void DrPixlMan::debugDeferredRenderAlbedoAndFogRatio(int x, int y, int width, int height) {}

DrPixlRenderTarget *DrPixlMan::getDeactivePixlObj(int type) {
  if (!isDblPixlObj(type)) {
    return nullptr;
  }
  return m_res->pixlObjs[type][DrMan::s_nDblIdx ^ 1];
}

grlib::CGLibDepthTarget *DrPixlMan::getDeactiveDepthObj() { return m_res->depthObjs[DrMan::s_nDblStockIdx]; }

void DrPixlMan::swapPixlObj(int type) {
  if (isDblPixlObj(type)) {
    DrPixlRenderTarget *deactive = m_res->pixlObjs[type][DrMan::s_nDblIdx ^ 1];
    m_res->pixlObjs[type][DrMan::s_nDblIdx ^ 1] = m_res->pixlObjs[type][DrMan::s_nDblIdx];
    m_res->pixlObjs[type][DrMan::s_nDblIdx] = deactive;
  }
}

DrPixlRenderTarget *DrPixlMan::getBackFaceDepthTexture() const { return m_res->backFaceDepthTexture; }

} // namespace ml
