#include "grlib/cglib_system_context.h"

#include "grlib/cglib_color_buffer.h"
#include "grlib/cglib_depth_buffer.h"
#include "grlib/cglib_mem_pool.h"
#include "ml/critical_section.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"
#include "nvn/nvn.h"

namespace grlib {
namespace context {

ml::CriticalSection &CGLibSystemContext::getCriticalSection() {
  static ml::CriticalSection s_criticalSection;
  return s_criticalSection;
}

void CGLibSystemContext::createMemPool(CGLibMemPool &memPool, mtl::ALLOC_HANDLE handle, u32 flags) {
  memPool.setupBuffer(reinterpret_cast<void *>(mtl::MemManager::getTopAdr(handle)), mtl::MemManager::getTotalSize(handle), flags);
}

bool CGLibSystemContext::isRelease() { return true; }

void CGLibSystemContext::beginRegisterRenderTarget() {
  m_registerNum = 0;
  m_registerDepth = nullptr;
}

void CGLibSystemContext::setRegisterRenderTarget(CGLibColorBuffer &colorBuffer, GrlMrtType mrt) {
  m_registerViews[mrt] = &colorBuffer.m_textureView;
  m_registerTextures[mrt] = colorBuffer.m_nvnTexture;
  m_registerNum++;
}

void CGLibSystemContext::setRegisterDepthTarget(CGLibDepthBuffer &depthBuffer) { m_registerDepth = depthBuffer.m_nvnTexture; }

void CGLibSystemContext::endRegisterRenderTarget() { nvnCommandBufferSetRenderTargets(m_pipeline.m_cmdBuf, m_registerNum, m_registerTextures, m_registerViews, m_registerDepth, nullptr); }

void CGLibSystemContext::setMainFrameBuffer() { m_mainRenderTargets[m_mainRenderTargetIndex].setRenderTarget(*m_mainDepthTarget.m_depthBuffer); }

void CGLibSystemContext::getGlbUniformParam(u8 *&buffer, u64 &address) {
  buffer = m_glbUniformBuffer + m_glbUniformOffset;
  address = m_glbUniformGpuAddress + m_glbUniformOffset;
}

void CGLibSystemContext::nextGlbUniformOfs(u32 size) {
  u32 alignedSize = size + (-size & 0xff);
  m_glbUniformOffset += alignedSize;
  m_glbUniformRest -= alignedSize;
}

u64 CGLibSystemContext::getPixelResAreaGpuAddress(u32 offset) { return m_pixelResAreaGpuAddress + offset; }

u32 CGLibSystemContext::getPixelResAreaOffset(u32 offset) { return m_pixelResAreaOffset + offset; }

} // namespace context
} // namespace grlib
