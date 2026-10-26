#include "dr/dr_shd_lgt_obj.h"

#include "dr/dr_res_fetch.h"
#include "grlib/cglib_ctl_shader.h"

namespace ml {

DrShdLgtObj::DrShdLgtObj() : unknown148(~0ull), unknown150(~0ull) {}

void DrShdLgtObj::shaderComputeSetup() { grlib::CGLibCtlShader::setComputeShader(*this); }

void DrShdLgtObj::shaderSetup(DrResFetch *fetch) { grlib::CGLibCtlShader::setShader(*this, *fetch); }

} // namespace ml
