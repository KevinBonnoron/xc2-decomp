#pragma once
#include "types.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

enum GrlTiledCacheAction {
  GRL_TILED_CACHE_ACTION_UNKNOWN_1 = 1,
  GRL_TILED_CACHE_ACTION_UNKNOWN_2,
  GRL_TILED_CACHE_ACTION_UNKNOWN_3,
};

namespace grlib {
class CGLibDepthBuffer;
class CGLibTextureBuffer;

class CGLibGPUCache {
public:
  static void setTiledCacheSize(u32 width, u32 height);
  static void setTiledCacheAction(GrlTiledCacheAction action);
  static void textreInvalidate(void *buffer, u32 size);
  static void textreInvalidate(CGLibTextureBuffer &texture);
  static void depthInvalidate(CGLibDepthBuffer &depth);
  static void shadowInvalidate(CGLibDepthBuffer &depth);
  static void setMemPoolMemHandle(mtl::ALLOC_HANDLE handle);
  static void setMemPoolBuffer(void *buffer, u32 size);
  static void releaseMemPoolMemHandle(mtl::ALLOC_HANDLE handle);
  static void releaseMemPoolBuffer(void *buffer);
};

} // namespace grlib
