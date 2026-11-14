#include "dr/dr_pixl_post_obj_depthof_field.h"

#include <math.h>

#include "dr/dr_ap_cache.h"
#include "dr/dr_ap_gx_type.h"
#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_pixl_render_target.h"
#include "dr/dr_res_filter_data.h"
#include "dr/dr_shd_data_list.h"
#include "dr/dr_shd_data_obj.h"
#include "dr/dr_shd_man.h"
#include "grlib/cglib_render_target.h"
#include "grlib/cglib_shader.h"
#include "grlib/cglib_uni_base_utility.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_array.h"

namespace ml {

DrPixlPostObjDepthofField::~DrPixlPostObjDepthofField() {
  unknown001(unknown18);
  unknown001(unknown20);
  unknown001(unknown28);
  unknown001(unknown30);
  unknown001(unknown38);
  unknown001(unknown48);
  unknown001(unknown40);
}

void DrPixlPostObjDepthofField::update() {
  s32 pixlLv = unknown00->unknown120[unknown00->unknown1c98]->unknown238;
  if (unknown50 != pixlLv) {
    unknown50 = pixlLv;
    if (pixlLv == 0) {
      unknown54 = 1.0f;
    } else if (pixlLv == 1) {
      unknown54 = 2.0f;
    } else {
      unknown54 = 4.0f;
    }
    resetColorBuff();
  }
  unknown59 = false;
  DrPixlPostParm *postParm = unknown00->unknown120[unknown00->unknown1c98];
  if (postParm->m_colTblOn) {
    DrResFilterData *filterData = unknown00->unknown98;
    f32 ratio = filterData->unknown10[filterData->unknown100].unknown34;
    unknown59 = postParm->m_colorFilterTransZ;
    if (ratio == 1.0f && postParm->unknown278 == postParm->unknown26c && filterData->unknown10[filterData->unknown100].unknown26 == postParm->unknown278 &&
        filterData->unknown10[filterData->unknown100].unknown24 == postParm->unknown278) {
      unknown59 = false;
    }
  }
}

void DrPixlPostObjDepthofField::render() {
  if (unknown00->unknown120[unknown00->unknown1c98]->unknown21c) {
    renderDepthSample();
    renderDepthAllSample();
  }
  renderDofScaleDown();
  renderDofPass();
  renderCalc();
}

void DrPixlPostObjDepthofField::releaseColorBuff() {
  unknown18->releaseTexture();
  unknown20->releaseTexture();
  unknown28->releaseTexture();
  unknown30->releaseTexture();
  unknown38->releaseTexture();
  unknown48->releaseTexture();
}

void DrPixlPostObjDepthofField::renderDepthAllSample() {
  DrCalcViewWork *viewWork = unknown00->unknown580->unknown10;
  f32 blend;
  if (unknown58) {
    unknown40->clearTexture(mm::Col4(0.0f, 0.0f, 0.0f, 0.0f), static_cast<GrlClaerMask>(0xf));
    unknown58 = false;
    blend = 0.0f;
  } else {
    blend = viewWork->unknown9a9 ? 0.0f : 0.95f;
  }
  unknown40->setRenderTarget();
  DrAPCache *apCache = unknown00->unknown5c0;
  DrPixlPostParm *postParm = unknown00->unknown120[unknown00->unknown1c98];
  DrShdDataList *shdList = unknown00->unknown80->unknown00;
  DrShdDataObj *shader;
  if (postParm->unknown23c != 0) {
    shader = shdList->getPostShdObj(0x20);
  } else {
    shader = shdList->getPostShdObj(0x1f);
  }
  {
    shdList->bindTriangle();
    shader->setupShader(0u);
    grlib::CGLibUniformEtcUtility uniform(shader);
    uniform.setUseUniformBlock("U_POST");
    int depthLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("dep");
    int oldLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("old");
    if (postParm->unknown23c == 0) {
      u32 offset = uniform.unknown001("pisu[0]");
      f32 height = static_cast<f32>(unknown38->unknownc0);
      f32 width = static_cast<f32>(unknown38->unknownbc);
      f32 pisu[8];
      pisu[0] = 1.0f / width;
      pisu[1] = 1.0f / height;
      pisu[2] = -1.0f / width;
      pisu[3] = -1.0f / height;
      pisu[4] = blend;
      pisu[5] = 0.0f;
      pisu[6] = 0.0f;
      pisu[7] = 0.0f;
      uniform.setF32SetF32Array(offset, pisu, 8);
    } else {
      u32 offset = uniform.unknown001("pisu");
      s32 index = postParm->unknown23c - 1;
      f32 pisu[4];
      s32 block = index / 4;
      s32 sub = index % 4;
      s32 x = block % 2 * 2 + sub % 2;
      s32 row = block / 2;
      s32 y = sub / 2 + row * 2;
      pisu[0] = static_cast<f32>(x) * 0.25f + 0.125f;
      pisu[1] = 1.0f - (static_cast<f32>(y) * 0.25f + 0.125f);
      pisu[2] = blend;
      pisu[3] = 0.0f;
      uniform.setF32SetVec4(offset, pisu);
    }
    apCache->beginTexSampling(2, 0);
    apCache->setTexture(*unknown38->unknown70, depthLocation);
    apCache->setTexture(*unknown40->unknown70, oldLocation);
    uniform.updateData();
    uniform.setUniformBlock();
    shdList->renderTriangle();
  }
  unknown40->setColorInvalidate();
  unknown48->setRenderTarget();
  shader = shdList->getPostShdObj(0x23);
  {
    shdList->bindTriangle();
    shader->setupShader(0u);
    grlib::CGLibUniformEtcUtility uniform(shader);
    uniform.setUseUniformBlock("U_POST");
    u32 ratioOffset = uniform.unknown001("ratio");
    f32 ratio[4];
    ratio[0] = viewWork->unknown430.x;
    ratio[1] = viewWork->unknown430.y;
    ratio[2] = postParm->unknown244;
    ratio[3] = postParm->unknown240;
    uniform.setF32SetVec4(ratioOffset, ratio);
    int calcLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("calc");
    apCache->beginTexSampling(2, 0);
    apCache->setTexture(*unknown40->unknown70, calcLocation);
    uniform.updateData();
    uniform.setUniformBlock();
    shdList->renderTriangle();
  }
  unknown48->setColorInvalidate();
}

void DrPixlPostObjDepthofField::renderDofScaleDown() {
  DrAPGxType::setupScreenQuads(false);
  unknown18->setRenderTarget();
  DrAPCache *apCache = unknown00->unknown5c0;
  DrPixlPostParm *postParm = unknown00->unknown120[unknown00->unknown1c98];
  DrShdDataList *shdList = unknown00->unknown80->unknown00;
  DrShdDataObj *shader = shdList->getPostShdObj(0x22);
  u32 downSec = postParm->unknown21b ? 1 : 2;
  shader->setDeclarationIdx(shader->getDeclarationOfs("DOWN_SEC"), downSec);
  shdList->bindTriangleTex();
  shader->setupShader(0u);
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  int frameLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
  int colorLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("s1");
  u32 scaleOffset = uniform.unknown001("gScal");
  u32 ratioOffset = uniform.unknown001("ratio");
  u32 dofParamOffset = uniform.unknown001("dofpam");
  f32 width = static_cast<f32>(unknown00->unknown5b8->unknown18);
  f32 height = static_cast<f32>(unknown00->unknown5b8->unknown1c);
  f32 scaleU = (width - 1.0f) / width;
  f32 scaleV = (height - 1.0f) / height;
  f32 work[8];
  if (!postParm->unknown21b) {
    work[0] = scaleU;
    work[1] = scaleV;
    work[2] = 1.0f / (width + width) - 1.0f / static_cast<f32>(unknown18->unknownbc);
    work[3] = 1.0f / (height + height) - 1.0f / static_cast<f32>(unknown18->unknownc0);
  } else {
    work[0] = 1.0f;
    work[1] = 1.0f;
    work[2] = (1.0f / static_cast<f32>(unknown18->unknownbc)) * -0.5f;
    work[3] = (1.0f / static_cast<f32>(unknown18->unknownc0)) * -0.5f;
  }
  uniform.setF32SetVec4(scaleOffset, work);
  DrCalcViewWork *viewWork = unknown00->unknown580->unknown10;
  f32 focus = postParm->unknown224 / viewWork->unknown430.x + viewWork->unknown430.y;
  f32 range = postParm->unknown228 / viewWork->unknown430.x;
  work[0] = -focus;
  work[1] = -1.0f / range;
  work[2] = postParm->unknown234;
  work[3] = postParm->unknown22c;
  uniform.setF32SetVec4(ratioOffset, work);
  work[0] = -focus;
  work[1] = -1.0f / range;
  work[2] = postParm->unknown21c ? 1.0f : 0.0f;
  work[3] = 0.0f;
  uniform.setF32SetVec4(dofParamOffset, work);
  int ratioLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("ratTex");
  apCache->beginTexSampling(2, 0);
  apCache->setTexture(*unknown48->unknown70, ratioLocation);
  if (!postParm->unknown21b) {
    u32 ofsOffset = uniform.unknown001("ofs[0]");
    f32 ofsU = scaleU / width;
    f32 ofsV = scaleV / height;
    work[0] = ofsU;
    work[1] = -ofsV;
    work[2] = ofsU * 3.0f;
    work[3] = -ofsV;
    work[4] = ofsU * 3.0f;
    work[5] = ofsV * -3.0f;
    work[6] = ofsU;
    work[7] = ofsV * -3.0f;
    uniform.setF32SetF32Array(ofsOffset, work, 8);
    apCache->beginTexSampling(2, 1);
  } else {
    apCache->beginTexSampling(2, 0);
  }
  apCache->setTexture(*unknown08->unknown7f0->unknown138->unknown70, frameLocation);
  wkPixlManRes *res = unknown08->unknown7f0;
  DrPixlRenderTarget *colorBuff = postParm->m_TMAAOn ? res->unknown00[13][DrMan::s_nDblIdx] : res->unknown00[4][0];
  apCache->setTexture(*colorBuff->unknown70, colorLocation);
  uniform.updateData();
  uniform.setUniformBlock();
  shdList->renderTriangle();
  unknown18->setColorInvalidate();
}

void DrPixlPostObjDepthofField::renderDofPass() {
  DrAPCache *apCache = unknown00->unknown5c0;
  DrPixlPostParm *postParm = unknown00->unknown120[unknown00->unknown1c98];
  DrShdDataList *shdList = unknown00->unknown80->unknown00;
  f32 pixlScale = postParm->unknown21a ? unknown54 * 0.5f : unknown54;
  f32 width = static_cast<f32>(unknown18->unknownbc);
  f32 height = static_cast<f32>(unknown18->unknownc0);
  f32 scale[4];
  scale[0] = (width - 1.0f) / width;
  scale[1] = (height - 1.0f) / height;
  scale[2] = 1.0f / (width + width);
  scale[3] = 1.0f / (height + height);
  if (postParm->unknownfb3) {
    f32 reductionX = postParm->unknownfc0;
    f32 reductionY = postParm->unknownfc4;
    width /= reductionX;
    height /= reductionY;
  }
  f32 ratio = postParm->unknown220;
  f32 ofsU = 1.0f / width * ratio * 0.125f;
  f32 stepU = pixlScale * ofsU;
  f32 stepV = pixlScale * (1.0f / height * ratio * 0.125f);
  s32 count = postParm->unknown21a ? 12 : 6;
  f32 ofs[48];
  f32 dofParam[4];
  for (s32 i = 0; i < count; i++) {
    ofs[i * 2] = 0.0f;
    ofs[i * 2 + 1] = -(stepV * 0.5f + stepV * i);
  }
  f32 s = sinf(60.0f * mm::DEG_TO_RAD);
  f32 c = cosf(60.0f * mm::DEG_TO_RAD);
  for (s32 i = 0; i < count; i++) {
    ofs[count * 2 + i * 2] = (stepU * 0.5f + stepU * i) * s;
    ofs[count * 2 + i * 2 + 1] = (stepV * 0.5f + stepV * i) * c;
  }
  dofParam[0] = postParm->unknown230;
  dofParam[1] = 0.0f;
  dofParam[2] = 0.0f;
  dofParam[3] = 0.0f;
  unknown20->setRenderTarget(*unknown28);
  DrShdDataObj *shader;
  if (postParm->unknown21a) {
    shader = shdList->getPostShdObj(0x16);
  } else {
    shader = shdList->getPostShdObj(0xf);
  }
  {
    shdList->bindTriangleTex();
    shader->setupShader(0u);
    grlib::CGLibUniformEtcUtility uniform(shader);
    uniform.setUseUniformBlock("U_POST");
    int location = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
    u32 scaleOffset = uniform.unknown001("gScal");
    u32 ofsOffset = uniform.unknown001("ofs[0]");
    u32 ratioOffset = uniform.unknown001("ratio");
    uniform.setF32SetVec4(scaleOffset, scale);
    uniform.setF32SetVec4(ratioOffset, dofParam);
    uniform.setF32SetF32Array(ofsOffset, ofs, count * 4);
    apCache->beginTexSampling(2, 1);
    apCache->setTexture(*unknown18->unknown70, location);
    uniform.updateData();
    uniform.setUniformBlock();
    shdList->renderTriangle();
    unknown20->setColorInvalidate();
    unknown28->setColorInvalidate();
  }
  unknown30->setRenderTarget();
  if (postParm->unknown21a) {
    shader = shdList->getPostShdObj(0x17);
  } else {
    shader = shdList->getPostShdObj(0x10);
  }
  shdList->bindTriangleTex();
  shader->setupShader(0u);
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  int nearLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
  int farLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("s1");
  u32 scaleOffset = uniform.unknown001("gScal");
  u32 ofsOffset = uniform.unknown001("ofs[0]");
  u32 ratioOffset = uniform.unknown001("ratio");
  int baseLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("s2");
  uniform.setF32SetVec4(scaleOffset, scale);
  for (s32 i = 0; i < count; i++) {
    ofs[i * 2] = (stepU * 0.5f + stepU * i) * -s;
    ofs[i * 2 + 1] = (stepV * 0.5f + stepV * i) * c;
  }
  uniform.setF32SetF32Array(ofsOffset, ofs, count * 4);
  uniform.setF32SetVec4(ratioOffset, dofParam);
  apCache->setTexture(*unknown20->unknown70, nearLocation);
  apCache->setTexture(*unknown28->unknown70, farLocation);
  apCache->setTexture(*unknown18->unknown70, baseLocation);
  uniform.updateData();
  uniform.setUniformBlock();
  shdList->renderTriangle();
  unknown30->setColorInvalidate();
}

void DrPixlPostObjDepthofField::renderCalc() {
  DrAPGxType::setupBlend(1);
  unknown08->unknown7f0->unknown138->setRenderTarget();
  DrShdMan *shdMan = unknown00->unknown80;
  DrAPCache *apCache = unknown00->unknown5c0;
  DrPixlPostParm *postParm = unknown00->unknown120[unknown00->unknown1c98];
  DrShdDataList *shdList = shdMan->unknown00;
  DrShdDataObj *shader = shdList->getPostShdObj(0x15);
  u32 autoFocus = postParm->unknown21c ? 1 : 2;
  shader->setDeclarationIdx(shader->getDeclarationOfs("AUTO_FOCUS"), autoFocus);
  shdList->bindTriangleTex();
  shader->setupShader(0u);
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  int colorLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
  int blurLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("s1");
  u32 sclOffset = uniform.unknown001("scl");
  u32 ratioOffset = uniform.unknown001("ratio");
  f32 width = static_cast<f32>(unknown30->unknownbc);
  f32 height = static_cast<f32>(unknown30->unknownc0);
  f32 work[4];
  work[0] = (width - 1.0f) / width;
  work[1] = (height - 1.0f) / height;
  work[2] = 1.0f / (width + width);
  work[3] = 1.0f / (height + height);
  uniform.setF32SetVec4(sclOffset, work);
  DrCalcViewWork *viewWork = unknown00->unknown580->unknown10;
  f32 focus = postParm->unknown224 / viewWork->unknown430.x + viewWork->unknown430.y;
  f32 range = postParm->unknown228 / viewWork->unknown430.x;
  work[0] = -focus;
  work[1] = -1.0f / range;
  work[2] = postParm->unknown234;
  work[3] = postParm->unknown22c;
  uniform.setF32SetVec4(ratioOffset, work);
  wkPixlManRes *res = unknown08->unknown7f0;
  DrPixlRenderTarget *colorBuff = postParm->m_TMAAOn ? res->unknown00[13][DrMan::s_nDblIdx] : res->unknown00[4][0];
  apCache->beginTexSampling(2, 0);
  apCache->setTexture(*colorBuff->unknown70, colorLocation);
  apCache->beginTexSampling(2, 1);
  apCache->setTexture(*unknown30->unknown70, blurLocation);
  if (postParm->unknown21c) {
    int ratioLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("ratTex");
    apCache->beginTexSampling(2, 0);
    apCache->setTexture(*unknown48->unknown70, ratioLocation);
  }
  uniform.updateData();
  uniform.setUniformBlock();
  shdList->renderTriangle();
  DrAPGxType::setupBlend(0);
}

} // namespace ml
