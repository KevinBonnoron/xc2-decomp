#include "dr/dr_pixl_shadow_raytrace.h"

#include <math.h>

#include "dr/dr_ap_cache.h"
#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_post_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_pixl_render_target.h"
#include "dr/dr_shd_data_list.h"
#include "dr/dr_shd_data_obj.h"
#include "dr/dr_shd_man.h"
#include "grlib/cglib_color_ctl.h"
#include "grlib/cglib_ctl_shader.h"
#include "grlib/cglib_render_target.h"
#include "grlib/cglib_shader.h"
#include "grlib/cglib_uni_base_utility.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_vec4.h"
#include "mm_mtl/fixed_array.h"
#include "mtl/alloc_handle.h"

namespace ml {
// Inferred role: first call flag of temporalFiltering, its only user (0x71008c6420): EXEC_CLEAR is declared 1 until it is set, 2 after;
// file static at 0x7101bd7464, no game symbol; original name unknown.
static bool unknown001;

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

void DrPixlShadowRaytrace::temporalFiltering() {
  DrPixlPostParm *postParm = unknown00->unknown120[unknown00->unknown1c98];
  DrPixlRenderTarget *target = unknown20[DrMan::s_nDblIdx];
  grlib::CGLibColorCtl::setBlendOffControl(GRL_LOGIC_TYPE_COPY);
  DrShdDataList *shdList = unknown00->unknown80->unknown00;
  DrShdDataObj *shader = shdList->getShadowShdObj(5);
  // Decision 2026-11-13 (ruling 1): the local places the `cinc` before the getDeclarationOfs call, as the game does (the ternary in the argument
  // gives 314 instructions). The game reloads the flag after the call and stores it only when clear (0x71008c64c4-0x71008c64cc); a plain
  // `unknown001 = true;` gives 314 instructions.
  u32 execClear = unknown001 ? 2 : 1;
  shader->setDeclarationIdx(shader->getDeclarationOfs("EXEC_CLEAR"), execClear);
  if (!unknown001) {
    unknown001 = true;
  }
  shdList->bindTriangle();
  shader->setupShader(0u);
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  u32 fragCoordToUv = uniform.unknown001("gFragCoordToUV");
  u32 uvToScreen = uniform.unknown001("gUVToScreen");
  u32 screenToUv = uniform.unknown001("gScreenToUV");
  u32 screenToViewPos = uniform.unknown001("gScreenToViewPos");
  u32 invView = uniform.unknown001("gInvView");
  u32 prevView = uniform.unknown001("gPrevView");
  u32 proj = uniform.unknown001("gProj");
  u32 param = uniform.unknown001("gParam");
  int shadowLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTShadow");
  int depthLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTDepth");
  int prevShadowLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTPrevShadow");
  int prevDepthLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTPrevDepth");
  int velocityLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTVelocity");
  f32 width = static_cast<f32>(target->unknownbc);
  f32 height = static_cast<f32>(target->unknownc0);
  // The game loads the view work before the two divisions of fragCoord; declared after the first division the loads and stores of
  // fragCoord are scheduled differently (first difference at 0x71008c66bc) (ruling 2).
  DrCalcViewWork *viewWork = unknown00->unknown580->unknown10;
  mm::Vec4 fragCoord;
  fragCoord.x = 1.0f / width;
  fragCoord.y = 1.0f / height;
  fragCoord.z = 0.0f;
  fragCoord.w = 0.0f;
  uniform.setF32SetVec4(fragCoordToUv, &fragCoord.x);
  f32 uvScreen[4];
  uvScreen[0] = 2.0f;
  uvScreen[1] = 2.0f;
  uvScreen[2] = -1.0f;
  uvScreen[3] = -1.0f;
  uniform.setF32SetVec4(uvToScreen, uvScreen);
  f32 screenUv[4];
  screenUv[0] = 0.5f;
  screenUv[1] = 0.5f;
  screenUv[2] = 0.5f;
  screenUv[3] = 0.5f;
  uniform.setF32SetVec4(screenToUv, screenUv);
  f32 viewPos[4];
  viewPos[1] = tanf(viewWork->unknown4c4 * 0.5f);
  viewPos[0] = viewPos[1] * viewWork->unknown4c0;
  viewPos[2] = 0.0f;
  viewPos[3] = 0.0f;
  uniform.setF32SetVec4(screenToViewPos, viewPos);
  uniform.setMat44SetMat44(invView, viewWork->unknown00);
  uniform.setMat44SetMat44(prevView, viewWork->unknown280);
  uniform.setMat44SetMat44(proj, viewWork->unknown380);
  f32 paramValue[4];
  paramValue[0] = 0.7388f;
  paramValue[1] = 0.71f;
  paramValue[2] = 1.0f / postParm->unknown1010;
  paramValue[3] = 0.0f;
  uniform.setF32SetVec4(param, paramValue);
  DrPixlRenderTarget *shadow = unknown10 ? unknown38 : unknown18;
  // The game loads the post man chain (`ldr x9, [x8, #120]`) before the cache (`ldr x23, [x8, #1472]`); with the cache declared first
  // the two loads swap (ruling 2).
  DrPixlPostMan *postMan = unknown00->unknown78->unknown7f0->unknown180;
  DrAPCache *apCache = unknown00->unknown5c0;
  apCache->beginTexSampling(3, 0);
  apCache->beginBorderWhite();
  apCache->setTexture(*postMan->getDownDepth()->unknown70, depthLocation);
  apCache->setTexture(*postMan->getOldDownDepth()->unknown70, prevDepthLocation);
  apCache->beginTexSampling(2, 0);
  apCache->setTexture(*shadow->unknown70, shadowLocation);
  apCache->setTexture(*unknown20[DrMan::s_nDblStockIdx]->unknown70, prevShadowLocation);
  apCache->setTexture(*unknown00->unknown78->getPixlObj(3)->unknown70, velocityLocation);
  target->setRenderTarget();
  uniform.updateData();
  uniform.setUniformBlock();
  shdList->renderQuads();
  target->setColorInvalidate();
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
