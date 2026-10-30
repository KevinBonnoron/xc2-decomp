#include "grlib/cglib_state.h"

#include "grlib/cglib_color_buffer.h"
#include "grlib/cglib_depth_buffer.h"
#include "grlib/cglib_depth_target.h"
#include "grlib/cglib_display.h"
#include "grlib/cglib_manager.h"
#include "grlib/cglib_mem_handle.h"
#include "grlib/cglib_mem_pool.h"
#include "grlib/cglib_pipeline.h"
#include "grlib/cglib_render_target.h"
#include "grlib/cglib_system_context.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"
#include "nvn/nvn.h"

namespace grlib {

namespace context {

void CGLibSystemContext::setPixelResidentArea(bool isEnable, u32 size) {
  unknown2588[CGLibManager::s_nStkNowIdx] = unknown2580;
  unknown2580 = nullptr;
  unknown2598 = size;
  if (isEnable) {
    unknown2580 = mtl::MemManager::allocate(CGLibMemHandle::s_hPxlHandle, size, 0x10000, false, "no name", 0);
    unknown25a8 = static_cast<u32>(reinterpret_cast<u64>(unknown2580)) - static_cast<u32>(reinterpret_cast<u64>(unknown2478.unknown18));
    unknown25a0 = nvnMemoryPoolGetBufferAddress(unknown2478.m_memoryPool) + unknown25a8;
  }
}

} // namespace context

void CGLibState::setMainFrameBuffer() {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  context->unknown1110.unknown000[context->unknown1110.unknownfc4].setRenderTarget(*context->unknown1110.unknown790.unknown120);
}

void CGLibState::setupInitialize() {}

void CGLibState::setViewport(const LibMainStateViewPort &viewPort) {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  nvnCommandBufferSetViewport(context->unknown1070.unknown00, viewPort.unknown00, viewPort.unknown04, viewPort.unknown08, viewPort.unknown0c);
  nvnCommandBufferSetScissor(context->unknown1070.unknown00, viewPort.unknown00, viewPort.unknown04, viewPort.unknown08, viewPort.unknown0c);
  context->unknown2630 = viewPort;
}

void CGLibState::setPixelResidentArea(bool isEnable, u32 size) { context::CGLibSystemContext::get()->setPixelResidentArea(isEnable, size); }

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
  context->unknown25b0[mrt] = &renderTarget.unknown78.unknown10;
  context->unknown25f0[mrt] = renderTarget.unknown78.unknown38;
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
  return &context->unknown1110.unknown000[context->unknown1110.unknownfc4];
}

CGLibDepthTarget *CGLibState::getMainDepthTarget() { return &context::CGLibSystemContext::get()->unknown1110.unknown790; }

LibMainStateViewPort *CGLibState::getDefViewPort() { return &context::CGLibSystemContext::get()->unknown2630; }

} // namespace grlib
