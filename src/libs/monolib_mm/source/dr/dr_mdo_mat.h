#pragma once
#include <stddef.h>

#include "dr/dr_mdl_base.h"
#include "mm_math/mm_col3.h"
#include "types.h"

namespace ml {
struct MdsMatInfoHeader {
  u8 _00[0x74 - 0x00];
};

static_assert(sizeof(MdsMatInfoHeader) == 0x74, "");

struct MdoWrkRimBloom;

struct MdsMeshPartsInfo {
  u8 _00[0x08 - 0x00];
  u8 flags;
  u8 _09[0x10 - 0x09];
};

static_assert(sizeof(MdsMeshPartsInfo) == 0x10, "");

struct MdsMeshHeader {
  u8 _00[0x64 - 0x00];
  u32 partsInfoOffset;
};

static_assert(offsetof(MdsMeshHeader, partsInfoOffset) == 0x64, "");

struct MdoWrkMatEntry {
  u8 _00[0x20 - 0x00];
};

static_assert(sizeof(MdoWrkMatEntry) == 0x20, "");

struct MdoWrkAvatarColors {
  f32 *values;
};

struct MdoWrkAvatar {
  u32 flags;
  u8 _04[0x08 - 0x04];
  void *baseTextures[2];
  void *textures[2];
  void *eyeBaseTexture;
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

struct MdoWrkMatRes {
  u8 _000[0x020 - 0x000];
  const MdsMeshHeader *meshHeader;
  MdsMatInfoHeader *matData;
  u32 matCount;
  u8 _034[0x0c0 - 0x034];
  MdoWrkMatEntry *matEntries;
  u8 _0c8[0x110 - 0x0c8];
  MdoWrkAvatar *avatar;
  MdoWrkShaderParm *shaderParm;
  u8 _120[0x158 - 0x120];
  MdoWrkRimBloom *rimBlooms;
};

static_assert(offsetof(MdoWrkMatRes, meshHeader) == 0x020, "");
static_assert(offsetof(MdoWrkMatRes, matData) == 0x028, "");
static_assert(offsetof(MdoWrkMatRes, matCount) == 0x030, "");
static_assert(offsetof(MdoWrkMatRes, matEntries) == 0x0c0, "");
static_assert(offsetof(MdoWrkMatRes, avatar) == 0x110, "");
static_assert(offsetof(MdoWrkMatRes, shaderParm) == 0x118, "");
static_assert(offsetof(MdoWrkMatRes, rimBlooms) == 0x158, "");

struct MdoWrkVanishEffect {
  u8 _00[0xa4 - 0x00];
  f32 ratio;
  u8 _a8[0xd4 - 0xa8];
  u32 flags;
};

static_assert(offsetof(MdoWrkVanishEffect, ratio) == 0xa4, "");
static_assert(offsetof(MdoWrkVanishEffect, flags) == 0xd4, "");

class DrMdoMat : public DrMdlBase {
public:
  u32 getVanishEffectMax() const;
  MdoWrkVanishEffect *getVanishEffectWrk(u32 index, u32 bufferIndex);
  void setExtraShaderSetup(const void *shader);
  void releaseExtraShader();

  u8 _24[0x30 - 0x24];
  MdoWrkMatRes *m_matRes;
};

static_assert(offsetof(DrMdoMat, m_matRes) == 0x30, "");

} // namespace ml
