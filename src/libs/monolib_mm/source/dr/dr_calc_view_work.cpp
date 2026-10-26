#include "dr/dr_calc_view_work.h"

#include <string.h>

#include "dr/dr_res_mdo_uniform_block.h"
#include "grlib/shd_util.h"

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

int DrCalcViewWork::unistatic_mpf_Fade(f32 *work) {
  grlib::ShdF32SetF32Array(work, unknown490, 12);
  return 48;
}

} // namespace ml
