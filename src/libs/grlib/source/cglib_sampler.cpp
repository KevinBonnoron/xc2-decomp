#include "grlib/cglib_sampler.h"

#include "grlib/cglib_buff_sampler_tbl.h"
#include "grlib/cglib_system_context.h"

namespace grlib {

namespace {
const mm::Col4 s_borderColors[] = {
    mm::Col4(0.0f, 0.0f, 0.0f, 0.0f),
    mm::Col4(0.0f, 0.0f, 0.0f, 1.0f),
    mm::Col4(1.0f, 1.0f, 1.0f, 1.0f),
};
} // namespace

CGLibSampler::CGLibSampler() : unknown18(nullptr) {}

CGLibSampler::~CGLibSampler() { release(); }

void CGLibSampler::release() {
  if (unknown18 != nullptr) {
    context::CGLibSystemContext::get()->unknown608.freeSampler(unknown18);
  }
}

void CGLibSampler::initSampler(GrlTexClamp clamp, GrlTexMagFilterType filter) {
  unknown00.m_value = 0;
  setClamp(clamp, clamp, clamp);
  unknown00.m_magFilter = filter;
  if (filter != GRL_TEX_MAG_FILTER_NEAREST) {
    unknown00.m_minFilter = GRL_TEX_MIN_FILTER_LINEAR;
  }
  unknown00.unknown04 = mm::Col4(1.0f, 1.0f, 1.0f, 1.0f);
  unknown00.unknown14 = 0.0f;
}

void CGLibSampler::setClamp(GrlTexClamp clampS, GrlTexClamp clampT, GrlTexClamp clampR) {
  unknown00.m_clampS = clampS;
  unknown00.m_clampT = clampT;
  unknown00.m_clampR = clampR;
  if (clampS >= GRL_TEX_CLAMP_CLAMP_TO_BORDER || clampT >= GRL_TEX_CLAMP_CLAMP_TO_BORDER || clampR >= GRL_TEX_CLAMP_CLAMP_TO_BORDER) {
    unknown00.m_isBorder = true;
  } else {
    unknown00.m_isBorder = false;
  }
}

void CGLibSampler::setFilter(GrlTexMagFilterType magFilter, GrlTexMinFilterType minFilter, GrlTexTexAnisoRatio anisoRatio) {
  unknown00.m_magFilter = magFilter;
  unknown00.m_minFilter = minFilter;
  unknown00.m_anisoRatio = anisoRatio;
}

void CGLibSampler::setLOD(f32 lod) { unknown00.unknown14 = lod; }

void CGLibSampler::setDepthCompare(GrlTexCompare compare) { unknown00.m_compare = compare; }

void CGLibSampler::setBorderType(GrlTexBorderType type) {
  const mm::Col4 &color = s_borderColors[type];
  unknown00.unknown04.r = color.r;
  unknown00.unknown04.g = color.g;
  unknown00.unknown04.b = color.b;
  unknown00.unknown04.a = color.a;
}

void CGLibSampler::setBorderColor(const mm::Col4 &color) {
  unknown00.unknown04.r = color.r;
  unknown00.unknown04.g = color.g;
  unknown00.unknown04.b = color.b;
  unknown00.unknown04.a = color.a;
}

void CGLibSampler::updateData() {
  if (unknown18 != nullptr) {
    context::CGLibSystemContext::get()->unknown608.freeSampler(unknown18);
  }
  unknown18 = context::CGLibSystemContext::get()->unknown608.allocSampler(unknown00);
}

} // namespace grlib
