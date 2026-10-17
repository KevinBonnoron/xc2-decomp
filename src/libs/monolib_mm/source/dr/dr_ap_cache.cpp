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

u16 DrAPCache::getSamplerID() {
  if (m_samplerID != 0) {
    return m_samplerID;
  }
  return m_clampV + m_clampU * 4 + m_filter * 16 + m_mipMap * 32;
}

void DrAPCache::depthBegin() {
  m_depthWrite = -1;
  m_depthTest = -1;
  m_stencilRef = -1;
}

void DrAPCache::shadowBegin() {
  m_depthWrite = 1;
  m_stencilType = -1;
  m_depthTest = 2;
  m_alphaBlend = 0;
  m_cullType = DR_AP_CULL_TYPE_OFF;
  m_stencilRef = -1;
  grlib::CGLibDepthCtl::setDepthControl(true, true, GRL_COMPARE_LESS);
  grlib::CGLibPolygon::setCullingOff();
  grlib::CGLibColorCtl::setBlendOffControl(GRL_LOGIC_TYPE_COPY);
}

void DrAPCache::beginZRender() {
  m_depthTest = 2;
  m_depthWrite = 1;
  m_stencilType = -1;
  m_cullType = DR_AP_CULL_TYPE_OFF;
  m_stencilRef = -1;
  grlib::CGLibDepthCtl::setDepthControl(true, true, GRL_COMPARE_LESS);
  grlib::CGLibPolygon::setCullingOff();
  grlib::CGLibColorCtl::setColorBufferOff();
}

void DrAPCache::endZRender() { grlib::CGLibColorCtl::setColorBufferOn(); }

void DrAPCache::beginThicknessRenderFirst() {
  m_depthTest = 2;
  m_stencilType = -1;
  m_depthWrite = 0;
  m_cullType = DR_AP_CULL_TYPE_OFF;
  m_stencilRef = -1;
  grlib::CGLibDepthCtl::setDepthControl(true, false, GRL_COMPARE_LESS);
  grlib::CGLibPolygon::setCullingOff();
  grlib::CGLibColorCtl::setColorChannelMask(true, false, false, false);
  grlib::CGLibColorCtl::setBlendControl(GRL_BLEND_FUNC_ONE,
                                        GRL_BLEND_FUNC_ONE,
                                        GRL_BLEND_COMBINE_MIN,
                                        GRL_BLEND_FUNC_ONE,
                                        GRL_BLEND_FUNC_ONE,
                                        GRL_BLEND_COMBINE_ADD,
                                        GRL_LOGIC_TYPE_COPY);
}

void DrAPCache::endThicknessRenderFirst() { grlib::CGLibColorCtl::setColorBufferOn(); }

void DrAPCache::beginThicknessRenderSecond() {
  m_depthTest = 2;
  m_depthWrite = 1;
  m_stencilType = -1;
  m_cullType = DR_AP_CULL_TYPE_OFF;
  m_stencilRef = -1;
  grlib::CGLibDepthCtl::setDepthControl(true, true, GRL_COMPARE_LESS);
  grlib::CGLibPolygon::setCullingOff();
  grlib::CGLibColorCtl::setColorBufferOff();
}

void DrAPCache::endThicknessRenderSecond() { grlib::CGLibColorCtl::setColorBufferOn(); }

void DrAPCache::beginMdlZRender() {
  m_depthTest = 2;
  m_depthWrite = 1;
  m_stencilRef = -1;
  m_stencilType = -1;
  grlib::CGLibDepthCtl::setDepthControl(true, true, GRL_COMPARE_LESS);
  grlib::CGLibColorCtl::setColorBufferOff();
}

void DrAPCache::endMdlZRender() { grlib::CGLibColorCtl::setColorBufferOn(); }

void DrAPCache::setGBuffRender(u32 mask) {
  if (m_gbuffMask == mask) {
    return;
  }
  m_gbuffMask = mask;
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
  if (m_cullType == cullType) {
    return;
  }
  m_cullType = cullType;
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
  m_samplerID = 0;
  m_samplerType = 0;
  m_clampU = clamp;
  m_clampV = clamp;
  m_filter = filter;
  m_mipMap = 0;
}

void DrAPCache::begin3DTextureSampling() {
  m_samplerID = 0x41;
  m_samplerType = 1;
}

void DrAPCache::begin3DTexturePointSampling() {
  m_samplerID = 0x42;
  m_samplerType = 1;
}

void DrAPCache::begin3DTextureWarpSampling() {
  m_samplerID = 0x43;
  m_samplerType = 1;
}

void DrAPCache::begin3DTextureWarpPointSampling() {
  m_samplerID = 0x44;
  m_samplerType = 1;
}

void DrAPCache::beginCubeTextureSampling(bool isArray) {
  m_samplerID = isArray ? 0x47 : 0x45;
  m_samplerType = 2;
}

void DrAPCache::beginCubeTexturePointSampling(bool isArray) {
  m_samplerID = isArray ? 0x48 : 0x46;
  m_samplerType = 2;
}

void DrAPCache::beginDepthCompare() {
  m_samplerID = 0x49;
  m_samplerType = 0;
}

void DrAPCache::beginBorderWhite() {
  m_samplerID = 0x4a;
  m_samplerType = 0;
}

void DrAPCache::beginBorderBlack() {
  m_samplerID = 0x4b;
  m_samplerType = 0;
}

void DrAPCache::beginBorderDepthMax() {
  m_samplerID = 0x4c;
  m_samplerType = 0;
}

void DrAPCache::beginBorderDepthMinusMax() {
  m_samplerID = 0x4d;
  m_samplerType = 0;
}

void DrAPCache::texSampClamping(int clampU, int clampV) {
  m_clampU = static_cast<u8>(clampU);
  m_clampV = static_cast<u8>(clampV);
}

void DrAPCache::setMipMapOn(const grlib::CGLibTextureBuffer &texture) { m_mipMap = texture.getMipmap() != 0; }

void DrAPCache::setupShader(grlib::CGLibDecShader *shader, DrResFetch *fetch) { grlib::CGLibCtlShader::setShader(*shader, *fetch); }

void DrAPCache::setupShader(grlib::CGLibDecShdExtTbl *shader, DrResFetch *fetch) { grlib::CGLibCtlShader::setShader(*shader, *fetch); }

void DrAPCache::setTexture(const grlib::CGLibTextureBuffer &texture, u32 location) {
  grlib::CGLibCtlTexture::setTexture(texture, m_samplers[getSamplerID()], location);
}

void DrAPCache::setTexture(const grlib::CGLibTextureBuffer &texture, const grlib::CGLibSampler &sampler, u32 location) {
  grlib::CGLibCtlTexture::setTexture(texture, sampler, location);
}

} // namespace ml
