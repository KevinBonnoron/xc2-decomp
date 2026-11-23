#include "dr/dr_pixl_post_obj_volume.h"

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
#include "grlib/cglib_render_target.h"
#include "grlib/cglib_shader.h"
#include "grlib/cglib_uni_base_utility.h"
#include "mm_math/mm_vec4.h"
#include "mm_mtl/fixed_array.h"
#include "types.h"

namespace ml {

void DrPixlPostObjVolume::calculateSclDown() {
  if (m_drMan->unknown120[m_drMan->unknown1c98]->m_TMAAOn) {
    calculateSclDown_Temporal();
  } else {
    calculateSclDown_NonTemporal();
  }
}

void DrPixlPostObjVolume::volumeRender() {
  DrAPGxType::setupScreenQuads(false);
  calculateSclDown();
  grlib::CGLibCtlShader::setMemoryBarrierBit(2);
  calculateVolume();
}

DrPixlPostObjVolume::~DrPixlPostObjVolume() {
  unknown001(unknown18[0]);
  unknown001(unknown18[1]);
  unknown001(unknown28);
}

void DrPixlPostObjVolume::resetColorBuff() { calcColorBuff(); }

void DrPixlPostObjVolume::update() {}

void DrPixlPostObjVolume::releaseColorBuff() {
  if (unknown18[0] != nullptr) {
    unknown18[0]->releaseTexture();
  }
  if (unknown18[1] != nullptr) {
    unknown18[1]->releaseTexture();
  }
  unknown28->releaseTexture();
}

void DrPixlPostObjVolume::calculateSclDown_NonTemporal() {
  DrPixlRenderTarget *source = m_drPixlMan->unknown7f0->unknown00[7][0];
  source->setColorInvalidate();
  grlib::CGLibRenderTarget *target = unknown18[DrMan::s_nDblIdx];
  target->setRenderTarget();
  DrShdDataList *shdList = m_drMan->m_drShdMan->m_drShdDataList;
  DrShdDataObj *shader = shdList->getSelectShdObj(0);
  shdList->unknown002(shader);
  int location = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
  DrAPCache *apCache = m_drMan->m_drAPCache;
  apCache->beginTexSampling(2, 1);
  apCache->setTexture(*source->unknown70, location);
  shdList->renderQuads();
  target->setColorInvalidate();
}

// Inferred role: set once the first temporal scale down ran, the shader clears the target only before that; original name unknown. Game data
// without a symbol at 0x7101bd6f58 (read at 0x710085b04c, set at 0x710085b084).
static bool unknown005;

void DrPixlPostObjVolume::calculateSclDown_Temporal() {
  DrPixlRenderTarget *source = m_drPixlMan->unknown7f0->unknown00[7][0];
  source->setColorInvalidate();
  grlib::CGLibRenderTarget *target = unknown18[DrMan::s_nDblIdx];
  grlib::CGLibRenderTarget *previous = unknown18[DrMan::s_nDblStockIdx];
  DrShdDataList *shdList = m_drMan->m_drShdMan->m_drShdDataList;
  DrShdDataObj *shader = shdList->getPostShdObj(0x32);
  u32 execClear = unknown005 ? 2 : 1;
  shader->setDeclarationIdx(shader->getDeclarationOfs("DECL_EXEC_CLEAR"), execClear);
  if (!unknown005) {
    unknown005 = true;
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
  int currentLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTCurrent");
  int depthLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTDepth");
  int prevLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTPrev");
  int prevDepthLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTPrevDepth");
  f32 height = static_cast<f32>(target->unknownc0);
  f32 width = static_cast<f32>(target->unknownbc);
  // The game loads the view work between the two divisions of the first vector and keeps the five uniform vectors in 16 byte aligned stack slots (frame
  // 304 bytes, with an 8 byte gap above them): they are mm::Vec4 locals, float[4] arrays give a 288 byte frame.
  DrCalcViewWork *viewWork = m_drMan->m_drCalcMan->m_drCalcViewWork;
  mm::Vec4 fragCoordToUvValue;
  fragCoordToUvValue.x = 1.0f / width;
  fragCoordToUvValue.y = 1.0f / height;
  fragCoordToUvValue.z = 0.0f;
  fragCoordToUvValue.w = 0.0f;
  uniform.setF32SetVec4(fragCoordToUv, &fragCoordToUvValue.x);
  mm::Vec4 uvToScreenValue;
  uvToScreenValue.x = 2.0f;
  uvToScreenValue.y = 2.0f;
  uvToScreenValue.z = -1.0f;
  uvToScreenValue.w = -1.0f;
  uniform.setF32SetVec4(uvToScreen, &uvToScreenValue.x);
  mm::Vec4 screenToUvValue;
  screenToUvValue.x = 0.5f;
  screenToUvValue.y = 0.5f;
  screenToUvValue.z = 0.5f;
  screenToUvValue.w = 0.5f;
  uniform.setF32SetVec4(screenToUv, &screenToUvValue.x);
  mm::Vec4 viewPos;
  viewPos.y = tanf(viewWork->unknown4c4 * 0.5f);
  viewPos.x = viewPos.y * viewWork->unknown4c0;
  viewPos.z = 0.0f;
  viewPos.w = 0.0f;
  uniform.setF32SetVec4(screenToViewPos, &viewPos.x);
  uniform.setMat44SetMat44(invView, viewWork->unknown00);
  uniform.setMat44SetMat44(prevView, viewWork->unknown280);
  uniform.setMat44SetMat44(proj, viewWork->unknown380);
  mm::Vec4 paramValue;
  paramValue.x = 0.7388f;
  paramValue.y = 100.0f;
  paramValue.z = 0.0f;
  paramValue.w = 0.0f;
  uniform.setF32SetVec4(param, &paramValue.x);
  DrPixlPostMan *postMan = m_drMan->m_drPixlMan->unknown7f0->m_drPixlPostMan;
  DrAPCache *apCache = m_drMan->m_drAPCache;
  apCache->beginTexSampling(2, 1);
  apCache->setTexture(*postMan->unknownc0[DrMan::s_nDblIdx]->unknown70, depthLocation);
  apCache->setTexture(*postMan->unknownc0[DrMan::s_nDblStockIdx]->unknown70, prevDepthLocation);
  apCache->beginTexSampling(2, 1);
  apCache->setTexture(*source->unknown70, currentLocation);
  apCache->setTexture(*previous->unknown70, prevLocation);
  target->setRenderTarget();
  grlib::CGLibColorCtl::setBlendOffControl(GRL_LOGIC_TYPE_COPY);
  uniform.updateData();
  uniform.setUniformBlock();
  shdList->renderQuads();
  target->setColorInvalidate();
}

} // namespace ml
