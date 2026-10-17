#pragma once
#include <stddef.h>

#include "dr/dr_mdl_base.h"
#include "mm_math/mm_col3.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {
class DrMan;
class DrMdoSmlShadowObj;
struct MdsMatCharMkTexTbl;
class DrResMdoTexList;
class DrResMdoVertex;

struct MdsMatInfoHeader {
  u8 _00[0x20 - 0x00];
  u32 textureIndexOffset;
  u8 _24[0x40 - 0x24];
  u32 valueOffset;
  u8 _44[0x64 - 0x44];
  u16 timeValueIndex;
  u8 _66[0x74 - 0x66];
};

static_assert(offsetof(MdsMatInfoHeader, textureIndexOffset) == 0x20, "");
static_assert(offsetof(MdsMatInfoHeader, valueOffset) == 0x40, "");
static_assert(offsetof(MdsMatInfoHeader, timeValueIndex) == 0x64, "");

static_assert(sizeof(MdsMatInfoHeader) == 0x74, "");

struct MdoWrkRimBloom;
struct MdoWrkVanishEffect;

struct MdsMeshPartsInfo {
  u8 _00[0x08 - 0x00];
  u8 flags;
  u8 _09[0x10 - 0x09];
};

static_assert(sizeof(MdsMeshPartsInfo) == 0x10, "");

struct MdsMeshHeader {
  enum Flag {
    FLAG_VANISH_EFFECT = 1 << 13,
  };

  u16 flags;
  u8 _02[0x64 - 0x02];
  u32 partsInfoOffset;
  u8 _68[0x94 - 0x68];
  u8 vanishEffectNum;
};

static_assert(offsetof(MdsMeshHeader, partsInfoOffset) == 0x64, "");
static_assert(offsetof(MdsMeshHeader, vanishEffectNum) == 0x94, "");

struct MdoWrkMatEntry {
  const char *name;
  u8 _08[0x20 - 0x08];
};

static_assert(sizeof(MdoWrkMatEntry) == 0x20, "");

struct MdoWrkAvatarColors {
  f32 *values;
};

struct MdoWrkAvatar {
  u32 flags;
  u8 _04[0x08 - 0x04];
  grlib::CGLibTextureBuffer *baseTextures[2];
  void *textures[2];
  grlib::CGLibTextureBuffer *eyeBaseTexture;
  void *eyeTexture;
  bool dollMat;
  u8 _39[0x40 - 0x39];
  MdoWrkAvatarColors *charColors;
  MdoWrkAvatarColors *dollColors;
};

static_assert(offsetof(MdoWrkAvatar, baseTextures) == 0x08, "");
static_assert(offsetof(MdoWrkAvatar, textures) == 0x18, "");
static_assert(offsetof(MdoWrkAvatar, eyeBaseTexture) == 0x28, "");
static_assert(offsetof(MdoWrkAvatar, eyeTexture) == 0x30, "");
static_assert(offsetof(MdoWrkAvatar, dollMat) == 0x38, "");
static_assert(offsetof(MdoWrkAvatar, charColors) == 0x40, "");
static_assert(offsetof(MdoWrkAvatar, dollColors) == 0x48, "");

struct MdoWrkShaderParm {
  mm::Col3 colors[4];
  f32 values[1];
};

static_assert(offsetof(MdoWrkShaderParm, values) == 0x30, "");

struct MdsMdlInfoHeader {
  u8 _00[0x30 - 0x00];
};

static_assert(sizeof(MdsMdlInfoHeader) == 0x30, "");

struct MdsMdlEntry {
  u32 infoOffset;
  s32 infoCount;
  u8 _08[0x0c - 0x08];
  f32 aabbMax[3];
  f32 aabbMin[3];
  u8 _24[0x44 - 0x24];
};

static_assert(offsetof(MdsMdlEntry, aabbMax) == 0x0c, "");
static_assert(offsetof(MdsMdlEntry, aabbMin) == 0x18, "");
static_assert(sizeof(MdsMdlEntry) == 0x44, "");

struct MdoWrkMatRes {
  u8 _000[0x010 - 0x000];
  const u8 *textureIndices;
  const u8 *modelData;
  const MdsMeshHeader *meshHeader;
  MdsMatInfoHeader *matData;
  s32 matCount;
  u8 _034[0x038 - 0x034];
  f32 *baseValues;
  u8 _040[0x0c0 - 0x040];
  MdoWrkMatEntry *matEntries;
  DrResMdoVertex *vertex;
  DrResMdoTexList *textureList;
  u8 _0d8[0x0e8 - 0x0d8];
  grlib::CGLibTextureBuffer **textures;
  s32 textureCount;
  u8 _0f4[0x0f8 - 0x0f4];
  f32 *values;
  u8 _100[0x110 - 0x100];
  MdoWrkAvatar *avatar;
  MdoWrkShaderParm *shaderParm;
  u8 _120[0x150 - 0x120];
  MdoWrkVanishEffect *vanishEffects;
  MdoWrkRimBloom *rimBlooms;
  u8 _160[0x168 - 0x160];
  const MdsMdlEntry *mdlEntries;
  u32 mdlEntryCount;
};

static_assert(offsetof(MdoWrkMatRes, textureIndices) == 0x010, "");
static_assert(offsetof(MdoWrkMatRes, modelData) == 0x018, "");
static_assert(offsetof(MdoWrkMatRes, meshHeader) == 0x020, "");
static_assert(offsetof(MdoWrkMatRes, matData) == 0x028, "");
static_assert(offsetof(MdoWrkMatRes, matCount) == 0x030, "");
static_assert(offsetof(MdoWrkMatRes, baseValues) == 0x038, "");
static_assert(offsetof(MdoWrkMatRes, matEntries) == 0x0c0, "");
static_assert(offsetof(MdoWrkMatRes, vertex) == 0x0c8, "");
static_assert(offsetof(MdoWrkMatRes, textureList) == 0x0d0, "");
static_assert(offsetof(MdoWrkMatRes, textures) == 0x0e8, "");
static_assert(offsetof(MdoWrkMatRes, textureCount) == 0x0f0, "");
static_assert(offsetof(MdoWrkMatRes, values) == 0x0f8, "");
static_assert(offsetof(MdoWrkMatRes, avatar) == 0x110, "");
static_assert(offsetof(MdoWrkMatRes, shaderParm) == 0x118, "");
static_assert(offsetof(MdoWrkMatRes, vanishEffects) == 0x150, "");
static_assert(offsetof(MdoWrkMatRes, rimBlooms) == 0x158, "");
static_assert(offsetof(MdoWrkMatRes, mdlEntries) == 0x168, "");
static_assert(offsetof(MdoWrkMatRes, mdlEntryCount) == 0x170, "");

struct MdoWrkVanishEffect {
  u8 _00[0xa4 - 0x00];
  f32 ratio;
  u8 _a8[0xd4 - 0xa8];
  u32 flags;
  u8 _d8[0xe0 - 0xd8];
};

static_assert(offsetof(MdoWrkVanishEffect, ratio) == 0xa4, "");
static_assert(offsetof(MdoWrkVanishEffect, flags) == 0xd4, "");
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
    MDL_FLAG_BLOOM = 1 << 15,
    MDL_FLAG_ALPHA_BLOOM = 1 << 16,
    MDL_FLAG_VOLUME = 1 << 17,
    MDL_FLAG_FULL_SCREEN_SHADOW = 1 << 18,
  };

  enum AlphaFlag {
    ALPHA_FLAG_UPDATED = 1 << 16,
    ALPHA_FLAG_SINGLE_BUFFER = 1 << 18,
  };

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
  MdoWrkMatRes *m_matRes;
  u8 _38[0x40 - 0x38];
  mm::Col3 *m_avatarMapColors;
  const MdsMatCharMkTexTbl *m_charMkTextures;
  u8 _50[0x58 - 0x50];
  DrMdoSmlShadowObj *m_smlShadow;
  u8 _60[0x70 - 0x60];
  mm::Mat44 m_matrix;
  u8 _b0[0xd0 - 0xb0];
  f32 m_alphas[2];
  f32 m_bloom;
  f32 m_frameSpd;
  f32 m_alpha;
  u8 _e4[0xe8 - 0xe4];
  f32 m_scale;
  u8 _ec[0xf0 - 0xec];
  bool m_isGpuRender;
  u8 _f1[0xf8 - 0xf1];
  u32 m_mdlFlags;
  u32 m_drawFlags;
  u32 m_alphaFlags;
  u8 _104[0x110 - 0x104];
  mm::Vec3 m_aabbMax;
  mm::Vec3 m_aabbMin;
  mm::Vec3 m_center;
  u8 _140[0x160 - 0x140];
  f32 m_length;
  u8 _164[0x16a - 0x164];
  u8 m_charMkTextureCount;
  u8 _16b;
};

static_assert(offsetof(DrMdoMat, m_drMan) == 0x28, "");
static_assert(offsetof(DrMdoMat, m_matRes) == 0x30, "");
static_assert(offsetof(DrMdoMat, m_avatarMapColors) == 0x40, "");
static_assert(offsetof(DrMdoMat, m_charMkTextures) == 0x48, "");
static_assert(offsetof(DrMdoMat, m_smlShadow) == 0x58, "");
static_assert(offsetof(DrMdoMat, m_matrix) == 0x70, "");
static_assert(offsetof(DrMdoMat, m_alphas) == 0xd0, "");
static_assert(offsetof(DrMdoMat, m_bloom) == 0xd8, "");
static_assert(offsetof(DrMdoMat, m_frameSpd) == 0xdc, "");
static_assert(offsetof(DrMdoMat, m_alpha) == 0xe0, "");
static_assert(offsetof(DrMdoMat, m_scale) == 0xe8, "");
static_assert(offsetof(DrMdoMat, m_isGpuRender) == 0xf0, "");
static_assert(offsetof(DrMdoMat, m_mdlFlags) == 0xf8, "");
static_assert(offsetof(DrMdoMat, m_drawFlags) == 0xfc, "");
static_assert(offsetof(DrMdoMat, m_alphaFlags) == 0x100, "");
static_assert(offsetof(DrMdoMat, m_aabbMax) == 0x110, "");
static_assert(offsetof(DrMdoMat, m_aabbMin) == 0x120, "");
static_assert(offsetof(DrMdoMat, m_center) == 0x130, "");
static_assert(offsetof(DrMdoMat, m_length) == 0x160, "");
static_assert(offsetof(DrMdoMat, m_charMkTextureCount) == 0x16a, "");

} // namespace ml
