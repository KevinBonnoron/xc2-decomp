#include "dr/dr_ap_cache.h"

#include "dr/dr_res_fetch.h"
#include "grlib/cglib_color_ctl.h"
#include "grlib/cglib_ctl_shader.h"
#include "grlib/cglib_ctl_texture.h"
#include "grlib/cglib_depth_ctl.h"
#include "grlib/cglib_polygon.h"
#include "grlib/cglib_sampler.h"
#include "grlib/cglib_texture_buffer.h"

namespace ml {

DrAPCache *DrAPCache::s_pIns;

void DrAPCache::releaseSampler() {
  if (unknown30 != nullptr) {
    delete[] unknown30;
    unknown30 = nullptr;
  }
}

u16 DrAPCache::getSamplerID() {
  if (unknown40 != 0) {
    return unknown40;
  }
  return unknown3a + unknown38 * 4 + m_filter * 16 + m_mipMapOn * 32;
}

void DrAPCache::depthBegin() {
  unknown1c = -1;
  unknown24 = -1;
  unknown14 = -1;
}

void DrAPCache::shadowBegin() {
  unknown1c = 1;
  unknown18 = -1;
  unknown24 = 2;
  unknown08 = 0;
  unknown10 = DR_AP_CULL_TYPE_UNKNOWN_2;
  unknown14 = -1;
  grlib::CGLibDepthCtl::setDepthControl(true, true, GRL_COMPARE_LESS);
  grlib::CGLibPolygon::setCullingOff();
  grlib::CGLibColorCtl::setBlendOffControl(GRL_LOGIC_TYPE_COPY);
}

void DrAPCache::beginZRender() {
  unknown24 = 2;
  unknown1c = 1;
  unknown18 = -1;
  unknown10 = DR_AP_CULL_TYPE_UNKNOWN_2;
  unknown14 = -1;
  grlib::CGLibDepthCtl::setDepthControl(true, true, GRL_COMPARE_LESS);
  grlib::CGLibPolygon::setCullingOff();
  grlib::CGLibColorCtl::setColorBufferOff();
}

void DrAPCache::endZRender() { grlib::CGLibColorCtl::setColorBufferOn(); }

void DrAPCache::beginThicknessRenderFirst() {
  unknown24 = 2;
  unknown18 = -1;
  unknown1c = 0;
  unknown10 = DR_AP_CULL_TYPE_UNKNOWN_2;
  unknown14 = -1;
  grlib::CGLibDepthCtl::setDepthControl(true, false, GRL_COMPARE_LESS);
  grlib::CGLibPolygon::setCullingOff();
  grlib::CGLibColorCtl::setColorChannelMask(true, false, false, false);
  grlib::CGLibColorCtl::setBlendControl(GRL_BLEND_FUNC_ONE, GRL_BLEND_FUNC_ONE, GRL_BLEND_COMBINE_MIN, GRL_BLEND_FUNC_ONE, GRL_BLEND_FUNC_ONE, GRL_BLEND_COMBINE_ADD, GRL_LOGIC_TYPE_COPY);
}

void DrAPCache::endThicknessRenderFirst() { grlib::CGLibColorCtl::setColorBufferOn(); }

void DrAPCache::beginThicknessRenderSecond() {
  unknown24 = 2;
  unknown1c = 1;
  unknown18 = -1;
  unknown10 = DR_AP_CULL_TYPE_UNKNOWN_2;
  unknown14 = -1;
  grlib::CGLibDepthCtl::setDepthControl(true, true, GRL_COMPARE_LESS);
  grlib::CGLibPolygon::setCullingOff();
  grlib::CGLibColorCtl::setColorBufferOff();
}

void DrAPCache::endThicknessRenderSecond() { grlib::CGLibColorCtl::setColorBufferOn(); }

void DrAPCache::beginMdlZRender() {
  unknown24 = 2;
  unknown1c = 1;
  unknown14 = -1;
  unknown18 = -1;
  grlib::CGLibDepthCtl::setDepthControl(true, true, GRL_COMPARE_LESS);
  grlib::CGLibColorCtl::setColorBufferOff();
}

void DrAPCache::endMdlZRender() { grlib::CGLibColorCtl::setColorBufferOn(); }

void DrAPCache::setGBuffRender(u32 mask) {
  if (unknown20 == mask) {
    return;
  }
  unknown20 = mask;
  if (mask == 0x77777777) {
    grlib::CGLibColorCtl::setColorChannelMask(true, true, true, true);
  } else if (mask == 0xffffffff) {
    grlib::CGLibColorCtl::setColorChannelMask(true, true, true, false);
  }
}

void DrAPCache::setMrtGBuffRender(u32 mask, u32 layout) {
  if (unknown20 == mask) {
    return;
  }
  u64 first = layout & 1;
  u64 second = first + ((layout >> 1) & 1);
  unknown20 = mask;
  u8 channels[3] = {0, 0, 0};
  if (mask & 1) {
    channels[0] |= 7;
  }
  if (mask & 2) {
    channels[second] |= 3;
  }
  if (mask & 4) {
    channels[first] |= 2;
  }
  if (mask & 8) {
    channels[first] |= 1;
  }
  if (mask & 0x10) {
    channels[first] |= 8;
  }
  if (mask & 0x20) {
    channels[first] |= 4;
  }
  if (mask & 0x40) {
    channels[second] |= 4;
  }
  for (int i = 0; i < 3; i++) {
    if (channels[i] != 0) {
      grlib::CGLibColorCtl::setColorChannelMask(static_cast<grlib::GrlMrtType>(i), channels[i] & 1, (channels[i] >> 1) & 1, (channels[i] >> 2) & 1, (channels[i] >> 3) & 1);
    }
  }
}

void DrAPCache::endGBuffRender() { grlib::CGLibColorCtl::setColorChannelMask(true, true, true, true); }

void DrAPCache::setRefractionRender() { grlib::CGLibColorCtl::setColorChannelMask(false, false, false, false); }

void DrAPCache::endRefractionRender() { grlib::CGLibColorCtl::setColorChannelMask(true, true, true, true); }

void DrAPCache::setupCulling(DrApCullType cullType) {
  if (unknown10 == cullType) {
    return;
  }
  unknown10 = cullType;
  switch (cullType) {
  case DR_AP_CULL_TYPE_UNKNOWN_0:
    grlib::CGLibPolygon::setCullingBack();
    break;
  case DR_AP_CULL_TYPE_UNKNOWN_1:
    grlib::CGLibPolygon::setCullingFront();
    break;
  case DR_AP_CULL_TYPE_UNKNOWN_2:
    grlib::CGLibPolygon::setCullingOff();
    break;
  default:
    grlib::CGLibPolygon::setCullingDispOff();
    break;
  }
}

// Inferred role: depth write flag of DrAPCache::setupDepthStencil indexed by its depthWrite argument; original name unknown.
static const u8 unknown001[] = {0, 1};

void DrAPCache::setupDepthStencil(int ref, int stencil, int depthWrite, int depthTest) {
  if (unknown14 == ref && unknown18 == stencil && unknown1c == depthWrite && unknown24 == depthTest) {
    return;
  }
  unknown14 = ref;
  unknown18 = stencil;
  unknown1c = depthWrite;
  unknown24 = depthTest;
  bool isTest = true;
  GrlCompare compare = GRL_COMPARE_LESS;
  if (depthTest == 0) {
    isTest = false;
  } else if (depthTest == 1) {
    compare = GRL_COMPARE_LEQUAL;
  } else if (depthTest == 3) {
    compare = GRL_COMPARE_EQUAL;
  }
  bool isStencil = false;
  GrlCompare stencilCompare = GRL_COMPARE_ALWAYS;
  u32 writeMask = 0xff;
  u32 mask = 0xff;
  GrlStencil fail = GRL_STENCIL_REPLACE;
  switch (stencil) {
  case 0:
    break;
  default:
    isStencil = true;
    if (stencil == 7) {
      writeMask = ref | 4;
      mask = 4;
    }
    break;
  case 2:
    isStencil = true;
    stencilCompare = GRL_COMPARE_EQUAL;
    fail = GRL_STENCIL_KEEP;
    writeMask = ref;
    mask = ref;
    break;
  case 3:
    ref = 0;
    isStencil = true;
    break;
  case 4:
    isStencil = true;
    stencilCompare = GRL_COMPARE_NOTEQUAL;
    writeMask = ref;
    mask = ref;
    break;
  case 5:
    isStencil = true;
    stencilCompare = GRL_COMPARE_EQUAL;
    fail = GRL_STENCIL_KEEP;
    writeMask = ref | 0x20;
    mask = ref | 0x20;
    break;
  case 6:
    isStencil = true;
    stencilCompare = GRL_COMPARE_EQUAL;
    writeMask = ref;
    mask = 4;
    break;
  }
  grlib::CGLibDepthCtl::setDepthStencilControl(isTest, unknown001[depthWrite], compare, isStencil, stencilCompare, ref, mask, writeMask, fail, GRL_STENCIL_KEEP, GRL_STENCIL_KEEP);
}

void DrAPCache::setupAlphaBlend(int blend) {
  if (blend == 0) {
    if (unknown08 != 0) {
      grlib::CGLibColorCtl::setBlendOffControl(GRL_LOGIC_TYPE_COPY);
      unknown08 = 0;
    }
  } else if (unknown08 != blend) {
    switch (blend) {
    case 1:
      grlib::CGLibColorCtl::setBlendControl(GRL_BLEND_FUNC_SRC_ALPHA, GRL_BLEND_FUNC_ONE_MINUS_SRC_ALPHA, GRL_BLEND_COMBINE_ADD, GRL_LOGIC_TYPE_COPY);
      break;
    case 2:
      grlib::CGLibColorCtl::setBlendControl(GRL_BLEND_FUNC_SRC_ALPHA, GRL_BLEND_FUNC_ONE, GRL_BLEND_COMBINE_ADD, GRL_LOGIC_TYPE_COPY);
      break;
    case 3:
      grlib::CGLibColorCtl::setBlendControl(GRL_BLEND_FUNC_ZERO, GRL_BLEND_FUNC_SRC_COLOR, GRL_BLEND_COMBINE_ADD, GRL_LOGIC_TYPE_COPY);
      break;
    case 4:
      grlib::CGLibColorCtl::setBlendControl(GRL_BLEND_FUNC_ONE_MINUS_DST_COLOR, GRL_BLEND_FUNC_ZERO, GRL_BLEND_COMBINE_ADD, GRL_LOGIC_TYPE_COPY);
      break;
    case 5:
      grlib::CGLibColorCtl::setBlendControl(GRL_BLEND_FUNC_ONE, GRL_BLEND_FUNC_ONE, GRL_BLEND_COMBINE_ADD, GRL_LOGIC_TYPE_COPY);
      break;
    case 6:
      grlib::CGLibColorCtl::setBlendControl(GRL_BLEND_FUNC_ONE, GRL_BLEND_FUNC_SRC_ALPHA, GRL_BLEND_COMBINE_ADD, GRL_LOGIC_TYPE_COPY);
      break;
    case 7:
      grlib::CGLibColorCtl::setMrtBlend(1, GRL_LOGIC_TYPE_COPY);
      grlib::CGLibColorCtl::setMrtBlendControl(grlib::GRL_MRT_TYPE_0, GRL_BLEND_FUNC_SRC_ALPHA, GRL_BLEND_FUNC_ONE_MINUS_SRC_ALPHA, GRL_BLEND_COMBINE_ADD);
      break;
    }
    unknown08 = blend;
  }
  unknown0c = -1;
}

void DrAPCache::setupMrtAlphaBlend(int blend) {
  if (unknown0c != blend) {
    switch (blend) {
    case 1:
      grlib::CGLibColorCtl::setMrtBlend(7, GRL_LOGIC_TYPE_COPY);
      grlib::CGLibColorCtl::setMrtBlendControl(grlib::GRL_MRT_TYPE_0, GRL_BLEND_FUNC_SRC_ALPHA, GRL_BLEND_FUNC_ONE_MINUS_SRC_ALPHA, GRL_BLEND_COMBINE_ADD);
      grlib::CGLibColorCtl::setMrtBlendControl(grlib::GRL_MRT_TYPE_1, GRL_BLEND_FUNC_SRC_ALPHA, GRL_BLEND_FUNC_ONE_MINUS_SRC_ALPHA, GRL_BLEND_COMBINE_ADD);
      grlib::CGLibColorCtl::setMrtBlendControl(grlib::GRL_MRT_TYPE_2, GRL_BLEND_FUNC_SRC_ALPHA, GRL_BLEND_FUNC_ONE_MINUS_SRC_ALPHA, GRL_BLEND_COMBINE_ADD);
      break;
    case 2:
      grlib::CGLibColorCtl::setMrtBlend(7, GRL_LOGIC_TYPE_COPY);
      grlib::CGLibColorCtl::setMrtBlendControl(grlib::GRL_MRT_TYPE_0, GRL_BLEND_FUNC_SRC_ALPHA, GRL_BLEND_FUNC_ONE, GRL_BLEND_COMBINE_ADD);
      grlib::CGLibColorCtl::setMrtBlendControl(grlib::GRL_MRT_TYPE_1, GRL_BLEND_FUNC_SRC_ALPHA, GRL_BLEND_FUNC_ONE, GRL_BLEND_COMBINE_ADD);
      grlib::CGLibColorCtl::setMrtBlendControl(grlib::GRL_MRT_TYPE_2, GRL_BLEND_FUNC_SRC_ALPHA, GRL_BLEND_FUNC_ONE, GRL_BLEND_COMBINE_ADD);
      break;
    case 3:
      grlib::CGLibColorCtl::setMrtBlend(7, GRL_LOGIC_TYPE_COPY);
      grlib::CGLibColorCtl::setMrtBlendControl(grlib::GRL_MRT_TYPE_0, GRL_BLEND_FUNC_ZERO, GRL_BLEND_FUNC_SRC_COLOR, GRL_BLEND_COMBINE_ADD);
      grlib::CGLibColorCtl::setMrtBlendControl(grlib::GRL_MRT_TYPE_1, GRL_BLEND_FUNC_ZERO, GRL_BLEND_FUNC_SRC_COLOR, GRL_BLEND_COMBINE_ADD);
      grlib::CGLibColorCtl::setMrtBlendControl(grlib::GRL_MRT_TYPE_2, GRL_BLEND_FUNC_ZERO, GRL_BLEND_FUNC_SRC_COLOR, GRL_BLEND_COMBINE_ADD);
      break;
    case 4:
      grlib::CGLibColorCtl::setMrtBlend(7, GRL_LOGIC_TYPE_COPY);
      grlib::CGLibColorCtl::setMrtBlendControl(grlib::GRL_MRT_TYPE_0, GRL_BLEND_FUNC_ONE_MINUS_DST_COLOR, GRL_BLEND_FUNC_ZERO, GRL_BLEND_COMBINE_ADD);
      grlib::CGLibColorCtl::setMrtBlendControl(grlib::GRL_MRT_TYPE_1, GRL_BLEND_FUNC_ONE_MINUS_DST_COLOR, GRL_BLEND_FUNC_ZERO, GRL_BLEND_COMBINE_ADD);
      grlib::CGLibColorCtl::setMrtBlendControl(grlib::GRL_MRT_TYPE_2, GRL_BLEND_FUNC_ONE_MINUS_DST_COLOR, GRL_BLEND_FUNC_ZERO, GRL_BLEND_COMBINE_ADD);
      break;
    case 5:
      grlib::CGLibColorCtl::setMrtBlend(7, GRL_LOGIC_TYPE_COPY);
      grlib::CGLibColorCtl::setMrtBlendControl(grlib::GRL_MRT_TYPE_0, GRL_BLEND_FUNC_ONE, GRL_BLEND_FUNC_ONE, GRL_BLEND_COMBINE_ADD);
      grlib::CGLibColorCtl::setMrtBlendControl(grlib::GRL_MRT_TYPE_1, GRL_BLEND_FUNC_ONE, GRL_BLEND_FUNC_ONE, GRL_BLEND_COMBINE_ADD);
      grlib::CGLibColorCtl::setMrtBlendControl(grlib::GRL_MRT_TYPE_2, GRL_BLEND_FUNC_ONE, GRL_BLEND_FUNC_ONE, GRL_BLEND_COMBINE_ADD);
      break;
    default:
      grlib::CGLibColorCtl::setBlendOffControl(GRL_LOGIC_TYPE_COPY);
      break;
    }
    unknown0c = blend;
  }
  unknown08 = -1;
}

void DrAPCache::setupMrtAlphaBlend(int blend, int mrt) {
  switch (blend) {
  case 1:
    grlib::CGLibColorCtl::setMrtBlend(1 << mrt, GRL_LOGIC_TYPE_COPY);
    grlib::CGLibColorCtl::setMrtBlendControl(static_cast<grlib::GrlMrtType>(mrt), GRL_BLEND_FUNC_SRC_ALPHA, GRL_BLEND_FUNC_ONE_MINUS_SRC_ALPHA, GRL_BLEND_COMBINE_ADD);
    break;
  case 2:
    grlib::CGLibColorCtl::setMrtBlend(1 << mrt, GRL_LOGIC_TYPE_COPY);
    grlib::CGLibColorCtl::setMrtBlendControl(static_cast<grlib::GrlMrtType>(mrt), GRL_BLEND_FUNC_SRC_ALPHA, GRL_BLEND_FUNC_ONE, GRL_BLEND_COMBINE_ADD);
    break;
  case 3:
    grlib::CGLibColorCtl::setMrtBlend(1 << mrt, GRL_LOGIC_TYPE_COPY);
    grlib::CGLibColorCtl::setMrtBlendControl(static_cast<grlib::GrlMrtType>(mrt), GRL_BLEND_FUNC_ZERO, GRL_BLEND_FUNC_SRC_COLOR, GRL_BLEND_COMBINE_ADD);
    break;
  case 4:
    grlib::CGLibColorCtl::setMrtBlend(1 << mrt, GRL_LOGIC_TYPE_COPY);
    grlib::CGLibColorCtl::setMrtBlendControl(static_cast<grlib::GrlMrtType>(mrt), GRL_BLEND_FUNC_ONE_MINUS_DST_COLOR, GRL_BLEND_FUNC_ZERO, GRL_BLEND_COMBINE_ADD);
    break;
  case 5:
    grlib::CGLibColorCtl::setMrtBlend(1 << mrt, GRL_LOGIC_TYPE_COPY);
    grlib::CGLibColorCtl::setMrtBlendControl(static_cast<grlib::GrlMrtType>(mrt), GRL_BLEND_FUNC_ONE, GRL_BLEND_FUNC_ONE, GRL_BLEND_COMBINE_ADD);
    break;
  default:
    grlib::CGLibColorCtl::setBlendOffControl(GRL_LOGIC_TYPE_COPY);
    break;
  }
  unknown08 = -1;
  unknown0c = -1;
}

void DrAPCache::beginTexSampling(int clamp, int filter) {
  unknown40 = 0;
  unknown42 = 0;
  unknown38 = clamp;
  unknown3a = clamp;
  m_filter = filter;
  m_mipMapOn = 0;
}

void DrAPCache::begin3DTextureSampling() {
  unknown40 = 0x41;
  unknown42 = 1;
}

void DrAPCache::begin3DTexturePointSampling() {
  unknown40 = 0x42;
  unknown42 = 1;
}

void DrAPCache::begin3DTextureWarpSampling() {
  unknown40 = 0x43;
  unknown42 = 1;
}

void DrAPCache::begin3DTextureWarpPointSampling() {
  unknown40 = 0x44;
  unknown42 = 1;
}

void DrAPCache::beginCubeTextureSampling(bool isArray) {
  unknown40 = isArray ? 0x47 : 0x45;
  unknown42 = 2;
}

void DrAPCache::beginCubeTexturePointSampling(bool isArray) {
  unknown40 = isArray ? 0x48 : 0x46;
  unknown42 = 2;
}

void DrAPCache::beginDepthCompare() {
  unknown40 = 0x49;
  unknown42 = 0;
}

void DrAPCache::beginBorderWhite() {
  unknown40 = 0x4a;
  unknown42 = 0;
}

void DrAPCache::beginBorderBlack() {
  unknown40 = 0x4b;
  unknown42 = 0;
}

void DrAPCache::beginBorderDepthMax() {
  unknown40 = 0x4c;
  unknown42 = 0;
}

void DrAPCache::beginBorderDepthMinusMax() {
  unknown40 = 0x4d;
  unknown42 = 0;
}

void DrAPCache::texSampClamping(int clampU, int clampV) {
  unknown38 = static_cast<u8>(clampU);
  unknown3a = static_cast<u8>(clampV);
}

void DrAPCache::setMipMapOn(const grlib::CGLibTextureBuffer &texture) { m_mipMapOn = texture.getMipmap() != 0; }

void DrAPCache::setupShader(grlib::CGLibDecShader *shader, DrResFetch *fetch) { grlib::CGLibCtlShader::setShader(*shader, *fetch); }

void DrAPCache::setupShader(grlib::CGLibDecShdExtTbl *shader, DrResFetch *fetch) { grlib::CGLibCtlShader::setShader(*shader, *fetch); }

void DrAPCache::setTexture(const grlib::CGLibTextureBuffer &texture, u32 location) { grlib::CGLibCtlTexture::setTexture(texture, unknown30[getSamplerID()], location); }

void DrAPCache::setTexture(const grlib::CGLibTextureBuffer &texture, const grlib::CGLibSampler &sampler, u32 location) { grlib::CGLibCtlTexture::setTexture(texture, sampler, location); }

} // namespace ml
