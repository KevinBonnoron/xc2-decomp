#pragma once
#include <stddef.h>

#include "dr/dr_calc_clip_work_view_plane.h"
#include "dr/dr_calc_clip_work_view_poli.h"
#include "grlib/cglib_dbl_uniform_block.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec2.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ml {
class DrMan;

class DrCalcViewWork {
public:
  DrCalcViewWork(DrMan *man);
  ~DrCalcViewWork();
  void begin(int loop);
  void updateDitherMatrix();
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
  int unistatic_specularIBL(f32 *work);
  int unistatic_dither_matrix(f32 *work);
  int unistatic_dither_param(f32 *work);
  int unistatic_inv_dither_matrix(f32 *work);
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
  int unistatic_digher_val(f32 *work, bool isJitter);
  int unistatic_screenSize(f32 *work, bool isJitter);
  int unistatic_lightCol(f32 *work);
  int unistatic_preProjMat(f32 *work, bool isJitter);

  mm::Mat44 unknown00;  // Inferred role: inv view; original member name unknown.
  mm::Mat44 unknown40;  // Inferred role: view; original member name unknown.
  mm::Mat44 unknown80;  // Inferred role: view without translation, copy of unknown40 made by DrCalcViewWork::begin (1.0.0: 0x71008aa940); read by
                        // DrMdoCtlNom::updateMdlUniformBlock; original member name unknown.
  mm::Mat44 unknownc0;  // Inferred role: billboard; original member name unknown.
  mm::Mat44 unknown100; // Inferred role: prev billboard; original member name unknown.
  mm::Mat44 unknown140; // Inferred role: saved billboard; original member name unknown.
  mm::Mat44 unknown180; // Inferred role: proj; original member name unknown.
  mm::Mat44 unknown1c0; // Inferred role: inverse view proj; original member name unknown.
  mm::Mat44 unknown200; // Inferred role: view proj; original member name unknown.
  mm::Mat44 unknown240; // Inferred role: billboard y vec; original member name unknown.
  mm::Mat44 unknown280; // Inferred role: prev view; original member name unknown.
  mm::Mat44 unknown2c0; // Inferred role: prev view proj; original member name unknown.
  mm::Mat44 unknown300; // Inferred role: diff pre orij matrix; original member name unknown.
  mm::Mat44 unknown340; // Inferred role: view proj non jitter; original member name unknown.
  mm::Mat44 unknown380; // Inferred role: proj non jitter; original member name unknown.
  mm::Mat44 unknown3c0; // Inferred role: inverse proj non jitter (gProjInv of DrPixlPostObjTSSAO::passTemporalFiltering, passed as a Mat44 at 0x71008c2f80); original member name unknown.
  mm::Vec3 unknown400;  // Inferred role: view pos; original member name unknown.
  mm::Vec3 unknown410;  // Inferred role: view direction (DrPixlPostObjMotionBlur2::calcBlurWork, 0x71008bcbe4: scaled by unknown4c8 and added to the view position); original member name unknown.
  mm::Vec3 unknown420;  // Inferred role: unit vector of DrCalcViewWork::begin (1.0.0: 0x71008aaf70) made from unknown410 and the columns of unknown00; original member name unknown.
  mm::Vec3 unknown430;  // Inferred role: depth parm; original member name unknown.
  u8 _440[0x450 - 0x440];
  mm::Vec3 unknown450; // Inferred role: view position transformed by the view matrix (1.0.0: 0x71008ab0f0); original member name unknown.
  mm::Vec3 unknown460; // Inferred role: view y vec; original member name unknown.
  mm::Vec3 unknown470; // Inferred role: unit vector of the x axis of unknown00 (1.0.0: 0x71008ab1c0); original member name unknown.
  mm::Vec3 unknown480; // Inferred role: unit vector of the y axis of unknown00 (1.0.0: 0x71008ab1c0); original member name unknown.
  f32 unknown490[12];  // Inferred role: fades; original member name unknown.
  f32 unknown4c0; // Inferred role: aspect factor of the screen to view position (gScreenToViewPos of DrPixlPostObjTSSAO::passTemporalFiltering, loaded at 0x71008c2ec4 and multiplied by the tangent);
                  // original member name unknown.
  f32 unknown4c4; // Inferred role: field of view of the screen to view position (gScreenToViewPos of DrPixlPostObjTSSAO::passTemporalFiltering, halved and passed to tanf at 0x71008c2eb0); original
                  // member name unknown.
  f32 unknown4c8; // Inferred role: distance along the view direction (DrPixlPostObjMotionBlur2::calcBlurWork, 0x71008bcbe0, times the direction and 10); original member name unknown.
  f32 unknown4cc; // Inferred role: velocity parameter of the sky base render (DrPixlSkyDome::baseRender, gVelocityParam x component); original member name unknown.
  f32 unknown4d0; // Inferred role: pixl scale; original member name unknown.
  u8 _4d4[0x4e0 - 0x4d4];
  DrCalcClipWorkViewPlane m_drCalcClipWorkViewPlane; // Inferred role: view clip plane; original member name unknown.
  DrCalcClipWorkViewPoli m_drCalcClipWorkViewPoli;   // Inferred role: view clip poli; original member name unknown.
  DrMan *m_drMan;                                    // Inferred role: dr man; original member name unknown.
  u8 _708[0x760 - 0x708];
  mm::Vec3 unknown760; // Inferred role: position kept while DrMan::unknown1d86 is set (DrCalcViewWork::begin, 1.0.0: 0x71008aa760); original member name unknown.
  mm::Vec3 unknown770; // Inferred role: prev view pos; original member name unknown.
  mm::Vec3 unknown780; // Inferred role: prev view direction; original member name unknown.
  f32 unknown790;      // Inferred role: smoothed distance moved by the view (DrCalcViewWork::begin, 1.0.0: 0x71008ad7ec); original member name unknown.
  u8 _794[0x798 - 0x794];
  f32 unknown798;  // Inferred role: scale of the blur parameter (DrPixlPostObjMotionBlur2::calcBlurWork, 0x71008bc2b4); original member name unknown.
  f32 unknown79c;  // Inferred role: distance moved by the view since the last begin; original member name unknown.
  f32 unknown7a0;  // Inferred role: distance moved by the view in the last begin; original member name unknown.
  f32 unknown7a4;  // Inferred role: dot product of the view direction with the previous one; original member name unknown.
  bool unknown7a8; // Inferred role: cloud plane enabled, set by DrEnvColiParameter::calcParams (0x71007d2970); original member name unknown.
  bool unknown7a9; // Inferred role: cloud hole, set from CloudMan::isHole by DrEnvColiParameter::calcParams (0x71007d2a6c); original member name unknown.
  u8 _7aa[0x7ac - 0x7aa];
  f32 unknown7ac;                         // Inferred role: cloud height, set from CloudMan::getHeight by DrEnvColiParameter::calcParams (0x71007d2a60); original member name unknown.
  grlib::CGLibDblUniformBlock unknown7b0; // Inferred role: static uniform; original member name unknown.
  grlib::CGLibDblUniformBlock unknown7e8; // Inferred role: uniform block, destroyed by the destructor; original member name unknown.
  grlib::CGLibDblUniformBlock unknown820; // Inferred role: fog uniform; original member name unknown.
  grlib::CGLibDblUniformBlock unknown858; // Inferred role: toon uniform; original member name unknown.
  grlib::CGLibDblUniformBlock unknown890; // Inferred role: toon2 uniform; original member name unknown.
  grlib::CGLibDblUniformBlock unknown8c8; // Inferred role: light uniform; original member name unknown.
  grlib::CGLibDblUniformBlock unknown900; // Inferred role: mpf uniform; original member name unknown.
  grlib::CGLibDblUniformBlock unknown938; // Inferred role: dither uniform for the first tex; original member name unknown.
  grlib::CGLibDblUniformBlock unknown970; // Inferred role: dither uniform; original member name unknown.
  bool unknown9a8;                        // Inferred role: camera position kept; original member name unknown.
  bool unknown9a9;                        // Inferred role: camera cut; original member name unknown.
  // Inferred role: SSR skip; original member name unknown. A u8 and not a bool: DrPixlPostMan::renderDeferredTemporal (0x7100843d50) normalises the byte
  // (`cmp w9, #0; cset w9, ne`) before it ors it into the reset flag, where a bool load carries a range and the compiler ors the byte as it is.
  u8 unknown9aa;
  bool unknown9ab; // Inferred role: first flag passed to DrMdoCtlMpfAuto::autoMpfCalc by DrResMdoSeamWrkMpf::updateRenderList; original member name unknown.
  bool unknown9ac; // Inferred role: set when the value at 0x79c exceeds 128; original member name unknown.
  bool unknown9ad; // Inferred role: request flag; original member name unknown.
  bool unknown9ae; // Inferred role: set by begin when the view jumped; original member name unknown.
  u8 _9af[0x9b0 - 0x9af];
  s32 unknown9b0; // Inferred role: frames left after a camera cut; original member name unknown.
  u32 unknown9b4; // Inferred role: index of the next jitter entry; original member name unknown.
  u8 _9b8[0x9c0 - 0x9b8];
  // Inferred role: eight jitter entries (Vec2, 16 bytes apart: the game copies the pair as one unit), the second float of each (offset 0x9c4 + 0x10 * index)
  // times 2 pi is the fourth gParam2 value of DrPixlPostObjTSSAO::passSSAO (index from the counter of that function); original member name unknown.
  mm::Vec2 unknown9c0[8];
  u8 _a40[0xac0 - 0xa40];
  // Inferred role: two pairs of floats, the differences of which (offset 0xac0 - 0xad0 and 0xac4 - 0xad4) are the gJitter uniform of
  // DrPixlPostMan::renderDownDepth (0x710084fcc0); original member names unknown. Vec2 members: 0x10 apart, and begin copies the
  // pair as one 64-bit unit (ldr x8, [x19, #0xac0]; str x8, [x19, #0xad0], 0x71008aaa04).
  mm::Vec2 unknownac0;
  mm::Vec2 unknownad0;
  mm::Vec2 unknownae0; // Inferred role: jitter; original member name unknown.
  mm::Vec2 unknownaf0; // Inferred role: prev jitter; original member name unknown.
  f32 unknownb00[4];   // Inferred role: dither tmaa values; original member name unknown.
  f32 unknownb10[2];   // Inferred role: dither param; original member name unknown.
  u8 _b18[0xb20 - 0xb18];
  u32 unknownb20[8][8]; // Inferred role: 8x8 dither pattern, 0 to 63, the source of the gDither matrix uniforms (unistatic_dither_matrix, 1.0.0: 0x71008b1d60); original member name unknown.
  // Inferred role: matrix passed as the gDither uniform of DrPixlPostObjTSSAO::passSSAO (0x71008c2388); original member name unknown.
  mm::Mat44 unknownc20;
};

static_assert(offsetof(DrCalcViewWork, unknown40) == 0x40, "");
static_assert(offsetof(DrCalcViewWork, unknown80) == 0x80, "");
static_assert(offsetof(DrCalcViewWork, unknownc0) == 0xc0, "");
static_assert(offsetof(DrCalcViewWork, unknown140) == 0x140, "");
static_assert(offsetof(DrCalcViewWork, unknown180) == 0x180, "");
static_assert(offsetof(DrCalcViewWork, unknown1c0) == 0x1c0, "");
static_assert(offsetof(DrCalcViewWork, unknown200) == 0x200, "");
static_assert(offsetof(DrCalcViewWork, unknown280) == 0x280, "");
static_assert(offsetof(DrCalcViewWork, unknown2c0) == 0x2c0, "");
static_assert(offsetof(DrCalcViewWork, unknown380) == 0x380, "");
static_assert(offsetof(DrCalcViewWork, unknown3c0) == 0x3c0, "");
static_assert(offsetof(DrCalcViewWork, unknown400) == 0x400, "");
static_assert(offsetof(DrCalcViewWork, unknown410) == 0x410, "");
static_assert(offsetof(DrCalcViewWork, unknown420) == 0x420, "");
static_assert(offsetof(DrCalcViewWork, unknown430) == 0x430, "");
static_assert(offsetof(DrCalcViewWork, unknown450) == 0x450, "");
static_assert(offsetof(DrCalcViewWork, unknown460) == 0x460, "");
static_assert(offsetof(DrCalcViewWork, unknown470) == 0x470, "");
static_assert(offsetof(DrCalcViewWork, unknown480) == 0x480, "");
static_assert(offsetof(DrCalcViewWork, unknown490) == 0x490, "");
static_assert(offsetof(DrCalcViewWork, unknown4c0) == 0x4c0, "");
static_assert(offsetof(DrCalcViewWork, unknown4c4) == 0x4c4, "");
static_assert(offsetof(DrCalcViewWork, unknown4c8) == 0x4c8, "");
static_assert(offsetof(DrCalcViewWork, unknown4d0) == 0x4d0, "");
static_assert(offsetof(DrCalcViewWork, m_drCalcClipWorkViewPlane) == 0x4e0, "");
static_assert(offsetof(DrCalcViewWork, m_drCalcClipWorkViewPoli) == 0x590, "");
static_assert(offsetof(DrCalcViewWork, m_drMan) == 0x700, "");
static_assert(offsetof(DrCalcViewWork, unknown760) == 0x760, "");
static_assert(offsetof(DrCalcViewWork, unknown770) == 0x770, "");
static_assert(offsetof(DrCalcViewWork, unknown780) == 0x780, "");
static_assert(offsetof(DrCalcViewWork, unknown790) == 0x790, "");
static_assert(offsetof(DrCalcViewWork, unknown798) == 0x798, "");
static_assert(offsetof(DrCalcViewWork, unknown79c) == 0x79c, "");
static_assert(offsetof(DrCalcViewWork, unknown7a0) == 0x7a0, "");
static_assert(offsetof(DrCalcViewWork, unknown7a4) == 0x7a4, "");
static_assert(offsetof(DrCalcViewWork, unknown7b0) == 0x7b0, "");
static_assert(offsetof(DrCalcViewWork, unknown7e8) == 0x7e8, "");
static_assert(offsetof(DrCalcViewWork, unknown820) == 0x820, "");
static_assert(offsetof(DrCalcViewWork, unknown858) == 0x858, "");
static_assert(offsetof(DrCalcViewWork, unknown890) == 0x890, "");
static_assert(offsetof(DrCalcViewWork, unknown8c8) == 0x8c8, "");
static_assert(offsetof(DrCalcViewWork, unknown900) == 0x900, "");
static_assert(offsetof(DrCalcViewWork, unknown938) == 0x938, "");
static_assert(offsetof(DrCalcViewWork, unknown970) == 0x970, "");
static_assert(offsetof(DrCalcViewWork, unknown9a8) == 0x9a8, "");
static_assert(offsetof(DrCalcViewWork, unknown9a9) == 0x9a9, "");
static_assert(offsetof(DrCalcViewWork, unknown9aa) == 0x9aa, "");
static_assert(offsetof(DrCalcViewWork, unknown9ab) == 0x9ab, "");
static_assert(offsetof(DrCalcViewWork, unknown9ac) == 0x9ac, "");
static_assert(offsetof(DrCalcViewWork, unknown9ad) == 0x9ad, "");
static_assert(offsetof(DrCalcViewWork, unknown9ae) == 0x9ae, "");
static_assert(offsetof(DrCalcViewWork, unknown9b0) == 0x9b0, "");
static_assert(offsetof(DrCalcViewWork, unknown9b4) == 0x9b4, "");
static_assert(offsetof(DrCalcViewWork, unknown9c0) == 0x9c0, "");
static_assert(offsetof(DrCalcViewWork, unknownae0) == 0xae0, "");
static_assert(offsetof(DrCalcViewWork, unknownaf0) == 0xaf0, "");
static_assert(offsetof(DrCalcViewWork, unknownac0) == 0xac0, "");
static_assert(offsetof(DrCalcViewWork, unknownad0) == 0xad0, "");
static_assert(offsetof(DrCalcViewWork, unknownb00) == 0xb00, "");
static_assert(offsetof(DrCalcViewWork, unknownb10) == 0xb10, "");
static_assert(offsetof(DrCalcViewWork, unknownc20) == 0xc20, "");
static_assert(sizeof(DrCalcViewWork) == 0xc60, "");

} // namespace ml
