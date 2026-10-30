#include "dr/dr_shd_lgt_obj.h"

#include "dr/dr_res_fetch.h"
#include "grlib/cglib_ctl_shader.h"
#include "grlib/cglib_shd_list.h"

namespace ml {

DrShdLgtObj::~DrShdLgtObj() { lgtRelease(); }

DrShdLgtObj::DrShdLgtObj() : unknown148(~0ull), unknown150(~0ull) {}

void DrShdLgtObj::shaderComputeSetup() { grlib::CGLibCtlShader::setComputeShader(*this); }

void DrShdLgtObj::shaderSetup(DrResFetch *fetch) { grlib::CGLibCtlShader::setShader(*this, *fetch); }

void DrShdLgtObj::lgtRelease() {
  for (int i = 0; i < 4; i++) {
    unknown68[i].release();
  }
  unknown148 = ~0ull;
  unknown150 = ~0ull;
  CGLibDecShader::release();
}

} // namespace ml

template class grlib::CGLibShdListBase<ml::DrShdLgtObj>;
