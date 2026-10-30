#include "grlib/cglib_system_context.h"

#include "grlib/cglib_color_buffer.h"
#include "grlib/cglib_depth_buffer.h"
#include "grlib/cglib_manager.h"
#include "grlib/cglib_mem_handle.h"
#include "grlib/cglib_mem_pool.h"
#include "grlib/cglib_release_obj.h"
#include "ml/critical_section.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"
#include "nvn/nvn.h"

namespace grlib {
class CGLibBuffResSamObj;

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

void CGLibSystemContext::createUniformBuffer() {
  unknown2570 = 0x700000;
  unknown2558[0] = static_cast<u32>(unknown10.cntOffset(0x700000, 0x100));
  unknown2558[1] = static_cast<u32>(unknown10.cntOffset(unknown2570, 0x100));
  unknown2550 = static_cast<u8 *>(unknown10.unknown18);
  unknown2548 = nvnMemoryPoolGetBufferAddress(unknown10.m_memoryPool);
  unknown2568 = 0;
  unknown2578 = static_cast<u32>(unknown10.cntOffset(0x80000, 0x1000));
}

void CGLibSystemContext::end() {
  unknown24d8.end();
  unknown268[CGLibManager::s_nDblNowIdx].end();
  unknown268[CGLibManager::s_nDblNowIdx].call();
  unknown88[CGLibManager::s_nDblNowIdx].end();
  unknown1070.unknown00 = nullptr;
  unknown08 = nullptr;
  unknown20d9 = false;
}

void CGLibSystemContext::setMainFrameBuffer() { unknown1110[unknown20d4].setRenderTarget(*unknown18a0.unknown120); }

void CGLibSystemContext::releaseDelayMempool(NVNmemoryPool *pool, void *buffer) {
  ml::CS lock(getCriticalSection());
  CGLibReleaseObj *obj = unknowneb8.createObj();
  obj->unknown00.unknown18 = 3;
  obj->unknown00.unknown1a = 0;
  obj->unknown00.unknown00 = pool;
  obj->unknown00.unknown08 = buffer;
}

void CGLibSystemContext::releaseDelayTexture(NVNtexture *texture, void *buffer, int textureId, int samplerId) {
  ml::CS lock(getCriticalSection());
  CGLibReleaseObj *obj = unknowneb8.createObj();
  obj->unknown00.unknown18 = 1;
  obj->unknown00.unknown1a = 1;
  if (texture != nullptr) {
    obj->unknown00.unknown18 = 5;
    obj->unknown00.unknown00 = texture;
  }
  obj->unknown00.unknown08 = buffer;
  obj->unknown00.unknown10 = textureId;
  obj->unknown00.unknown14 = samplerId;
}

void CGLibSystemContext::releaseDelaySampler(CGLibBuffResSamObj *sampler) {
  ml::CS lock(getCriticalSection());
  CGLibReleaseObj *obj = unknowneb8.createObj();
  obj->unknown00.unknown00 = sampler;
  obj->unknown00.unknown18 = 1;
  obj->unknown00.unknown1a = 2;
}

void CGLibSystemContext::releaseDelayVertex(CGLibMemType &memType) {
  if (memType.unknown08 != CGLibMemType::TYPE_EXTERNAL) {
    ml::CS lock(getCriticalSection());
    CGLibReleaseObj *obj = unknowneb8.createObj();
    reinterpret_cast<CGLibMemType &>(obj->unknown00) = memType;
    obj->unknown00.unknown18 = 1;
    obj->unknown00.unknown1a = 3;
  }
  memType.m_buffer = nullptr;
  memType.unknown08 = CGLibMemType::TYPE_EXTERNAL;
}

void CGLibSystemContext::getUniformoGpuAddress(u64 &address, const CGLibMemType &memType) {
  if (memType.unknown08 == CGLibMemType::TYPE_UNKNOWN_6) {
    u64 offset = reinterpret_cast<u64>(memType.m_buffer) - reinterpret_cast<u64>(unknown24b8.unknown18);
    address = offset + nvnMemoryPoolGetBufferAddress(unknown24b8.m_memoryPool);
  } else {
    CGLibMemPool &memPool = unknownf08[memType.unknown08].unknown28;
    u64 offset = reinterpret_cast<u64>(memType.m_buffer) - reinterpret_cast<u64>(memPool.unknown18);
    address = offset + nvnMemoryPoolGetBufferAddress(memPool.m_memoryPool);
  }
}

void CGLibSystemContext::getVertexGpuAddress(u64 &address, const CGLibMemType &memType) {
  if (memType.unknown08 == CGLibMemType::TYPE_UNKNOWN_6) {
    u64 offset = reinterpret_cast<u64>(memType.m_buffer) - reinterpret_cast<u64>(unknown2498.unknown18);
    address = offset + nvnMemoryPoolGetBufferAddress(unknown2498.m_memoryPool);
  } else {
    CGLibMemPool &memPool = unknownf08[memType.unknown08].unknown28;
    u64 offset = reinterpret_cast<u64>(memType.m_buffer) - reinterpret_cast<u64>(memPool.unknown18);
    address = offset + nvnMemoryPoolGetBufferAddress(memPool.m_memoryPool);
  }
}

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
