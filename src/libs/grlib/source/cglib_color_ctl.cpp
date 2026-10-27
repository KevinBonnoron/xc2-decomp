#include "grlib/cglib_color_ctl.h"

#include "grlib/cglib_pipeline.h"
#include "grlib/cglib_render_target.h"
#include "grlib/cglib_system_context.h"
#include "mm_math/mm_col4.h"
#include "nvn/nvn.h"

namespace grlib {

void CGLibColorCtl::setBlendControl(GrlBlendFunc source, GrlBlendFunc destination, GrlBlendCombine combine, GrlLogicType logic) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  nvnColorStateSetLogicOp(&context->unknown1070.unknown24, static_cast<NVNlogicOp>(logic));
  nvnCommandBufferBindColorState(context->unknown1070.unknown00, &context->unknown1070.unknown24);
  NVNblendState *blend = &context->unknown1070.unknown08;
  nvnBlendStateSetBlendEquation(blend, static_cast<NVNblendEquation>(combine), static_cast<NVNblendEquation>(combine));
  nvnBlendStateSetBlendFunc(blend, static_cast<NVNblendFunc>(source), static_cast<NVNblendFunc>(destination), static_cast<NVNblendFunc>(source), static_cast<NVNblendFunc>(destination));
  for (int i = 0; i < CGLibPipeline::COLOR_TARGET_NUM; i++) {
    nvnBlendStateSetBlendTarget(blend, i);
    nvnCommandBufferBindBlendState(context->unknown1070.unknown00, blend);
  }
}

void CGLibColorCtl::setBlendControl(GrlBlendFunc source, GrlBlendFunc destination, GrlBlendCombine combine, GrlBlendFunc alphaSource, GrlBlendFunc alphaDestination, GrlBlendCombine alphaCombine,
                                    GrlLogicType logic) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  nvnColorStateSetLogicOp(&context->unknown1070.unknown24, static_cast<NVNlogicOp>(logic));
  nvnCommandBufferBindColorState(context->unknown1070.unknown00, &context->unknown1070.unknown24);
  NVNblendState *blend = &context->unknown1070.unknown08;
  nvnBlendStateSetBlendEquation(blend, static_cast<NVNblendEquation>(combine), static_cast<NVNblendEquation>(alphaCombine));
  nvnBlendStateSetBlendFunc(blend, static_cast<NVNblendFunc>(source), static_cast<NVNblendFunc>(destination), static_cast<NVNblendFunc>(alphaSource), static_cast<NVNblendFunc>(alphaDestination));
  for (int i = 0; i < CGLibPipeline::COLOR_TARGET_NUM; i++) {
    nvnBlendStateSetBlendTarget(blend, i);
    nvnCommandBufferBindBlendState(context->unknown1070.unknown00, blend);
  }
}

void CGLibColorCtl::setBlendOffControl(GrlLogicType logic) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  nvnColorStateSetLogicOp(&context->unknown1070.unknown20, static_cast<NVNlogicOp>(logic));
  nvnCommandBufferBindColorState(context->unknown1070.unknown00, &context->unknown1070.unknown20);
}

void CGLibColorCtl::setMrtBlend(u8 mask, GrlLogicType logic) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  NVNcolorState *color = &context->unknown1070.unknown1c;
  for (int i = 0; i < CGLibPipeline::COLOR_TARGET_NUM; i++) {
    if (mask & (1 << i)) {
      nvnColorStateSetBlendEnable(color, i, true);
    } else {
      nvnColorStateSetBlendEnable(color, i, false);
    }
  }
  nvnColorStateSetLogicOp(color, static_cast<NVNlogicOp>(logic));
  nvnCommandBufferBindColorState(context->unknown1070.unknown00, color);
}

void CGLibColorCtl::setMrtBlendControl(GrlMrtType mrt, GrlBlendFunc source, GrlBlendFunc destination, GrlBlendCombine combine) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  NVNblendState *blend = &context->unknown1070.unknown08;
  nvnBlendStateSetBlendTarget(blend, mrt);
  nvnBlendStateSetBlendEquation(blend, static_cast<NVNblendEquation>(combine), static_cast<NVNblendEquation>(combine));
  nvnBlendStateSetBlendFunc(blend, static_cast<NVNblendFunc>(source), static_cast<NVNblendFunc>(destination), static_cast<NVNblendFunc>(source), static_cast<NVNblendFunc>(destination));
  nvnCommandBufferBindBlendState(context->unknown1070.unknown00, blend);
}

void CGLibColorCtl::setMrtBlendControl(GrlMrtType mrt, GrlBlendFunc source, GrlBlendFunc destination, GrlBlendCombine combine, GrlBlendFunc alphaSource, GrlBlendFunc alphaDestination,
                                       GrlBlendCombine alphaCombine) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  NVNblendState *blend = &context->unknown1070.unknown08;
  nvnBlendStateSetBlendTarget(blend, mrt);
  nvnBlendStateSetBlendEquation(blend, static_cast<NVNblendEquation>(combine), static_cast<NVNblendEquation>(alphaCombine));
  nvnBlendStateSetBlendFunc(blend, static_cast<NVNblendFunc>(source), static_cast<NVNblendFunc>(destination), static_cast<NVNblendFunc>(alphaSource), static_cast<NVNblendFunc>(alphaDestination));
  nvnCommandBufferBindBlendState(context->unknown1070.unknown00, blend);
}

void CGLibColorCtl::setColorChannelMask(u8 red, u8 green, u8 blue, u8 alpha) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  NVNchannelMaskState *channelMask = &context->unknown1070.unknown10;
  for (int i = 0; i < CGLibPipeline::COLOR_TARGET_NUM; i++) {
    nvnChannelMaskStateSetChannelMask(channelMask, i, red, green, blue, alpha);
  }
  nvnCommandBufferBindChannelMaskState(context->unknown1070.unknown00, channelMask);
}

void CGLibColorCtl::setColorChannelMask(GrlMrtType mrt, u8 red, u8 green, u8 blue, u8 alpha) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  NVNchannelMaskState *channelMask = &context->unknown1070.unknown10;
  nvnChannelMaskStateSetChannelMask(channelMask, mrt, red, green, blue, alpha);
  nvnCommandBufferBindChannelMaskState(context->unknown1070.unknown00, channelMask);
}

void CGLibColorCtl::setBlendColor(const mm::Col4 &color) { nvnCommandBufferSetBlendColor(context::CGLibSystemContext::get()->unknown1070.unknown00, &color.r); }

void CGLibColorCtl::setColorBufferOn() {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  nvnCommandBufferBindChannelMaskState(context->unknown1070.unknown00, &context->unknown1070.unknown14);
}

void CGLibColorCtl::setColorBufferOff() {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  nvnCommandBufferBindChannelMaskState(context->unknown1070.unknown00, &context->unknown1070.unknown18);
}

void CGLibColorCtl::clearMainFrameBuffer(const mm::Col4 &color) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  context->unknown1110[context->unknown20d4].clearTexture(color, static_cast<GrlClaerMask>(0xf));
}

} // namespace grlib
