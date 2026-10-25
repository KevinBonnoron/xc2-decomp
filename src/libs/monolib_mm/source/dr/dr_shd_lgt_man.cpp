#include "dr/dr_shd_lgt_man.h"

#include "dr/dr_shd_lgt_global_ibl.h"
#include "dr/dr_shd_lgt_obj.h"
#include "grlib/cglib_ctl_shader.h"

namespace ml {

DrShdLgtHybrid *DrShdLgtMan::getHybridLight() { return m_hybridLight; }

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

} // namespace ml
