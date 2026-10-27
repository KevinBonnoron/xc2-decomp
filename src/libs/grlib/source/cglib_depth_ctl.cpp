#include "grlib/cglib_depth_ctl.h"

#include "grlib/cglib_color_buffer.h"
#include "grlib/cglib_depth_buffer.h"
#include "grlib/cglib_pipeline.h"
#include "grlib/cglib_state.h"
#include "grlib/cglib_system_context.h"
#include "mm_math/mm_col4.h"
#include "nvn/nvn.h"

namespace grlib {

namespace {

const NVNdepthFunc unknown003[] = {
    NVN_DEPTH_FUNC_NEVER,
    NVN_DEPTH_FUNC_LESS,
    NVN_DEPTH_FUNC_EQUAL,
    NVN_DEPTH_FUNC_LEQUAL,
    NVN_DEPTH_FUNC_GREATER,
    NVN_DEPTH_FUNC_NOTEQUAL,
    NVN_DEPTH_FUNC_GEQUAL,
    NVN_DEPTH_FUNC_ALWAYS,
};

// Inferred role: restores the registered render targets, viewport and scissor after a clear; original name unknown.
inline void unknown004(context::CGLibSystemContext *context) {
  nvnCommandBufferSetRenderTargets(context->unknown1070.unknown00, context->unknown25ac, context->unknown25f0, context->unknown25b0, context->unknown2648, nullptr);
  nvnCommandBufferSetViewport(context->unknown1070.unknown00, 0, 0, context->unknown2630.unknown08, context->unknown2630.unknown0c);
  nvnCommandBufferSetScissor(context->unknown1070.unknown00, 0, 0, context->unknown2630.unknown08, context->unknown2630.unknown0c);
}

} // namespace

void CGLibDepthCtl::setDepthControl(u8 isTest, u8 isWrite, GrlCompare compare) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  NVNdepthStencilState *depthStencil = &context->unknown1070.unknown28;
  nvnDepthStencilStateSetDepthTestEnable(depthStencil, isTest);
  nvnDepthStencilStateSetDepthFunc(depthStencil, unknown003[compare]);
  nvnDepthStencilStateSetDepthWriteEnable(depthStencil, isWrite);
  nvnDepthStencilStateSetStencilTestEnable(depthStencil, 0);
  nvnCommandBufferBindDepthStencilState(context->unknown1070.unknown00, depthStencil);
}

void CGLibDepthCtl::setDepthStencilControl(u8 isTest, u8 isWrite, GrlCompare compare, u8 isStencil, GrlCompare stencilCompare, u32 ref, u32 mask, u32 writeMask, GrlStencil fail, GrlStencil depthFail,
                                           GrlStencil pass) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  if (isStencil == 0) {
    nvnDepthStencilStateSetStencilTestEnable(&context->unknown1070.unknown28, 0);
  } else {
    nvnCommandBufferSetStencilRef(context->unknown1070.unknown00, NVN_FACE_FRONT_AND_BACK, ref);
    nvnCommandBufferSetStencilValueMask(context->unknown1070.unknown00, NVN_FACE_FRONT_AND_BACK, mask);
    nvnCommandBufferSetStencilMask(context->unknown1070.unknown00, NVN_FACE_FRONT_AND_BACK, writeMask);
    NVNdepthStencilState *stencilState = &context->unknown1070.unknown28;
    nvnDepthStencilStateSetStencilTestEnable(stencilState, 1);
    nvnDepthStencilStateSetStencilOp(stencilState, NVN_FACE_FRONT_AND_BACK, static_cast<NVNstencilOp>(pass), static_cast<NVNstencilOp>(depthFail), static_cast<NVNstencilOp>(fail));
    nvnDepthStencilStateSetStencilFunc(stencilState, NVN_FACE_FRONT_AND_BACK, unknown003[stencilCompare]);
  }
  NVNdepthStencilState *depthStencil = &context->unknown1070.unknown28;
  nvnDepthStencilStateSetDepthTestEnable(depthStencil, isTest);
  nvnDepthStencilStateSetDepthFunc(depthStencil, unknown003[compare]);
  nvnDepthStencilStateSetDepthWriteEnable(depthStencil, isWrite);
  nvnCommandBufferBindDepthStencilState(context->unknown1070.unknown00, depthStencil);
}

void CGLibDepthCtl::clearColorBuffer(CGLibColorBuffer &colorBuffer, const mm::Col4 &color, GrlClaerMask mask) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  const NVNtextureView *view = &colorBuffer.unknown10;
  nvnCommandBufferSetViewport(context->unknown1070.unknown00, 0, 0, colorBuffer.getWidth(), colorBuffer.getHeight());
  nvnCommandBufferSetScissor(context->unknown1070.unknown00, 0, 0, colorBuffer.getWidth(), colorBuffer.getHeight());
  nvnCommandBufferSetRenderTargets(context->unknown1070.unknown00, 1, &colorBuffer.unknown38, &view, nullptr, nullptr);
  nvnCommandBufferClearColor(context->unknown1070.unknown00, 0, &color.r, mask);
  unknown004(context);
}

void CGLibDepthCtl::clearIntColorBuffer(CGLibColorBuffer &colorBuffer, const int *color, GrlClaerMask mask) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  const NVNtextureView *view = &colorBuffer.unknown10;
  nvnCommandBufferSetViewport(context->unknown1070.unknown00, 0, 0, colorBuffer.getWidth(), colorBuffer.getHeight());
  nvnCommandBufferSetScissor(context->unknown1070.unknown00, 0, 0, colorBuffer.getWidth(), colorBuffer.getHeight());
  nvnCommandBufferSetRenderTargets(context->unknown1070.unknown00, 1, &colorBuffer.unknown38, &view, nullptr, nullptr);
  nvnCommandBufferClearColori(context->unknown1070.unknown00, 0, color, mask);
  unknown004(context);
}

void CGLibDepthCtl::clearDepthBuffer(CGLibDepthBuffer &depthBuffer, bool isClear) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  nvnCommandBufferSetViewport(context->unknown1070.unknown00, 0, 0, depthBuffer.getWidth(), depthBuffer.getHeight());
  nvnCommandBufferSetScissor(context->unknown1070.unknown00, 0, 0, depthBuffer.getWidth(), depthBuffer.getHeight());
  nvnCommandBufferSetRenderTargets(context->unknown1070.unknown00, 0, nullptr, nullptr, depthBuffer.unknown10, nullptr);
  if (isClear) {
    nvnCommandBufferClearDepthStencil(context->unknown1070.unknown00, 1.0f, 0, 0, 0xffff);
  } else {
    nvnCommandBufferClearDepthStencil(context->unknown1070.unknown00, 1.0f, 1, 0, 0xffff);
  }
  unknown004(context);
}

void CGLibDepthCtl::clearValDepthBuffer(CGLibDepthBuffer &depthBuffer, f32 value, bool isClear) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  nvnCommandBufferSetViewport(context->unknown1070.unknown00, 0, 0, depthBuffer.getWidth(), depthBuffer.getHeight());
  nvnCommandBufferSetScissor(context->unknown1070.unknown00, 0, 0, depthBuffer.getWidth(), depthBuffer.getHeight());
  nvnCommandBufferSetRenderTargets(context->unknown1070.unknown00, 0, nullptr, nullptr, depthBuffer.unknown10, nullptr);
  if (isClear) {
    nvnCommandBufferClearDepthStencil(context->unknown1070.unknown00, value, 0, 0, 0xffff);
  } else {
    nvnCommandBufferClearDepthStencil(context->unknown1070.unknown00, value, 1, 0, 0xffff);
  }
  unknown004(context);
}

} // namespace grlib
