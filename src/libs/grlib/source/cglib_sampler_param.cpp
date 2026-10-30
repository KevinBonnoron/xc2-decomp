#include "grlib/cglib_sampler_param.h"

#include "grlib/cglib_manager.h"
#include "grlib/cglib_sampler.h"
#include "grlib/cglib_sampler_descriptor.h"
#include "grlib/cglib_system_context.h"
#include "mm_math/mm_col4.h"
#include "nvn/nvn.h"

namespace grlib {

namespace {

// Inferred role: NVN wrap mode of each GrlTexClamp; original name unknown.
const NVNwrapMode unknown003[] = {
    NVN_WRAP_MODE_REPEAT,
    NVN_WRAP_MODE_MIRRORED_REPEAT,
    NVN_WRAP_MODE_CLAMP_TO_EDGE,
    NVN_WRAP_MODE_MIRROR_CLAMP_TO_EDGE,
    NVN_WRAP_MODE_CLAMP,
    NVN_WRAP_MODE_MIRROR_CLAMP,
    NVN_WRAP_MODE_CLAMP_TO_BORDER,
    NVN_WRAP_MODE_MIRROR_CLAMP_TO_BORDER,
};

// Inferred role: NVN min filter of each GrlTexMinFilterType; original name unknown.
const NVNminFilter unknown004[] = {
    NVN_MIN_FILTER_NEAREST,
    NVN_MIN_FILTER_LINEAR,
    NVN_MIN_FILTER_NEAREST_MIPMAP_NEAREST,
    NVN_MIN_FILTER_LINEAR_MIPMAP_NEAREST,
    NVN_MIN_FILTER_NEAREST_MIPMAP_LINEAR,
    NVN_MIN_FILTER_LINEAR_MIPMAP_LINEAR,
};

// Inferred role: NVN mag filter of each GrlTexMagFilterType; original name unknown.
const NVNmagFilter unknown005[] = {
    NVN_MAG_FILTER_NEAREST,
    NVN_MAG_FILTER_LINEAR,
};

// Inferred role: max anisotropy of each GrlTexTexAnisoRatio; original name unknown.
const f32 unknown006[] = {
    1.0f,
    2.0f,
    3.0f,
    4.0f,
    5.0f,
    6.0f,
    7.0f,
    8.0f,
    9.0f,
    10.0f,
    11.0f,
    12.0f,
    13.0f,
    14.0f,
    15.0f,
    16.0f,
};

// Inferred role: NVN compare function of each GrlTexCompare; original name unknown.
const NVNcompareFunc unknown007[] = {
    NVN_COMPARE_FUNC_NEVER,
    NVN_COMPARE_FUNC_LESS,
    NVN_COMPARE_FUNC_EQUAL,
    NVN_COMPARE_FUNC_LEQUAL,
    NVN_COMPARE_FUNC_GREATER,
    NVN_COMPARE_FUNC_NOTEQUAL,
    NVN_COMPARE_FUNC_GEQUAL,
    NVN_COMPARE_FUNC_ALWAYS,
};

} // namespace

const f32 CGLibSampler::SAMPLER_LOD_MAX = 15.999f;
const f32 CGLibSampler::SAMPLER_LOD_MIN = 0.0f;

void CGLibSamplerParam::setupResource(const CGLibWkrSamplerParams &params) {
  NVNsamplerBuilder builder;
  nvnSamplerBuilderSetDefaults(&builder);
  nvnSamplerBuilderSetDevice(&builder, &CGLibManager::get()->unknown00);
  nvnSamplerBuilderSetWrapMode(&builder, unknown003[params.m_clampS], unknown003[params.m_clampT], unknown003[params.m_clampR]);
  nvnSamplerBuilderSetMinMagFilter(&builder, unknown004[params.m_minFilter], unknown005[params.m_magFilter]);
  nvnSamplerBuilderSetMaxAnisotropy(&builder, unknown006[params.m_anisoRatio]);
  nvnSamplerBuilderSetLodClamp(&builder, CGLibSampler::SAMPLER_LOD_MIN, CGLibSampler::SAMPLER_LOD_MAX);
  nvnSamplerBuilderSetLodBias(&builder, params.unknown14);
  if (params.m_isBorder) {
    nvnSamplerBuilderSetBorderColor(&builder, &params.unknown04.r);
  }
  if (params.m_compare != 0) {
    nvnSamplerBuilderSetCompare(&builder, NVN_COMPARE_MODE_COMPARE_R_TO_TEXTURE, unknown007[params.m_compare]);
  } else {
    nvnSamplerBuilderSetCompare(&builder, NVN_COMPARE_MODE_NONE, NVN_COMPARE_FUNC_NEVER);
  }
  nvnSamplerInitialize(&unknown00, &builder);
  unknown60 = true;
  if (unknown64 == -1) {
    context::CGLibSystemContext *context = context::CGLibSystemContext::get();
    unknown64 = context->unknown5a0.allocID();
    context->unknown5a0.bindSampler(*this, unknown64);
  }
}

void CGLibSamplerParam::releaseParams() {
  if (unknown60) {
    nvnSamplerFinalize(&unknown00);
    unknown60 = false;
  }
  if (unknown64 != -1) {
    context::CGLibSystemContext::get()->unknown5a0.freeID(unknown64);
    unknown64 = -1;
  }
}

} // namespace grlib
