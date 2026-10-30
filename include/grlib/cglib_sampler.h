#pragma once
#include <stddef.h>

#include "mm_math/mm_col4.h"
#include "types.h"

enum GrlTexClamp {
  GRL_TEX_CLAMP_REPEAT,
  GRL_TEX_CLAMP_MIRRORED_REPEAT,
  GRL_TEX_CLAMP_CLAMP,
  GRL_TEX_CLAMP_CLAMP_TO_EDGE,
  GRL_TEX_CLAMP_MIRROR_CLAMP,
  GRL_TEX_CLAMP_MIRROR_CLAMP_TO_EDGE,
  GRL_TEX_CLAMP_CLAMP_TO_BORDER,
  GRL_TEX_CLAMP_MIRROR_CLAMP_TO_BORDER,
};

enum GrlTexMagFilterType {
  GRL_TEX_MAG_FILTER_NEAREST,
  GRL_TEX_MAG_FILTER_LINEAR,
};

enum GrlTexMinFilterType {
  GRL_TEX_MIN_FILTER_NEAREST,
  GRL_TEX_MIN_FILTER_LINEAR,
};

enum GrlTexTexAnisoRatio {};

enum GrlTexCompare {};

enum GrlTexBorderType {
  GRL_TEX_BORDER_TRANSPARENT_BLACK,
  GRL_TEX_BORDER_OPAQUE_BLACK,
  GRL_TEX_BORDER_OPAQUE_WHITE,
};

namespace grlib {

class CGLibBuffResSamObj;

struct CGLibWkrSamplerParams {
  CGLibWkrSamplerParams() { unknown001(); }

  // Inferred role: reset the params to their defaults; original name unknown.
  void unknown001() {
    m_value = 0;
    unknown04.r = unknown04.g = unknown04.b = unknown04.a = 1.0f;
    unknown14 = 0.0f;
  }

  union {
    struct {
      u32 m_clampS : 4;
      u32 m_clampT : 4;
      u32 m_clampR : 4;
      u32 m_compare : 4;
      u32 m_magFilter : 1;
      u32 m_minFilter : 5;
      u32 m_anisoRatio : 4;
      u32 m_isBorder : 1;
    };
    u32 m_value;
  };
  mm::Col4 unknown04; // Inferred role: border color; original member name unknown.
  f32 unknown14;      // Inferred role: lod; original member name unknown.
};

static_assert(offsetof(CGLibWkrSamplerParams, unknown04) == 0x04, "");
static_assert(offsetof(CGLibWkrSamplerParams, unknown14) == 0x14, "");

class CGLibSampler {
public:
  static const f32 SAMPLER_LOD_MAX;
  static const f32 SAMPLER_LOD_MIN;

  CGLibSampler();
  ~CGLibSampler();
  void release();
  void initSampler(GrlTexClamp clamp, GrlTexMagFilterType filter);
  void setClamp(GrlTexClamp clampS, GrlTexClamp clampT, GrlTexClamp clampR);
  void setFilter(GrlTexMagFilterType magFilter, GrlTexMinFilterType minFilter, GrlTexTexAnisoRatio anisoRatio);
  void setLOD(f32 lod);
  void setDepthCompare(GrlTexCompare compare);
  void setBorderType(GrlTexBorderType type);
  void setBorderColor(const mm::Col4 &color);
  void updateData();

  CGLibWkrSamplerParams unknown00; // Inferred role: params; original member name unknown.
  CGLibBuffResSamObj *unknown18;   // Inferred role: resource; original member name unknown.
};

static_assert(offsetof(CGLibSampler, unknown18) == 0x18, "");
static_assert(sizeof(CGLibSampler) == 0x20, "");

} // namespace grlib
