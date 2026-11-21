#include "dr/dr_pixl_post_obj_tssao.h"

#include <math.h>

#include "dr/dr_ap_cache.h"
#include "dr/dr_ap_gx_type.h"
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
#include "grlib/cglib_depth_ctl.h"
#include "grlib/cglib_depth_target.h"
#include "grlib/cglib_render_target.h"
#include "grlib/cglib_shader.h"
#include "grlib/cglib_state.h"
#include "grlib/cglib_uni_base_utility.h"
#include "ml/rand.h"
#include "ml/work_cpu.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_vec4.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_vector.h"

namespace ml {

// Inferred role: per frame values (frame count modulo 3) of the last two components of the gParam uniform of passQuaterNormal and passSSAO; original name unknown.
static const f32 unknown003[3][2] = {{0.0f, 0.0f}, {100.0f, 100.0f}, {-100.0f, -100.0f}};

void DrPixlPostObjTSSAO::passQuaterNormal() {
  DrPixlPostParm *postParm = unknown00->unknown120[unknown00->unknown1c98];
  DrPixlRenderTarget *target = unknown08->unknown7f0->unknown180->unknowne0;
  bool isQuarterDepth = unknown00->unknown1e10;
  if (isQuarterDepth) {
    target->clearTexture(mm::Col4(0.5f, 0.5f, 0.0f, 1.0f), static_cast<GrlClaerMask>(0xf));
  }
  grlib::CGLibColorCtl::setBlendOffControl(GRL_LOGIC_TYPE_COPY);
  DrShdDataList *shdList = unknown00->unknown80->unknown00;
  DrShdDataObj *shader = shdList->getPostShdObj(0x44);
  shader->setDeclarationIdx(shader->getDeclarationOfs("OUTPUT_CLASSIFICATION"), 2);
  u32 branchLess = isQuarterDepth ? 1 : 2;
  shader->setDeclarationIdx(shader->getDeclarationOfs("BRANCH_LESS"), branchLess);
  shdList->unknown002(shader);
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  u32 param = uniform.unknown001("gParam");
  u32 param2 = uniform.unknown001("gParam2");
  uniform.unknown001("gRotMat");
  u32 coordToUv = uniform.unknown001("gCoordToUV");
  u32 coordToScreenPos = uniform.unknown001("gCoordToScreenPos");
  u32 screenToViewPos = uniform.unknown001("gScreenToViewPos");
  int depthLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTDepth");
  (shader->unknown38 + shader->unknown58)->getTextureLocation("gTNormal");
  (shader->unknown38 + shader->unknown58)->getTextureLocation("gTStencil");
  (shader->unknown38 + shader->unknown58)->getTextureLocation("gTEtc");
  f32 paddedWidth = static_cast<f32>(target->unknownbc) + (static_cast<f32>(unknown70) + static_cast<f32>(unknown70));
  f32 paddedHeight = static_cast<f32>(target->unknownc0) + (static_cast<f32>(unknown70) + static_cast<f32>(unknown70));
  DrCalcViewWork *viewWork = unknown00->unknown580->unknown10;
  mm::Vec4 paramValue;
  f32 value178 = postParm->unknown178;
  paramValue.x = value178 * ((paddedHeight * viewWork->unknown4c8) / (viewWork->unknown4c8 * tanf(viewWork->unknown4c4 * 0.5f)));
  paramValue.y = value178 * value178;
  paramValue.z = unknown003[ml::WorkCpu::getFrameCount() % 3][0];
  paramValue.w = unknown003[ml::WorkCpu::getFrameCount() % 3][1];
  uniform.setF32SetVec4(param, &paramValue.x);
  // Dead store the game holds: it copies mm::Vec4::zero (through the GOT, 0x71008c21b4) over the first vector after the call.
  paramValue = mm::Vec4::zero;
  // The fourth component is never set: the game stores three values and passes the vector.
  mm::Vec4 param2Value;
  param2Value.x = postParm->unknown180 * 100.0f;
  param2Value.y = postParm->unknownfa4;
  param2Value.z = (1.0f - postParm->unknown190) * (1.0f - postParm->unknown190);
  if (param2Value.z > 1.0f) {
    param2Value.z = 1.0f;
  }
  uniform.setF32SetVec4(param2, &param2Value.x);
  mm::Vec4 coordToUvValue;
  calcFragCoordToUV(coordToUvValue, paddedWidth, paddedHeight);
  uniform.setF32SetVec4(coordToUv, &coordToUvValue.x);
  mm::Vec4 coordToScreenPosValue;
  calcFragCoordToScreen(coordToScreenPosValue, paddedWidth, paddedHeight);
  uniform.setF32SetVec4(coordToScreenPos, &coordToScreenPosValue.x);
  f32 viewPos[4];
  viewPos[1] = tanf(viewWork->unknown4c4 * 0.5f);
  viewPos[0] = viewPos[1] * viewWork->unknown4c0;
  viewPos[2] = 0.0f;
  viewPos[3] = 0.0f;
  uniform.setF32SetVec4(screenToViewPos, viewPos);
  DrAPCache *apCache = unknown00->unknown5c0;
  apCache->beginBorderDepthMax();
  apCache->setTexture(*unknown10->getDownDepth()->unknown70, depthLocation);
  uniform.updateData();
  uniform.setUniformBlock();
  if (!isQuarterDepth) {
    target->setRenderTarget();
  } else {
    target->setRenderTarget(*unknown08->unknown7f0->unknown1c0->unknown120);
    grlib::CGLibDepthCtl::setDepthControl(true, false, GRL_COMPARE_LEQUAL);
  }
  shdList->renderQuads();
  target->setColorInvalidate();
}

// Inferred role: index of the dither entry of the next passSSAO; original name unknown.
static int unknown004;

void DrPixlPostObjTSSAO::passSSAO() {
  DrPixlPostParm *postParm = unknown00->unknown120[unknown00->unknown1c98];
  DrPixlRenderTarget *target = unknown20;
  grlib::CGLibColorCtl::setBlendOffControl(GRL_LOGIC_TYPE_COPY);
  DrShdDataList *shdList = unknown00->unknown80->unknown00;
  DrShdDataObj *shader = shdList->getPostShdObj(0x2c);
  bool isMpfSkip = postParm->unknownfb0;
  bool isQuarterDepth = unknown00->unknown1e10;
  u32 outputClassification = postParm->unknownfa0 ? 1 : 2;
  shader->setDeclarationIdx(shader->getDeclarationOfs("OUTPUT_CLASSIFICATION"), outputClassification);
  u32 useQuaterNormal = postParm->unknownfb1 ? 1 : 2;
  shader->setDeclarationIdx(shader->getDeclarationOfs("USE_QUATER_NORMAL"), useQuaterNormal);
  u32 mpfSkip = isMpfSkip ? 1 : 2;
  shader->setDeclarationIdx(shader->getDeclarationOfs("MPF_SKIP"), mpfSkip);
  u32 branchLess = isQuarterDepth ? 1 : 2;
  shader->setDeclarationIdx(shader->getDeclarationOfs("BRANCH_LESS"), branchLess);
  shdList->unknown002(shader);
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  u32 param = uniform.unknown001("gParam");
  u32 param2 = uniform.unknown001("gParam2");
  uniform.unknown001("gRotMat");
  u32 coordToUv = uniform.unknown001("gCoordToUV");
  u32 coordToScreenPos = uniform.unknown001("gCoordToScreenPos");
  u32 screenToViewPos = uniform.unknown001("gScreenToViewPos");
  u32 dither = uniform.unknown001("gDither");
  int depthLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTDepth");
  int nomLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTNom");
  int stencilLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTStencil");
  int etcLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTEtc");
  (shader->unknown38 + shader->unknown58)->getTextureLocation("gTSimilarity");
  int prevSimilarityLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTPrevSimilarity");
  f32 paddedWidth = static_cast<f32>(target->unknownbc) + (static_cast<f32>(unknown70) + static_cast<f32>(unknown70));
  f32 paddedHeight = static_cast<f32>(target->unknownc0) + (static_cast<f32>(unknown70) + static_cast<f32>(unknown70));
  DrCalcViewWork *viewWork = unknown00->unknown580->unknown10;
  mm::Vec4 paramValue;
  f32 value178 = postParm->unknown178;
  paramValue.x = value178 * ((paddedHeight * viewWork->unknown4c8) / (viewWork->unknown4c8 * tanf(viewWork->unknown4c4 * 0.5f)));
  paramValue.y = value178 * value178;
  paramValue.z = unknown003[ml::WorkCpu::getFrameCount() % 3][0];
  paramValue.w = unknown003[ml::WorkCpu::getFrameCount() % 3][1];
  uniform.setF32SetVec4(param, &paramValue.x);
  // Dead store the game holds: it copies mm::Vec4::zero (through the GOT, 0x71008c2750) over the first vector after the call.
  paramValue = mm::Vec4::zero;
  mm::Vec4 param2Value;
  param2Value.x = postParm->unknown180 * 100.0f;
  param2Value.y = postParm->unknownfa4;
  f32 blend = (1.0f - postParm->unknown190) * (1.0f - postParm->unknown190);
  // The game reads the counter as an unsigned index (ldr w10, 0x71008c279c: zero-extended; `unknown9c0[unknown004]` with the int gives ldrsw)
  // and updates it with a signed `% 8`, so the counter stays an int.
  u32 index = unknown004;
  if (blend > 1.0f) {
    blend = 1.0f;
  }
  param2Value.z = blend;
  param2Value.w = viewWork->unknown9c0[index].y * 6.2831855f;
  unknown004 = (unknown004 + 1) % 8;
  uniform.setF32SetVec4(param2, &param2Value.x);
  mm::Vec4 coordToUvValue;
  calcFragCoordToUV(coordToUvValue, paddedWidth, paddedHeight);
  uniform.setF32SetVec4(coordToUv, &coordToUvValue.x);
  mm::Vec4 coordToScreenPosValue;
  calcFragCoordToScreen(coordToScreenPosValue, paddedWidth, paddedHeight);
  uniform.setF32SetVec4(coordToScreenPos, &coordToScreenPosValue.x);
  f32 viewPos[4];
  viewPos[1] = tanf(viewWork->unknown4c4 * 0.5f);
  viewPos[0] = viewPos[1] * viewWork->unknown4c0;
  viewPos[2] = 0.0f;
  viewPos[3] = 0.0f;
  uniform.setF32SetVec4(screenToViewPos, viewPos);
  uniform.setMat44SetMat44(dither, viewWork->unknownc20);
  DrAPCache *apCache = unknown00->unknown5c0;
  apCache->beginBorderDepthMinusMax();
  apCache->setTexture(*unknown10->unknowne8->unknown70, depthLocation);
  apCache->beginTexSampling(2, 0);
  apCache->setTexture(*unknown08->getDepthObj()->unknown130, stencilLocation);
  apCache->setTexture(*unknown08->getPixlObj(1)->unknown70, etcLocation);
  apCache->setTexture(*unknown08->unknown7f0->unknown180->unknowne0->unknown70, nomLocation);
  apCache->beginBorderWhite();
  apCache->setTexture(*unknown50[DrMan::s_nDblStockIdx]->unknown70, prevSimilarityLocation);
  mm::mtl::FixedVector<grlib::CGLibRenderTarget *, 2> targets;
  targets.push_back(unknown48);
  if (!isQuarterDepth) {
    target->setRenderTargetImpl(targets.begin(), targets.size(), nullptr);
  } else {
    target->setRenderTargetImpl(targets.begin(), targets.size(), unknown08->unknown7f0->unknown1c0->unknown120);
    grlib::CGLibDepthCtl::setDepthControl(true, false, GRL_COMPARE_LEQUAL);
  }
  uniform.updateData();
  uniform.setUniformBlock();
  shdList->renderQuads();
  target->setColorInvalidate();
}

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

void DrPixlPostObjTSSAO::passDilateContinuityMask() {
  bool isQuarterDepth = unknown00->unknown1e10;
  DrPixlRenderTarget *source = unknown60;
  DrPixlRenderTarget *target = unknown68;
  if (isQuarterDepth) {
    target->clearTexture(mm::Col4(0.0f, 0.0f, 0.0f, 0.0f), static_cast<GrlClaerMask>(0xf));
  }
  grlib::CGLibColorCtl::setBlendOffControl(GRL_LOGIC_TYPE_COPY);
  DrShdDataList *shdList = unknown00->unknown80->unknown00;
  DrShdDataObj *shader = shdList->getPostShdObj(0x30);
  u32 branchLess = isQuarterDepth ? 1 : 2;
  shader->setDeclarationIdx(shader->getDeclarationOfs("BRANCH_LESS"), branchLess);
  shdList->unknown002(shader);
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  u32 coordToUv = uniform.unknown001("gCoordToUV");
  int sourceLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTSource");
  f32 width = static_cast<f32>(source->unknownbc);
  mm::Vec4 coord;
  coord.x = 1.0f / width;
  f32 height = static_cast<f32>(source->unknownc0);
  coord.y = 1.0f / height;
  coord.z = 0.5f / width;
  coord.w = 0.5f / height;
  uniform.setF32SetVec4(coordToUv, &coord.x);
  DrAPCache *apCache = unknown00->unknown5c0;
  apCache->beginTexSampling(2, 0);
  apCache->setTexture(*source->unknown70, sourceLocation);
  if (!isQuarterDepth) {
    target->setRenderTarget(*unknown60);
  } else {
    target->setRenderTarget(*unknown08->unknown7f0->unknown1c0->unknown120, *unknown60);
    grlib::CGLibDepthCtl::setDepthControl(true, false, GRL_COMPARE_LEQUAL);
  }
  uniform.updateData();
  uniform.setUniformBlock();
  shdList->renderQuads();
  target->setColorInvalidate();
}

void DrPixlPostObjTSSAO::passBlur_Sub(BlurAxis axis, f32 strength, DrPixlRenderTarget *source, DrPixlRenderTarget *destination, bool flag) {
  grlib::CGLibColorCtl::setBlendOffControl(GRL_LOGIC_TYPE_COPY);
  DrShdDataList *shdList = unknown00->unknown80->unknown00;
  DrShdDataObj *shader = shdList->getPostShdObj(0x2d);
  u32 branchLess = flag ? 1 : 2;
  shader->setDeclarationIdx(shader->getDeclarationOfs("BRANCH_LESS"), branchLess);
  shader->setDeclarationIdx(shader->getDeclarationOfs("TAP_AXIS"), axis);
  shdList->unknown002(shader);
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  u32 param = uniform.unknown001("gParam");
  u32 coordToGbUv = uniform.unknown001("gCoordToGBUV");
  u32 coordToUv = uniform.unknown001("gCoordToUV");
  int sourceLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTSource");
  int depthLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTDepth");
  int similarityLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTSimilarity");
  int prevSimilarityLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTPrevSimilarity");
  DrPixlRenderTarget *downDepth = unknown10->getDownDepth();
  mm::Vec4 paramValue;
  paramValue.x = strength;
  paramValue.y = static_cast<f32>(unknown70);
  paramValue.z = static_cast<f32>(mtRand(0, destination->unknownbc));
  paramValue.w = static_cast<f32>(mtRand(0, destination->unknownc0));
  uniform.setF32SetVec4(param, &paramValue.x);
  mm::Vec4 coordToGbUvValue;
  f32 width = static_cast<f32>(destination->unknownbc);
  coordToGbUvValue.x = 1.0f / width;
  f32 height = static_cast<f32>(destination->unknownc0);
  coordToGbUvValue.y = 1.0f / height;
  coordToGbUvValue.z = 0.5f / width;
  coordToGbUvValue.w = 0.5f / height;
  uniform.setF32SetVec4(coordToGbUv, &coordToGbUvValue.x);
  mm::Vec4 coordToUvValue;
  coordToUvValue.x = 1.0f / static_cast<f32>(destination->unknownbc);
  coordToUvValue.y = 1.0f / static_cast<f32>(destination->unknownc0);
  coordToUvValue.z = -0.5f / static_cast<f32>(downDepth->unknownbc);
  coordToUvValue.w = -0.5f / static_cast<f32>(downDepth->unknownc0);
  uniform.setF32SetVec4(coordToUv, &coordToUvValue.x);
  DrAPCache *apCache = unknown00->unknown5c0;
  apCache->beginTexSampling(2, 1);
  apCache->setTexture(*source->unknown70, sourceLocation);
  apCache->setTexture(*downDepth->unknown70, depthLocation);
  apCache->beginBorderWhite();
  apCache->setTexture(*unknown48->unknown70, similarityLocation);
  apCache->setTexture(*unknown50[DrMan::s_nDblStockIdx]->unknown70, prevSimilarityLocation);
  if (!flag) {
    destination->setRenderTarget();
  } else {
    destination->setRenderTarget(*unknown08->unknown7f0->unknown1c0->unknown120);
    grlib::CGLibDepthCtl::setDepthControl(true, false, GRL_COMPARE_LEQUAL);
  }
  uniform.updateData();
  uniform.setUniformBlock();
  shdList->renderQuads();
  destination->setColorInvalidate();
}

void DrPixlPostObjTSSAO::passUpScaleToMiddle() {
  DrPixlRenderTarget *target = unknown40;
  grlib::CGLibColorCtl::setBlendOffControl(GRL_LOGIC_TYPE_COPY);
  unknown10->getDownDepth();
  DrShdDataList *shdList = unknown00->unknown80->unknown00;
  DrShdDataObj *shader = shdList->getPostShdObj(0x4a);
  shdList->unknown002(shader);
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  u32 sampleOffset = uniform.unknown001("gSampleOffset");
  u32 param = uniform.unknown001("gParam");
  u32 fragCoordToGbUv = uniform.unknown001("gFragCoordToGBUV");
  int aoLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTAO");
  int depthLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTDepth");
  int halfDepthLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTHalfDepth");
  DrPixlPostParm *postParm = unknown00->unknown120[unknown00->unknown1c98];
  DrPixlRenderTarget *ao = unknown28[DrMan::s_nDblIdx];
  mm::Vec4 sampleOffsetValue;
  sampleOffsetValue.x = 1.5f / static_cast<f32>(target->unknownbc);
  sampleOffsetValue.y = 1.5f / static_cast<f32>(target->unknownc0);
  sampleOffsetValue.z = 0.0f;
  sampleOffsetValue.w = 0.0f;
  uniform.setF32SetVec4(sampleOffset, &sampleOffsetValue.x);
  mm::Vec4 paramValue;
  paramValue.x = postParm->unknown17c;
  paramValue.y = static_cast<f32>(ao->unknownbc) / static_cast<f32>(target->unknownbc);
  paramValue.z = mm::clamp(1.0f - postParm->unknown190, 0.0f, 1.0f);
  paramValue.w = postParm->unknown184;
  uniform.setF32SetVec4(param, &paramValue.x);
  mm::Vec4 fragCoordToGbUvValue;
  fragCoordToGbUvValue.x = 1.0f / static_cast<f32>(ao->unknownbc);
  fragCoordToGbUvValue.y = 1.0f / static_cast<f32>(ao->unknownc0);
  fragCoordToGbUvValue.z = (0.5f - static_cast<f32>(unknown70)) / static_cast<f32>(ao->unknownbc);
  fragCoordToGbUvValue.w = (0.5f - static_cast<f32>(unknown70)) / static_cast<f32>(ao->unknownc0);
  uniform.setF32SetVec4(fragCoordToGbUv, &fragCoordToGbUvValue.x);
  DrAPCache *apCache = unknown00->unknown5c0;
  apCache->beginBorderDepthMax();
  apCache->setTexture(*unknown10->getDownDepth()->unknown70, depthLocation);
  apCache->setTexture(*unknown10->getOldDownDepth()->unknown70, halfDepthLocation);
  apCache->beginTexSampling(2, 1);
  apCache->setTexture(*ao->unknown70, aoLocation);
  uniform.updateData();
  uniform.setUniformBlock();
  target->setRenderTarget();
  shdList->renderQuads();
  target->setColorInvalidate();
}

void DrPixlPostObjTSSAO::passUpScaleToFull() {
  DrPixlRenderTarget *target = unknown08->getPixlObj(2);
  DrPixlRenderTarget *downDepth = unknown10->getDownDepth();
  DrShdDataList *shdList = unknown00->unknown80->unknown00;
  DrShdDataObj *shader = shdList->getPostShdObj(0x2f);
  shdList->unknown002(shader);
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  u32 fragCoordToUv = uniform.unknown001("gFragCoordToUV");
  u32 param = uniform.unknown001("gParam");
  u32 fragCoordToGbUv = uniform.unknown001("gFragCoordToGBUV");
  int aoLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTAO");
  int depthLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTDepth");
  int halfDepthLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTHalfDepth");
  int etcLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTEtc");
  // The game loads the member and doubles it before the other loads of this function (lsl right after the texture locations), and reads it
  // again further down for the gFragCoordToGBUV values.
  int margin = unknown70 * 2;
  f32 downDepthWidth = static_cast<f32>(downDepth->unknownbc);
  f32 downDepthHeight = static_cast<f32>(downDepth->unknownc0);
  DrPixlPostParm *postParm = unknown00->unknown120[unknown00->unknown1c98];
  DrPixlRenderTarget *middle = unknown40;
  DrPixlRenderTarget *etc = unknown00->unknown78->getPixlObj(1);
  mm::Vec4 fragCoordToUvValue;
  fragCoordToUvValue.x = 1.0f / downDepthWidth;
  fragCoordToUvValue.y = 1.0f / downDepthHeight;
  fragCoordToUvValue.z = 0.5f / downDepthWidth;
  fragCoordToUvValue.w = 0.5f / downDepthHeight;
  uniform.setF32SetVec4(fragCoordToUv, &fragCoordToUvValue.x);
  mm::Vec4 paramValue;
  paramValue.x = postParm->unknown17c;
  paramValue.y = static_cast<f32>(middle->unknownbc) / static_cast<f32>(target->unknownbc);
  paramValue.z = mm::clamp(1.0f - postParm->unknown190, 0.0f, 1.0f);
  paramValue.w = postParm->unknown184;
  uniform.setF32SetVec4(param, &paramValue.x);
  mm::Vec4 fragCoordToGbUvValue;
  fragCoordToGbUvValue.x = 1.0f / static_cast<f32>(middle->unknownbc);
  fragCoordToGbUvValue.y = 1.0f / static_cast<f32>(middle->unknownc0);
  fragCoordToGbUvValue.z = (0.5f - static_cast<f32>(unknown70)) / static_cast<f32>(middle->unknownbc);
  fragCoordToGbUvValue.w = (0.5f - static_cast<f32>(unknown70)) / static_cast<f32>(middle->unknownc0);
  uniform.setF32SetVec4(fragCoordToGbUv, &fragCoordToGbUvValue.x);
  DrAPCache *apCache = unknown00->unknown5c0;
  apCache->beginBorderDepthMax();
  apCache->setTexture(*unknown10->getDownDepth()->unknown70, depthLocation);
  apCache->setTexture(*unknown10->getOldDownDepth()->unknown70, halfDepthLocation);
  apCache->beginTexSampling(2, 1);
  apCache->setTexture(*middle->unknown70, aoLocation);
  apCache->setTexture(*etc->unknown70, etcLocation);
  target->setRenderTarget(*unknown08->getDepthObj()->unknown120);
  grlib::CGLibColorCtl::setBlendControl(GRL_BLEND_FUNC_UNKNOWN_9, GRL_BLEND_FUNC_ZERO, GRL_BLEND_COMBINE_ADD, GRL_BLEND_FUNC_ONE, GRL_BLEND_FUNC_ONE, GRL_BLEND_COMBINE_ADD, GRL_LOGIC_TYPE_COPY);
  grlib::CGLibColorCtl::setColorChannelMask(false, false, true, false);
  grlib::LibMainStateViewPort viewPort(static_cast<f32>(margin),
                                       static_cast<f32>(margin),
                                       static_cast<f32>(target->unknownbc) - (static_cast<f32>(margin) + static_cast<f32>(margin)),
                                       static_cast<f32>(target->unknownc0) - (static_cast<f32>(margin) + static_cast<f32>(margin)),
                                       0.0f,
                                       1.0f);
  grlib::CGLibState::setViewport(viewPort);
  DrAPGxType::setupStencilTest(false, false, 7, true, 0, 8, 5, 0, 0, 0);
  uniform.updateData();
  uniform.setUniformBlock();
  shdList->renderQuads();
  target->setColorInvalidate();
  grlib::CGLibColorCtl::setColorChannelMask(true, true, true, true);
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
