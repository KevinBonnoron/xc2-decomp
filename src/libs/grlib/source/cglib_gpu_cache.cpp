#include "grlib/cglib_gpu_cache.h"

#include "grlib/cglib_depth_buffer.h"
#include "grlib/cglib_pipeline.h"
#include "grlib/cglib_system_context.h"
#include "grlib/cglib_texture_buffer.h"
#include "nvn/nvn.h"

namespace grlib {

void CGLibGPUCache::setTiledCacheSize(u32 width, u32 height) { nvnCommandBufferSetTiledCacheTileSize(context::CGLibSystemContext::get()->m_pipeline.m_cmdBuf, width, height); }

void CGLibGPUCache::setTiledCacheAction(GrlTiledCacheAction action) {
  nvnCommandBufferSetTiledCacheAction(context::CGLibSystemContext::get()->m_pipeline.m_cmdBuf, static_cast<NVNtiledCacheAction>(action));
}

void CGLibGPUCache::textreInvalidate(void *buffer, u32 size) {}

void CGLibGPUCache::textreInvalidate(CGLibTextureBuffer &texture) { texture.invalidate(); }

void CGLibGPUCache::depthInvalidate(CGLibDepthBuffer &depth) { depth.invalidate(); }

void CGLibGPUCache::shadowInvalidate(CGLibDepthBuffer &depth) { depth.invalidate(); }

} // namespace grlib
