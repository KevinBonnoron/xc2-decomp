#include "dr/dr_calc_view_work.h"

#include <math.h>
#include <string.h>

#include "dr/dr_draw_work_info.h"
#include "dr/dr_ini_sys.h"
#include "dr/dr_light_man.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_post_man.h"
#include "dr/dr_pixl_post_obj_cube_map_multi_ibl.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_pixl_render_target.h"
#include "dr/dr_res_mdo_uniform_block.h"
#include "grlib/cglib_texture_buffer.h"
#include "grlib/shd_util.h"
#include "ml/attr_transform.h"
#include "ml/rand.h"
#include "ml/scn.h"
#include "ml/threadval.h"
#include "mm_math/mm_col3.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_vec4.h"
#include "mm_mtl/fixed_array.h"

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

void DrCalcViewWork::begin(int loop) {
  ScnObjCam *camera = DrMan::getIns()->unknown68->getCam(loop);
  memmove(&unknown00, &camera->unknown70.m_front->unknown00.unknown70, sizeof(mm::Mat44));
  if (m_drMan->unknown1d86) {
    if (unknown9a8) {
      unknown400 = unknown760;
    } else {
      unknown760 = camera->unknown70.m_front->unknown00.unknown10;
      unknown9a8 = true;
    }
  } else {
    unknown9a8 = false;
    unknown400 = camera->unknown70.m_front->unknown00.unknown10;
  }
  unknown4c8 = camera->unknown70.m_front->unknown1f4;
  unknown4cc = camera->unknown70.m_front->unknown1f8;
  unknown4c0 = static_cast<f32>(m_drMan->unknown5b8->unknown28) / static_cast<f32>(m_drMan->unknown5b8->unknown2c);
  unknown4c4 = camera->unknown70.m_front->unknown1e8 * mm::DEG_TO_RAD;
  unknown40 = unknown00;
  unknown40.unknown012();
  unknown80 = unknown40;
  // The direction vectors are unit vectors transformed by the matrix (`v.x * m[0][i] + v.y * m[1][i] + v.z * m[2][i]` with the constants of each vector, folded by the compiler). The
  // asymmetric spellings of the same sums (`r10 * 0.0f - r00 + r20 * 0.0f` for the side vector) schedule the z chain of the side vector differently (first difference at 0x71008ad33c).
  f32 directionX = 0.0f * unknown00.rows[0][0] + 0.0f * unknown00.rows[1][0] + -1.0f * unknown00.rows[2][0];
  f32 directionY = 0.0f * unknown00.rows[0][1] + 0.0f * unknown00.rows[1][1] + -1.0f * unknown00.rows[2][1];
  f32 directionZ = 0.0f * unknown00.rows[0][2] + 0.0f * unknown00.rows[1][2] + -1.0f * unknown00.rows[2][2];
  unknown410.x = directionX;
  unknown410.y = directionY;
  unknown80.rows[3][0] = unknown80.rows[3][1] = 0.0f;
  unknown80.rows[3][2] = 0.0f;
  unknown410.z = directionZ;
  unknown410.unknown001();
  unknownc0 = unknown00;
  unknownc0.rows[3][0] = unknownc0.rows[3][1] = 0.0f;
  unknownc0.rows[3][2] = 0.0f;
  unknown140 = unknownc0;
  f32 tangent = tanf(unknown4c4 * 0.5f);
  unknown4d0 = 1.0f / tangent;
  unknown180.unknown022(unknown4c4, unknown4c0, unknown4c8, unknown4cc);
  unknown340 = unknown40 * unknown180;
  unknown380 = unknown180;
  unknown3c0 = unknown180;
  unknown3c0.unknown012();
  unknownad0 = unknownac0;
  unknownaf0 = unknownae0;
  if (!m_drMan->unknown120[loop]->getTMAAOn()) {
    unknownae0.x = 0.0f;
    unknownae0.y = 0.0f;
    unknownac0.x = 0.0f;
    unknownac0.y = 0.0f;
  } else {
    DrPixlPostParm *postParm = m_drMan->unknown120[loop];
    u32 count = postParm->unknown14c;
    mm::Vec2 jitter;
    if (count >= 2) {
      u32 index = unknown9b4;
      jitter = unknown9c0[index];
      unknown9b4 = (index + 1) % count;
    } else {
      jitter = mm::Vec2(0.5f, 0.5f);
    }
    f32 jitterX = jitter.x - 0.5f;
    unknownac0.x = jitterX / static_cast<f32>(m_drMan->unknown5b8->unknown18);
    f32 jitterY = jitter.y - 0.5f;
    unknownac0.y = jitterY / static_cast<f32>(m_drMan->unknown5b8->unknown1c);
    f32 offsetX = (jitterX + jitterX) / static_cast<f32>(m_drMan->unknown5b8->unknown18);
    unknownae0.x = offsetX;
    f32 offsetY = (jitterY + jitterY) / static_cast<f32>(m_drMan->unknown5b8->unknown1c);
    unknown180.rows[2][0] += offsetX;
    unknownae0.y = offsetY;
    unknown180.rows[2][1] += offsetY;
    unknownb00[0] = static_cast<f32>(mtRand(8));
    unknownb00[1] = static_cast<f32>(mtRand(8));
    unknownb00[2] = static_cast<f32>(mtRand(0x40));
    unknownb00[3] = static_cast<f32>(mtRand(0x40));
  }
  unknown200 = unknown40 * unknown180;
  unknown1c0 = unknown180;
  unknown1c0.unknown012();
  f32 sightX = unknown410.x * unknown00.rows[0][0] + unknown410.y * unknown00.rows[1][0] + unknown410.z * unknown00.rows[2][0];
  f32 sightY = unknown410.x * unknown00.rows[0][1] + unknown410.y * unknown00.rows[1][1] + unknown410.z * unknown00.rows[2][1];
  f32 sightZ = unknown410.x * unknown00.rows[0][2] + unknown410.y * unknown00.rows[1][2] + unknown410.z * unknown00.rows[2][2];
  unknown420 = mm::Vec3(sightX, sightY, sightZ);
  unknown420.unknown001();
  f32 viewX = unknown400.x * unknown40.rows[0][0] + unknown400.y * unknown40.rows[1][0] + unknown400.z * unknown40.rows[2][0] + unknown40.rows[3][0];
  f32 viewY = unknown400.x * unknown40.rows[0][1] + unknown400.y * unknown40.rows[1][1] + unknown400.z * unknown40.rows[2][1] + unknown40.rows[3][1];
  f32 viewZ = unknown400.x * unknown40.rows[0][2] + unknown400.y * unknown40.rows[1][2] + unknown400.z * unknown40.rows[2][2] + unknown40.rows[3][2];
  unknown450.z = viewZ;
  unknown450.x = viewX;
  unknown450.y = viewY;
  unknown460 = mm::Vec3(0.0f * unknown40.rows[0][0] + 1.0f * unknown40.rows[1][0] + 0.0f * unknown40.rows[2][0],
                        0.0f * unknown40.rows[0][1] + 1.0f * unknown40.rows[1][1] + 0.0f * unknown40.rows[2][1],
                        0.0f * unknown40.rows[0][2] + 1.0f * unknown40.rows[1][2] + 0.0f * unknown40.rows[2][2]);
  unknown460.unknown001();
  if (!m_drMan->unknown1d86) {
    m_drCalcClipWorkViewPlane.setMatrix(unknown200);
    m_drCalcClipWorkViewPoli.setMatrix(unknown40, unknown4c4, unknown4c0, unknown400);
  }
  unknown470 = mm::Vec3(1.0f * unknown00.rows[0][0] + 0.0f * unknown00.rows[1][0] + 0.0f * unknown00.rows[2][0],
                        1.0f * unknown00.rows[0][1] + 0.0f * unknown00.rows[1][1] + 0.0f * unknown00.rows[2][1],
                        1.0f * unknown00.rows[0][2] + 0.0f * unknown00.rows[1][2] + 0.0f * unknown00.rows[2][2]);
  unknown480 = mm::Vec3(0.0f * unknown00.rows[0][0] + 1.0f * unknown00.rows[1][0] + 0.0f * unknown00.rows[2][0],
                        0.0f * unknown00.rows[0][1] + 1.0f * unknown00.rows[1][1] + 0.0f * unknown00.rows[2][1],
                        0.0f * unknown00.rows[0][2] + 1.0f * unknown00.rows[1][2] + 0.0f * unknown00.rows[2][2]);
  unknown470.unknown001();
  unknown480.unknown001();
  f32 depthParam = unknown180.rows[2][2];
  unknown430.x = 1.0f / depthParam;
  unknown430.y = unknown180.rows[3][2];
  unknown430.z = -1.0f / depthParam;
  if (unknown9ad) {
    unknown280 = unknown40;
    unknown100 = unknownc0;
    unknown300 = mm::Mat44::identity;
  } else {
    mm::Mat44 inverseView;
    inverseView.unknown014(unknown40);
    unknown300.unknown009(inverseView, unknown280);
  }
  unknown300.unknown009(unknown300, unknown180);
  unknown2c0 = unknown280 * unknown180;
  mm::Vec3 forward(0.0f * unknown00.rows[0][0] + 0.0f * unknown00.rows[1][0] + 1.0f * unknown00.rows[2][0],
                   0.0f * unknown00.rows[0][1] + 0.0f * unknown00.rows[1][1] + 1.0f * unknown00.rows[2][1],
                   0.0f * unknown00.rows[0][2] + 0.0f * unknown00.rows[1][2] + 1.0f * unknown00.rows[2][2]);
  forward.unknown002();
  f32 forwardLength = sqrtf(forward.x * forward.x + forward.z * forward.z);
  f32 forwardSlope = sqrtf(forwardLength * forwardLength + forward.y * forward.y);
  f32 forwardScale = 1.0f / forwardSlope;
  f32 forwardCos = forwardLength * forwardScale;
  f32 forwardSin = forward.y * forwardScale;
  f32 pitch = atan2f(forwardSin, forwardCos);
  mm::Vec3 side(-1.0f * unknown00.rows[0][0] + 0.0f * unknown00.rows[1][0] + 0.0f * unknown00.rows[2][0],
                -1.0f * unknown00.rows[0][1] + 0.0f * unknown00.rows[1][1] + 0.0f * unknown00.rows[2][1],
                -1.0f * unknown00.rows[0][2] + 0.0f * unknown00.rows[1][2] + 0.0f * unknown00.rows[2][2]);
  side.unknown002();
  f32 sideLength = sqrtf(side.x * side.x + side.z * side.z);
  f32 sideSlope = sqrtf(sideLength * sideLength + side.y * side.y);
  f32 sideScale = 1.0f / sideSlope;
  f32 sideCos = sideLength * sideScale;
  f32 sideSin = side.y * sideScale;
  f32 yaw = atan2f(sideSin, sideCos);
  unknown240.unknown016(pitch);
  mm::Mat44 yawMatrix;
  yawMatrix.unknown017(yaw);
  // Product into a temporary: unknown009 compares &yawMatrix with this, which keeps the yaw matrix in memory, and the first row of products then has the load of unknown240 on the left
  // (`fmul s2, s1, s0`); the game has the cosine of the yaw on the left (3248 instructions, 7 differing lines with unknown009, first difference at 0x71008ad490).
  mm::Mat44 rotation;
  rotation.unknown008(unknown240, yawMatrix);
  unknown240 = rotation;
  // Vec3's operator-: the game computes the three differences before squaring them. With the differences repeated inside the squares (3248 instructions, 7 differing lines) unknown400.z is
  // loaded after the sum of the first two squares, the game loads it inside the product block above (first difference at 0x71008ad5d8).
  mm::Vec3 delta = unknown770 - unknown400;
  f32 moved = sqrtf(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
  unknown79c = moved;
  unknown9aa = 0;
  f32 turned = unknown780.x * unknown410.x + unknown780.y * unknown410.y + unknown780.z * unknown410.z;
  unknown7a4 = turned;
  // The game decrements unknown9b0 after the stores of unknown79c, unknown9aa and unknown7a4 (0x71008ad6a4). Written before them (3248 instructions, 2 differing lines) the product of the z
  // components of the dot product is scheduled before the sum of the first two (first difference at 0x71008ad6b8).
  unknown9b0 = unknown9b0 - 1 < 0 ? 0 : unknown9b0 - 1;
  bool isJumped = false;
  if (turned < 0.87630665f || (1.0f < moved && (8.0f <= moved || unknown790 / moved < 0.8f))) {
    unknown9aa = 1;
  } else if (DrMan::get()->m_autoResetScene) {
    if (0.3f < unknown79c - unknown7a0 && unknown7a0 < 0.05) {
      isJumped = true;
      unknown9aa = 1;
    }
  }
  unknown9ae = isJumped;
  // The game branches on DrMan::get()->m_autoResetScene with a cbz and stores 1 in one arm; the other arm shares the `strb wzr, [x19, #0x9a9]` of the unknown9aa == 0 arm (0x71008ad71c to
  // 0x71008ad794). A copy of the byte (`unknown9a9 = DrMan::get()->m_autoResetScene`) stores the loaded value and is 3 instructions short (3245).
  if (unknown9aa == 0) {
    unknown9ab = 8.0f < unknown79c;
    unknown9ac = 128.0f < unknown79c;
    unknown9a9 = false;
  } else {
    unknown9b0 = 10;
    unknown9ab = 8.0f < unknown79c;
    unknown9ac = 128.0f < unknown79c;
    if (DrMan::get()->m_autoResetScene) {
      unknown9a9 = true;
    } else {
      unknown9a9 = false;
    }
  }
  unknown770 = unknown400;
  unknown780 = unknown410;
  unknown790 += (unknown79c - unknown790) * 0.25f;
  unknown7a0 = unknown79c;
  if (m_drMan->unknown120[loop]->getTMAAOn()) {
    updateDitherMatrix();
  }
  IDrDrawWorkInfo &info = m_drMan->m_iDrDrawWorkInfo[m_drMan->unknown1c98];
  info.unknownd0 = unknown00;
  info.unknown110 = unknown40;
  info.unknown150 = unknown180;
  info.unknown190 = unknown380;
  info.unknownb0 = unknown400;
  info.unknownc0 = unknown410;
  info.unknown534 = unknown4c0;
  info.unknown538 = unknown4c4;
  info.unknown53c = unknown4c8;
  info.unknown540 = unknown4cc;
  info.unknown550 = m_drMan->unknown5b8->unknown28;
  info.unknown554 = m_drMan->unknown5b8->unknown2c;
  info.unknown558 = m_drMan->unknown5b8->unknown20;
  info.unknown55c = m_drMan->unknown5b8->unknown24;
}

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
  work[0] = unknownae0.x;
  work[1] = unknownae0.y;
  work[2] = unknownaf0.x;
  work[3] = unknownaf0.y;
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
