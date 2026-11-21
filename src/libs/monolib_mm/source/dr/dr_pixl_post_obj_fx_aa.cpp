#include "dr/dr_pixl_post_obj_fx_aa.h"

#include "dr/dr_ap_cache.h"
#include "dr/dr_ap_gx_type.h"
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
#include "grlib/cglib_shader.h"
#include "grlib/cglib_uni_base_utility.h"
#include "mm_math/mm_mat44.h"
#include "mm_mtl/fixed_array.h"
#include "mtl/alloc_handle.h"

namespace ml {

DrPixlPostObjFxAA::DrPixlPostObjFxAA(DrMan *drMan, DrPixlMan *pixlMan, DrPixlPostMan *postMan) : DrPixlPostObj(drMan, pixlMan, postMan) {
  unknown18 = new (drMan->unknown0c) DrPixlRenderTarget(drMan);
  resetColorBuff();
}

DrPixlPostObjFxAA::~DrPixlPostObjFxAA() {
  if (unknown18 != nullptr) {
    delete unknown18;
    unknown18 = nullptr;
  }
}

void DrPixlPostObjFxAA::releaseColorBuff() { unknown18->releaseTexture(); }

void DrPixlPostObjFxAA::update() {}

void DrPixlPostObjFxAA::render() {
  DrAPGxType::setupScreenQuads(false);
  calcScale();
}

void DrPixlPostObjFxAA::resetColorBuff() {
  unknown20 = static_cast<f32>(unknown00->unknown5b8->unknown18);
  unknown24 = static_cast<f32>(unknown00->unknown5b8->unknown1c);
}

// Ruling 8: the shader-pass blocks (uniform block opening, `getTextureLocation` and `unknown001` lookups, the 1/width vectors, the `fxaaRcpFrOpt` and
// `aaVal` vectors) repeat in calcAA and in the other post passes (Bloom, DepthofField, MotionBlur2, DrPixlMan::toneMapRender). The game writes them
// out in each function (0x710085725c: six getUniformBlockValOfs and six setF32SetVec4 calls, no call to a local helper). A file-local helper for the
// two vectors shared with calcAA does not match (241 instructions against 264, 193 against 213 for calcAA).
void DrPixlPostObjFxAA::calcScale() {
  DrPixlPostParm *postParm = unknown00->unknown120[unknown00->unknown1c98];
  if (!DrMan::isSRGBMode() || postParm->m_colTblOn || postParm->m_toneMapOn) {
    unknown08->setMainRenderTarget();
  } else {
    unknown08->setMainSRGBRenderTarget();
  }
  DrAPGxType::setupDepthContl(true, true, 7);
  DrPixlRenderTarget *source = unknown08->unknown7f0->unknown138;
  DrShdDataList *shdList = unknown00->unknown80->unknown00;
  DrShdDataObj *shader = shdList->getSelectShdObj(7);
  DrPixlRenderTarget *downDepth = unknown10->getDownDepth();
  DrCalcViewWork *viewWork = unknown00->unknown580->unknown10;
  shdList->bindTriangleTex();
  shader->setupShader(0u);
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  int sourceLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
  int depthLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("dep");
  u32 rcpOffset = uniform.unknown001("fxaaRcpFrOpt");
  u32 aaOffset = uniform.unknown001("aaVal");
  u32 ratioOffset = uniform.unknown001("ratio");
  u32 scaleOffset = uniform.unknown001("gScal");
  u32 subOffset = uniform.unknown001("gSub");
  u32 uvsclOffset = uniform.unknown001("uvscl");
  f32 width = static_cast<f32>(unknown00->unknown5b8->unknown18);
  f32 height = static_cast<f32>(unknown00->unknown5b8->unknown1c);
  f32 vec[4];
  vec[0] = 1.0f;
  vec[1] = 1.0f;
  vec[2] = 0.0f;
  vec[3] = 0.0f;
  uniform.setF32SetVec4(scaleOffset, vec);
  vec[0] = 1.0f / width;
  vec[1] = 1.0f / height;
  uniform.setF32SetVec4(subOffset, vec);
  vec[0] = postParm->unknown10c / width;
  vec[1] = postParm->unknown10c / height;
  vec[2] = 2.0f / width;
  vec[3] = 2.0f / height;
  uniform.setF32SetVec4(rcpOffset, vec);
  vec[0] = postParm->unknown104;
  vec[1] = postParm->unknown108;
  vec[2] = postParm->unknown100;
  uniform.setF32SetVec4(aaOffset, vec);
  f32 depthHeight = static_cast<f32>(downDepth->unknownc0);
  f32 depthWidth = static_cast<f32>(downDepth->unknownbc);
  vec[0] = (depthWidth - 1.0f) / depthWidth;
  vec[1] = (depthHeight - 1.0f) / depthHeight;
  vec[2] = 1.0f / (depthWidth + depthWidth);
  vec[3] = 1.0f / (depthHeight + depthHeight);
  uniform.setF32SetVec4(uvsclOffset, vec);
  vec[0] = 0.0f;
  vec[1] = viewWork->unknown180.rows[2][2];
  vec[2] = viewWork->unknown180.rows[3][2];
  vec[3] = 0.0f;
  uniform.setF32SetVec4(ratioOffset, vec);
  uniform.updateData();
  uniform.setUniformBlock();
  DrAPCache *apCache = unknown00->unknown5c0;
  apCache->beginTexSampling(2, 1);
  apCache->setTexture(*source->unknown70, sourceLocation);
  apCache->setTexture(*downDepth->unknown70, depthLocation);
  shdList->renderTriangle();
  DrAPGxType::setupDepthContl(false, false, 7);
}

void DrPixlPostObjFxAA::calcLuminosity() {
  wkPixlManRes *res = unknown08->unknown7f0;
  DrPixlRenderTarget *target = res->unknown130;
  if (res->unknown138 == target) {
    target = res->unknown140;
  }
  unknown18->setRenderTarget(*target);
  DrShdDataList *shdList = unknown00->unknown80->unknown00;
  DrShdDataObj *shader = shdList->getSelectShdObj(3);
  shdList->bindTriangleTex();
  shader->setupShader(0u);
  int location = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
  DrPixlRenderTarget *source = unknown08->unknown7f0->unknown138;
  DrAPCache *apCache = unknown00->unknown5c0;
  apCache->beginTexSampling(2, 0);
  apCache->setTexture(*source->unknown70, location);
  shdList->renderTriangle();
  unknown18->setColorInvalidate();
}

// Ruling 8: written out like calcScale (0x7100857754: four getUniformBlockValOfs and four setF32SetVec4 calls, no call to a local helper).
void DrPixlPostObjFxAA::calcAA() {
  DrPixlPostParm *postParm = unknown00->unknown120[unknown00->unknown1c98];
  if (!DrMan::isSRGBMode() || postParm->m_colTblOn || postParm->m_toneMapOn) {
    unknown08->setMainRenderTarget();
  } else {
    unknown08->setMainSRGBRenderTarget();
  }
  DrShdDataList *shdList = unknown00->unknown80->unknown00;
  DrShdDataObj *shader = shdList->getSelectShdObj(2);
  DrPixlRenderTarget *source = unknown08->unknown7f0->unknown138;
  shdList->bindTriangleTex();
  shader->setupShader(0u);
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  int sourceLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
  int texLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("tex");
  u32 rcpOffset = uniform.unknown001("fxaaRcpFrOpt");
  u32 aaOffset = uniform.unknown001("aaVal");
  u32 scaleOffset = uniform.unknown001("gScal");
  u32 subOffset = uniform.unknown001("gSub");
  f32 height = static_cast<f32>(unknown00->unknown5b8->unknown1c);
  f32 width = static_cast<f32>(unknown00->unknown5b8->unknown18);
  f32 vec[4];
  vec[0] = (width - 1.0f) / width;
  vec[1] = (height - 1.0f) / height;
  vec[2] = 1.0f / (width + width);
  vec[3] = 1.0f / (height + height);
  uniform.setF32SetVec4(scaleOffset, vec);
  vec[0] = 1.0f / width;
  vec[1] = 1.0f / height;
  uniform.setF32SetVec4(subOffset, vec);
  vec[0] = postParm->unknown10c / width;
  vec[1] = postParm->unknown10c / height;
  vec[2] = 2.0f / width;
  vec[3] = 2.0f / height;
  uniform.setF32SetVec4(rcpOffset, vec);
  vec[0] = postParm->unknown104;
  vec[1] = postParm->unknown108;
  vec[2] = postParm->unknown100;
  uniform.setF32SetVec4(aaOffset, vec);
  uniform.updateData();
  uniform.setUniformBlock();
  DrAPCache *apCache = unknown00->unknown5c0;
  apCache->beginTexSampling(2, 1);
  apCache->setTexture(*unknown18->unknown70, sourceLocation);
  apCache->beginTexSampling(2, 1);
  apCache->setTexture(*source->unknown70, texLocation);
  shdList->renderTriangle();
}

void DrPixlPostObjFxAA::debugRender() {
  const unknown057 *screen = unknown00->unknown5b8;
  unknown18->debugRender(0, 0, screen->unknown18 / 2, screen->unknown1c / 2, false, false, 1.0f, true);
}

} // namespace ml
