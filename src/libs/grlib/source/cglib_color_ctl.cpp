#include "grlib/cglib_color_ctl.h"

#include "grlib/cglib_render_target.h"
#include "grlib/cglib_system_context.h"
#include "mm_math/mm_col4.h"
#include "nvn/nvn.h"

namespace grlib {

void CGLibColorCtl::setBlendColor(const mm::Col4 &color) { nvnCommandBufferSetBlendColor(context::CGLibSystemContext::get()->m_cmdBuf, &color.r); }

void CGLibColorCtl::setColorBufferOn() {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  nvnCommandBufferBindChannelMaskState(context->m_cmdBuf, &context->m_colorBufferOn);
}

void CGLibColorCtl::setColorBufferOff() {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  nvnCommandBufferBindChannelMaskState(context->m_cmdBuf, &context->m_colorBufferOff);
}

void CGLibColorCtl::clearMainFrameBuffer(const mm::Col4 &color) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  context->m_mainRenderTargets[context->m_mainRenderTargetIndex].clearTexture(color, static_cast<GrlClaerMask>(0xf));
}

} // namespace grlib
