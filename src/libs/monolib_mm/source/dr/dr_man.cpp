#include "dr/dr_man.h"

#include <string.h>

#include "dr/dr_ap_cache.h"
#include "dr/dr_calc_gpu_cost.h"
#include "dr/dr_calc_tex_stream_man.h"
#include "dr/dr_light_man.h"
#include "dr/dr_mdl_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_mem_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_pixl_tile_parm.h"
#include "grlib/cglib_debug.h"
#include "grlib/cglib_manager.h"

namespace ml {

DrMan *DrMan::getIns() { return s_pTop; }

DrMan *DrMan::get() { return s_pTop; }

int DrMan::loopCnt() { return 1; }

void DrMan::applyEnd(int loop) {}

void DrMan::applyViewBegin() {
  apCache->begin();
  pixlMan->updateShadowDisplayList();
}

void DrMan::renderBegin(int loop) { tileParm->begin(DrPixlTileParm::TILE_TYPE_MAIN); }

void DrMan::setMainRenderTarget() { pixlMan->setMainRenderTarget(); }

bool DrMan::isIBLHalfRes() const { return true; }

void DrMdlMan::renderBegin() {}

void DrMan::fastRender() { pixlMan->fastRender(); }

void DrMan::setCallBack(IDrDrawCallback *callback) {
  if (callbackNum < 16) {
    callbacks[callbackNum] = callback;
    callbackNum++;
  }
}

void DrMan::releaseCallBack(IDrDrawCallback *callback) {
  for (int i = 0; i < callbackNum; i++) {
    if (callbacks[i] == callback) {
      for (; i < callbackNum - 1; i++) {
        callbacks[i] = callbacks[i + 1];
      }
      callbackNum--;
      callbacks[callbackNum] = nullptr;
      return;
    }
  }
}

void DrMan::setCacherClearMode(bool cacherClearMode) {
  texStreamMan->m_flags = !cacherClearMode ? texStreamMan->m_flags & ~DrCalcTexStreamMan::FLAG_CACHER_CLEAR_MODE
                                           : texStreamMan->m_flags | DrCalcTexStreamMan::FLAG_CACHER_CLEAR_MODE;
}

void DrMan::openPixelDebugWindow(WinProc *window) {}

void DrMan::openHistgramDebugWindow(WinProc *window) {}

void DrMan::memcpyLcDMA(void *destination, const void *source, u32 size) { memcpy(destination, source, size); }

u32 DrMan::getMem1AlphaFree() { return DrPixlMemMan::get()->m_mem1AlphaFree; }

void DrMan::setGblIdx(s32 id) {
  if (!(gblTbl[id >> 5] & (1 << (id & 31)))) {
    pixlMan->callShadowCacheVariance();
    gblTbl[id >> 5] |= 1 << (id & 31);
  }
}

void DrMan::offGblIdx(s32 id) {
  if (gblTbl[id >> 5] & (1 << (id & 31))) {
    pixlMan->callShadowCacheVariance();
    gblTbl[id >> 5] &= ~(1 << (id & 31));
  }
}

void DrMan::setTimeVal(f32 timeVal) {
  s32 index = s_nDblStockIdx;
  if (timeVal > 1.0f) {
    timeVals[index] = 1.0f;
  } else if (timeVal < 0.0f) {
    timeVals[index] = 0.0f;
  } else {
    timeVals[index] = timeVal;
  }
}

void DrMan::setGroupsDisp(s32 group, bool disp) { mdlMan->setGroupsDisp(group, disp); }

void DrMdlMan::setGroupsDisp(s32 group, bool disp) {
  if (disp) {
    m_groupsDisp |= 1 << group;
  } else {
    m_groupsDisp &= ~(1 << group);
  }
}

void DrMan::setReduction(bool isReduction, f32 scaleX, f32 scaleY) {
  DrPixlPostParm *postParm = postParms[0];
  postParm->reduction = isReduction;
  postParm->reductionScX = scaleX;
  postParm->reductionScY = scaleY;
}

void DrMan::setAutoReduction(bool autoReduction) { gpuCost->m_autoReduction = autoReduction; }

void DrMan::setAA(bool isAA) { postParms[0]->aa = isAA; }

void DrMan::setColorFilter(bool isColorFilter) { postParms[0]->colorFilter = isColorFilter; }

void DrMan::setSSAO(bool isSSAO) { postParms[0]->ssao = isSSAO; }

void DrMan::setBloom(bool isBloom, bool isLensFlare) { postParms[0]->bloom = isBloom; }

void DrMan::setToneMap(bool isToneMap) { postParms[0]->toneMap = isToneMap; }

void DrMan::setMotionBlur(bool isMotionBlur) { postParms[0]->motBlur = isMotionBlur; }

void DrMan::setMotionBlur(f32 strength, f32 sub) {}

void DrMan::setDepthOfField(bool isDepthOfField) { postParms[0]->setDOF(isDepthOfField); }

void DrMan::setDepthOfFieldParm(f32 distance, f32 range, f32 strength, f32 blend) {
  DrPixlPostParm *postParm = postParms[0];
  postParm->setDoFDistance(distance);
  postParm->setDoFRange(range);
  postParm->setDoFPixlRatio(strength);
  postParm->setDoFLens(blend);
}

void DrMan::setGlobalWind(const mm::Vec3 &globalWind) { globalWinds[s_nDblStockIdx] = globalWind; }

const mm::Vec3 &DrMan::getGlobalWind() const { return globalWinds[s_nDblNowIdx]; }

void DrMan::callCubeMapRender(const DR_CAPCUBE_PARAM &param) {}

bool DrMan::isSRGBMode() { return s_bSRGBMode; }

bool DrMan::isFogSRGB() { return s_bFogSRGB; }

bool DrMan::isSeamDebug() { return s_bSeamDebug; }

void DrMan::beginMetric(const char *name) { grlib::CGLibDebug::setPushDebugGroup(name); }

void DrMan::endMetric(const char *name) { grlib::CGLibDebug::setPopDebugGroup(); }

void DrMan::releaseFastLight(s32 index) {
  if (lightMans[index] != nullptr) {
    lightMans[index]->releaseFastLight();
  }
}

void DrMan::setAllMiddelTexStmChk(bool isCheck) { allMiddelTexStmChks[s_nDblIdx] |= isCheck; }

bool DrMan::isAllMiddelTexStmChk() const { return allMiddelTexStmChks[s_nDblStockIdx]; }

void DrMan::setSeamMapStmOk(bool isOk) { seamMapStmOks[s_nDblIdx] = isOk; }

bool DrMan::isSeamMapStmOk() const { return seamMapStmOks[s_nDblStockIdx]; }

void DrMan::setAvatarCapMode(s32 avatarCapMode) {}

void DrMan::setDblNowIdx(int index) {
  s_nDblNowIdx = index;
  grlib::CGLibManager::s_nDblNowIdx = index;
}

void DrMan::bkgHomeMenu(bool isOpen) {
  if (isOpen) {
    homeMenuOpened = true;
  }
}

} // namespace ml
