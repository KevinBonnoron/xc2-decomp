#include "dr/dr_shd_lgt_obj.h"

#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_man.h"
#include "dr/dr_res_fetch.h"
#include "grlib/cglib_ctl_shader.h"
#include "grlib/cglib_shader.h"
#include "grlib/cglib_shd_list.h"
#include "grlib/shd_util.h"
#include "mm_math/mm_mat44.h"

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

void DrShdLgtObj::setShaderGlobalIBLIndexVS(DrMan *man, const mm::Mat44 &matrix, u8 *buffer, u32 index) {
  DrCalcViewWork *viewWork = man->unknown580->unknown10;
  u32 offset = (unknown38 + unknown58)->getUniformBlockValOfs(index, "gWVP");
  if (offset != 0xffffffff) {
    mm::Mat44 wvp;
    wvp.unknown009(matrix, viewWork->unknown200);
    grlib::ShdMat44SetMat44(reinterpret_cast<f32 *>(buffer + offset), wvp);
  }
}

} // namespace ml

template class grlib::CGLibShdListBase<ml::DrShdLgtObj>;
