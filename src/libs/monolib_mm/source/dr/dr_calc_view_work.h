#pragma once
#include <stddef.h>

#include "dr/dr_calc_clip_work_view_plane.h"
#include "grlib/cglib_dbl_uniform_block.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ml {
class DrMan;

class DrCalcViewWork {
public:
  void begin(int loop);
  void end();
  f32 getPixlLen(f32 depth, f32 length) const;
  void shadowBegin(const mm::Mat44 &matrix);
  void shadowEnd();
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
  int unistatic_depth_change(f32 *work, bool isJitter);
  int unistatic_lightAmb(f32 *work);
  int unistatic_diffuseIBL(f32 *work);
  int unistatic_dither_param(f32 *work);
  int unistatic_inv_dither_param(f32 *work);
  void renderEnd();
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

  mm::Mat44 unknown00; // Inferred role: inv view; original member name unknown.
  mm::Mat44 unknown40; // Inferred role: view; original member name unknown.
  u8 _80[0xc0 - 0x80];
  mm::Mat44 unknownc0;  // Inferred role: billboard; original member name unknown.
  mm::Mat44 unknown100; // Inferred role: prev billboard; original member name unknown.
  mm::Mat44 unknown140; // Inferred role: saved billboard; original member name unknown.
  mm::Mat44 unknown180; // Inferred role: proj; original member name unknown.
  u8 _1c0[0x200 - 0x1c0];
  mm::Mat44 unknown200; // Inferred role: view proj; original member name unknown.
  mm::Mat44 unknown240; // Inferred role: billboard y vec; original member name unknown.
  mm::Mat44 unknown280; // Inferred role: prev view; original member name unknown.
  mm::Mat44 unknown2c0; // Inferred role: prev view proj; original member name unknown.
  mm::Mat44 unknown300; // Inferred role: diff pre orij matrix; original member name unknown.
  mm::Mat44 unknown340; // Inferred role: view proj non jitter; original member name unknown.
  mm::Mat44 unknown380; // Inferred role: proj non jitter; original member name unknown.
  u8 _3c0[0x400 - 0x3c0];
  mm::Vec3 unknown400; // Inferred role: view pos; original member name unknown.
  u8 _410[0x430 - 0x410];
  mm::Vec3 unknown430; // Inferred role: depth parm; original member name unknown.
  u8 _440[0x460 - 0x440];
  mm::Vec3 unknown460; // Inferred role: view y vec; original member name unknown.
  u8 _470[0x490 - 0x470];
  f32 unknown490[12]; // Inferred role: fades; original member name unknown.
  u8 _4c0[0x4d0 - 0x4c0];
  f32 unknown4d0; // Inferred role: pixl scale; original member name unknown.
  u8 _4d4[0x4e0 - 0x4d4];
  DrCalcClipWorkViewPlane unknown4e0; // Inferred role: view clip plane; original member name unknown.
  u8 _590[0x700 - 0x590];
  DrMan *unknown700; // Inferred role: dr man; original member name unknown.
  u8 _708[0x770 - 0x708];
  mm::Vec3 unknown770; // Inferred role: prev view pos; original member name unknown.
  u8 _780[0x7b0 - 0x780];
  grlib::CGLibDblUniformBlock unknown7b0; // Inferred role: static uniform; original member name unknown.
  u8 _7e8[0x820 - 0x7e8];
  grlib::CGLibDblUniformBlock unknown820; // Inferred role: fog uniform; original member name unknown.
  grlib::CGLibDblUniformBlock unknown858; // Inferred role: toon uniform; original member name unknown.
  grlib::CGLibDblUniformBlock unknown890; // Inferred role: toon2 uniform; original member name unknown.
  grlib::CGLibDblUniformBlock unknown8c8; // Inferred role: light uniform; original member name unknown.
  u8 _900[0x9ad - 0x900];
  bool unknown9ad; // Inferred role: request flag; original member name unknown.
  u8 _9ae[0xae0 - 0x9ae];
  f32 unknownae0[2]; // Inferred role: jitter; original member name unknown.
  u8 _ae8[0xaf0 - 0xae8];
  f32 unknownaf0[2]; // Inferred role: prev jitter; original member name unknown.
  u8 _af8[0xb00 - 0xaf8];
  f32 unknownb00[4]; // Inferred role: dither tmaa values; original member name unknown.
  f32 unknownb10[2]; // Inferred role: dither param; original member name unknown.
};

static_assert(offsetof(DrCalcViewWork, unknown40) == 0x40, "");
static_assert(offsetof(DrCalcViewWork, unknownc0) == 0xc0, "");
static_assert(offsetof(DrCalcViewWork, unknown140) == 0x140, "");
static_assert(offsetof(DrCalcViewWork, unknown180) == 0x180, "");
static_assert(offsetof(DrCalcViewWork, unknown200) == 0x200, "");
static_assert(offsetof(DrCalcViewWork, unknown280) == 0x280, "");
static_assert(offsetof(DrCalcViewWork, unknown2c0) == 0x2c0, "");
static_assert(offsetof(DrCalcViewWork, unknown380) == 0x380, "");
static_assert(offsetof(DrCalcViewWork, unknown400) == 0x400, "");
static_assert(offsetof(DrCalcViewWork, unknown430) == 0x430, "");
static_assert(offsetof(DrCalcViewWork, unknown460) == 0x460, "");
static_assert(offsetof(DrCalcViewWork, unknown490) == 0x490, "");
static_assert(offsetof(DrCalcViewWork, unknown4d0) == 0x4d0, "");
static_assert(offsetof(DrCalcViewWork, unknown4e0) == 0x4e0, "");
static_assert(offsetof(DrCalcViewWork, unknown700) == 0x700, "");
static_assert(offsetof(DrCalcViewWork, unknown770) == 0x770, "");
static_assert(offsetof(DrCalcViewWork, unknown7b0) == 0x7b0, "");
static_assert(offsetof(DrCalcViewWork, unknown820) == 0x820, "");
static_assert(offsetof(DrCalcViewWork, unknown858) == 0x858, "");
static_assert(offsetof(DrCalcViewWork, unknown890) == 0x890, "");
static_assert(offsetof(DrCalcViewWork, unknown8c8) == 0x8c8, "");
static_assert(offsetof(DrCalcViewWork, unknown9ad) == 0x9ad, "");
static_assert(offsetof(DrCalcViewWork, unknownae0) == 0xae0, "");
static_assert(offsetof(DrCalcViewWork, unknownaf0) == 0xaf0, "");
static_assert(offsetof(DrCalcViewWork, unknownb00) == 0xb00, "");
static_assert(offsetof(DrCalcViewWork, unknownb10) == 0xb10, "");

} // namespace ml
