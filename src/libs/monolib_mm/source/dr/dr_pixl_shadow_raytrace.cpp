#include "dr/dr_pixl_shadow_raytrace.h"

#include "dr/dr_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_pixl_render_target.h"
#include "grlib/cglib_ctl_shader.h"
#include "grlib/cglib_render_target.h"
#include "mm_math/mm_col4.h"
#include "mm_mtl/fixed_array.h"
#include "mtl/alloc_handle.h"

namespace ml {

DrPixlShadowRaytrace::DrPixlShadowRaytrace(DrMan *man) : unknown00(man), unknown10(true) {
  unknown18 = new (unknown00->unknown0c) DrPixlRenderTarget(unknown00);
  for (int i = 0; i < 2; i++) {
    unknown20[i] = new (unknown00->unknown0c) DrPixlRenderTarget(unknown00);
  }
  unknown30 = new (unknown00->unknown0c) DrPixlRenderTarget(unknown00);
  unknown38 = new (unknown00->unknown0c) DrPixlRenderTarget(unknown00);
}

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

void DrPixlShadowRaytrace::debugRender() {
  int width = unknown00->unknown5b8->unknown28;
  int height = unknown00->unknown5b8->unknown2c;
  DrPixlRenderTarget *target = nullptr;
  switch (unknown00->unknown120[unknown00->unknown1c98]->unknown1008) {
  case 2:
    target = unknown18;
    break;
  case 3:
    target = unknown38;
    break;
  case 4:
    target = unknown20[DrMan::s_nDblIdx];
    break;
  }
  if (target != nullptr) {
    target->debugRender(0, 0, width, height, false, false, 1.0f, true);
  }
  if (unknown00->unknown120[unknown00->unknown1c98]->unknown1008 == 1) {
    int halfWidth = unknown00->unknown5b8->unknown28 / 2;
    int halfHeight = unknown00->unknown5b8->unknown2c / 2;
    unknown18->debugRender(0, 0, halfWidth, halfHeight, false, false, 1.0f, true);
    unknown38->debugRender(halfWidth + 1, 0, halfWidth, halfHeight, false, false, 1.0f, true);
    // Decision 2026-11-14 #17 (P2): the local places the `add w2, w21, #1` before the load of the target in the tail call
    // (0x71008c6ea4-0x71008c6ecc); the plain call, `1 + halfHeight`, a target local or an early return give the load first (96 instructions, one swap).
    int y = halfHeight + 1;
    unknown20[DrMan::s_nDblIdx]->debugRender(0, y, halfWidth, halfHeight, false, false, 1.0f, true);
  }
}

} // namespace ml
