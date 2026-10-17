#pragma once
#include <stddef.h>

#include "grlib/cglib_dbl_uniform_block.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ml {
class DrMan;

class DrCalcViewWork {
public:
  f32 getPixlLen(f32 depth, f32 length) const;
  int unistatic_view(f32 *work, bool isJitter);
  int unistatic_proj(f32 *work, bool isJitter);
  int unistatic_viewproj(f32 *work, bool isJitter);
  int unistatic_invview(f32 *work, bool isJitter);
  int unistatic_billborad_Def(f32 *work, bool isJitter);
  int unistatic_billborad_YVec(f32 *work, bool isJitter);
  int unistatic_viewYvec(f32 *work, bool isJitter);
  int unistatic_jitter(f32 *work, bool isJitter);
  int unistatic_dither_tmaa_val(f32 *work, bool isJitter);
  int unistatic_proj_non_jitter(f32 *work, bool isJitter);
  int unistatic_diff_pre_orijmat(f32 *work, bool isJitter);
  int unistatic_lightNotUse(f32 *work);
  int unistatic_mpf_ViewProj(f32 *work);
  int unistatic_mpf_OldViewProj(f32 *work);
  int unistatic_mpf_View(f32 *work);
  int unistatic_mpf_BiiMat(f32 *work);
  int unistatic_mpf_OldBiiMat(f32 *work);
  int unistatic_mpf_DepthParm(f32 *work);
  int unistatic_mpf_ViewYVec(f32 *work);
  int unistatic_mpf_ViewPos(f32 *work);
  int unistatic_mpf_OldViewPos(f32 *work);
  int unistatic_mpf_Fade(f32 *work);

  mm::Mat44 m_invView;
  mm::Mat44 m_view;
  u8 _80[0xc0 - 0x80];
  mm::Mat44 m_billboard;
  mm::Mat44 m_prevBillboard;
  u8 _140[0x180 - 0x140];
  mm::Mat44 m_proj;
  u8 _1c0[0x200 - 0x1c0];
  mm::Mat44 m_viewProj;
  mm::Mat44 m_billboardYVec;
  u8 _280[0x2c0 - 0x280];
  mm::Mat44 m_prevViewProj;
  mm::Mat44 m_diffPreOrijMatrix;
  mm::Mat44 m_viewProjNonJitter;
  mm::Mat44 m_projNonJitter;
  u8 _3c0[0x400 - 0x3c0];
  mm::Vec3 m_viewPos;
  u8 _410[0x430 - 0x410];
  mm::Vec3 m_depthParm;
  u8 _440[0x460 - 0x440];
  mm::Vec3 m_viewYVec;
  u8 _470[0x490 - 0x470];
  f32 m_fades[12];
  u8 _4c0[0x4d0 - 0x4c0];
  f32 m_pixlScale;
  u8 _4d4[0x700 - 0x4d4];
  DrMan *m_drMan;
  u8 _708[0x770 - 0x708];
  mm::Vec3 m_prevViewPos;
  u8 _780[0x7b0 - 0x780];
  grlib::CGLibDblUniformBlock m_staticUniform;
  u8 _7e8[0x820 - 0x7e8];
  grlib::CGLibDblUniformBlock m_fogUniform;
  grlib::CGLibDblUniformBlock m_toonUniform;
  grlib::CGLibDblUniformBlock m_toon2Uniform;
  grlib::CGLibDblUniformBlock m_lightUniform;
  u8 _900[0xae0 - 0x900];
  f32 m_jitter[2];
  u8 _ae8[0xaf0 - 0xae8];
  f32 m_prevJitter[2];
  u8 _af8[0xb00 - 0xaf8];
  f32 m_ditherTmaaValues[4];
};

static_assert(offsetof(DrCalcViewWork, m_view) == 0x40, "");
static_assert(offsetof(DrCalcViewWork, m_billboard) == 0xc0, "");
static_assert(offsetof(DrCalcViewWork, m_proj) == 0x180, "");
static_assert(offsetof(DrCalcViewWork, m_viewProj) == 0x200, "");
static_assert(offsetof(DrCalcViewWork, m_prevViewProj) == 0x2c0, "");
static_assert(offsetof(DrCalcViewWork, m_projNonJitter) == 0x380, "");
static_assert(offsetof(DrCalcViewWork, m_viewPos) == 0x400, "");
static_assert(offsetof(DrCalcViewWork, m_depthParm) == 0x430, "");
static_assert(offsetof(DrCalcViewWork, m_viewYVec) == 0x460, "");
static_assert(offsetof(DrCalcViewWork, m_fades) == 0x490, "");
static_assert(offsetof(DrCalcViewWork, m_pixlScale) == 0x4d0, "");
static_assert(offsetof(DrCalcViewWork, m_drMan) == 0x700, "");
static_assert(offsetof(DrCalcViewWork, m_prevViewPos) == 0x770, "");
static_assert(offsetof(DrCalcViewWork, m_staticUniform) == 0x7b0, "");
static_assert(offsetof(DrCalcViewWork, m_fogUniform) == 0x820, "");
static_assert(offsetof(DrCalcViewWork, m_toonUniform) == 0x858, "");
static_assert(offsetof(DrCalcViewWork, m_toon2Uniform) == 0x890, "");
static_assert(offsetof(DrCalcViewWork, m_lightUniform) == 0x8c8, "");
static_assert(offsetof(DrCalcViewWork, m_jitter) == 0xae0, "");
static_assert(offsetof(DrCalcViewWork, m_prevJitter) == 0xaf0, "");
static_assert(offsetof(DrCalcViewWork, m_ditherTmaaValues) == 0xb00, "");

} // namespace ml
