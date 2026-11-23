#include "dr/dr_pixl_deferred.h"

#include "dr/dr_ap_gx_type.h"
#include "dr/dr_light_man.h"
#include "dr/dr_man.h"
#include "dr/dr_mdl_man.h"
#include "dr/dr_pixl_format.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_mem_man.h"
#include "dr/dr_pixl_post_man.h"
#include "dr/dr_pixl_post_obj_histgram.h"
#include "dr/dr_pixl_post_obj_tone_map.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_pixl_render_target.h"
#include "dr/dr_pixl_shadow_cache_man.h"
#include "dr/dr_pixl_shadow_man.h"
#include "dr/dr_pixl_shadow_obj.h"
#include "dr/dr_shd_lgt_clustered.h"
#include "dr/dr_shd_lgt_global_ibl.h"
#include "dr/dr_shd_lgt_hybrid.h"
#include "dr/dr_shd_lgt_man.h"
#include "dr/dr_shd_man.h"
#include "grlib/cglib_color_ctl.h"
#include "grlib/cglib_depth_target.h"
#include "grlib/cglib_render_target.h"
#include "grlib/cglib_state.h"
#include "mm_math/mm_col4.h"
#include "mm_mtl/fixed_array.h"
#include "mtl/alloc_handle.h"

namespace ml {

// Inferred role: deletes an object and clears the pointer; original name unknown.
template <typename T> inline void unknown001(T *&object) {
  T *deleted = object;
  if (deleted != nullptr) {
    delete deleted;
    object = nullptr;
  }
}

DrPixlDeferred::DrPixlDeferred(DrMan *man, DrPixlMan *pixlMan) : unknown00(nullptr), m_drMan(man), m_drPixlMan(pixlMan), m_temporalInputShadowMap(nullptr) {
  m_drShdMan = man->m_drShdMan;
  m_temporalInputShadowMap = new (man->unknown0c) DrPixlRenderTarget(m_drMan);
  m_temporalInputShadowMap->setTextureInfo(1.0f, 1.0f, DrPixlFormat::s_DirShadowFormat, true, (DrPixlMemMan::get()->unknown010 + DrMan::getIns()->unknown1c98)->unknown0e8[0]);
  for (int i = 0; i < 2; i++) {
    unknown28[i] = new (m_drMan->unknown0c) DrPixlRenderTarget(m_drMan);
  }
  unknown38 = 1;
  unknown3a = 1;
}

DrPixlDeferred::~DrPixlDeferred() {
  unknown001(m_temporalInputShadowMap);
  unknown001(unknown28[0]);
  unknown001(unknown28[1]);
}

void DrPixlDeferred::shadowCharacterRender() {
  DrPixlShadowMan *shadowMan = m_drPixlMan->unknown7f0->m_drPixlShadowMan;
  DrMdlMan *mdlMan = shadowMan->m_drMan->m_drMdlMan;
  for (int i = 0; i < shadowMan->unknown8900; i++) {
    if (shadowMan->unknown0000[i]->dispChk() && shadowMan->unknown0000[i]->unknown4c == 0) {
      mdlMan->shadowRender(shadowMan->unknown0000[i]);
    }
  }
}

void DrPixlDeferred::displayUpdate() {
  DrPixlPostParm *postParm = m_drMan->unknown120[m_drMan->unknown1c98];
  s32 width;
  s32 height;
  if (!postParm->unknown103c) {
    width = m_drMan->unknown5b8->unknown18;
    height = m_drMan->unknown5b8->unknown1c;
  } else {
    m_drPixlMan->unknown7f0->m_drPixlPostMan->unknownf8 |= DrPixlPostMan::FLAG_UNKNOWN_19;
    width = static_cast<s32>(postParm->unknown1048 * static_cast<f32>(m_drMan->unknown5b8->unknown18));
    height = static_cast<s32>(postParm->unknown1048 * static_cast<f32>(m_drMan->unknown5b8->unknown1c));
  }
  if ((unknown38 != 0 || unknown3a != 0) && (width != unknown38 || height != unknown3a)) {
    m_temporalInputShadowMap->setTextureInfo(
        static_cast<f32>(width), static_cast<f32>(height), DrPixlFormat::s_DirShadowFormat, true, (DrPixlMemMan::get()->unknown010 + DrMan::getIns()->unknown1c98)->unknown0e8[0]);
    if (m_drMan->unknown120[m_drMan->unknown1c98]->unknown103c) {
      unknown28[0]->setTextureInfo(
          static_cast<f32>(width), static_cast<f32>(height), DrPixlFormat::s_DirShadowFormat, true, (DrPixlMemMan::get()->unknown010 + DrMan::getIns()->unknown1c98)->unknown0e8[1]);
      unknown28[1]->setTextureInfo(
          static_cast<f32>(width), static_cast<f32>(height), DrPixlFormat::s_DirShadowFormat, true, (DrPixlMemMan::get()->unknown010 + DrMan::getIns()->unknown1c98)->unknown0e8[2]);
    }
    unknown38 = static_cast<s16>(width);
    unknown3a = static_cast<s16>(height);
  }
}

void DrPixlDeferred::fastDeferredRender(int cate) {
  DrLightMan *lightMan = m_drMan->unknown588;
  DrShdLgtMan *shdLgtMan = m_drMan->m_drShdMan->m_drShdLgtMan;
  shdLgtMan->renderBegin();
  // Ruling 8: the tail (setupBlend, setMainViewPort, resetRenderTarget) is written in both paths (function at 0x710083967c). With one shared tail after the if, GVN partial redundancy
  // elimination turns `this + 24` into a phi (an extra add and branch: 106 instructions measured again, the game has 104); two tails are merged later.
  if (m_drMan->unknown1d6e) {
    DrAPGxType::setupBlend(0);
    m_drPixlMan->setMainViewPort();
    m_drPixlMan->resetRenderTarget();
    return;
  }
  shadowLightRender();
  if (!m_drMan->unknown1d78) {
    shdLgtMan->m_drShdLgtClustered->render(shdLgtMan, lightMan);
  }
  shdLgtMan->setupLgtBuff();
  shdLgtMan->m_hybridLight->render(shdLgtMan, lightMan);
  m_drPixlMan->endDeferredRenderTarget();
  DrAPGxType::setupBlend(0);
  m_drPixlMan->setMainViewPort();
  m_drPixlMan->resetRenderTarget();
}

void DrPixlDeferred::shadowLightRender() {
  if (m_drMan->unknown1d7a || m_drMan->unknown588->unknown160 <= 0.0f) {
    return;
  }
  DrPixlShadowMan *shadowMan = m_drPixlMan->unknown7f0->m_drPixlShadowMan;
  DrMdlMan *mdlMan = shadowMan->m_drMan->m_drMdlMan;
  for (int i = 0; i < shadowMan->unknown8900; i++) {
    if (shadowMan->unknown0000[i]->dispChk() && shadowMan->unknown0000[i]->unknown4c != 0) {
      if (mdlMan->shadowRender(shadowMan->unknown0000[i])) {
        shadowMan->unknown0000[i]->renderLight();
      } else {
        shadowMan->unknown0000[i]->stockTile();
      }
    }
  }
}

bool DrPixlDeferred::shadowTexRender(int cate) {
  if (m_drMan->unknown1d7a || m_drMan->unknown588->unknown160 <= 0.0f || !m_drMan->unknown588->unknown1b9) {
    return false;
  }
  shadowCharacterRender();
  shadowBuffBegin();
  if (m_drPixlMan->m_drPixlShadowCacheMan->isShadowMap() && cate == 0) {
    shadowBuffCacheRender();
  } else if (!shadowBuffDefRender()) {
    m_temporalInputShadowMap->clearTexture(mm::Col4::white, static_cast<GrlClaerMask>(0xf));
  }
  m_temporalInputShadowMap->setColorInvalidate();
  return true;
}

void DrPixlDeferred::debugRender() {
  s32 width = static_cast<s32>(m_drMan->unknown5b8->unknown28 * 0.25f);
  s32 height = static_cast<s32>(m_drMan->unknown5b8->unknown2c * 0.25f);
  s32 y = height * 2;
  getTemporalInputShadowMap()->debugRender(0, y, width, height, false, false, 1.0f, true);
  const DrPixlPostParm *postParm = m_drMan->unknown120[m_drMan->unknown1c98];
  if (postParm->unknown103c && postParm->unknown103d) {
    s32 x = width + 1;
    getTemporalHistoryShadowMap()->debugRender(x, y, width, height, false, false, 1.0f, true);
    getTemporalOutputShadowMap()->debugRender(x * 2, y, width, height, false, false, 1.0f, true);
  }
}

void DrPixlDeferred::globalIBLRender() {
  DrShdLgtMan *lgtMan = m_drMan->m_drShdMan->m_drShdLgtMan;
  lgtMan->m_drShdLgtGlobalIBL->render(lgtMan);
}

void DrPixlDeferred::shadowBuffBegin() { DrAPGxType::setupStencilTest(false, false, 7, false, 0, 0, 2, 0, 0, 0); }

void DrPixlDeferred::shadowBuffClear() { m_temporalInputShadowMap->clearTexture(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f), static_cast<GrlClaerMask>(0xf)); }

grlib::CGLibTextureBuffer *DrPixlDeferred::getShadowMapTexture() const {
  if (m_drMan->unknown1d7a || !m_drMan->unknown588->unknown1b9 || m_drMan->unknown588->unknown160 <= 0.0f) {
    return m_drMan->m_drPixlMan->unknown838->unknown70;
  }
  const DrPixlPostParm *parm = m_drMan->unknown120[m_drMan->unknown1c98];
  if (parm->unknown103c && parm->unknown103d) {
    return getTemporalOutputShadowMap()->unknown70;
  }
  return m_temporalInputShadowMap->unknown70;
}

DrPixlRenderTarget *DrPixlDeferred::getTemporalInputShadowMap() { return m_temporalInputShadowMap; }

DrPixlRenderTarget *DrPixlDeferred::getTemporalOutputShadowMap() { return unknown28[DrMan::s_nDblIdx]; }

DrPixlRenderTarget *DrPixlDeferred::getTemporalOutputShadowMap() const { return unknown28[DrMan::s_nDblIdx]; }

DrPixlRenderTarget *DrPixlDeferred::getTemporalHistoryShadowMap() { return unknown28[DrMan::s_nDblStockIdx]; }

void DrPixlDeferred::lastDeferredRender() {
  lgtCalcRender();
  m_drPixlMan->endGBuffTexture();
  DrPixlPostMan *postMan = m_drPixlMan->unknown7f0->m_drPixlPostMan;
  if (postMan->m_drPixlPostObjToneMap != nullptr) {
    postMan->m_drPixlPostObjToneMap->fastRender();
  }
  if (postMan->m_drPixlPostObjHistgram != nullptr) {
    postMan->m_drPixlPostObjHistgram->render();
  }
  DrAPGxType::setupBlend(0);
  m_drPixlMan->setMainViewPort();
  m_drPixlMan->resetRenderTarget();
  if (m_drPixlMan->unknown7f0->unknown1d8 & 2) {
    DrAPGxType::setupScreenQuads(false);
    m_drPixlMan->setMainRenderTarget();
    m_drPixlMan->toneMapRender(false);
  }
}

void DrPixlDeferred::lgtCalcRender() {
  DrPixlMan *pixlMan = m_drPixlMan;
  pixlMan->unknown858 = 6;
  grlib::CGLibState::beginRegisterRenderTarget();
  grlib::CGLibState::setRegisterRenderTarget(*pixlMan->unknown7f0->unknown00[5][0], grlib::GRL_MRT_TYPE_0);
  grlib::CGLibState::setRegisterRenderTarget(*pixlMan->unknown7f0->unknown00[6][0], grlib::GRL_MRT_TYPE_1);
  DrPixlRenderTarget **row = pixlMan->unknown7f0->unknown00[9];
  grlib::CGLibState::setRegisterRenderTarget(*row[DrMan::s_nDblIdx], grlib::GRL_MRT_TYPE_2);
  grlib::CGLibState::setRegisterDepthTarget(*pixlMan->unknown7f0->unknown1a0[DrMan::s_nDblIdx]->unknown120);
  grlib::CGLibState::endRegisterRenderTarget();
  DrAPGxType::setupCullingOff();
  DrAPGxType::setupBlend(7);
  pixlMan = m_drPixlMan;
  grlib::CGLibState::beginRegisterRenderTarget();
  grlib::CGLibState::setRegisterRenderTarget(*pixlMan->unknown7f0->unknown00[5][0], grlib::GRL_MRT_TYPE_0);
  grlib::CGLibState::setRegisterDepthTarget(*pixlMan->unknown7f0->unknown1a0[DrMan::s_nDblIdx]->unknown120);
  grlib::CGLibState::endRegisterRenderTarget();
}

void DrPixlDeferred::releaseColorBuff() {
  DrPixlPostParm *postParm = m_drMan->unknown120[m_drMan->unknown1c98];
  unknown38 = 0;
  unknown3a = 0;
  if (postParm->unknownfe4 == 3) {
    unknown28[0]->releaseTexture();
    unknown28[1]->releaseTexture();
  } else {
    unknown28[DrMan::s_nDblIdx]->releaseTexture();
  }
  if (postParm->unknownfe4 == 2) {
    return;
  }
  m_temporalInputShadowMap->releaseTexture();
}

} // namespace ml
