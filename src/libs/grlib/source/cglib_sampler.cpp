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

CGLibSampler::CGLibSampler() {
  m_params.m_borderColor.b = 1.0f;
  m_params.m_borderColor.a = 1.0f;
  m_params.m_value = 0;
  m_params.m_borderColor.r = 1.0f;
  m_params.m_borderColor.g = 1.0f;
  m_params.m_lod = 0.0f;
  m_resource = nullptr;
}

CGLibSampler::~CGLibSampler() { release(); }

void CGLibSampler::release() {
  if (m_resource != nullptr) {
    context::CGLibSystemContext::get()->m_buffSamplerTbl.freeSampler(m_resource);
  }
}

void CGLibSampler::initSampler(GrlTexClamp clamp, GrlTexMagFilterType filter) {
  m_params.m_value = 0;
  setClamp(clamp, clamp, clamp);
  m_params.m_magFilter = filter;
  if (filter != GRL_TEX_MAG_FILTER_NEAREST) {
    m_params.m_minFilter = GRL_TEX_MIN_FILTER_LINEAR;
  }
  m_params.m_borderColor = mm::Col4(1.0f, 1.0f, 1.0f, 1.0f);
  m_params.m_lod = 0.0f;
}

void CGLibSampler::setClamp(GrlTexClamp clampS, GrlTexClamp clampT, GrlTexClamp clampR) {
  m_params.m_clampS = clampS;
  m_params.m_clampT = clampT;
  m_params.m_clampR = clampR;
  if (clampS >= GRL_TEX_CLAMP_CLAMP_TO_BORDER || clampT >= GRL_TEX_CLAMP_CLAMP_TO_BORDER || clampR >= GRL_TEX_CLAMP_CLAMP_TO_BORDER) {
    m_params.m_isBorder = true;
  } else {
    m_params.m_isBorder = false;
  }
}

void CGLibSampler::setFilter(GrlTexMagFilterType magFilter, GrlTexMinFilterType minFilter, GrlTexTexAnisoRatio anisoRatio) {
  m_params.m_magFilter = magFilter;
  m_params.m_minFilter = minFilter;
  m_params.m_anisoRatio = anisoRatio;
}

void CGLibSampler::setLOD(f32 lod) { m_params.m_lod = lod; }

void CGLibSampler::setDepthCompare(GrlTexCompare compare) { m_params.m_compare = compare; }

void CGLibSampler::setBorderType(GrlTexBorderType type) {
  const mm::Col4 &color = s_borderColors[type];
  m_params.m_borderColor.r = color.r;
  m_params.m_borderColor.g = color.g;
  m_params.m_borderColor.b = color.b;
  m_params.m_borderColor.a = color.a;
}

void CGLibSampler::setBorderColor(const mm::Col4 &color) {
  m_params.m_borderColor.r = color.r;
  m_params.m_borderColor.g = color.g;
  m_params.m_borderColor.b = color.b;
  m_params.m_borderColor.a = color.a;
}

void CGLibSampler::updateData() {
  if (m_resource != nullptr) {
    context::CGLibSystemContext::get()->m_buffSamplerTbl.freeSampler(m_resource);
  }
  m_resource = context::CGLibSystemContext::get()->m_buffSamplerTbl.allocSampler(m_params);
}

} // namespace grlib
