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
  u32 unknown04;          // Inferred role: stride; original member name unknown.
  u32 unknown08;          // Inferred role: count; original member name unknown.
  CGLibMemType unknown10; // Inferred role: mem type; original member name unknown.
  u64 unknown20;          // Inferred role: gpu address; original member name unknown.
};

static_assert(offsetof(CGLibVtxVertex, unknown08) == 0x08, "");
static_assert(offsetof(CGLibVtxVertex, unknown10) == 0x10, "");
static_assert(offsetof(CGLibVtxVertex, unknown20) == 0x20, "");
static_assert(sizeof(CGLibVtxVertex) == 0x28, "");

} // namespace grlib
