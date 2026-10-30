#pragma once
#include <stddef.h>

#include "mm_math/mm_col3.h"
#include "types.h"

namespace ml {
class DrFogObjGbl;
class DrLightObjDir;
class DrLightObjPnt;
class DrLightObjSpt;

struct LgtAnimInf {
  u32 unknown00; // Inferred role: key index; original member name unknown.
  f32 unknown04; // Inferred role: start frame; original member name unknown.
  f32 unknown08; // Inferred role: end frame; original member name unknown.
  u8 _0c[0x0e - 0x0c];
  u16 unknown0e; // Inferred role: key num; original member name unknown.
};

static_assert(offsetof(LgtAnimInf, unknown0e) == 0x0e, "");
static_assert(sizeof(LgtAnimInf) == 0x10, "");

// Inferred role: light hermite key; original type name unknown.
struct unknown086 {
  f32 unknown00; // Inferred role: out slope; original member name unknown.
  f32 unknown04; // Inferred role: in slope; original member name unknown.
  f32 unknown08; // Inferred role: value; original member name unknown.
  u16 unknown0c; // Inferred role: frame; original member name unknown.
  u8 _0e[0x10 - 0x0e];
};

static_assert(sizeof(unknown086) == 0x10, "");

struct LgtObjData {
  u8 _00[0x28];
  u16 unknown28; // Inferred role: animation index; original member name unknown.
};

static_assert(offsetof(LgtObjData, unknown28) == 0x28, "");

struct LgtGlbFogObj {
  u8 _00[0x44];
  u16 unknown44; // Inferred role: animation index; original member name unknown.
};

static_assert(offsetof(LgtGlbFogObj, unknown44) == 0x44, "");

// Inferred role: frame range of an environment animation; original type name unknown.
struct unknown001 {
  u16 unknown00; // Inferred role: first command; original member name unknown.
  u16 unknown02; // Inferred role: command num; original member name unknown.
  u8 _04[0x08 - 0x04];
  f32 unknown08; // Inferred role: loop start frame; original member name unknown.
  f32 unknown0c; // Inferred role: end frame; original member name unknown.
};

static_assert(offsetof(unknown001, unknown0c) == 0x0c, "");
static_assert(sizeof(unknown001) == 0x10, "");

// Inferred role: light bit key; original type name unknown.
struct unknown087 {
  u16 frame;
  u16 value;
};

class DrEnvironmentAnim {
public:
  DrEnvironmentAnim();
  static u32 getAnimWork(const u8 *data, u32 offset);
  f32 setupAnim(void *frames, const u8 *data, u32 offset);
  void changeMemAnim(const u8 *data, u32 offset);
  void setFrame(f32 frame);
  void calcFrameUpdate(const LgtObjData *obj, f32 frame);
  void calcFogFrameUpdate(const LgtGlbFogObj *obj, f32 frame);
  void setupAnmVal(const f32 *values);
  void envlgt_amb_color_R(const LgtAnimInf *inf, f32 frame);
  void envlgt_amb_color_G(const LgtAnimInf *inf, f32 frame);
  void envlgt_amb_color_B(const LgtAnimInf *inf, f32 frame);
  void envlgt_amb_color_Intensity(const LgtAnimInf *inf, f32 frame);
  void envlgt_amb_non(const LgtAnimInf *inf, f32 frame);
  f32 getHermiteAttr(const LgtAnimInf *inf, f32 frame);
  void envlgt_dir_color_R(DrLightObjDir *light, const LgtAnimInf *inf, f32 frame);
  void envlgt_dir_color_G(DrLightObjDir *light, const LgtAnimInf *inf, f32 frame);
  void envlgt_dir_color_B(DrLightObjDir *light, const LgtAnimInf *inf, f32 frame);
  void envlgt_dir_color_Intensity(DrLightObjDir *light, const LgtAnimInf *inf, f32 frame);
  void envlgt_dir_spe_Intensity(DrLightObjDir *light, const LgtAnimInf *inf, f32 frame);
  void envlgt_dir_non(DrLightObjDir *light, const LgtAnimInf *inf, f32 frame);
  void envlgt_dir_texonoff(DrLightObjDir *light, const LgtAnimInf *inf, f32 frame);
  void envlgt_dir_texofsX(DrLightObjDir *light, const LgtAnimInf *inf, f32 frame);
  void envlgt_dir_texofsY(DrLightObjDir *light, const LgtAnimInf *inf, f32 frame);
  void envlgt_dir_size(DrLightObjDir *light, const LgtAnimInf *inf, f32 frame);
  void envlgt_dir_rotz(DrLightObjDir *light, const LgtAnimInf *inf, f32 frame);
  void envlgt_dir_roty(DrLightObjDir *light, const LgtAnimInf *inf, f32 frame);
  void envlgt_dir_rotx(DrLightObjDir *light, const LgtAnimInf *inf, f32 frame);
  void envlgt_pnt_color_R(DrLightObjPnt *light, const LgtAnimInf *inf, f32 frame);
  void envlgt_pnt_color_G(DrLightObjPnt *light, const LgtAnimInf *inf, f32 frame);
  void envlgt_pnt_color_B(DrLightObjPnt *light, const LgtAnimInf *inf, f32 frame);
  void envlgt_pnt_color_Intensity(DrLightObjPnt *light, const LgtAnimInf *inf, f32 frame);
  void envlgt_pnt_spe_Intensity(DrLightObjPnt *light, const LgtAnimInf *inf, f32 frame);
  void envlgt_pnt_non(DrLightObjPnt *light, const LgtAnimInf *inf, f32 frame);
  void envlgt_pnt_texonoff(DrLightObjPnt *light, const LgtAnimInf *inf, f32 frame);
  void envlgt_pnt_texofsX(DrLightObjPnt *light, const LgtAnimInf *inf, f32 frame);
  void envlgt_pnt_texofsY(DrLightObjPnt *light, const LgtAnimInf *inf, f32 frame);
  void envlgt_pnt_size(DrLightObjPnt *light, const LgtAnimInf *inf, f32 frame);
  void envlgt_pnt_rotz(DrLightObjPnt *light, const LgtAnimInf *inf, f32 frame);
  void envlgt_pnt_roty(DrLightObjPnt *light, const LgtAnimInf *inf, f32 frame);
  void envlgt_pnt_rotx(DrLightObjPnt *light, const LgtAnimInf *inf, f32 frame);
  void envlgt_spt_color_R(DrLightObjSpt *light, const LgtAnimInf *inf, f32 frame);
  void envlgt_spt_color_G(DrLightObjSpt *light, const LgtAnimInf *inf, f32 frame);
  void envlgt_spt_color_B(DrLightObjSpt *light, const LgtAnimInf *inf, f32 frame);
  void envlgt_spt_color_Intensity(DrLightObjSpt *light, const LgtAnimInf *inf, f32 frame);
  void envlgt_spt_spe_Intensity(DrLightObjSpt *light, const LgtAnimInf *inf, f32 frame);
  void envlgt_spt_angle(DrLightObjSpt *light, const LgtAnimInf *inf, f32 frame);
  void envlgt_spt_texonoff(DrLightObjSpt *light, const LgtAnimInf *inf, f32 frame);
  void envlgt_spt_texofsX(DrLightObjSpt *light, const LgtAnimInf *inf, f32 frame);
  void envlgt_spt_texofsY(DrLightObjSpt *light, const LgtAnimInf *inf, f32 frame);
  void envlgt_spt_size(DrLightObjSpt *light, const LgtAnimInf *inf, f32 frame);
  void envlgt_spt_rotz(DrLightObjSpt *light, const LgtAnimInf *inf, f32 frame);
  void envlgt_spt_roty(DrLightObjSpt *light, const LgtAnimInf *inf, f32 frame);
  void envlgt_spt_rotx(DrLightObjSpt *light, const LgtAnimInf *inf, f32 frame);
  void envlgt_trans_posx(const LgtAnimInf *inf, f32 frame);
  void envlgt_trans_posy(const LgtAnimInf *inf, f32 frame);
  void envlgt_trans_posz(const LgtAnimInf *inf, f32 frame);
  void envfog_parm_color_R(DrFogObjGbl *fog, const LgtAnimInf *inf, f32 frame);
  void envfog_parm_color_G(DrFogObjGbl *fog, const LgtAnimInf *inf, f32 frame);
  void envfog_parm_color_B(DrFogObjGbl *fog, const LgtAnimInf *inf, f32 frame);
  void envfog_parm_color_sideR(DrFogObjGbl *fog, const LgtAnimInf *inf, f32 frame);
  void envfog_parm_color_sideG(DrFogObjGbl *fog, const LgtAnimInf *inf, f32 frame);
  void envfog_parm_color_sideB(DrFogObjGbl *fog, const LgtAnimInf *inf, f32 frame);
  void envfog_parm_near(DrFogObjGbl *fog, const LgtAnimInf *inf, f32 frame);
  void envfog_parm_far(DrFogObjGbl *fog, const LgtAnimInf *inf, f32 frame);
  void envfog_parm_str(DrFogObjGbl *fog, const LgtAnimInf *inf, f32 frame);
  void envfog_parm_pow(DrFogObjGbl *fog, const LgtAnimInf *inf, f32 frame);
  void envfog_parm_color_sunR(DrFogObjGbl *fog, const LgtAnimInf *inf, f32 frame);
  void envfog_parm_color_sunG(DrFogObjGbl *fog, const LgtAnimInf *inf, f32 frame);
  void envfog_parm_color_sunB(DrFogObjGbl *fog, const LgtAnimInf *inf, f32 frame);
  u16 getBitAttr(const LgtAnimInf *inf, f32 frame);

  const unknown001 *unknown00; // Inferred role: animation ranges; original member name unknown.
  const u8 *unknown08;         // Inferred role: animation commands; original member name unknown.
  const unknown086 *unknown10; // Inferred role: hermite keys; original member name unknown.
  const unknown087 *unknown18; // Inferred role: bit keys; original member name unknown.
  const u8 *unknown20;         // Inferred role: rotation values; original member name unknown.
  int unknown28;               // Inferred role: anim num; original member name unknown.
  f32 *unknown30;              // Inferred role: frames; original member name unknown.
  mm::Col3 unknown38;          // Inferred role: color; original member name unknown.
  mm::Col3 unknown44;          // Inferred role: side color; original member name unknown.
  mm::Col3 unknown50;          // Inferred role: sun color; original member name unknown.
  f32 unknown5c;               // Inferred role: intensity; original member name unknown.
  f32 unknown60[3];            // Inferred role: anm val; original member name unknown.
};

static_assert(offsetof(DrEnvironmentAnim, unknown08) == 0x08, "");
static_assert(offsetof(DrEnvironmentAnim, unknown20) == 0x20, "");
static_assert(offsetof(DrEnvironmentAnim, unknown10) == 0x10, "");
static_assert(offsetof(DrEnvironmentAnim, unknown28) == 0x28, "");
static_assert(offsetof(DrEnvironmentAnim, unknown38) == 0x38, "");
static_assert(offsetof(DrEnvironmentAnim, unknown44) == 0x44, "");
static_assert(offsetof(DrEnvironmentAnim, unknown50) == 0x50, "");
static_assert(offsetof(DrEnvironmentAnim, unknown5c) == 0x5c, "");
static_assert(offsetof(DrEnvironmentAnim, unknown60) == 0x60, "");

} // namespace ml
