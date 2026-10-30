#include "grlib/cglib_gpu_cache.h"

#include "grlib/cglib_depth_buffer.h"
#include "grlib/cglib_mem_handle.h"
#include "grlib/cglib_mem_pool_adder.h"
#include "grlib/cglib_pipeline.h"
#include "grlib/cglib_system_context.h"
#include "grlib/cglib_texture_buffer.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"
#include "nvn/nvn.h"

namespace grlib {

void CGLibGPUCache::setTiledCacheSize(u32 width, u32 height) { nvnCommandBufferSetTiledCacheTileSize(context::CGLibSystemContext::get()->unknown1070.unknown00, width, height); }

void CGLibGPUCache::setTiledCacheAction(GrlTiledCacheAction action) {
  nvnCommandBufferSetTiledCacheAction(context::CGLibSystemContext::get()->unknown1070.unknown00, static_cast<NVNtiledCacheAction>(action));
}

void CGLibGPUCache::textreInvalidate(void *buffer, u32 size) {}

void CGLibGPUCache::textreInvalidate(CGLibTextureBuffer &texture) { texture.invalidate(); }

void CGLibGPUCache::depthInvalidate(CGLibDepthBuffer &depth) { depth.invalidate(); }

void CGLibGPUCache::shadowInvalidate(CGLibDepthBuffer &depth) { depth.invalidate(); }

void CGLibGPUCache::setMemPoolMemHandle(mtl::ALLOC_HANDLE handle) { context::CGLibSystemContext::get()->unknownef8.addAdder(handle); }

void CGLibGPUCache::setMemPoolBuffer(void *buffer, u32 size) { context::CGLibSystemContext::get()->unknownef8.addAdder(buffer, size); }

void CGLibGPUCache::releaseMemPoolMemHandle(mtl::ALLOC_HANDLE handle) { context::CGLibSystemContext::get()->unknownef8.releaseAdder(handle); }

void CGLibGPUCache::releaseMemPoolBuffer(void *buffer) { context::CGLibSystemContext::get()->unknownef8.releaseAdder(buffer); }

void CGLibGPUCache::checkMemList() {
  mtl::ALLOC_HANDLE handle = CGLibMemHandle::s_hDefHandle;
  mtl::MemManager::valid(handle, true);
  handle = CGLibMemHandle::s_hPxlHandle;
  mtl::MemManager::valid(handle, true);
  handle = CGLibMemHandle::s_hVtxHandle;
  mtl::MemManager::valid(handle, true);
  handle = CGLibMemHandle::s_hUniHandle;
  mtl::MemManager::valid(handle, true);
  handle = CGLibMemHandle::s_hMemHandle;
  mtl::MemManager::valid(handle, true);
  handle = CGLibMemHandle::s_hFchHandle;
  mtl::MemManager::valid(handle, true);
  handle = CGLibMemHandle::s_hShdHandle;
  mtl::MemManager::valid(handle, true);
}

} // namespace grlib
