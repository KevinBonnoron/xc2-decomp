#include "dr/dr_pixl_sky_dome.h"

#include <string.h>

#include "dr/dr_ap_gx_type.h"
#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_fog_man.h"
#include "dr/dr_light_man.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_res_use_query_obj.h"
#include "dr/dr_shd_data_list.h"
#include "dr/dr_shd_data_obj.h"
#include "dr/dr_shd_man.h"
#include "grlib/cglib_uni_base_utility.h"
#include "mm_math/mm_col3.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec4.h"
#include "mm_mtl/fixed_array.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace ml {

DrPixlSkyDome::DrPixlSkyDome(DrMan *drMan)
    : unknown00(drMan), unknown08(nullptr), unknown10(0.0f), unknown14(0), unknown20(1.0f, 1.0f, 1.0f), unknown30(0.5f, 0.5f, 0.5f), unknown40(0.0f), unknown44(0), unknown48(0) {
  unknown08 = new (drMan->unknown0c) DrResUseQueryObj();
}

void DrPixlSkyDome::update() {
  unknown08->update();
  if (!unknown00->unknown580->unknown10->unknown9aa) {
    if (unknown08->m_pixel == 0) {
      unknown10 += (0.0f - unknown10) * 0.2f;
    } else {
      unknown10 += (1.0f - unknown10) * 0.5f;
    }
  } else {
    unknown10 = 1.0f;
    unknown14 = 3;
  }
  if (unknown14 > 0) {
    unknown14--;
    unknown10 = 1.0f;
  }
  updateUniform();
}

void DrPixlSkyDome::luminanceRender() {
  DrFogMan *fogMan = unknown00->unknown590;
  if (fogMan->isFogOn() && fogMan->unknownd1) {
    DrPixlPostParm *postParm = unknown00->unknown120[unknown00->unknown1c98];
    DrLightMan *lightMan = unknown00->unknown588;
    f32 ratio = postParm->unknown46c;
    f32 otherRatio = postParm->unknown468;
    mm::Vec4 color;
    color.x = ratio * lightMan->unknown12c.r + otherRatio * lightMan->unknown120.r;
    color.y = ratio * lightMan->unknown12c.g + otherRatio * lightMan->unknown120.g;
    color.z = ratio * lightMan->unknown12c.b + otherRatio * lightMan->unknown120.b;
    color.w = 0.0f;
    renderColorBackground(color);
  }
}

void DrPixlSkyDome::baseRender() {
  DrFogMan *fogMan = unknown00->unknown590;
  if (!fogMan->isFogOn()) {
    renderColorBackground(mm::Vec4(0.0f, 0.0f, 0.0f, 0.0f));
    return;
  }
  DrShdDataList *shdList = unknown00->unknown80->unknown00;
  bool isLuminance = fogMan->unknownd1;
  DrShdDataObj *shader = shdList->getPostShdObj(0x12);
  shader->setDeclarationIdx(shader->getDeclarationOfs("DEB_SKY_VISIBILITY"), 2);
  // The local places the select before the getDeclarationOfs call (0x7100850f98, ruling 1); with the select written in the call it comes after
  // (547 instructions, 548 with the local).
  u32 ambientIdx = isLuminance ? 2 : 1;
  shader->setDeclarationIdx(shader->getDeclarationOfs("DEB_SKY_AMBIENT"), ambientIdx);
  shader->setDeclarationIdx(shader->getDeclarationOfs("OUTPUT_VELOCITY"), 1);
  DrCalcViewWork *viewWork = unknown00->unknown580->unknown10;
  unknown00->unknown78->skyRenderTarget();
  DrAPGxType::setupStencilTest(true, false, 2, false, 0, 0, 2, 0, 0, 0);
  DrAPGxType::setupBlend(0);
  shdList->bindShdVertex();
  shader->setupShader(0u);
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  u32 projOffset = uniform.unknown001("proj");
  u32 parmOffset = uniform.unknown001("gParm[0]");
  uniform.setMat44SetMat44(projOffset, viewWork->unknown3c0);
  f32 parm[20];
  memcpy(parm, fogMan->unknown60, sizeof(parm));
  uniform.setF32SetF32Array(parmOffset, parm, 20);
  if (!isLuminance) {
    mm::Vec4 ambient = mm::Vec4::zero;
    u32 ambientOffset = uniform.unknown001("cSkyAmbient");
    uniform.setF32SetVec4(ambientOffset, &ambient.x);
  }
  u32 toPrevViewOffset = uniform.unknown001("gToPrevView");
  u32 prevProjOffset = uniform.unknown001("gPrevProj");
  u32 velocityOffset = uniform.unknown001("gVelocityParam");
  // The game loads the view work a second time here (0x71008511a0, after the three offset lookups) instead of keeping the first load alive. The product is a
  // named local: as a temporary passed to the call its return copy shares the slot of the velocity vector (frame 432 bytes, 448 in the game).
  DrCalcViewWork *view = unknown00->unknown580->unknown10;
  mm::Mat44 toPrevView = view->unknown00 * view->unknown280;
  uniform.setMat44SetMat44(toPrevViewOffset, toPrevView);
  mm::Mat44 prevProj = view->unknown380;
  uniform.setMat44SetMat44(prevProjOffset, prevProj);
  mm::Vec4 velocity = mm::Vec4::zero;
  velocity.x = view->unknown4cc;
  uniform.setF32SetVec4(velocityOffset, &velocity.x);
  uniform.updateData();
  uniform.setUniformBlock();
  shdList->renderQuads();
  unknown00->unknown78->endSkyRenderTarget();
}

// 0x71008517a8. The three fog values at 0xc0, 0xc4 and 0xc8 are read as unknown60[24] to unknown60[26] (the game loads them as floats at
// 0x71008517dc, 0x71008517e8 and 0x71008517f4). Each is tested with `fcmp s0, #0.0` then `b.hi` (greater or unordered, 0x71008517e4,
// 0x71008517f0): that is `!(x <= 0.0f)`, the NaN-correct test; a plain `x > 0.0f` gives `b.gt`.
void DrPixlSkyDome::godRayRender() {
  DrFogMan *fogMan = unknown00->unknown590;
  if (fogMan->isFogOn() && !(fogMan->unknown60[24] <= 0.0f && fogMan->unknown60[25] <= 0.0f && fogMan->unknown60[26] <= 0.0f)) {
    DrShdDataList *shdList = unknown00->unknown80->unknown00;
    DrShdDataObj *shader = shdList->getPostShdObj(0x14);
    DrCalcViewWork *viewWork = unknown00->unknown580->unknown10;
    DrAPGxType::setupStencilTest(true, false, 2, false, 0, 0, 2, 0, 0, 0);
    DrAPGxType::setupBlend(0);
    shdList->bindShdVertex();
    shader->setupShader(0u);
    grlib::CGLibUniformEtcUtility uniform(shader);
    uniform.setUseUniformBlock("U_POST");
    u32 projOffset = uniform.unknown001("proj");
    u32 parmOffset = uniform.unknown001("gParm[0]");
    uniform.setMat44SetMat44(projOffset, viewWork->unknown1c0);
    DrLightMan *lightMan = unknown00->unknown588;
    f32 parm[8];
    parm[0] = lightMan->unknown140.r;
    parm[1] = lightMan->unknown140.g;
    parm[2] = lightMan->unknown140.b;
    parm[3] = fogMan->unknown5c;
    parm[4] = fogMan->unknown60[24] * unknown10;
    parm[5] = unknown10 * fogMan->unknown60[25];
    parm[6] = fogMan->unknown60[26] * unknown10;
    parm[7] = 1.0f;
    uniform.setF32SetF32Array(parmOffset, parm, 8);
    unknown08->begin(unknown00->unknown78->unknown7f8);
    uniform.updateData();
    uniform.setUniformBlock();
    shdList->renderQuads();
    unknown08->end();
  }
}

DrPixlSkyDome::~DrPixlSkyDome() {
  if (unknown08 != nullptr) {
    delete unknown08;
    unknown08 = nullptr;
  }
}

void DrPixlSkyDome::renderColorBackground(const mm::Vec4 &color) {
  DrShdDataList *shdList = unknown00->unknown80->unknown00;
  DrShdDataObj *shader = shdList->getPostShdObj(18);
  shader->setDeclarationIdx(shader->getDeclarationOfs("DEB_SKY_VISIBILITY"), 2);
  shader->setDeclarationIdx(shader->getDeclarationOfs("DEB_SKY_AMBIENT"), 1);
  shader->setDeclarationIdx(shader->getDeclarationOfs("OUTPUT_VELOCITY"), 2);
  DrCalcViewWork *viewWork = unknown00->unknown580->unknown10;
  DrAPGxType::setupStencilTest(true, false, 2, false, 0, 0, 2, 0, 0, 0);
  DrAPGxType::setupBlend(0);
  shdList->bindShdVertex();
  shader->setupShader(0u);
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  u32 projOffset = uniform.unknown001("proj");
  u32 ambientOffset = uniform.unknown001("cSkyAmbient");
  uniform.setMat44SetMat44(projOffset, viewWork->unknown1c0);
  uniform.setF32SetVec4(ambientOffset, &color.x);
  uniform.updateData();
  uniform.setUniformBlock();
  shdList->renderQuads();
}

void DrPixlSkyDome::renderBackgroundCube() {}

} // namespace ml
