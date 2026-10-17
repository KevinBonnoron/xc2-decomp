#include "dr/dr_calc_view_work.h"

#include "dr/dr_res_mdo_uniform_block.h"
#include "grlib/shd_util.h"

namespace ml {

f32 DrCalcViewWork::getPixlLen(f32 depth, f32 length) const {
  f32 clipW = m_proj.rows[2][3] * depth + m_proj.rows[3][3];
  return m_pixlScale * length / -clipW;
}

int DrCalcViewWork::unistatic_view(f32 *work, bool isJitter) {
  grlib::ShdMat44TransposeMat34(work, m_view);
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_VIEW];
}

int DrCalcViewWork::unistatic_proj(f32 *work, bool isJitter) {
  grlib::ShdMat44TransposeMat44(work, isJitter ? m_proj : m_projNonJitter);
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_PROJ];
}

int DrCalcViewWork::unistatic_viewproj(f32 *work, bool isJitter) {
  grlib::ShdMat44TransposeMat44(work, isJitter ? m_viewProj : m_viewProjNonJitter);
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_VIEW_PROJ];
}

int DrCalcViewWork::unistatic_invview(f32 *work, bool isJitter) {
  grlib::ShdMat44TransposeMat34(work, m_invView);
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_INV_VIEW];
}

int DrCalcViewWork::unistatic_billborad_Def(f32 *work, bool isJitter) {
  grlib::ShdMat44TransposeMat34(work, m_billboard);
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_BILLBOARD_DEF];
}

int DrCalcViewWork::unistatic_billborad_YVec(f32 *work, bool isJitter) {
  grlib::ShdMat44TransposeMat34(work, m_billboardYVec);
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_BILLBOARD_Y_VEC];
}

int DrCalcViewWork::unistatic_viewYvec(f32 *work, bool isJitter) {
  work[0] = m_viewYVec.x;
  work[1] = m_viewYVec.y;
  work[2] = m_viewYVec.z;
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_VIEW_Y_VEC];
}

int DrCalcViewWork::unistatic_jitter(f32 *work, bool isJitter) {
  work[0] = m_jitter[0];
  work[1] = m_jitter[1];
  work[2] = m_prevJitter[0];
  work[3] = m_prevJitter[1];
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_JITTER];
}

int DrCalcViewWork::unistatic_dither_tmaa_val(f32 *work, bool isJitter) {
  grlib::ShdF32SetVec4(work, m_ditherTmaaValues);
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_DITHER_TMAA_VAL];
}

int DrCalcViewWork::unistatic_proj_non_jitter(f32 *work, bool isJitter) {
  grlib::ShdMat44TransposeMat44(work, m_projNonJitter);
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_PROJ_NON_JITTER];
}

int DrCalcViewWork::unistatic_diff_pre_orijmat(f32 *work, bool isJitter) {
  grlib::ShdMat44TransposeMat44(work, m_diffPreOrijMatrix);
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
  grlib::ShdMat44TransposeMat44(work, m_viewProj);
  return 16;
}

int DrCalcViewWork::unistatic_mpf_OldViewProj(f32 *work) {
  grlib::ShdMat44TransposeMat44(work, m_prevViewProj);
  return 16;
}

int DrCalcViewWork::unistatic_mpf_View(f32 *work) {
  grlib::ShdMat44TransposeMat34(work, m_view);
  return 12;
}

int DrCalcViewWork::unistatic_mpf_BiiMat(f32 *work) {
  grlib::ShdMat44TransposeMat34(work, m_billboard);
  return 12;
}

int DrCalcViewWork::unistatic_mpf_OldBiiMat(f32 *work) {
  grlib::ShdMat44TransposeMat34(work, m_prevBillboard);
  return 12;
}

int DrCalcViewWork::unistatic_mpf_DepthParm(f32 *work) {
  work[0] = m_depthParm.x;
  work[1] = m_depthParm.y;
  work[2] = m_depthParm.z;
  work[3] = 0.0f;
  return 4;
}

int DrCalcViewWork::unistatic_mpf_ViewYVec(f32 *work) {
  work[0] = m_viewYVec.x;
  work[1] = m_viewYVec.y;
  work[2] = m_viewYVec.z;
  work[3] = 0.0f;
  return 4;
}

int DrCalcViewWork::unistatic_mpf_ViewPos(f32 *work) {
  work[0] = m_viewPos.x;
  work[1] = m_viewPos.y;
  work[2] = m_viewPos.z;
  work[3] = 1.0f;
  return 4;
}

int DrCalcViewWork::unistatic_mpf_OldViewPos(f32 *work) {
  work[0] = m_prevViewPos.x;
  work[1] = m_prevViewPos.y;
  work[2] = m_prevViewPos.z;
  work[3] = 1.0f;
  return 4;
}

int DrCalcViewWork::unistatic_mpf_Fade(f32 *work) {
  grlib::ShdF32SetF32Array(work, m_fades, 12);
  return 48;
}

} // namespace ml
