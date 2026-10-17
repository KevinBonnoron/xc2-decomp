#pragma once
#include <stddef.h>

#include "grlib/cglib_texture_buffer.h"
#include "mm_math/mm_col3.h"
#include "mm_math/mm_mat44.h"
#include "types.h"

namespace ml {

class DrLightObjGlobalIBL {
public:
  static const int TEXTURE_MAX = 7;
  static const int SH_TERM_NUM = 4;

  u8 _00[0x08 - 0x00];
  int m_version;
  u8 _0c[0x14 - 0x0c];
  int m_textureNum;
  u8 _18[0x78 - 0x18];
  grlib::CGLibTextureBuffer m_textures[TEXTURE_MAX];
  u8 _388[0x3a0 - 0x388];
  mm::Col3 m_additionalAmbient;
  u8 _3ac[0x3b0 - 0x3ac];
  f32 m_skyIntensity;
  f32 m_dirLightIntensity;
  u8 _3b8[0x450 - 0x3b8];
  f32 m_shTerms[TEXTURE_MAX][SH_TERM_NUM][9];
  mm::Mat44 m_shMatrices[TEXTURE_MAX * SH_TERM_NUM];
};

static_assert(offsetof(DrLightObjGlobalIBL, m_version) == 0x08, "");
static_assert(offsetof(DrLightObjGlobalIBL, m_textureNum) == 0x14, "");
static_assert(offsetof(DrLightObjGlobalIBL, m_textures) == 0x78, "");
static_assert(offsetof(DrLightObjGlobalIBL, m_additionalAmbient) == 0x3a0, "");
static_assert(offsetof(DrLightObjGlobalIBL, m_skyIntensity) == 0x3b0, "");
static_assert(offsetof(DrLightObjGlobalIBL, m_dirLightIntensity) == 0x3b4, "");
static_assert(offsetof(DrLightObjGlobalIBL, m_shTerms) == 0x450, "");
static_assert(offsetof(DrLightObjGlobalIBL, m_shMatrices) == 0x840, "");

} // namespace ml
