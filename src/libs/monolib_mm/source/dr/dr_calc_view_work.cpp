#include "dr/dr_calc_view_work.h"

#include <string.h>

#include "dr/dr_ini_sys.h"
#include "dr/dr_light_man.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_render_target.h"
#include "dr/dr_res_mdo_uniform_block.h"
#include "grlib/cglib_texture_buffer.h"
#include "grlib/shd_util.h"
#include "mm_math/mm_col3.h"
#include "mm_math/mm_vec4.h"

namespace ml {

namespace _dcvwk {

f32 calcHaltonSequence(u32 index, u32 base) {
  f32 result = 0.0f;
  if (index != 0) {
    f32 fraction = 1.0f;
    bool hasNext;
    do {
      u32 next = index / base;
      fraction = fraction / (f32)base;
      hasNext = base <= index;
      result += fraction * (f32)(index - next * base);
      index = next;
    } while (hasNext);
  }
  return result;
}

} // namespace _dcvwk

void DrCalcViewWork::shadowBegin(const mm::Mat44 &matrix) {
  unknownc0 = matrix;
  unknownc0.rows[3][0] = unknownc0.rows[3][1] = 0.0f;
  unknownc0.rows[3][2] = 0.0f;
}

void DrCalcViewWork::shadowEnd() { memcpy(&unknownc0, &unknown140, 0x40); }

f32 DrCalcViewWork::getPixlLen(f32 depth, f32 length) const {
  f32 clipW = unknown180.rows[2][3] * depth + unknown180.rows[3][3];
  return unknown4d0 * length / -clipW;
}

int DrCalcViewWork::unistatic_view(f32 *work, bool isJitter) {
  grlib::ShdMat44TransposeMat34(work, unknown40);
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_VIEW];
}

int DrCalcViewWork::unistatic_proj(f32 *work, bool isJitter) {
  grlib::ShdMat44TransposeMat44(work, isJitter ? unknown180 : unknown380);
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_PROJ];
}

int DrCalcViewWork::unistatic_viewproj(f32 *work, bool isJitter) {
  grlib::ShdMat44TransposeMat44(work, isJitter ? unknown200 : unknown340);
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_VIEW_PROJ];
}

int DrCalcViewWork::unistatic_invview(f32 *work, bool isJitter) {
  grlib::ShdMat44TransposeMat34(work, unknown00);
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_INV_VIEW];
}

int DrCalcViewWork::unistatic_billborad_Def(f32 *work, bool isJitter) {
  grlib::ShdMat44TransposeMat34(work, unknownc0);
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_BILLBOARD_DEF];
}

int DrCalcViewWork::unistatic_billborad_YVec(f32 *work, bool isJitter) {
  grlib::ShdMat44TransposeMat34(work, unknown240);
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_BILLBOARD_Y_VEC];
}

int DrCalcViewWork::unistatic_viewYvec(f32 *work, bool isJitter) {
  work[0] = unknown460.x;
  work[1] = unknown460.y;
  work[2] = unknown460.z;
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_VIEW_Y_VEC];
}

int DrCalcViewWork::unistatic_jitter(f32 *work, bool isJitter) {
  work[0] = unknownae0[0];
  work[1] = unknownae0[1];
  work[2] = unknownaf0[0];
  work[3] = unknownaf0[1];
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_JITTER];
}

int DrCalcViewWork::unistatic_dither_tmaa_val(f32 *work, bool isJitter) {
  grlib::ShdF32SetVec4(work, unknownb00);
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_DITHER_TMAA_VAL];
}

int DrCalcViewWork::unistatic_proj_non_jitter(f32 *work, bool isJitter) {
  grlib::ShdMat44TransposeMat44(work, unknown380);
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_PROJ_NON_JITTER];
}

int DrCalcViewWork::unistatic_diff_pre_orijmat(f32 *work, bool isJitter) {
  grlib::ShdMat44TransposeMat44(work, unknown300);
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_DIFF_PRE_ORIJ_MAT];
}

int DrCalcViewWork::unistatic_lightNotUse(f32 *work) {
  work[0] = 0.0f;
  work[1] = 0.0f;
  work[2] = 0.0f;
  work[3] = 0.0f;
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_LIGHT_NOT_USE];
}

int DrCalcViewWork::unistatic_depth_change(f32 *work, bool isJitter) {
  work[0] = unknown430.x;
  work[1] = unknown430.y;
  work[2] = unknown430.z;
  work[3] = unknown700->unknown78->unknown00;
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_UNKNOWN_25];
}

int DrCalcViewWork::unistatic_lightAmb(f32 *work) {
  DrLightMan *lightMan = unknown700->unknown588;
  work[0] = lightMan->unknown12c.r;
  work[1] = lightMan->unknown12c.g;
  work[2] = lightMan->unknown12c.b;
  work[3] = 1.0f;
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_UNKNOWN_30];
}

int DrCalcViewWork::unistatic_diffuseIBL(f32 *work) {
  mm::Mat44 matrices[3];
  memset(matrices, 0, sizeof(matrices));
  grlib::ShdMat44TransposeMat44Array(work, matrices, 3);
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_UNKNOWN_58];
}

int DrCalcViewWork::unistatic_dither_param(f32 *work) {
  mm::Vec4 value;
  value.x = 1.0f;
  value.y = 0.0f;
  value.z = unknownb10[0];
  value.w = unknownb10[1];
  grlib::ShdVec4SetVec4(work, value);
  return 4;
}

int DrCalcViewWork::unistatic_inv_dither_param(f32 *work) {
  mm::Vec4 value;
  value.x = -1.0f;
  value.y = 1.0f;
  value.z = unknownb10[0];
  value.w = unknownb10[1];
  grlib::ShdVec4SetVec4(work, value);
  return 4;
}

void DrCalcViewWork::renderEnd() {
  if (unknown9ad) {
    unknown9ad = false;
  }
  memcpy(&unknown280, &unknown40, 0x40);
  memcpy(&unknown100, &unknownc0, 0x40);
}

int DrCalcViewWork::unistatic_mpf_ViewProj(f32 *work) {
  grlib::ShdMat44TransposeMat44(work, unknown200);
  return 16;
}

int DrCalcViewWork::unistatic_mpf_OldViewProj(f32 *work) {
  grlib::ShdMat44TransposeMat44(work, unknown2c0);
  return 16;
}

int DrCalcViewWork::unistatic_mpf_View(f32 *work) {
  grlib::ShdMat44TransposeMat34(work, unknown40);
  return 12;
}

int DrCalcViewWork::unistatic_mpf_BiiMat(f32 *work) {
  grlib::ShdMat44TransposeMat34(work, unknownc0);
  return 12;
}

int DrCalcViewWork::unistatic_mpf_OldBiiMat(f32 *work) {
  grlib::ShdMat44TransposeMat34(work, unknown100);
  return 12;
}

int DrCalcViewWork::unistatic_mpf_DepthParm(f32 *work) {
  work[0] = unknown430.x;
  work[1] = unknown430.y;
  work[2] = unknown430.z;
  work[3] = 0.0f;
  return 4;
}

int DrCalcViewWork::unistatic_mpf_ViewYVec(f32 *work) {
  work[0] = unknown460.x;
  work[1] = unknown460.y;
  work[2] = unknown460.z;
  work[3] = 0.0f;
  return 4;
}

int DrCalcViewWork::unistatic_mpf_ViewPos(f32 *work) {
  work[0] = unknown400.x;
  work[1] = unknown400.y;
  work[2] = unknown400.z;
  work[3] = 1.0f;
  return 4;
}

int DrCalcViewWork::unistatic_mpf_OldViewPos(f32 *work) {
  work[0] = unknown770.x;
  work[1] = unknown770.y;
  work[2] = unknown770.z;
  work[3] = 1.0f;
  return 4;
}

int DrCalcViewWork::unistatic_digher_val(f32 *work, bool isJitter) {
  grlib::CGLibTextureBuffer &texture = unknown700->unknown70->unknown98[1];
  f32 width = texture.getWidth();
  f32 height = texture.getHeight();
  work[0] = unknown700->unknown5b8->unknown18 * 0.25f;
  work[1] = (1.0f / height) * unknown700->unknown5b8->unknown1c;
  work[2] = 4.0f / width;
  work[3] = width * 0.25f;
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_UNKNOWN_26];
}

int DrCalcViewWork::unistatic_screenSize(f32 *work, bool isJitter) {
  mm::Vec4 value = mm::Vec4::unit;
  DrPixlRenderTarget *target = unknown700->unknown78->getPixlObj(5);
  if (target != nullptr) {
    value.x = target->unknownbc;
    value.y = target->unknownc0;
    value.x = 1.0f / value.x;
    value.y = 1.0f / value.y;
    value.z = 0.0f;
    value.w = 0.0f;
  }
  grlib::ShdF32SetVec4(work, &value.x);
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_UNKNOWN_62];
}

int DrCalcViewWork::unistatic_mpf_Fade(f32 *work) {
  grlib::ShdF32SetF32Array(work, unknown490, 12);
  return 48;
}

} // namespace ml
