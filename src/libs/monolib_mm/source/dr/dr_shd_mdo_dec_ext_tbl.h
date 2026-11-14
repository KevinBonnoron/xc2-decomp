#pragma once
#include <stddef.h>

#include "grlib/cglib_dec_shd_ext_tbl.h"
#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {
class DrResMdoSampler;
class DrShdMdoDecRes;
struct MdsMatTextureInfo;

class DrShdMdoDecExtTbl : public grlib::CGLibDecShdExtTbl {
public:
  DrShdMdoDecExtTbl();
  ~DrShdMdoDecExtTbl();
  void setTextureParam(int num);
  u32 getValGlobalParam(int index);
  void bindShader();
  void setShaderParamAdd(u32 *param, u32 *globalParam);
  void setTextureList(const MdsMatTextureInfo *infos, grlib::CGLibTextureBuffer **textures, DrResMdoSampler *sampler);

  DrShdMdoDecRes *unknown18; // Inferred role: dec res; original member name unknown.
  u32 *unknown20;            // Inferred role: shader param add; original member name unknown.
  u32 *m_valGlobalParam;
  u8 unknown30; // Inferred role: global parameter index of the billboard uniform block; original member name unknown.
  u8 _31[0x36 - 0x31];
  u8 unknown36; // Inferred role: texture count; original member name unknown.
  u8 _37[0x38 - 0x37];
};

static_assert(offsetof(DrShdMdoDecExtTbl, unknown18) == 0x18, "");
static_assert(offsetof(DrShdMdoDecExtTbl, m_valGlobalParam) == 0x28, "");
static_assert(offsetof(DrShdMdoDecExtTbl, unknown30) == 0x30, "");
static_assert(offsetof(DrShdMdoDecExtTbl, unknown36) == 0x36, "");
static_assert(sizeof(DrShdMdoDecExtTbl) == 0x38, "");

} // namespace ml
