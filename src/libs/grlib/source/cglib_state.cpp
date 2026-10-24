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
  context->m_mainRenderTargets[context->m_mainRenderTargetIndex].setRenderTarget(*context->m_mainDepthTarget.m_depthBuffer);
}

void CGLibState::setupInitialize() {}

void CGLibState::setOnlyViewport(const LibMainStateViewPort &viewPort) {
  nvnCommandBufferSetViewport(context::CGLibSystemContext::get()->m_pipeline.m_cmdBuf, viewPort.x, viewPort.y, viewPort.width, viewPort.height);
}

void CGLibState::setOnlyScissor(const LibMainStateViewPort &viewPort) {
  nvnCommandBufferSetScissor(context::CGLibSystemContext::get()->m_pipeline.m_cmdBuf, viewPort.x, viewPort.y, viewPort.width, viewPort.height);
}

void CGLibState::beginRegisterRenderTarget() {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  context->m_registerNum = 0;
  context->m_registerDepth = nullptr;
}

void CGLibState::setRegisterRenderTarget(CGLibColorBuffer &colorBuffer, GrlMrtType mrt) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  context->m_registerViews[mrt] = &colorBuffer.m_textureView;
  context->m_registerTextures[mrt] = colorBuffer.m_nvnTexture;
  context->m_registerNum++;
}

void CGLibState::setRegisterRenderTarget(CGLibRenderTarget &renderTarget, GrlMrtType mrt) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  context->m_registerViews[mrt] = &renderTarget.m_textureView;
  context->m_registerTextures[mrt] = renderTarget.m_nvnTexture;
  context->m_registerNum++;
}

void CGLibState::setRegisterDepthTarget(CGLibDepthBuffer &depthBuffer) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  context->m_registerDepth = depthBuffer.m_nvnTexture;
}

void CGLibState::endRegisterRenderTarget() {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  nvnCommandBufferSetRenderTargets(context->m_pipeline.m_cmdBuf, context->m_registerNum, context->m_registerTextures, context->m_registerViews, context->m_registerDepth, nullptr);
}

CGLibRenderTarget *CGLibState::getMainRenderTarget() {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  return &context->m_mainRenderTargets[context->m_mainRenderTargetIndex];
}

CGLibDepthTarget *CGLibState::getMainDepthTarget() { return &context::CGLibSystemContext::get()->m_mainDepthTarget; }

LibMainStateViewPort *CGLibState::getDefViewPort() { return &context::CGLibSystemContext::get()->m_defViewPort; }

} // namespace grlib
