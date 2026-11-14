#pragma once
#include <stddef.h>

#include "dr/dr_mdo_mat.h"
#include "types.h"

namespace grlib {
class CGLibEtcUniformBlock;
} // namespace grlib

namespace mm {
struct Vec3;
struct Mat44;
} // namespace mm

namespace ml {
class DrResEtcPamObj;
class DrResMdoMat;

struct MdsFixAnmCate {
  u8 _00[0x02 - 0x00];
  u16 unknown02; // Inferred role: first anim info; original member name unknown.
  u16 unknown04; // Inferred role: anim info num; original member name unknown.
  u16 unknown06; // Inferred role: work offset; original member name unknown.
  u8 _08[0x0c - 0x08];
};

static_assert(offsetof(MdsFixAnmCate, unknown02) == 0x02, "");
static_assert(offsetof(MdsFixAnmCate, unknown04) == 0x04, "");
static_assert(offsetof(MdsFixAnmCate, unknown06) == 0x06, "");
static_assert(sizeof(MdsFixAnmCate) == 0x0c, "");

struct MdsMdlNodeAnmInfo {
  u8 _00[0x04 - 0x00];
  s32 unknown04; // Inferred role: start frame; original member name unknown.
  s32 unknown08; // Inferred role: end frame; original member name unknown.
  u32 unknown0c; // Inferred role: key offset; original member name unknown.
  s32 unknown10; // Inferred role: key num; original member name unknown.
};

static_assert(offsetof(MdsMdlNodeAnmInfo, unknown04) == 0x04, "");
static_assert(offsetof(MdsMdlNodeAnmInfo, unknown0c) == 0x0c, "");
static_assert(offsetof(MdsMdlNodeAnmInfo, unknown10) == 0x10, "");

// Inferred role: node animation hermite key; original type name unknown.
struct unknown014 {
  f32 unknown00; // Inferred role: out slope; original member name unknown.
  f32 unknown04; // Inferred role: in slope; original member name unknown.
  f32 unknown08; // Inferred role: value; original member name unknown.
  u16 unknown0c; // Inferred role: frame; original member name unknown.
  u8 _0e;
  u8 unknown0f; // Inferred role: flags, bit 0 is a step key; original member name unknown.
};

static_assert(offsetof(unknown014, unknown0c) == 0x0c, "");
static_assert(offsetof(unknown014, unknown0f) == 0x0f, "");
static_assert(sizeof(unknown014) == 0x10, "");

class DrMdoAnim : public DrMdoMat {
public:
  void setMatAnmFrme(f32 frame);
  void changeMemFixAnim(MdoWrkMatRes *matRes, const void *data);
  void setupFixAnim(const void *data);
  void updateAnim(f32 frame, const u32 *flags, DrResEtcPamObj *pamObj);
  void updateAnimFast(f32 frame, DrResEtcPamObj *pamObj);
  void updateAnimEnd(f32 frame, const u32 *flags, DrResEtcPamObj *pamObj);
  void calcPlaneMatrix(mm::Mat44 *matrix, const f32 *work);
  void calcAnim(const MdsFixAnmCate *cate, DrResMdoMat *mat, DrResEtcPamObj *pamObj, f32 *work, f32 frame);
  f32 getHermiteAttr(const MdsFixAnmInf *inf, f32 frame);
  void calcAnimFrameOnly(const MdsFixAnmCate *cate, f32 frame);
  void setMatAnimFrame(const MdsFixAnmCate *cate, f32 frame);
  f32 getNodeAnmHermiteAttr(const MdsMdlNodeAnmInfo *info, f32 frame);
  static void animcall_UV_Scr_U(DrResMdoMat *mat, f32 *work, f32 value);
  static void animcall_UV_Scr_V(DrResMdoMat *mat, f32 *work, f32 value);
  static void animcall_UV_Trans_U(DrResMdoMat *mat, f32 *work, f32 value);
  static void animcall_UV_Trans_V(DrResMdoMat *mat, f32 *work, f32 value);
  static void animcall_UV_Rot(DrResMdoMat *mat, f32 *work, f32 value);
  static void animcall_WorkFloat1(DrResMdoMat *mat, f32 *work, f32 value);
  static void animcall_MatAlpha(DrResMdoMat *mat, f32 *work, f32 value);
  static void animcall_MatColorR(DrResMdoMat *mat, f32 *work, f32 value);
  static void animcall_MatColorG(DrResMdoMat *mat, f32 *work, f32 value);
  static void animcall_MatColorB(DrResMdoMat *mat, f32 *work, f32 value);
  static void anmNodeParm_TranX(mm::Vec3 *transform, f32 value);
  static void anmNodeParm_TranY(mm::Vec3 *transform, f32 value);
  static void anmNodeParm_TranZ(mm::Vec3 *transform, f32 value);
  static void anmNodeParm_RotX(mm::Vec3 *transform, f32 value);
  static void anmNodeParm_RotY(mm::Vec3 *transform, f32 value);
  static void anmNodeParm_RotZ(mm::Vec3 *transform, f32 value);
  static void anmNodeParm_SclX(mm::Vec3 *transform, f32 value);
  static void anmNodeParm_SclY(mm::Vec3 *transform, f32 value);
  static void anmNodeParm_SclZ(mm::Vec3 *transform, f32 value);

  static void (*s_pCallAnim[])(DrResMdoMat *mat, f32 *work, f32 value);

  u8 _16c[0x170 - 0x16c];
  grlib::CGLibEtcUniformBlock *unknown170; // Inferred role: etc uniform; original member name unknown.
  u8 unknown178;                           // Inferred role: setup flags; original member name unknown.
  u8 unknown179;                           // Inferred role: seam flag; original member name unknown.
  s16 unknown17a;                          // Inferred role: uniform index; original member name unknown.
  s16 unknown17c;                          // Inferred role: material index; original member name unknown.
  s16 unknown17e;                          // Inferred role: previous material index; original member name unknown.
  s16 m_nodeMax;
  u8 _182[0x190 - 0x182];
};

static_assert(offsetof(DrMdoAnim, unknown170) == 0x170, "");
static_assert(offsetof(DrMdoAnim, unknown178) == 0x178, "");
static_assert(offsetof(DrMdoAnim, unknown17a) == 0x17a, "");
static_assert(offsetof(DrMdoAnim, unknown17c) == 0x17c, "");
static_assert(offsetof(DrMdoAnim, m_nodeMax) == 0x180, "");
static_assert(sizeof(DrMdoAnim) == 0x190, "");

} // namespace ml
