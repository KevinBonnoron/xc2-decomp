#include "dr/dr_pixl_deferred.h"

#include "dr/dr_ap_gx_type.h"
#include "dr/dr_light_man.h"
#include "dr/dr_man.h"
#include "dr/dr_mdl_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_pixl_render_target.h"
#include "dr/dr_pixl_shadow_man.h"
#include "dr/dr_pixl_shadow_obj.h"
#include "dr/dr_shd_lgt_global_ibl.h"
#include "dr/dr_shd_lgt_man.h"
#include "dr/dr_shd_man.h"
#include "grlib/cglib_color_ctl.h"
#include "grlib/cglib_depth_target.h"
#include "grlib/cglib_render_target.h"
#include "grlib/cglib_state.h"
#include "mm_math/mm_col4.h"
#include "mm_mtl/fixed_array.h"

namespace ml {

// Inferred role: deletes an object and clears the pointer; original name unknown.
template <typename T> inline void unknown001(T *&object) {
  T *deleted = object;
  if (deleted != nullptr) {
    delete deleted;
    object = nullptr;
  }
}

DrPixlDeferred::~DrPixlDeferred() {
  unknown001(m_temporalInputShadowMap);
  unknown001(unknown28[0]);
  unknown001(unknown28[1]);
}

void DrPixlDeferred::shadowCharacterRender() {
  DrPixlShadowMan *shadowMan = unknown18->unknown7f0->unknown178;
  DrMdlMan *mdlMan = shadowMan->unknown8908->unknown88;
  for (int i = 0; i < shadowMan->unknown8900; i++) {
    if (shadowMan->unknown0000[i]->dispChk() && shadowMan->unknown0000[i]->unknown4c == 0) {
      mdlMan->shadowRender(shadowMan->unknown0000[i]);
    }
  }
}

void DrPixlDeferred::shadowLightRender() {
  if (unknown08->unknown1d7a || unknown08->unknown588->unknown160 <= 0.0f) {
    return;
  }
  DrPixlShadowMan *shadowMan = unknown18->unknown7f0->unknown178;
  DrMdlMan *mdlMan = shadowMan->unknown8908->unknown88;
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

void DrPixlDeferred::globalIBLRender() {
  DrShdLgtMan *lgtMan = unknown08->unknown80->unknown18;
  lgtMan->unknown58->render(lgtMan);
}

void DrPixlDeferred::shadowBuffBegin() { DrAPGxType::setupStencilTest(false, false, 7, false, 0, 0, 2, 0, 0, 0); }

void DrPixlDeferred::shadowBuffClear() { m_temporalInputShadowMap->clearTexture(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f), static_cast<GrlClaerMask>(0xf)); }

grlib::CGLibTextureBuffer *DrPixlDeferred::getShadowMapTexture() const {
  if (unknown08->unknown1d7a || !unknown08->unknown588->unknown1b9 || unknown08->unknown588->unknown160 <= 0.0f) {
    return unknown08->unknown78->unknown838->unknown70;
  }
  const DrPixlPostParm *parm = unknown08->unknown120[unknown08->unknown1c98];
  if (parm->unknown103c && parm->unknown103d) {
    return getTemporalOutputShadowMap()->unknown70;
  }
  return m_temporalInputShadowMap->unknown70;
}

DrPixlRenderTarget *DrPixlDeferred::getTemporalInputShadowMap() { return m_temporalInputShadowMap; }

DrPixlRenderTarget *DrPixlDeferred::getTemporalOutputShadowMap() { return unknown28[DrMan::s_nDblIdx]; }

DrPixlRenderTarget *DrPixlDeferred::getTemporalOutputShadowMap() const { return unknown28[DrMan::s_nDblIdx]; }

DrPixlRenderTarget *DrPixlDeferred::getTemporalHistoryShadowMap() { return unknown28[DrMan::s_nDblStockIdx]; }

void DrPixlDeferred::lgtCalcRender() {
  DrPixlMan *pixlMan = unknown18;
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
  pixlMan = unknown18;
  grlib::CGLibState::beginRegisterRenderTarget();
  grlib::CGLibState::setRegisterRenderTarget(*pixlMan->unknown7f0->unknown00[5][0], grlib::GRL_MRT_TYPE_0);
  grlib::CGLibState::setRegisterDepthTarget(*pixlMan->unknown7f0->unknown1a0[DrMan::s_nDblIdx]->unknown120);
  grlib::CGLibState::endRegisterRenderTarget();
}

void DrPixlDeferred::releaseColorBuff() {
  DrPixlPostParm *postParm = unknown08->unknown120[unknown08->unknown1c98];
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
