#pragma once
#include <stddef.h>

#include "grlib/cglib_mem_handle.h"
#include "types.h"

namespace grlib {

class CGLibVtlMemPool;

class CGLibOneUniformBlock {
public:
  CGLibOneUniformBlock();
  ~CGLibOneUniformBlock();
  void release();
  void setup(int size);
  void setup(CGLibVtlMemPool *memPool, u32 size, u32 offset);
  int setupArray(int size, CGLibMemType &memType, u32 offset);
  void setupArray(CGLibVtlMemPool *memPool, u32 size, u32 offset);
  void updateData();
  void updateData(u32 offset, u32 size);
  void *getMapping();
  void setUniformBlock(u32 index);

  void *m_mapping;
  u32 m_size;
  u64 m_gpuAddress;
  CGLibMemType m_memType;
};

static_assert(offsetof(CGLibOneUniformBlock, m_size) == 0x08, "");
static_assert(offsetof(CGLibOneUniformBlock, m_gpuAddress) == 0x10, "");
static_assert(offsetof(CGLibOneUniformBlock, m_memType) == 0x18, "");
static_assert(sizeof(CGLibOneUniformBlock) == 0x28, "");

} // namespace grlib
