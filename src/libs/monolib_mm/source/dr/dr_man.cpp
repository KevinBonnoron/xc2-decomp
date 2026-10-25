#include "dr/dr_man.h"

#include <string.h>

#include "dr/dr_ap_cache.h"
#include "dr/dr_calc_gpu_cost.h"
#include "dr/dr_calc_man.h"
#include "dr/dr_calc_tex_stream_man.h"
#include "dr/dr_draw_callback.h"
#include "dr/dr_light_man.h"
#include "dr/dr_mdl_man.h"
#include "dr/dr_mdo_sml_shadow_man.h"
#include "dr/dr_mdo_zsort.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_mem_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_pixl_tile_parm.h"
#include "grlib/cglib_ctl_shader.h"
#include "grlib/cglib_debug.h"
#include "grlib/cglib_manager.h"

namespace ml {

DrMan *DrMan::getIns() { return s_pTop; }

DrMan *DrMan::get() { return s_pTop; }

int DrMan::loopCnt() { return 1; }

void DrMan::applyEnd(int loop) {}

void DrMan::setSRGBMode(bool isSRGBMode) { s_bSRGBMode = isSRGBMode; }

void DrMan::renderEnd(int loop) {
  unknown78->setMainRenderTarget();
  unknown180->end(DrPixlTileParm::TILE_TYPE_MAIN);
}

void DrMan::renderViewBegin() {
  unknown5c0->begin();
  unknown78->renderBegin(unknown1c98);
}

void DrMan::renderViewEnd() {
  unknown580->renderEnd();
  unknown78->renderEnd(unknown1c98);
}

void DrMan::setSkyGodRayRenderTarget() {
  unknown5c0->begin();
  unknown78->resetRenderTarget();
  unknown78->skyGodRayRenderTarget();
}

void DrMan::setAlphaRenderTarget() {
  unknown5c0->begin();
  unknown78->resetRenderTarget();
  unknown78->alphaRenderTarget();
}

void DrMan::blurCallBackRender() {
  for (int i = 0; i < unknown658; i++) {
    unknown5d8[i]->blurRender(&unknown660[unknown1c98]);
  }
}

void DrMan::applyViewBegin() {
  unknown5c0->begin();
  unknown78->updateShadowDisplayList();
}

void DrMan::renderBegin(int loop) { unknown180->begin(DrPixlTileParm::TILE_TYPE_MAIN); }

void DrMan::setMainRenderTarget() { unknown78->setMainRenderTarget(); }

bool DrMan::isIBLHalfRes() const { return true; }

void DrMdlMan::simpleShadowRender() { unknown030->shadowRender(); }

void DrMdlMan::lightPrePassRender() {
  if (unknown000->unknown1d64) {
    return;
  }
  if (unknown001()) {
    return;
  }
  unknown218->viewLightPrePassRender();
}

void DrMdlMan::alphaRender() {
  if (unknown000->unknown1d66) {
    return;
  }
  if (unknown001()) {
    return;
  }
  unknown218->viewAlphaRender();
}

void DrMdlMan::spAlphaRender() {
  if (unknown000->unknown1d67) {
    return;
  }
  if (unknown001()) {
    return;
  }
  unknown218->viewSpAlphaRender();
}

void DrMdlMan::GBuffRender() {
  if (unknown000->unknown1d64) {
    return;
  }
  if (unknown001()) {
    return;
  }
  grlib::CGLibCtlShader::setMemoryBarrierBit(2);
  unknown218->viewGBuffRender();
}

void DrMdlMan::setupRender() {
  if (unknown001()) {
    return;
  }
  unknown218->viewSetupRender();
}

void DrMdlMan::ZPrePassRender() {
  if (unknown001()) {
    return;
  }
  unknown218->viewZPrepassRender();
}

void DrMdlMan::ThicknessRenderFirst() {
  if (unknown001()) {
    return;
  }
  unknown218->viewThicknessRenderFirst();
}

void DrMdlMan::ThicknessRenderSecond() {
  if (unknown001()) {
    return;
  }
  unknown218->viewThicknessRenderSecond();
}

void DrMdlMan::refractionRender() {
  if (unknown000->unknown1d64 || unknown000->unknown1d65) {
    return;
  }
  if (unknown001()) {
    return;
  }
  unknown218->viewRefractionRender();
}

void DrMdlMan::renderBegin() {}

void DrMan::fastRender() { unknown78->fastRender(); }

void DrMan::setCallBack(IDrDrawCallback *callback) {
  if (unknown658 < 16) {
    unknown5d8[unknown658] = callback;
    unknown658++;
  }
}

void DrMan::releaseCallBack(IDrDrawCallback *callback) {
  for (int i = 0; i < unknown658; i++) {
    if (unknown5d8[i] == callback) {
      for (; i < unknown658 - 1; i++) {
        unknown5d8[i] = unknown5d8[i + 1];
      }
      unknown658--;
      unknown5d8[unknown658] = nullptr;
      return;
    }
  }
}

void DrMan::setCacherClearMode(bool cacherClearMode) {
  unknown5b0->unknown2068 = !cacherClearMode ? unknown5b0->unknown2068 & ~DrCalcTexStreamMan::FLAG_CACHER_CLEAR_MODE : unknown5b0->unknown2068 | DrCalcTexStreamMan::FLAG_CACHER_CLEAR_MODE;
}

void DrMan::openPixelDebugWindow(WinProc *window) {}

void DrMan::openHistgramDebugWindow(WinProc *window) {}

void DrMan::memcpyLcDMA(void *destination, const void *source, u32 size) { memcpy(destination, source, size); }

u32 DrMan::getMem1AlphaFree() { return DrPixlMemMan::get()->unknown434; }

void DrMan::setGblIdx(s32 id) {
  if (!(unknown1d20[id >> 5] & (1 << (id & 31)))) {
    unknown78->callShadowCacheVariance();
    unknown1d20[id >> 5] |= 1 << (id & 31);
  }
}

void DrMan::offGblIdx(s32 id) {
  if (unknown1d20[id >> 5] & (1 << (id & 31))) {
    unknown78->callShadowCacheVariance();
    unknown1d20[id >> 5] &= ~(1 << (id & 31));
  }
}

void DrMan::setTimeVal(f32 timeVal) {
  s32 index = s_nDblStockIdx;
  if (timeVal > 1.0f) {
    unknown1ca4[index] = 1.0f;
  } else if (timeVal < 0.0f) {
    unknown1ca4[index] = 0.0f;
  } else {
    unknown1ca4[index] = timeVal;
  }
}

void DrMan::setGroupsDisp(s32 group, bool disp) { unknown88->setGroupsDisp(group, disp); }

void DrMdlMan::setGroupsDisp(s32 group, bool disp) {
  if (disp) {
    unknown23c |= 1 << group;
  } else {
    unknown23c &= ~(1 << group);
  }
}

void DrMan::setReduction(bool isReduction, f32 scaleX, f32 scaleY) {
  DrPixlPostParm *postParm = unknown120[0];
  postParm->unknownfb2 = isReduction;
  postParm->unknownfb8 = scaleX;
  postParm->unknownfbc = scaleY;
}

void DrMan::setAutoReduction(bool autoReduction) { unknown5c8->m_autoReduction = autoReduction; }

void DrMan::setAA(bool isAA) { unknown120[0]->m_AAOn = isAA; }

void DrMan::setColorFilter(bool isColorFilter) { unknown120[0]->m_colTblOn = isColorFilter; }

void DrMan::setSSAO(bool isSSAO) { unknown120[0]->unknown194 = isSSAO; }

void DrMan::setBloom(bool isBloom, bool isLensFlare) { unknown120[0]->m_bloomOn = isBloom; }

void DrMan::setToneMap(bool isToneMap) { unknown120[0]->m_toneMapOn = isToneMap; }

void DrMan::setMotionBlur(bool isMotionBlur) { unknown120[0]->unknown1ca = isMotionBlur; }

void DrMan::setMotionBlur(f32 strength, f32 sub) {}

void DrMan::setDepthOfField(bool isDepthOfField) { unknown120[0]->setDOF(isDepthOfField); }

void DrMan::setDepthOfFieldParm(f32 distance, f32 range, f32 strength, f32 blend) {
  DrPixlPostParm *postParm = unknown120[0];
  postParm->setDoFDistance(distance);
  postParm->setDoFRange(range);
  postParm->setDoFPixlRatio(strength);
  postParm->setDoFLens(blend);
}

void DrMan::setGlobalWind(const mm::Vec3 &globalWind) { unknown1d30[s_nDblStockIdx] = globalWind; }

const mm::Vec3 &DrMan::getGlobalWind() const { return unknown1d30[s_nDblNowIdx]; }

void DrMan::callCubeMapRender(const DR_CAPCUBE_PARAM &param) {}

bool DrMan::isSRGBMode() { return s_bSRGBMode; }

bool DrMan::isFogSRGB() { return s_bFogSRGB; }

bool DrMan::isSeamDebug() { return s_bSeamDebug; }

void DrMan::beginMetric(const char *name) { grlib::CGLibDebug::setPushDebugGroup(name); }

void DrMan::endMetric(const char *name) { grlib::CGLibDebug::setPopDebugGroup(); }

void DrMan::releaseFastLight(s32 index) {
  if (unknownc0[index] != nullptr) {
    unknownc0[index]->releaseFastLight();
  }
}

void DrMan::setAllMiddelTexStmChk(bool isCheck) { unknown1d9c[s_nDblIdx] |= isCheck; }

bool DrMan::isAllMiddelTexStmChk() const { return unknown1d9c[s_nDblStockIdx]; }

void DrMan::setSeamMapStmOk(bool isOk) { unknown1d9e[s_nDblIdx] = isOk; }

bool DrMan::isSeamMapStmOk() const { return unknown1d9e[s_nDblStockIdx]; }

void DrMan::setAvatarCapMode(s32 avatarCapMode) {}

void DrMan::setDblNowIdx(int index) {
  s_nDblNowIdx = index;
  grlib::CGLibManager::s_nDblNowIdx = index;
}

void DrMan::bkgHomeMenu(bool isOpen) {
  if (isOpen) {
    unknown1cc0 = true;
  }
}

} // namespace ml
