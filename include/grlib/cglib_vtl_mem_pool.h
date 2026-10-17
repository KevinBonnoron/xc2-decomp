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

  NVNmemoryPool *m_memoryPool;
  u64 m_address;
  u32 m_size;
  u64 m_offset;
  bool m_isOwnPool;
  void *m_buffer;
};

static_assert(offsetof(CGLibVtlMemPool, m_size) == 0x10, "");
static_assert(offsetof(CGLibVtlMemPool, m_offset) == 0x18, "");
static_assert(offsetof(CGLibVtlMemPool, m_isOwnPool) == 0x20, "");
static_assert(offsetof(CGLibVtlMemPool, m_buffer) == 0x28, "");

} // namespace grlib
