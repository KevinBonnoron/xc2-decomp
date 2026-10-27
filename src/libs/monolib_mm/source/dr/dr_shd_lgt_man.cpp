#include "dr/dr_shd_lgt_man.h"

#include "dr/dr_ap_gx_type.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_shd_lgt_clustered.h"
#include "dr/dr_shd_lgt_global_ibl.h"
#include "dr/dr_shd_lgt_hybrid.h"
#include "dr/dr_shd_lgt_obj.h"
#include "grlib/cglib_ctl_shader.h"

namespace ml {

DrShdLgtHybrid *DrShdLgtMan::getHybridLight() { return m_hybridLight; }

const char *DrShdLgtMan::getDeclarationName(DECLARATION type) const { return s_DeclarationNames[type]; }

void DrShdLgtMan::renderBegin() {
  unknown42 = 0xffff;
  unknown44 = 0xffff;
  unknown48 = 0xffffffff;
  unknown40 = 1;
}

void DrShdLgtMan::beforeUpdateCate(int viewNum) { unknown58->update(viewNum); }

void DrShdLgtMan::resetColorBuff(int index) {
  DrShdLgtGlobalIBL *globalIBL = unknown58;
  if (globalIBL != nullptr) {
    globalIBL->resetColorBuff(index);
  }
}

void DrShdLgtMan::setupLocalIBLShader(DrShdLgtObj *obj) { grlib::CGLibCtlShader::setShader(*obj, unknown30); }

void DrShdLgtMan::setupGlobalIBLShader(DrShdLgtObj *obj) { grlib::CGLibCtlShader::setShader(*obj, unknown30); }

DrShdLgtObj *DrShdLgtMan::getGlobalIBLShader(GIBL_SHADER_TYPE type) { return &unknown20[type]; }

DrShdLgtObj *DrShdLgtMan::getComputeShader(COMP_SHADER_TYPE type) { return &unknown28[type]; }

void DrShdLgtMan::stockBegin() {
  m_hybridLight->stockBegin();
  unknown60->stockBegin();
}

void DrShdLgtMan::stockEnd() {
  m_hybridLight->stockEnd();
  unknown60->stockEnd();
}

void DrShdLgtMan::updateCate(int cate) {
  m_hybridLight->update();
  unknown60->update();
}

void DrShdLgtMan::setupCate(int cate) {
  m_hybridLight->setupCate(cate);
  unknown60->setupCate(cate);
}

void DrShdLgtMan::addViewInfo(int cate) {
  m_hybridLight->addViewInfo(cate);
  unknown60->addViewInfo(cate);
}

void DrShdLgtMan::delViewInfo(int cate) {
  m_hybridLight->delViewInfo(cate);
  unknown60->delViewInfo(cate);
  unknown58->delViewInfo(cate);
}

void DrShdLgtMan::setupLgtBuff() {
  if (unknown48 != 0) {
    unknown48 = 0;
    DrAPGxType::setupCullingOff();
    DrAPGxType::setupBlend(7);
    unknown00->unknown78->selectLightRenderTarget();
  }
}

} // namespace ml
