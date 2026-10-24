#pragma once
#include <stddef.h>

#include "types.h"

struct NVNmemoryPool;

namespace grlib {

class CGLibVtlMemPool {
public:
  CGLibVtlMemPool();
  ~CGLibVtlMemPool();
  void release();
  void setupBuffer(void *buffer, u32 size);
  void delayRelease();

  NVNmemoryPool *unknown00; // Inferred role: memory pool; original member name unknown.
  u64 unknown08;            // Inferred role: address; original member name unknown.
  u32 m_size;
  u64 unknown18;  // Inferred role: offset; original member name unknown.
  bool unknown20; // Inferred role: own pool; original member name unknown.
  void *m_buffer;
};

static_assert(offsetof(CGLibVtlMemPool, m_size) == 0x10, "");
static_assert(offsetof(CGLibVtlMemPool, unknown18) == 0x18, "");
static_assert(offsetof(CGLibVtlMemPool, unknown20) == 0x20, "");
static_assert(offsetof(CGLibVtlMemPool, m_buffer) == 0x28, "");

} // namespace grlib
