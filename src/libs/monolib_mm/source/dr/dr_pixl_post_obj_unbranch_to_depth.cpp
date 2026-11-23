#include "dr/dr_pixl_post_obj_unbranch_to_depth.h"

#include "dr/dr_ap_cache.h"
#include "dr/dr_ap_gx_type.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_post_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_pixl_render_target.h"
#include "dr/dr_shd_data_list.h"
#include "dr/dr_shd_data_obj.h"
#include "dr/dr_shd_man.h"
#include "grlib/cglib_color_ctl.h"
#include "grlib/cglib_depth_target.h"
#include "grlib/cglib_shader.h"
#include "grlib/cglib_uni_base_utility.h"
#include "mm_math/mm_vec4.h"
#include "mm_mtl/fixed_array.h"
#include "types.h"

namespace ml {

DrPixlPostObjUnbranchToDepth::DrPixlPostObjUnbranchToDepth(DrMan *drMan, DrPixlMan *pixlMan, DrPixlPostMan *postMan) : DrPixlPostObj(drMan, pixlMan, postMan) {}

DrPixlPostObjUnbranchToDepth::~DrPixlPostObjUnbranchToDepth() {}

void DrPixlPostObjUnbranchToDepth::debugRender() {}

void DrPixlPostObjUnbranchToDepth::resetColorBuff() {}

void DrPixlPostObjUnbranchToDepth::update() {}

void DrPixlPostObjUnbranchToDepth::render() {
  renderFull();
  if (m_drMan->unknown1e10) {
    renderQuater();
  }
}

void DrPixlPostObjUnbranchToDepth::renderFull() {
  DrShdDataList *shdList = m_drMan->m_drShdMan->m_drShdDataList;
  DrShdDataObj *shader = shdList->getPostShdObj(0x3e);
  shader->setupShader(0u);
  m_drMan->m_drPixlMan->unknown7f0->unknown1b8->setRenderTarget();
  DrAPCache *apCache = m_drMan->m_drAPCache;
  DrPixlRenderTarget *etc = m_drMan->m_drPixlMan->getPixlObj(1);
  DrPixlRenderTarget *color = m_drMan->m_drPixlMan->getPixlObj(0);
  int etcLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTEtc");
  int stencilLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTStencil");
  int colorLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTCol");
  apCache->setTexture(*etc->unknown70, etcLocation);
  apCache->setTexture(*color->unknown70, colorLocation);
  apCache->setTexture(*m_drMan->m_drPixlMan->getDepthObj()->unknown130, stencilLocation);
  DrAPGxType::setupDepthContl(true, true, 7);
  shdList->bindTriangle();
  grlib::CGLibColorCtl::setColorBufferOff();
  shdList->renderTriangle();
  grlib::CGLibColorCtl::setColorBufferOn();
}

void DrPixlPostObjUnbranchToDepth::renderQuater() {
  DrShdDataList *shdList = m_drMan->m_drShdMan->m_drShdDataList;
  DrShdDataObj *shader = shdList->getPostShdObj(0x45);
  shader->setupShader(0u);
  m_drMan->m_drPixlMan->unknown7f0->unknown1c0->setRenderTarget();
  DrAPCache *apCache = m_drMan->m_drAPCache;
  DrPixlRenderTarget *etc = m_drMan->m_drPixlMan->getPixlObj(1);
  DrPixlRenderTarget *color = m_drMan->m_drPixlMan->getPixlObj(0);
  int etcLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTEtc");
  int stencilLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTStencil");
  int colorLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTCol");
  int downDepthLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTDownDepth");
  apCache->beginTexSampling(2, 0);
  apCache->setTexture(*etc->unknown70, etcLocation);
  apCache->setTexture(*color->unknown70, colorLocation);
  apCache->setTexture(*m_drMan->m_drPixlMan->getDepthObj()->unknown130, stencilLocation);
  apCache->setTexture(*m_drMan->m_drPixlMan->unknown7f0->m_drPixlPostMan->getDownDepth()->unknown70, downDepthLocation);
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  u32 scaleOffset = uniform.unknown001("gScal");
  u32 paramOffset = uniform.unknown001("gParam");
  DrPixlPostParm *postParm = m_drMan->unknown120[m_drMan->unknown1c98];
  mm::Vec4 value;
  value.x = 1.0f;
  value.y = 1.0f;
  value.z = 0.0f;
  value.w = 0.0f;
  uniform.setVec4SetVec4(scaleOffset, value);
  value.x = postParm->unknown101c;
  value.w = 0.0f;
  value.y = 0.0f;
  value.z = 0.0f;
  uniform.setVec4SetVec4(paramOffset, value);
  uniform.updateData();
  uniform.setUniformBlock();
  DrAPGxType::setupDepthContl(true, true, 7);
  shdList->bindTriangleTex();
  grlib::CGLibColorCtl::setColorBufferOff();
  shdList->renderTriangle();
  grlib::CGLibColorCtl::setColorBufferOn();
}

} // namespace ml
