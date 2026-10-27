#include "dr/dr_pixl_shadow_raytrace.h"

#include "dr/dr_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_pixl_render_target.h"
#include "grlib/cglib_ctl_shader.h"
#include "grlib/cglib_render_target.h"
#include "mm_math/mm_col4.h"

namespace ml {

DrPixlShadowRaytrace::~DrPixlShadowRaytrace() {
  if (unknown38 != nullptr) {
    delete unknown38;
    unknown38 = nullptr;
  }
  if (unknown30 != nullptr) {
    delete unknown30;
    unknown30 = nullptr;
  }
  if (unknown20[0] != nullptr) {
    delete unknown20[0];
    unknown20[0] = nullptr;
  }
  if (unknown20[1] != nullptr) {
    delete unknown20[1];
    unknown20[1] = nullptr;
  }
  if (unknown18 != nullptr) {
    delete unknown18;
    unknown18 = nullptr;
  }
}

void DrPixlShadowRaytrace::update() {}

void DrPixlShadowRaytrace::render_beforeTemporal() {
  DrPixlPostParm *postParm = unknown00->unknown120[unknown00->unknown1c98];
  raytracePass();
  if (unknown10) {
    blurPass();
  }
  if (!postParm->isShwRaytraceTemporalWithOthers()) {
    temporalFiltering();
  }
}

void DrPixlShadowRaytrace::blurPass() {
  unknown30->clearTexture(mm::Col4(0.0f, 0.0f, 0.0f, 0.0f), static_cast<GrlClaerMask>(0xf));
  unknown38->clearTexture(mm::Col4(0.0f, 0.0f, 0.0f, 0.0f), static_cast<GrlClaerMask>(0xf));
  grlib::CGLibCtlShader::setMemoryBarrierBit(2);
  blurPassSub(BLUR_AXIS_UNKNOWN_1, unknown18, unknown30);
  grlib::CGLibCtlShader::setMemoryBarrierBit(2);
  blurPassSub(BLUR_AXIS_UNKNOWN_2, unknown30, unknown38);
}

grlib::CGLibRenderTarget *DrPixlShadowRaytrace::getTemporalOutputTexture() { return unknown20[DrMan::s_nDblIdx]; }

grlib::CGLibRenderTarget *DrPixlShadowRaytrace::getTemporalHistoryTexture() { return unknown20[DrMan::s_nDblStockIdx]; }

grlib::CGLibTextureBuffer *DrPixlShadowRaytrace::getScreenSpaceShadow() const { return unknown20[DrMan::s_nDblIdx]->unknown70; }

void DrPixlShadowRaytrace::releaseColorBuff() {
  DrPixlPostParm *postParm = unknown00->unknown120[unknown00->unknown1c98];
  if (postParm->unknownfe4 == 3) {
    unknown20[0]->releaseTexture();
    unknown20[1]->releaseTexture();
  } else {
    unknown20[DrMan::s_nDblIdx]->releaseTexture();
  }
  if (postParm->unknownfe4 == 2) {
    return;
  }
  unknown18->releaseTexture();
  unknown30->releaseTexture();
  unknown38->releaseTexture();
}

} // namespace ml
