#include "dr/dr_ap_gx_type.h"

#include "grlib/cglib_depth_ctl.h"
#include "grlib/cglib_polygon.h"
#include "grlib/cglib_render_target.h"
#include "grlib/cglib_state.h"

namespace ml {

static const GrlStencil s_stencils[] = {
    GRL_STENCIL_KEEP,
    GRL_STENCIL_ZERO,
    GRL_STENCIL_REPLACE,
    GRL_STENCIL_INCR,
    GRL_STENCIL_DECR,
    GRL_STENCIL_INVERT,
    GRL_STENCIL_INCR_WRAP,
    GRL_STENCIL_DECR_WRAP,
};

static const GrlCompare s_compares[] = {
    GRL_COMPARE_NEVER,
    GRL_COMPARE_LESS,
    GRL_COMPARE_EQUAL,
    GRL_COMPARE_LEQUAL,
    GRL_COMPARE_GREATER,
    GRL_COMPARE_NOTEQUAL,
    GRL_COMPARE_GEQUAL,
    GRL_COMPARE_ALWAYS,
};

void DrAPGxType::setupScreenQuads(bool isBlend) {
  if (isBlend) {
    grlib::CGLibColorCtl::setBlendControl(GRL_BLEND_FUNC_SRC_ALPHA, GRL_BLEND_FUNC_ONE_MINUS_SRC_ALPHA, GRL_BLEND_COMBINE_ADD, GRL_LOGIC_TYPE_COPY);
  } else {
    grlib::CGLibColorCtl::setBlendOffControl(GRL_LOGIC_TYPE_COPY);
  }
  grlib::CGLibDepthCtl::setDepthControl(false, false, GRL_COMPARE_ALWAYS);
  grlib::CGLibPolygon::setCullingOff();
}

void DrAPGxType::setupScreenQuadsWithAlpha() {
  grlib::CGLibColorCtl::setBlendControl(GRL_BLEND_FUNC_ONE, GRL_BLEND_FUNC_ZERO, GRL_BLEND_COMBINE_ADD, GRL_BLEND_FUNC_ONE, GRL_BLEND_FUNC_ZERO, GRL_BLEND_COMBINE_ADD, GRL_LOGIC_TYPE_COPY);
  grlib::CGLibDepthCtl::setDepthControl(false, false, GRL_COMPARE_ALWAYS);
  grlib::CGLibPolygon::setCullingOff();
}

void DrAPGxType::setupAlphaAddMaterial() {
  grlib::CGLibColorCtl::setBlendControl(GRL_BLEND_FUNC_SRC_ALPHA, GRL_BLEND_FUNC_ONE, GRL_BLEND_COMBINE_ADD, GRL_LOGIC_TYPE_COPY);
  grlib::CGLibDepthCtl::setDepthControl(false, false, GRL_COMPARE_ALWAYS);
  grlib::CGLibPolygon::setCullingOff();
}

void DrAPGxType::setupBloomAddMaterial(GrlBlendFunc source, GrlBlendFunc destination) {
  grlib::CGLibColorCtl::setBlendControl(source, destination, GRL_BLEND_COMBINE_ADD, GRL_LOGIC_TYPE_COPY);
  grlib::CGLibDepthCtl::setDepthControl(false, false, GRL_COMPARE_ALWAYS);
  grlib::CGLibPolygon::setCullingOff();
}

void DrAPGxType::beginOccQuery() {
  grlib::CGLibPolygon::setCullingOff();
  grlib::CGLibColorCtl::setColorBufferOff();
  grlib::CGLibDepthCtl::setDepthControl(true, false, GRL_COMPARE_LEQUAL);
}

void DrAPGxType::endOccQuery() { grlib::CGLibColorCtl::setColorBufferOn(); }

void DrAPGxType::beginMaxBlend() {
  grlib::CGLibColorCtl::setBlendControl(GRL_BLEND_FUNC_ONE, GRL_BLEND_FUNC_ONE, GRL_BLEND_COMBINE_MAX, GRL_BLEND_FUNC_ONE, GRL_BLEND_FUNC_ONE, GRL_BLEND_COMBINE_MAX, GRL_LOGIC_TYPE_COPY);
}

void DrAPGxType::endMaxBlend() { grlib::CGLibColorCtl::setBlendOffControl(GRL_LOGIC_TYPE_COPY); }

void DrAPGxType::beginShadow() { grlib::CGLibColorCtl::setColorBufferOff(); }

void DrAPGxType::endShadow() { grlib::CGLibColorCtl::setColorBufferOn(); }

void DrAPGxType::beginSimpleShadow() { grlib::CGLibColorCtl::setColorChannelMask(false, true, false, false); }

void DrAPGxType::endSimpleShadow() { grlib::CGLibColorCtl::setColorChannelMask(true, true, true, true); }

void DrAPGxType::shadowCacheSetup() {
  grlib::CGLibColorCtl::setColorBufferOff();
  grlib::CGLibDepthCtl::setDepthControl(true, true, GRL_COMPARE_ALWAYS);
  grlib::CGLibPolygon::setCullingOff();
}

void DrAPGxType::beginAoBlur() { grlib::CGLibColorCtl::setColorChannelMask(true, false, false, false); }

void DrAPGxType::endAoBlur() { grlib::CGLibColorCtl::setColorChannelMask(true, true, true, true); }

void DrAPGxType::beginColorOff() { grlib::CGLibColorCtl::setColorBufferOff(); }

void DrAPGxType::endColorOff() { grlib::CGLibColorCtl::setColorBufferOn(); }

void DrAPGxType::setupAlphaChanel(bool isAlpha) {
  if (isAlpha) {
    grlib::CGLibColorCtl::setColorChannelMask(true, true, true, true);
  } else {
    grlib::CGLibColorCtl::setColorChannelMask(true, true, true, false);
  }
}

void DrAPGxType::setupCullingOff() { grlib::CGLibPolygon::setCullingOff(); }

void DrAPGxType::setupCullingFront() { grlib::CGLibPolygon::setCullingFront(); }

void DrAPGxType::setupCullingBack() { grlib::CGLibPolygon::setCullingBack(); }

void DrAPGxType::setupStencilPrePassReset() { grlib::CGLibDepthCtl::setDepthControl(true, true, GRL_COMPARE_LESS); }

void DrAPGxType::setupStencilTest(u8 isTest, u8 isWrite, int compare, u8 isStencil, u32 ref, u32 mask, int stencilCompare, int fail, int depthFail, int pass) {
  grlib::CGLibDepthCtl::setDepthStencilControl(isTest, isWrite, s_compares[compare], isStencil, s_compares[stencilCompare], ref, mask, mask, s_stencils[fail], s_stencils[depthFail], s_stencils[pass]);
}

void DrAPGxType::setupStencilTestWriteMask(u8 isTest, u8 isWrite, int compare, u8 isStencil, u32 ref, u32 mask, u32 writeMask, int stencilCompare, int fail, int depthFail, int pass) {
  grlib::CGLibDepthCtl::setDepthStencilControl(
      isTest, isWrite, s_compares[compare], isStencil, s_compares[stencilCompare], ref, mask, writeMask, s_stencils[fail], s_stencils[depthFail], s_stencils[pass]);
}

void DrAPGxType::setupDepthContl(u8 isTest, u8 isWrite, int compare) { grlib::CGLibDepthCtl::setDepthControl(isTest, isWrite, s_compares[compare]); }

void DrAPGxType::getMainScreenSize(int &width, int &height) {
  width = grlib::CGLibState::getMainRenderTarget()->m_width;
  height = grlib::CGLibState::getMainRenderTarget()->m_height;
}

} // namespace ml
