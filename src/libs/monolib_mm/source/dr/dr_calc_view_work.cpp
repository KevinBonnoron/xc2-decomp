#include "dr/dr_calc_view_work.h"

#include <string.h>

#include "dr/dr_ini_sys.h"
#include "dr/dr_light_man.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_post_man.h"
#include "dr/dr_pixl_post_obj_cube_map_multi_ibl.h"
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

int DrCalcViewWork::unistatic_preProjMat(f32 *work, bool isJitter) {
  mm::Mat44 matrix;
  matrix.unknown009(unknown00, unknown280);
  matrix.unknown009(matrix, isJitter ? unknown180 : unknown380);
  grlib::ShdMat44TransposeMat44(work, matrix);
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_UNKNOWN_68];
}

DrCalcViewWork::~DrCalcViewWork() {}

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
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_UNKNOWN_2];
}

int DrCalcViewWork::unistatic_proj(f32 *work, bool isJitter) {
  grlib::ShdMat44TransposeMat44(work, isJitter ? unknown180 : unknown380);
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_UNKNOWN_3];
}

int DrCalcViewWork::unistatic_viewproj(f32 *work, bool isJitter) {
  grlib::ShdMat44TransposeMat44(work, isJitter ? unknown200 : unknown340);
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_UNKNOWN_4];
}

int DrCalcViewWork::unistatic_invview(f32 *work, bool isJitter) {
  grlib::ShdMat44TransposeMat34(work, unknown00);
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_UNKNOWN_6];
}

int DrCalcViewWork::unistatic_billborad_Def(f32 *work, bool isJitter) {
  grlib::ShdMat44TransposeMat34(work, unknownc0);
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_UNKNOWN_45];
}

int DrCalcViewWork::unistatic_billborad_YVec(f32 *work, bool isJitter) {
  grlib::ShdMat44TransposeMat34(work, unknown240);
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_UNKNOWN_46];
}

int DrCalcViewWork::unistatic_viewYvec(f32 *work, bool isJitter) {
  work[0] = unknown460.x;
  work[1] = unknown460.y;
  work[2] = unknown460.z;
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_UNKNOWN_8];
}

int DrCalcViewWork::unistatic_jitter(f32 *work, bool isJitter) {
  work[0] = unknownae0[0];
  work[1] = unknownae0[1];
  work[2] = unknownaf0[0];
  work[3] = unknownaf0[1];
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_UNKNOWN_73];
}

int DrCalcViewWork::unistatic_dither_tmaa_val(f32 *work, bool isJitter) {
  grlib::ShdF32SetVec4(work, unknownb00);
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_UNKNOWN_93];
}

int DrCalcViewWork::unistatic_proj_non_jitter(f32 *work, bool isJitter) {
  grlib::ShdMat44TransposeMat44(work, unknown380);
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_UNKNOWN_115];
}

int DrCalcViewWork::unistatic_diff_pre_orijmat(f32 *work, bool isJitter) {
  grlib::ShdMat44TransposeMat44(work, unknown300);
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_UNKNOWN_120];
}

int DrCalcViewWork::unistatic_lightNotUse(f32 *work) {
  work[0] = 0.0f;
  work[1] = 0.0f;
  work[2] = 0.0f;
  work[3] = 0.0f;
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_UNKNOWN_77];
}

int DrCalcViewWork::unistatic_depth_change(f32 *work, bool isJitter) {
  work[0] = unknown430.x;
  work[1] = unknown430.y;
  work[2] = unknown430.z;
  work[3] = m_drMan->m_drPixlMan->unknown00;
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_UNKNOWN_25];
}

int DrCalcViewWork::unistatic_lightAmb(f32 *work) {
  DrLightMan *lightMan = m_drMan->unknown588;
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

int DrCalcViewWork::unistatic_specularIBL(f32 *work) {
  DrPixlPostObjCubeMapMultiIBL *ibl = m_drMan->m_drPixlMan->unknown7f0->m_drPixlPostMan->m_drPixlPostObjCubeMapMultiIBL;
  if (ibl != nullptr) {
    bool isSkip = m_drMan->isIBLSkip();
    mm::Vec4 value = mm::Vec4::zero;
    if (!isSkip) {
      value.x = ibl->getPremMipCount();
    }
    grlib::ShdF32SetVec4(work, &value.x);
  }
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_UNKNOWN_59];
}

// 0x71008b1d60. The game keeps the inner loop of 8 rolled (cmp x12, #8 at 0x71008b1dec). The named `value` does that: with -g its dbg.value is one more instruction in the loop body for LoopUnroll,
// whose full unroll bound for 8 iterations is 300 (`-Rpass=loop-unroll` reports "completely unrolled loop with 8 iterations" and the function has 79 instructions without the local; a dbg.value for an
// i64 counter has the same effect, which is why s64 counters and casts matched before).
int DrCalcViewWork::unistatic_dither_matrix(f32 *work) {
  mm::Mat44 matrices[4];
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      f32 value = (static_cast<f32>(unknownb20[i][j]) + 1.0f) / 65.0f;
      matrices[i / 4 * 2 + j / 4].rows[i % 4][j % 4] = value;
    }
  }
  grlib::ShdMat44SetMat44Array(work, matrices, 4);
  return 0x40;
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

// 0x71008b1e70, the same loops on the inverted pattern value (0x3f - v). The named `value` is needed as in unistatic_dither_matrix.
int DrCalcViewWork::unistatic_inv_dither_matrix(f32 *work) {
  mm::Mat44 matrices[4];
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      f32 value = (static_cast<f32>(0x3f - unknownb20[i][j]) + 1.0f) / 65.0f;
      matrices[i / 4 * 2 + j / 4].rows[i % 4][j % 4] = value;
    }
  }
  grlib::ShdMat44SetMat44Array(work, matrices, 4);
  return 0x40;
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
  grlib::CGLibTextureBuffer &texture = m_drMan->m_drIniSys->unknown98[1];
  f32 width = texture.getWidth();
  f32 height = texture.getHeight();
  work[0] = m_drMan->unknown5b8->unknown18 * 0.25f;
  work[1] = (1.0f / height) * m_drMan->unknown5b8->unknown1c;
  work[2] = 4.0f / width;
  work[3] = width * 0.25f;
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_UNKNOWN_26];
}

int DrCalcViewWork::unistatic_screenSize(f32 *work, bool isJitter) {
  mm::Vec4 value = mm::Vec4::unit;
  DrPixlRenderTarget *target = m_drMan->m_drPixlMan->getPixlObj(5);
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

int DrCalcViewWork::unistatic_lightCol(f32 *work) {
  DrLightMan *lightMan = m_drMan->unknown588;
  s32 count = lightMan->unknown168;
  s32 used = count < 3 ? count : 2;
  const mm::Col3 *color = lightMan->unknown16c;
  for (s32 i = 0; i < used; i++, color++) {
    work[i * 4 + 0] = color->r;
    work[i * 4 + 1] = color->g;
    work[i * 4 + 2] = color->b;
  }
  for (s32 i = used; i < 2; i++) {
    work[i * 4 + 0] = 0.0f;
    work[i * 4 + 1] = 0.0f;
    work[i * 4 + 2] = 0.0f;
  }
  return DrResMdoUniformBlock::s_nVarSizeTbl[DrResMdoUniformBlock::VAR_TYPE_UNKNOWN_29];
}

int DrCalcViewWork::unistatic_mpf_Fade(f32 *work) {
  grlib::ShdF32SetF32Array(work, unknown490, 12);
  return 48;
}

} // namespace ml
