#pragma once
#include <stddef.h>

#include "types.h"

struct NVNmemoryPool;

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace grlib {

class CGLibMemPool {
public:
  CGLibMemPool();
  ~CGLibMemPool();
  void release();
  void delayRelease();
  void setupHandle(mtl::ALLOC_HANDLE handle, u32 size, u32 flags);
  void setupBuffer(void *buffer, u32 size, u32 flags);

  NVNmemoryPool *m_memoryPool;
  u32 unknown08;   // Inferred role: initialized size; original member name unknown.
  void *unknown10; // Inferred role: allocated buffer; original member name unknown.
  void *unknown18; // Inferred role: storage buffer; original member name unknown.
};

static_assert(offsetof(CGLibMemPool, unknown08) == 0x08, "");
static_assert(offsetof(CGLibMemPool, unknown10) == 0x10, "");
static_assert(offsetof(CGLibMemPool, unknown18) == 0x18, "");
static_assert(sizeof(CGLibMemPool) == 0x20, "");

} // namespace grlib
