#include "dr/dr_pixl_deferred.h"

#include "dr/dr_ap_gx_type.h"
#include "dr/dr_light_man.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_pixl_render_target.h"
#include "dr/dr_shd_lgt_global_ibl.h"
#include "dr/dr_shd_lgt_man.h"
#include "dr/dr_shd_man.h"
#include "grlib/cglib_color_ctl.h"
#include "grlib/cglib_depth_target.h"
#include "grlib/cglib_render_target.h"
#include "grlib/cglib_state.h"
#include "mm_math/mm_col4.h"

namespace ml {

void DrPixlDeferred::globalIBLRender() {
  DrShdLgtMan *lgtMan = unknown08->unknown80->unknown18;
  lgtMan->unknown58->render(lgtMan);
}

void DrPixlDeferred::shadowBuffBegin() { DrAPGxType::setupStencilTest(false, false, 7, false, 0, 0, 2, 0, 0, 0); }

void DrPixlDeferred::shadowBuffClear() { unknown20->clearTexture(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f), static_cast<GrlClaerMask>(0xf)); }

grlib::CGLibTextureBuffer *DrPixlDeferred::getShadowMapTexture() const {
  if (unknown08->unknown1d7a || !unknown08->unknown588->unknown1b9 || unknown08->unknown588->unknown160 <= 0.0f) {
    return unknown08->unknown78->unknown838->unknown70;
  }
  const DrPixlPostParm *parm = unknown08->unknown120[unknown08->unknown1c98];
  if (parm->unknown103c && parm->unknown103d) {
    return getTemporalOutputShadowMap()->unknown70;
  }
  return unknown20->unknown70;
}

DrPixlRenderTarget *DrPixlDeferred::getTemporalInputShadowMap() { return unknown20; }

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
  if (postParm->unknownfe4 == 3) {
    unknown28[0]->releaseTexture();
    unknown28[1]->releaseTexture();
  } else {
    unknown28[DrMan::s_nDblIdx]->releaseTexture();
  }
  if (postParm->unknownfe4 == 2) {
    return;
  }
  unknown20->releaseTexture();
}

} // namespace ml
