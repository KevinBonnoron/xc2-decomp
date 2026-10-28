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
  unknown25ac = 0;
  unknown2648 = nullptr;
}

void CGLibSystemContext::setRegisterRenderTarget(CGLibColorBuffer &colorBuffer, GrlMrtType mrt) {
  unknown25b0[mrt] = &colorBuffer.unknown10;
  unknown25f0[mrt] = colorBuffer.unknown38;
  unknown25ac++;
}

void CGLibSystemContext::setRegisterDepthTarget(CGLibDepthBuffer &depthBuffer) { unknown2648 = depthBuffer.unknown10; }

void CGLibSystemContext::endRegisterRenderTarget() { nvnCommandBufferSetRenderTargets(unknown1070.unknown00, unknown25ac, unknown25f0, unknown25b0, unknown2648, nullptr); }

void CGLibSystemContext::setMainFrameBuffer() { unknown1110[unknown20d4].setRenderTarget(*unknown18a0.unknown120); }

void CGLibSystemContext::getGlbUniformParam(u8 *&buffer, u64 &address) {
  buffer = unknown2550 + unknown2568;
  address = unknown2548 + unknown2568;
}

void CGLibSystemContext::nextGlbUniformOfs(u32 size) {
  u32 alignedSize = size + (-size & 0xff);
  unknown2568 += alignedSize;
  unknown2574 -= alignedSize;
}

u64 CGLibSystemContext::getPixelResAreaGpuAddress(u32 offset) { return unknown25a0 + offset; }

u32 CGLibSystemContext::getPixelResAreaOffset(u32 offset) { return unknown25a8 + offset; }

} // namespace context
} // namespace grlib

template mm::mtl::PtrSingleton<grlib::context::CGLibSystemContext>::~PtrSingleton();
