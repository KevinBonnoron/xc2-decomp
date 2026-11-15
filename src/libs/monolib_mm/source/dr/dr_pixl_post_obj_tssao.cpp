#include "dr/dr_pixl_post_obj_tssao.h"

#include <math.h>

#include "dr/dr_ap_cache.h"
#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_post_man.h"
#include "dr/dr_pixl_post_obj.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_pixl_render_target.h"
#include "dr/dr_shd_data_list.h"
#include "dr/dr_shd_data_obj.h"
#include "dr/dr_shd_man.h"
#include "grlib/cglib_color_ctl.h"
#include "grlib/cglib_ctl_shader.h"
#include "grlib/cglib_shader.h"
#include "grlib/cglib_uni_base_utility.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_vec4.h"
#include "mm_mtl/fixed_array.h"

namespace ml {

DrPixlPostObjTSSAO::~DrPixlPostObjTSSAO() {
  if (unknown48 != nullptr) {
    delete unknown48;
    unknown48 = nullptr;
  }
  if (unknown68 != nullptr) {
    delete unknown68;
    unknown68 = nullptr;
  }
  if (unknown60 != nullptr) {
    delete unknown60;
    unknown60 = nullptr;
  }
  if (unknown40 != nullptr) {
    delete unknown40;
    unknown40 = nullptr;
  }
  if (unknown38 != nullptr) {
    delete unknown38;
    unknown38 = nullptr;
  }
  if (unknown28[0] != nullptr) {
    delete unknown28[0];
    unknown28[0] = nullptr;
  }
  if (unknown50[0] != nullptr) {
    delete unknown50[0];
    unknown50[0] = nullptr;
  }
  if (unknown28[1] != nullptr) {
    delete unknown28[1];
    unknown28[1] = nullptr;
  }
  if (unknown50[1] != nullptr) {
    delete unknown50[1];
    unknown50[1] = nullptr;
  }
  if (unknown20 != nullptr) {
    delete unknown20;
    unknown20 = nullptr;
  }
}

void DrPixlPostObjTSSAO::calcFragCoordToUV(mm::Vec4 &uv, f32 width, f32 height) {
  uv.x = 1.0f / width;
  uv.y = 1.0f / height;
  uv.z = static_cast<f32>(unknown70) / width;
  uv.w = static_cast<f32>(unknown70) / height;
}

void DrPixlPostObjTSSAO::calcFragCoordToScreen(mm::Vec4 &screen, f32 width, f32 height) {
  screen.x = 2.0f / width;
  screen.y = 2.0f / height;
  screen.z = (static_cast<f32>(unknown70) + static_cast<f32>(unknown70)) / width - 1.0f;
  screen.w = (static_cast<f32>(unknown70) + static_cast<f32>(unknown70)) / height - 1.0f;
}

void DrPixlPostObjTSSAO::render_beforeTemporal() {
  DrPixlPostParm *postParm = unknown00->unknown120[unknown00->unknown1c98];
  if (!postParm->unknown174) {
    return;
  }
  if (postParm->unknownfb1) {
    passQuaterNormal();
  }
  passSSAO();
  grlib::CGLibCtlShader::setMemoryBarrierBit(2);
  passPrevBlur();
  passTemporalFiltering();
}

void DrPixlPostObjTSSAO::passPrevBlur() {
  f32 strength = unknown00->unknown120[unknown00->unknown1c98]->unknownf94;
  passBlur_Sub(BLUR_AXIS_UNKNOWN_1, strength, unknown20, unknown38, false);
  grlib::CGLibCtlShader::setMemoryBarrierBit(2);
  passBlur_Sub(BLUR_AXIS_UNKNOWN_2, strength, unknown38, unknown20, false);
}

void DrPixlPostObjTSSAO::passTemporalFiltering() {
  DrCalcViewWork *viewWork = unknown00->unknown580->unknown10;
  DrPixlRenderTarget *target = unknown28[DrMan::s_nDblIdx];
  grlib::CGLibColorCtl::setBlendOffControl(GRL_LOGIC_TYPE_COPY);
  DrShdDataList *shdList = unknown00->unknown80->unknown00;
  DrShdDataObj *shader = shdList->getPostShdObj(0x2e);
  u32 execClear = 1;
  if (!viewWork->unknown9ac && !viewWork->unknown9a9) {
    execClear = 2;
  }
  shader->setDeclarationIdx(shader->getDeclarationOfs("EXEC_CLEAR"), execClear);
  shader->setDeclarationIdx(shader->getDeclarationOfs("SELECTIVE_FILTERING"), 2);
  shader->setDeclarationIdx(shader->getDeclarationOfs("DEB_OUTPUT"), 2);
  shdList->unknown002(shader);
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  u32 fragCoordToUv = uniform.unknown001("gFragCoordToUV");
  u32 uvToScreen = uniform.unknown001("gUVToScreen");
  u32 screenToUv = uniform.unknown001("gScreenToUV");
  u32 screenToViewPos = uniform.unknown001("gScreenToViewPos");
  u32 screenToGbUv = uniform.unknown001("gScreenToGBUV");
  u32 invView = uniform.unknown001("gInvView");
  u32 prevView = uniform.unknown001("gPrevView");
  u32 proj = uniform.unknown001("gProj");
  u32 param = uniform.unknown001("gParam");
  u32 projInv = uniform.unknown001("gProjInv");
  u32 toPrevScreen = uniform.unknown001("gToPrevScreen");
  int aoLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTAO");
  int depthLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTDepth");
  int prevAoLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTPrevAO");
  int prevDepthLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTPrevDepth");
  int velocityLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTVelocity");
  int similarityLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTSimilarity");
  int prevSimilarityLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTPrevSimilarity");
  f32 paddedWidth = static_cast<f32>(target->unknownbc) + (static_cast<f32>(unknown70) + static_cast<f32>(unknown70));
  f32 paddedHeight = static_cast<f32>(target->unknownc0) + (static_cast<f32>(unknown70) + static_cast<f32>(unknown70));
  mm::Vec4 fragCoordUv;
  calcFragCoordToUV(fragCoordUv, paddedWidth, paddedHeight);
  uniform.setF32SetVec4(fragCoordToUv, &fragCoordUv.x);
  f32 uvScreen[4];
  uvScreen[0] = 2.0f;
  uvScreen[1] = -2.0f;
  uvScreen[2] = -1.0f;
  uvScreen[3] = 1.0f;
  uniform.setF32SetVec4(uvToScreen, uvScreen);
  f32 screenUv[4];
  screenUv[0] = 0.5f;
  screenUv[1] = -0.5f;
  screenUv[2] = 0.5f;
  screenUv[3] = 0.5f;
  uniform.setF32SetVec4(screenToUv, screenUv);
  f32 viewPos[4];
  viewPos[1] = tanf(viewWork->unknown4c4 * 0.5f);
  viewPos[0] = viewPos[1] * viewWork->unknown4c0;
  viewPos[2] = 0.0f;
  viewPos[3] = 0.0f;
  uniform.setF32SetVec4(screenToViewPos, viewPos);
  f32 width = static_cast<f32>(target->unknownbc);
  f32 gbUv[4];
  gbUv[0] = 0.5f / ((width * 0.5f) / (paddedWidth * 0.5f));
  f32 height = static_cast<f32>(target->unknownc0);
  gbUv[1] = -0.5f / ((height * 0.5f) / (paddedHeight * 0.5f));
  gbUv[2] = 0.5f - 0.0f / width;
  gbUv[3] = 0.5f - 0.0f / height;
  uniform.setF32SetVec4(screenToGbUv, gbUv);
  uniform.setMat44SetMat44(invView, viewWork->unknown00);
  uniform.setMat44SetMat44(prevView, viewWork->unknown280);
  uniform.setMat44SetMat44(proj, viewWork->unknown380);
  uniform.setMat44SetMat44(projInv, viewWork->unknown3c0);
  f32 paramValue[4];
  paramValue[0] = static_cast<f32>(unknown10->unknowne8->unknownbc);
  paramValue[1] = static_cast<f32>(unknown10->unknowne8->unknownc0);
  paramValue[2] = 0.0f;
  paramValue[3] = 0.0f;
  uniform.setF32SetVec4(param, paramValue);
  // The game copies unknown00 into the variable (the alignment assert at 0x71008c2fc8 and the memcpy at 0x71008c2ff4 of Mat44's copy
  // constructor, after the gParam store at 0x71008c2fc0) and then stores the product into it; the product itself reads unknown00 directly.
  // Forms tried: `Mat44 matrix = a * b * c;` (no copy, 1050 instructions against 1062) and `matrix = matrix * b * c;` (1053 instructions).
  mm::Mat44 matrix = viewWork->unknown00;
  matrix = viewWork->unknown00 * viewWork->unknown280 * viewWork->unknown380;
  uniform.setMat44SetMat44(toPrevScreen, matrix);
  DrAPCache *apCache = unknown00->unknown5c0;
  apCache->beginTexSampling(2, 0);
  apCache->setTexture(*unknown10->getOldDownDepth()->unknown70, prevDepthLocation);
  apCache->beginTexSampling(2, 1);
  apCache->setTexture(*unknown20->unknown70, aoLocation);
  apCache->setTexture(*unknown28[DrMan::s_nDblStockIdx]->unknown70, prevAoLocation);
  apCache->beginBorderDepthMinusMax();
  apCache->setTexture(*unknown10->unknowne8->unknown70, depthLocation);
  apCache->beginTexSampling(2, 0);
  apCache->setTexture(*unknown08->getPixlObj(3)->unknown70, velocityLocation);
  apCache->beginBorderWhite();
  apCache->setTexture(*unknown48->unknown70, similarityLocation);
  apCache->setTexture(*unknown50[DrMan::s_nDblStockIdx]->unknown70, prevSimilarityLocation);
  target->setRenderTarget(*unknown50[DrMan::s_nDblIdx]);
  uniform.updateData();
  uniform.setUniformBlock();
  shdList->renderQuads();
  target->setColorInvalidate();
}

void DrPixlPostObjTSSAO::render_afterTemporal() {
  DrPixlPostParm *postParm = unknown00->unknown120[unknown00->unknown1c98];
  if (!postParm->unknown174) {
    return;
  }
  passPostBlur();
  passUpScaleToMiddle();
}

void DrPixlPostObjTSSAO::passPostBlur() {
  f32 strength = unknown00->unknown120[unknown00->unknown1c98]->unknown188;
  DrPixlRenderTarget *source = unknown28[DrMan::s_nDblIdx];
  f32 weight[4];
  for (s32 i = 0; i < 4; i++) {
    weight[i] = DrPixlPostObj::gaussianDistribution(static_cast<f32>(i), 0.0f, 1.0f);
  }
  passBlur_Sub(BLUR_AXIS_UNKNOWN_1, strength, source, unknown38, false);
  grlib::CGLibCtlShader::setMemoryBarrierBit(2);
  passBlur_Sub(BLUR_AXIS_UNKNOWN_2, strength, unknown38, source, false);
}

void DrPixlPostObjTSSAO::passUpScaling() { passUpScaleToMiddle(); }

void DrPixlPostObjTSSAO::update() { unknown10->setDownDepth(); }

void DrPixlPostObjTSSAO::releaseColorBuff() {
  DrPixlPostParm *postParm = unknown00->unknown120[unknown00->unknown1c98];
  if (postParm->unknownfe4 == 3) {
    unknown28[0]->releaseTexture();
    unknown50[0]->releaseTexture();
    unknown28[1]->releaseTexture();
    unknown50[1]->releaseTexture();
  } else {
    unknown28[DrMan::s_nDblIdx]->releaseTexture();
    unknown50[DrMan::s_nDblIdx]->releaseTexture();
    if (postParm->unknownfe4 == 2) {
      return;
    }
  }
  unknown20->releaseTexture();
  unknown38->releaseTexture();
  if (unknown60 != nullptr) {
    unknown60->releaseTexture();
  }
  if (unknown68 != nullptr) {
    unknown68->releaseTexture();
  }
  unknown48->releaseTexture();
}

void DrPixlPostObjTSSAO::debugRender() {
  if (!unknown00->unknown120[unknown00->unknown1c98]->unknown175) {
    return;
  }
  int width = mm::min(unknown00->unknown5b8->unknown28, 1280);
  int height = mm::min(unknown00->unknown5b8->unknown2c, 720);
  int halfWidth = static_cast<int>(width * 0.5f);
  int halfHeight = static_cast<int>(height * 0.5f);
  int quarterWidth = static_cast<int>(halfWidth * 0.5f);
  int quarterHeight = static_cast<int>(halfHeight * 0.5f);
  unknown28[DrMan::s_nDblIdx]->debugRenderCh(0, 0, halfWidth, halfHeight, 0);
  int x1 = halfWidth + 1;
  unknown20->debugRenderCh(x1, 0, quarterWidth, quarterHeight, 0);
  int x2 = halfWidth + quarterWidth + 2;
  unknown48->debugRenderCh(x2, 0, quarterWidth, quarterHeight, 0);
  int y1 = quarterHeight + 1;
  unknown08->debugRenderSimilarity(x1, y1, quarterWidth, quarterHeight);
  unknown50[DrMan::s_nDblIdx]->debugRenderCh(x2, y1, quarterWidth, quarterHeight, 0);
  int y2 = quarterHeight * 2 + 2;
  if (unknown00->unknown120[unknown00->unknown1c98]->unknownfa0) {
    unknown60->debugRenderCh(x1, y2, quarterWidth, quarterHeight, 0);
  }
  if (unknown00->unknown120[unknown00->unknown1c98]->unknownfb1) {
    unknown00->unknown78->unknown7f0->unknown180->unknowne0->debugRender(x2, y2, quarterWidth, quarterHeight, false, false, 1.0f, true);
  }
}

} // namespace ml
