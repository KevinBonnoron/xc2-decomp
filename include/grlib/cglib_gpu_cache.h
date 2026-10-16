#pragma once
#include "types.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace grlib {

class CGLibGPUCache {
public:
  static void setMemPoolMemHandle(mtl::ALLOC_HANDLE handle);
  static void setMemPoolBuffer(void *buffer, u32 size);
  static void releaseMemPoolMemHandle(mtl::ALLOC_HANDLE handle);
  static void releaseMemPoolBuffer(void *buffer);
};

} // namespace grlib
