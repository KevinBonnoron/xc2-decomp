#pragma once
#include <stddef.h>

#include "grlib/cglib_mem_handle.h"
#include "types.h"

namespace grlib {

class CGLibVtlMemPool;

class CGLibVtxVertex {
public:
  CGLibVtxVertex();
  ~CGLibVtxVertex();
  void release();
  void delayRelease();
  void createVertexBuff(u32 size, u32 stride);
  void createMemVertexBuff(CGLibVtlMemPool *memPool, u32 offset, u32 size, u32 stride);
  void createCopyVertexBuff(const void *data, u32 size, u32 stride);
  void resetVertexBuff(CGLibVtlMemPool *memPool, u32 offset);
  void lock(void **buffer, u32 *size);
  void unlock();
  void unlock(u32 offset, u32 size);
  void copyVertexBuff(const void *data);

  u32 m_size;
  u32 m_stride;
  u32 m_count;
  CGLibMemType m_memType;
  u64 m_gpuAddress;
};

static_assert(offsetof(CGLibVtxVertex, m_count) == 0x08, "");
static_assert(offsetof(CGLibVtxVertex, m_memType) == 0x10, "");
static_assert(offsetof(CGLibVtxVertex, m_gpuAddress) == 0x20, "");
static_assert(sizeof(CGLibVtxVertex) == 0x28, "");

} // namespace grlib
