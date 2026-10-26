#pragma once
#include <stddef.h>

#include "dr/dr_mdl_base.h"
#include "grlib/cglib_uniform_array.h"
#include "mm_math/mm_col3.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace grlib {
class CGLibDblUniformBlock;
class CGLibOneUniformBlock;
class CGLibTextureBuffer;
class CGLibTriUniformBlock;
} // namespace grlib

namespace ml {

class DrResMdoMat;
class DrMan;
class DrMdoSmlShadowObj;
struct MdsMatCharMkTexTbl;
class DrResMdoTexList;
class DrResMdoVertex;
class DrShdMdoDecExtTbl;

struct MdsMatInfoHeader {
  u8 _00[0x0c - 0x00];
  f32 unknown0c; // Inferred role: color r; original member name unknown.
  f32 unknown10; // Inferred role: color g; original member name unknown.
  f32 unknown14; // Inferred role: color b; original member name unknown.
  f32 unknown18; // Inferred role: color a; original member name unknown.
  u8 _1c[0x20 - 0x1c];
  u32 unknown20; // Inferred role: texture index offset; original member name unknown.
  u8 _24[0x40 - 0x24];
  u32 unknown40; // Inferred role: value offset; original member name unknown.
  u8 _44[0x64 - 0x44];
  u16 unknown64; // Inferred role: time value index; original member name unknown.
  u8 _66[0x74 - 0x66];
};

static_assert(offsetof(MdsMatInfoHeader, unknown0c) == 0x0c, "");
static_assert(offsetof(MdsMatInfoHeader, unknown18) == 0x18, "");
static_assert(offsetof(MdsMatInfoHeader, unknown20) == 0x20, "");
static_assert(offsetof(MdsMatInfoHeader, unknown40) == 0x40, "");
static_assert(offsetof(MdsMatInfoHeader, unknown64) == 0x64, "");

static_assert(sizeof(MdsMatInfoHeader) == 0x74, "");

struct MdoWrkRimBloom;
struct MdoWrkVanishEffect;

struct MdsMeshPartsInfo {
  u8 _00[0x08 - 0x00];
  u8 unknown08; // Inferred role: flags; original member name unknown.
  u8 _09[0x10 - 0x09];
};

static_assert(sizeof(MdsMeshPartsInfo) == 0x10, "");

struct MdsMeshHeader {
  enum Flag {
    FLAG_VANISH_EFFECT = 1 << 13,
  };

  u16 unknown00; // Inferred role: flags; original member name unknown.
  u8 _02[0x64 - 0x02];
  u32 unknown64; // Inferred role: parts info offset; original member name unknown.
  u8 _68[0x94 - 0x68];
  u8 unknown94; // Inferred role: vanish effect num; original member name unknown.
};

static_assert(offsetof(MdsMeshHeader, unknown64) == 0x64, "");
static_assert(offsetof(MdsMeshHeader, unknown94) == 0x94, "");

struct MdoWrkAvatar {
  u32 unknown00; // Inferred role: flags; original member name unknown.
  u8 _04[0x08 - 0x04];
  grlib::CGLibTextureBuffer *unknown08[2]; // Inferred role: base textures; original member name unknown.
  void *unknown18[2];                      // Inferred role: textures; original member name unknown.
  grlib::CGLibTextureBuffer *unknown28;    // Inferred role: eye base texture; original member name unknown.
  void *unknown30;                         // Inferred role: eye texture; original member name unknown.
  bool unknown38;                          // Inferred role: doll mat; original member name unknown.
  u8 _39[0x40 - 0x39];
  grlib::CGLibOneUniformBlock *unknown40; // Inferred role: char colors; original member name unknown.
  grlib::CGLibOneUniformBlock *unknown48; // Inferred role: doll colors; original member name unknown.
};

static_assert(offsetof(MdoWrkAvatar, unknown08) == 0x08, "");
static_assert(offsetof(MdoWrkAvatar, unknown18) == 0x18, "");
static_assert(offsetof(MdoWrkAvatar, unknown28) == 0x28, "");
static_assert(offsetof(MdoWrkAvatar, unknown30) == 0x30, "");
static_assert(offsetof(MdoWrkAvatar, unknown38) == 0x38, "");
static_assert(offsetof(MdoWrkAvatar, unknown40) == 0x40, "");
static_assert(offsetof(MdoWrkAvatar, unknown48) == 0x48, "");

struct MdoWrkShaderParm {
  mm::Col3 unknown00[4]; // Inferred role: colors; original member name unknown.
  f32 unknown30[1];      // Inferred role: values; original member name unknown.
};

static_assert(offsetof(MdoWrkShaderParm, unknown30) == 0x30, "");

// Inferred type: fixed animation data header; the original type name is unknown.
struct MdsFixedAnimData {
  u8 _00[0x14];
  u32 unknown14;
  u8 _18[0x1c - 0x18];
  u32 unknown1c;
  u8 _20[0x24 - 0x20];
  u32 unknown24;
};

static_assert(offsetof(MdsFixedAnimData, unknown14) == 0x14, "");
static_assert(offsetof(MdsFixedAnimData, unknown1c) == 0x1c, "");
static_assert(offsetof(MdsFixedAnimData, unknown24) == 0x24, "");

struct MdsMdlInfoHeader {
  u8 _00[0x30 - 0x00];
};

static_assert(sizeof(MdsMdlInfoHeader) == 0x30, "");

struct MdsMdlEntry {
  u32 unknown00; // Inferred role: info offset; original member name unknown.
  s32 unknown04; // Inferred role: info count; original member name unknown.
  u8 _08[0x0c - 0x08];
  f32 unknown0c[3]; // Inferred role: aabb max; original member name unknown.
  f32 unknown18[3]; // Inferred role: aabb min; original member name unknown.
  u8 _24[0x44 - 0x24];
};

static_assert(offsetof(MdsMdlEntry, unknown0c) == 0x0c, "");
static_assert(offsetof(MdsMdlEntry, unknown18) == 0x18, "");
static_assert(sizeof(MdsMdlEntry) == 0x44, "");

struct MdoWrkMatRes {
  u8 _000[0x010 - 0x000];
  const u8 *unknown10;            // Inferred role: texture indices; original member name unknown.
  const u8 *unknown18;            // Inferred role: model data; original member name unknown.
  const MdsMeshHeader *unknown20; // Inferred role: mesh header; original member name unknown.
  MdsMatInfoHeader *unknown28;    // Inferred role: mat data; original member name unknown.
  s32 unknown30;                  // Inferred role: mat count; original member name unknown.
  u8 _034[0x038 - 0x034];
  f32 *unknown38; // Inferred role: base values; original member name unknown.
  u8 _040[0x050 - 0x040];
  const u8 *unknown50; // Inferred role: fixed anim data; original member name unknown.
  const u8 *unknown58; // Inferred role: fixed anim arrays; original member name unknown.
  const u8 *unknown60; // Inferred role: fixed anim arrays; original member name unknown.
  const u8 *unknown68; // Inferred role: fixed anim arrays; original member name unknown.
  u8 _070[0x090 - 0x070];
  grlib::CGLibUniformArray<grlib::CGLibDblUniformBlock> *unknown90; // Inferred role: material uniforms; original member name unknown.
  u8 _098[0x0a0 - 0x098];
  grlib::CGLibUniformArray<grlib::CGLibTriUniformBlock> *unknowna0; // Inferred role: mdl uniforms; original member name unknown.
  u8 _0a8[0x0b0 - 0x0a8];
  grlib::CGLibUniformArray<grlib::CGLibDblUniformBlock> *unknownb0; // Inferred role: vol tex uniforms; original member name unknown.
  grlib::CGLibUniformArray<grlib::CGLibDblUniformBlock> *unknownb8; // Inferred role: rim bloom uniforms; original member name unknown.
  DrResMdoMat *unknownc0;                                           // Inferred role: mat entries; original member name unknown.
  DrResMdoVertex *unknownc8;                                        // Inferred role: vertex; original member name unknown.
  DrResMdoTexList *unknownd0;                                       // Inferred role: texture list; original member name unknown.
  u8 _0d8[0x0e8 - 0x0d8];
  grlib::CGLibTextureBuffer **unknowne8; // Inferred role: textures; original member name unknown.
  s32 unknownf0;                         // Inferred role: texture count; original member name unknown.
  u8 _0f4[0x0f8 - 0x0f4];
  f32 *unknownf8; // Inferred role: values; original member name unknown.
  u8 _100[0x110 - 0x100];
  MdoWrkAvatar *unknown110;     // Inferred role: avatar; original member name unknown.
  MdoWrkShaderParm *unknown118; // Inferred role: shader parm; original member name unknown.
  u8 _120[0x150 - 0x120];
  MdoWrkVanishEffect *unknown150; // Inferred role: vanish effects; original member name unknown.
  MdoWrkRimBloom *unknown158;     // Inferred role: rim blooms; original member name unknown.
  u8 _160[0x168 - 0x160];
  const MdsMdlEntry *unknown168; // Inferred role: mdl entries; original member name unknown.
  u32 unknown170;                // Inferred role: mdl entry count; original member name unknown.
};

static_assert(offsetof(MdoWrkMatRes, unknown10) == 0x010, "");
static_assert(offsetof(MdoWrkMatRes, unknown50) == 0x050, "");
static_assert(offsetof(MdoWrkMatRes, unknown68) == 0x068, "");
static_assert(offsetof(MdoWrkMatRes, unknown18) == 0x018, "");
static_assert(offsetof(MdoWrkMatRes, unknown20) == 0x020, "");
static_assert(offsetof(MdoWrkMatRes, unknown28) == 0x028, "");
static_assert(offsetof(MdoWrkMatRes, unknown30) == 0x030, "");
static_assert(offsetof(MdoWrkMatRes, unknown38) == 0x038, "");
static_assert(offsetof(MdoWrkMatRes, unknown90) == 0x090, "");
static_assert(offsetof(MdoWrkMatRes, unknowna0) == 0x0a0, "");
static_assert(offsetof(MdoWrkMatRes, unknownb0) == 0x0b0, "");
static_assert(offsetof(MdoWrkMatRes, unknownb8) == 0x0b8, "");
static_assert(offsetof(MdoWrkMatRes, unknownc0) == 0x0c0, "");
static_assert(offsetof(MdoWrkMatRes, unknownc8) == 0x0c8, "");
static_assert(offsetof(MdoWrkMatRes, unknownd0) == 0x0d0, "");
static_assert(offsetof(MdoWrkMatRes, unknowne8) == 0x0e8, "");
static_assert(offsetof(MdoWrkMatRes, unknownf0) == 0x0f0, "");
static_assert(offsetof(MdoWrkMatRes, unknownf8) == 0x0f8, "");
static_assert(offsetof(MdoWrkMatRes, unknown110) == 0x110, "");
static_assert(offsetof(MdoWrkMatRes, unknown118) == 0x118, "");
static_assert(offsetof(MdoWrkMatRes, unknown150) == 0x150, "");
static_assert(offsetof(MdoWrkMatRes, unknown158) == 0x158, "");
static_assert(offsetof(MdoWrkMatRes, unknown168) == 0x168, "");
static_assert(offsetof(MdoWrkMatRes, unknown170) == 0x170, "");

struct MdoWrkVanishEffect {
  u8 _00[0xa4 - 0x00];
  f32 unknowna4; // Inferred role: ratio; original member name unknown.
  u8 _a8[0xd4 - 0xa8];
  u32 unknownd4; // Inferred role: flags; original member name unknown.
  u8 _d8[0xe0 - 0xd8];
};

static_assert(offsetof(MdoWrkVanishEffect, unknowna4) == 0xa4, "");
static_assert(offsetof(MdoWrkVanishEffect, unknownd4) == 0xd4, "");
static_assert(sizeof(MdoWrkVanishEffect) == 0xe0, "");

class DrMdoMat : public DrMdlBase {
public:
  enum DrawFlag {
    DRAW_FLAG_ALWAYS_TEX_STM = 1 << 2,
    DRAW_FLAG_WRITE_STENCIL = 1 << 4,
    DRAW_FLAG_FLAG_WAVE = 1 << 6,
    DRAW_FLAG_SIMPLE_SHADOW = 1 << 10,
    DRAW_FLAG_SP_ALPHA_MODE = 1 << 14,
    DRAW_FLAG_SP_BLUR_OFF = 1 << 15,
    DRAW_FLAG_GPU_CLIP_OFF = 1 << 16,
    DRAW_FLAG_ALWAYS_MIDDLE_TEX_STM = 1 << 17,
    DRAW_FLAG_OCCLUSION_QUERY_OFF = 1 << 18,
    DRAW_FLAG_EXPRESS_DRAW_MODE = 1 << 20,
    DRAW_FLAG_CAM_CHECK_MODE = 1 << 28,
    DRAW_FLAG_CAM_CHECK_RESL = 1 << 29,
    DRAW_FLAG_DEBUG_DELETE = 1 << 30,
    DRAW_FLAG_DEBUG_WINDOW = 1u << 31,
  };

  enum MdlFlag {
    MDL_FLAG_UNKNOWN_0 = 1 << 0,
    MDL_FLAG_UNKNOWN_1 = 1 << 1,
    MDL_FLAG_UNKNOWN_2 = 1 << 2,
    MDL_FLAG_UNKNOWN_3 = 1 << 3,
    MDL_FLAG_UNKNOWN_4 = 1 << 4,
    MDL_FLAG_UNKNOWN_5 = 1 << 5,
    MDL_FLAG_UNKNOWN_6 = 1 << 6,
    MDL_FLAG_UNKNOWN_20 = 1 << 20,
    MDL_FLAG_BLOOM = 1 << 15,
    MDL_FLAG_ALPHA_BLOOM = 1 << 16,
    MDL_FLAG_VOLUME = 1 << 17,
    MDL_FLAG_FULL_SCREEN_SHADOW = 1 << 18,
    MDL_FLAG_UNKNOWN_25 = 1 << 25,
    MDL_FLAG_UNKNOWN_26 = 1 << 26,
    MDL_FLAG_UNKNOWN_27 = 1 << 27,
  };

  enum AlphaFlag {
    ALPHA_FLAG_UPDATED = 1 << 16,
    ALPHA_FLAG_SINGLE_BUFFER = 1 << 18,
  };

  void releaseMat();
  void setDrMan(DrMan *drMan);
  void updateAlphaCall();
  bool isBloomMdl() const;
  bool isAlphaBloomMdl() const;
  u32 getVanishEffectMax() const;
  bool isFullScreenShadowMdl() const;
  MdoWrkVanishEffect *getVanishEffectWrk(u32 index, u32 bufferIndex);
  bool isVolumeMdl() const;
  void setFlagWaveOn(bool isOn);
  void setExtraShaderSetup(const void *shader);
  void releaseExtraShader();
  void matCall_TransVal(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_CalcColor(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_EmissiveTime(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_RgbTime(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_RTime(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_AccRgb1(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_AccRgb2(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_AccRgb3(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_AccRgb4(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_AccMulRgb1(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_AccMulRgb2(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_AccMulRgb3(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_AccMulRgb4(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_AccVal1(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_AccVal2(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_AccVal3(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_AccVal4(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_AccMulVal1(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_AccMulVal2(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_AccMulVal3(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_AccMulVal4(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_CalcBloom(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_ToonId(const MdsMatInfoHeader *header, int valueIndex, int matIndex);
  void matCall_VolumeTest(const MdsMatInfoHeader *header, int valueIndex, int matIndex);

  u8 _24[0x28 - 0x24];
  DrMan *m_drMan;
  MdoWrkMatRes *unknown30;             // Inferred role: mat res; original member name unknown.
  DrShdMdoDecExtTbl *unknown38;        // Inferred role: dec ext tbl; original member name unknown.
  mm::Col3 *unknown40;                 // Inferred role: avatar map colors; original member name unknown.
  const MdsMatCharMkTexTbl *unknown48; // Inferred role: char mk textures; original member name unknown.
  void *unknown50;                     // Inferred role: dammy data; original member name unknown.
  DrMdoSmlShadowObj *unknown58;        // Inferred role: sml shadow; original member name unknown.
  u8 _60[0x70 - 0x60];
  mm::Mat44 m_matrix;
  mm::Vec3 m_offsetPos;
  u8 _c0[0xd0 - 0xc0];
  f32 unknownd0[2]; // Inferred role: alphas; original member name unknown.
  f32 unknownd8;    // Inferred role: bloom; original member name unknown.
  f32 unknowndc;    // Inferred role: frame spd; original member name unknown.
  f32 unknowne0;    // Inferred role: alpha; original member name unknown.
  u8 _e4[0xe8 - 0xe4];
  f32 unknowne8; // Inferred role: scale; original member name unknown.
  u8 _ec[0xf0 - 0xec];
  bool m_gpuRender;
  u8 _f1;
  u16 unknownf2; // Inferred role: render pass id; original member name unknown.
  u16 unknownf4; // Inferred role: render pass index; original member name unknown.
  u8 _f6[0xf8 - 0xf6];
  u32 unknownf8;  // Inferred role: mdl flags; original member name unknown.
  u32 unknownfc;  // Inferred role: draw flags; original member name unknown.
  u32 unknown100; // Inferred role: alpha flags; original member name unknown.
  u8 _104[0x110 - 0x104];
  mm::Vec3 m_AABBMax;
  mm::Vec3 m_AABBMin;
  mm::Vec3 unknown130; // Inferred role: center; original member name unknown.
  u8 _140[0x160 - 0x140];
  f32 unknown160; // Inferred role: length; original member name unknown.
  u8 _164[0x16a - 0x164];
  u8 unknown16a; // Inferred role: char mk texture count; original member name unknown.
  u8 _16b;
};

static_assert(offsetof(DrMdoMat, m_drMan) == 0x28, "");
static_assert(offsetof(DrMdoMat, unknown30) == 0x30, "");
static_assert(offsetof(DrMdoMat, unknown38) == 0x38, "");
static_assert(offsetof(DrMdoMat, unknown40) == 0x40, "");
static_assert(offsetof(DrMdoMat, unknown48) == 0x48, "");
static_assert(offsetof(DrMdoMat, unknown50) == 0x50, "");
static_assert(offsetof(DrMdoMat, unknown58) == 0x58, "");
static_assert(offsetof(DrMdoMat, m_matrix) == 0x70, "");
static_assert(offsetof(DrMdoMat, m_offsetPos) == 0xb0, "");
static_assert(offsetof(DrMdoMat, unknownd0) == 0xd0, "");
static_assert(offsetof(DrMdoMat, unknownd8) == 0xd8, "");
static_assert(offsetof(DrMdoMat, unknowndc) == 0xdc, "");
static_assert(offsetof(DrMdoMat, unknowne0) == 0xe0, "");
static_assert(offsetof(DrMdoMat, unknowne8) == 0xe8, "");
static_assert(offsetof(DrMdoMat, m_gpuRender) == 0xf0, "");
static_assert(offsetof(DrMdoMat, unknownf2) == 0xf2, "");
static_assert(offsetof(DrMdoMat, unknownf4) == 0xf4, "");
static_assert(offsetof(DrMdoMat, unknownf8) == 0xf8, "");
static_assert(offsetof(DrMdoMat, unknownfc) == 0xfc, "");
static_assert(offsetof(DrMdoMat, unknown100) == 0x100, "");
static_assert(offsetof(DrMdoMat, m_AABBMax) == 0x110, "");
static_assert(offsetof(DrMdoMat, m_AABBMin) == 0x120, "");
static_assert(offsetof(DrMdoMat, unknown130) == 0x130, "");
static_assert(offsetof(DrMdoMat, unknown160) == 0x160, "");
static_assert(offsetof(DrMdoMat, unknown16a) == 0x16a, "");

} // namespace ml
