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
  return unknown3a + unknown38 * 4 + m_filter * 16 + unknown3e * 32;
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
  unknown10 = DR_AP_CULL_TYPE_OFF;
  unknown14 = -1;
  grlib::CGLibDepthCtl::setDepthControl(true, true, GRL_COMPARE_LESS);
  grlib::CGLibPolygon::setCullingOff();
  grlib::CGLibColorCtl::setBlendOffControl(GRL_LOGIC_TYPE_COPY);
}

void DrAPCache::beginZRender() {
  unknown24 = 2;
  unknown1c = 1;
  unknown18 = -1;
  unknown10 = DR_AP_CULL_TYPE_OFF;
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
  unknown10 = DR_AP_CULL_TYPE_OFF;
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
  unknown10 = DR_AP_CULL_TYPE_OFF;
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

void DrAPCache::endGBuffRender() { grlib::CGLibColorCtl::setColorChannelMask(true, true, true, true); }

void DrAPCache::setRefractionRender() { grlib::CGLibColorCtl::setColorChannelMask(false, false, false, false); }

void DrAPCache::endRefractionRender() { grlib::CGLibColorCtl::setColorChannelMask(true, true, true, true); }

void DrAPCache::setupCulling(DrApCullType cullType) {
  if (unknown10 == cullType) {
    return;
  }
  unknown10 = cullType;
  switch (cullType) {
  case DR_AP_CULL_TYPE_BACK:
    grlib::CGLibPolygon::setCullingBack();
    break;
  case DR_AP_CULL_TYPE_FRONT:
    grlib::CGLibPolygon::setCullingFront();
    break;
  case DR_AP_CULL_TYPE_OFF:
    grlib::CGLibPolygon::setCullingOff();
    break;
  default:
    grlib::CGLibPolygon::setCullingDispOff();
    break;
  }
}

void DrAPCache::beginTexSampling(int clamp, int filter) {
  unknown40 = 0;
  unknown42 = 0;
  unknown38 = clamp;
  unknown3a = clamp;
  m_filter = filter;
  unknown3e = 0;
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

void DrAPCache::setMipMapOn(const grlib::CGLibTextureBuffer &texture) { unknown3e = texture.getMipmap() != 0; }

void DrAPCache::setupShader(grlib::CGLibDecShader *shader, DrResFetch *fetch) { grlib::CGLibCtlShader::setShader(*shader, *fetch); }

void DrAPCache::setupShader(grlib::CGLibDecShdExtTbl *shader, DrResFetch *fetch) { grlib::CGLibCtlShader::setShader(*shader, *fetch); }

void DrAPCache::setTexture(const grlib::CGLibTextureBuffer &texture, u32 location) { grlib::CGLibCtlTexture::setTexture(texture, unknown30[getSamplerID()], location); }

void DrAPCache::setTexture(const grlib::CGLibTextureBuffer &texture, const grlib::CGLibSampler &sampler, u32 location) { grlib::CGLibCtlTexture::setTexture(texture, sampler, location); }

} // namespace ml
