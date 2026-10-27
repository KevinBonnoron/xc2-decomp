#include "dr/dr_pixl_post_obj_3d_lut.h"

#include "dr/dr_ap_cache.h"
#include "dr/dr_ap_gx_type.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_res_filter_data.h"
#include "dr/dr_shd_data_list.h"
#include "dr/dr_shd_data_obj.h"
#include "dr/dr_shd_man.h"
#include "grlib/cglib_color_ctl.h"
#include "grlib/cglib_ctl_shader.h"
#include "grlib/cglib_etc_uniform_block.h"
#include "grlib/cglib_render_volume.h"
#include "grlib/cglib_shader.h"
#include "grlib/cglib_uni_base_utility.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {

DrPixlPostObj3dLut::~DrPixlPostObj3dLut() {
  grlib::CGLibRenderVolume *volume = unknown20[0];
  if (volume != nullptr) {
    volume->releaseWork();
    delete volume;
    unknown20[0] = nullptr;
  }
  volume = unknown20[1];
  if (volume != nullptr) {
    volume->releaseWork();
    delete volume;
    unknown20[1] = nullptr;
  }
}

void DrPixlPostObj3dLut::update() {}

void DrPixlPostObj3dLut::render(bool isFirst, bool isSecond) {
  render_applyLUT(isFirst, isSecond);
  unknown18 = false;
}

void DrPixlPostObj3dLut::renderLUT() {
  render_updateLUT();
  grlib::CGLibCtlShader::setMemoryBarrierBit(2);
  unknown18 = true;
}

void DrPixlPostObj3dLut::render_updateLUT() {
  DrPixlPostParm *postParm = unknown00->unknown120[unknown00->unknown1c98];
  f32 farRatio = postParm->unknown298;
  DrResFilterData *filterData = unknown00->unknown98;
  DrAPCache *apCache = unknown00->unknown5c0;
  f32 nearRatio = postParm->unknown294;
  DrAPGxType::setupScreenQuads(false);
  DrShdDataList *shdList = unknown00->unknown80->unknown00;
  grlib::CGLibRenderVolume *nearVolume = unknown20[0];
  grlib::CGLibRenderVolume *farVolume = unknown20[1];
  shdList->bindQuadsTex();
  DrShdDataObj *shader = shdList->getPostShdObj(0x4b);
  shader->setupShader(0u);
  int curNear = (shader->unknown38 + shader->unknown58)->getTextureLocation("t3dCurNear");
  int curFar = (shader->unknown38 + shader->unknown58)->getTextureLocation("t3dCurFar");
  int oldNear = (shader->unknown38 + shader->unknown58)->getTextureLocation("t3dOldNear");
  int oldFar = (shader->unknown38 + shader->unknown58)->getTextureLocation("t3dOldFar");
  grlib::CGLibTextureBuffer *curNearTexture = filterData->findFilterTexture(postParm->unknown26c);
  grlib::CGLibTextureBuffer *curFarTexture = filterData->findFilterTexture(postParm->unknown278);
  grlib::CGLibTextureBuffer *oldNearTexture = filterData->findFilterTexture(postParm->unknown28c);
  grlib::CGLibTextureBuffer *oldFarTexture = filterData->findFilterTexture(postParm->unknown290);
  apCache->begin3DTexturePointSampling();
  apCache->setTexture(*curNearTexture, curNear);
  apCache->setTexture(*curFarTexture, curFar);
  apCache->setTexture(*oldNearTexture, oldNear);
  apCache->setTexture(*oldFarTexture, oldFar);
  if (farRatio < 1.0f) {
    grlib::CGLibColorCtl::setBlendControl(GRL_BLEND_FUNC_SRC_ALPHA, GRL_BLEND_FUNC_ONE_MINUS_SRC_ALPHA, GRL_BLEND_COMBINE_ADD, GRL_LOGIC_TYPE_COPY);
    grlib::CGLibColorCtl::setMrtBlend(3, GRL_LOGIC_TYPE_COPY);
  } else {
    grlib::CGLibColorCtl::setBlendOffControl(GRL_LOGIC_TYPE_COPY);
  }
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  u32 offset = uniform.unknown001("ratio");
  for (u32 slice = 0; slice < nearVolume->unknown8c; slice++) {
    if (slice != 0) {
      uniform.unknown20.Rebuilding();
      static_cast<grlib::CGLibUniBaseUtility &>(uniform).setMoveMem();
    }
    f32 ratio[4];
    ratio[0] = farRatio;
    ratio[1] = (static_cast<f32>(slice) + 0.5f) / static_cast<f32>(nearVolume->unknown8c);
    ratio[2] = nearRatio;
    ratio[3] = 0.0f;
    uniform.setF32SetVec4(offset, ratio);
    uniform.updateData();
    uniform.setUniformBlock();
    nearVolume->setRenderTarget(slice, *farVolume);
    shdList->renderQuads();
  }
}

} // namespace ml
