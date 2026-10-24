#include "grlib/cglib_state.h"

#include "grlib/cglib_color_buffer.h"
#include "grlib/cglib_depth_buffer.h"
#include "grlib/cglib_depth_target.h"
#include "grlib/cglib_pipeline.h"
#include "grlib/cglib_render_target.h"
#include "grlib/cglib_system_context.h"
#include "nvn/nvn.h"

namespace grlib {

void CGLibState::setMainFrameBuffer() {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  context->unknown1110[context->unknown20d4].setRenderTarget(*context->unknown18a0.unknown120);
}

void CGLibState::setupInitialize() {}

void CGLibState::setOnlyViewport(const LibMainStateViewPort &viewPort) {
  nvnCommandBufferSetViewport(context::CGLibSystemContext::get()->unknown1070.unknown00, viewPort.unknown00, viewPort.unknown04, viewPort.unknown08, viewPort.unknown0c);
}

void CGLibState::setOnlyScissor(const LibMainStateViewPort &viewPort) {
  nvnCommandBufferSetScissor(context::CGLibSystemContext::get()->unknown1070.unknown00, viewPort.unknown00, viewPort.unknown04, viewPort.unknown08, viewPort.unknown0c);
}

void CGLibState::beginRegisterRenderTarget() {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  context->unknown25ac = 0;
  context->unknown2648 = nullptr;
}

void CGLibState::setRegisterRenderTarget(CGLibColorBuffer &colorBuffer, GrlMrtType mrt) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  context->unknown25b0[mrt] = &colorBuffer.unknown10;
  context->unknown25f0[mrt] = colorBuffer.unknown38;
  context->unknown25ac++;
}

void CGLibState::setRegisterRenderTarget(CGLibRenderTarget &renderTarget, GrlMrtType mrt) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  context->unknown25b0[mrt] = &renderTarget.unknown88;
  context->unknown25f0[mrt] = renderTarget.unknownb0;
  context->unknown25ac++;
}

void CGLibState::setRegisterDepthTarget(CGLibDepthBuffer &depthBuffer) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  context->unknown2648 = depthBuffer.unknown10;
}

void CGLibState::endRegisterRenderTarget() {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  nvnCommandBufferSetRenderTargets(context->unknown1070.unknown00, context->unknown25ac, context->unknown25f0, context->unknown25b0, context->unknown2648, nullptr);
}

CGLibRenderTarget *CGLibState::getMainRenderTarget() {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  return &context->unknown1110[context->unknown20d4];
}

CGLibDepthTarget *CGLibState::getMainDepthTarget() { return &context::CGLibSystemContext::get()->unknown18a0; }

LibMainStateViewPort *CGLibState::getDefViewPort() { return &context::CGLibSystemContext::get()->unknown2630; }

} // namespace grlib
