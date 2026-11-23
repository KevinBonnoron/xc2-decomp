#include "dr/dr_pixl_post_obj_motion_blur.h"

#include "dr/dr_ap_cache.h"
#include "dr/dr_ap_gx_type.h"
#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_post_obj.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_pixl_render_target.h"
#include "dr/dr_shd_data_list.h"
#include "dr/dr_shd_data_obj.h"
#include "dr/dr_shd_man.h"
#include "grlib/cglib_render_target.h"
#include "grlib/cglib_shader.h"
#include "grlib/cglib_uni_base_utility.h"
#include "grlib/shd_util.h"
#include "mm_mtl/fixed_array.h"
#include "mtl/alloc_handle.h"

namespace ml {
class DrPixlPostMan;

DrPixlPostObjMotionBlur::DrPixlPostObjMotionBlur(DrMan *drMan, DrPixlMan *pixlMan, DrPixlPostMan *postMan)
    : DrPixlPostObj(drMan, pixlMan, postMan), unknown20(nullptr), unknown28(nullptr), unknown30(nullptr) {
  unknown28 = new (m_drMan->unknown0c) DrPixlRenderTarget(m_drMan);
  unknown30 = new (m_drMan->unknown0c) DrPixlRenderTarget(m_drMan);
  unknown20 = new (m_drMan->unknown0c) DrPixlRenderTarget(m_drMan);
  calcBludBuffColorBuff();
  m_cGLibDblUniformBlock.setup(0x50);
  unknown18 = 0.0f;
  unknown1c = 0.0f;
}

DrPixlPostObjMotionBlur::~DrPixlPostObjMotionBlur() {
  unknown001(unknown28);
  unknown001(unknown30);
  unknown001(unknown20);
}

void DrPixlPostObjMotionBlur::debugRender() {}

void DrPixlPostObjMotionBlur::resetColorBuff() { calcBludBuffColorBuff(); }

void DrPixlPostObjMotionBlur::releaseColorBuff() {
  unknown28->releaseTexture();
  unknown30->releaseTexture();
  unknown20->releaseTexture();
}

void DrPixlPostObjMotionBlur::render() {
  DrAPGxType::setupScreenQuads(false);
  calcBlurWork();
  calcObjMotionBlur();
  renderCalcBlur();
  lastRender();
}

void DrPixlPostObjMotionBlur::calcObjMotionBlur() {
  DrPixlPostParm *postParm = m_drMan->unknown120[m_drMan->unknown1c98];
  if (!m_drMan->m_drCalcMan->m_drCalcViewWork->unknown9a9 && postParm->unknown1cd && 0.0f < postParm->unknown1ec) {
    calcVelocityBlur();
  }
  m_drMan->blurCallBackRender();
  unknown28->setColorInvalidate();
}

void DrPixlPostObjMotionBlur::renderCalcBlur() {
  DrAPGxType::setupScreenQuads(false);
  unknown20->setRenderTarget();
  DrShdDataList *shdList = m_drMan->m_drShdMan->m_drShdDataList;
  DrPixlPostParm *postParm = m_drMan->unknown120[m_drMan->unknown1c98];
  // The game has one getPostShdObj call after a branch that sets w1 to 0x1d or 0xe (0x7100858aa8..0x7100858abc). Only a call in each arm gives that
  // shape (clang sinks the common call). `getPostShdObj(postParm->unknown1cf ? 0x1d : 0xe)` becomes a select (138 instructions, first difference at
  // 0x7100858aa0) and so does an index variable assigned in the arms (cmp instead of cbz at 0x7100858aa8). The if/else form is the one of the two
  // arms in DrPixlPostObjDepthofField on main.
  DrShdDataObj *shader;
  if (postParm->unknown1cf) {
    shader = shdList->getPostShdObj(0x1d);
  } else {
    shader = shdList->getPostShdObj(0xe);
  }
  shdList->bindTriangleTex();
  shader->setupShader(0u);
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  int frameLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
  int velocityLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("s1");
  u32 ofsOffset = uniform.unknown001("ofs[0]");
  f32 velocityHeight = static_cast<f32>(unknown28->unknownc0);
  DrPixlRenderTarget *target = m_drPixlMan->unknown7f0->unknown138;
  f32 velocityWidth = static_cast<f32>(unknown28->unknownbc);
  DrAPCache *apCache = m_drMan->m_drAPCache;
  f32 targetHeight = static_cast<f32>(target->unknownc0);
  f32 targetWidth = static_cast<f32>(target->unknownbc);
  f32 ofs[8];
  ofs[0] = (targetWidth - 1.0f) / targetWidth;
  ofs[1] = (targetHeight - 1.0f) / targetHeight;
  ofs[2] = 1.0f / (targetWidth + targetWidth);
  ofs[3] = 1.0f / (targetHeight + targetHeight);
  ofs[4] = (velocityWidth - 1.0f) / velocityWidth;
  ofs[5] = (velocityHeight - 1.0f) / velocityHeight;
  ofs[6] = 1.0f / (velocityWidth + velocityWidth);
  ofs[7] = 1.0f / (velocityHeight + velocityHeight);
  uniform.setF32SetF32Array(ofsOffset, ofs, 8);
  apCache->beginTexSampling(2, 1);
  apCache->setTexture(*m_drPixlMan->unknown7f0->unknown138->unknown70, frameLocation);
  apCache->setTexture(*unknown28->unknown70, velocityLocation);
  uniform.updateData();
  uniform.setUniformBlock();
  shdList->renderTriangle();
  unknown20->setColorInvalidate();
}

void DrPixlPostObjMotionBlur::lastRender() {
  m_drPixlMan->unknown7f0->unknown138->setRenderTarget();
  DrAPGxType::setupBlend(1);
  DrShdDataList *shdList = m_drMan->m_drShdMan->m_drShdDataList;
  DrShdDataObj *shader = shdList->unknown001();
  shdList->bindTriangleTex();
  shader->setupShader(0u);
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  u32 scaleOffset = uniform.unknown001("gScal");
  f32 height = static_cast<f32>(unknown20->unknownc0);
  f32 width = static_cast<f32>(unknown20->unknownbc);
  f32 scale[4];
  scale[0] = (width - 1.0f) / width;
  scale[1] = (height - 1.0f) / height;
  scale[2] = 1.0f / (width + width);
  scale[3] = 1.0f / (height + height);
  // The game calls getBuff() and adds the byte offset itself (0x7100858dbc), without the offset test of setF32SetVec4. getBuff() returns u8 * (grlib,
  // reserved), so the cast is the one of CGLibUniBaseUtility's own setters (cglib_uni_base_utility.cpp); no typed form adds a byte offset.
  grlib::ShdF32SetVec4(reinterpret_cast<f32 *>(uniform.getBuff() + scaleOffset), scale);
  uniform.updateData();
  uniform.setUniformBlock();
  int location = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
  DrAPCache *apCache = m_drMan->m_drAPCache;
  apCache->beginTexSampling(2, 1);
  apCache->setTexture(*unknown20->unknown70, location);
  shdList->renderTriangle();
  DrAPGxType::setupBlend(0);
}
} // namespace ml
