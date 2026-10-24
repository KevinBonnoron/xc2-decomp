#include "grlib/cglib_color_ctl.h"

#include "grlib/cglib_pipeline.h"
#include "grlib/cglib_render_target.h"
#include "grlib/cglib_system_context.h"
#include "mm_math/mm_col4.h"
#include "nvn/nvn.h"

namespace grlib {

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
