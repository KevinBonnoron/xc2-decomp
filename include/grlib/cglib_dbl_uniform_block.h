#pragma once
#include <stddef.h>

#include "grlib/cglib_mem_handle.h"
#include "types.h"

namespace grlib {

class CGLibVtlMemPool;

class CGLibDblUniformBlock {
public:
  CGLibDblUniformBlock();
  ~CGLibDblUniformBlock();
  void release();
  void setup(int size);
  void setup(CGLibVtlMemPool *memPool, u32 size, u32 offset);
  int setupArray(int size, CGLibMemType &memType, u32 offset);
  void updateData();
  void updateData(u32 offset, u32 size);
  void *getBuff();
  void *getOldBuff();
  void *getMapping();

  void *m_mappings[2];
  u32 m_size;
  u64 m_gpuAddresses[2];
  CGLibMemType m_memType;
};

static_assert(offsetof(CGLibDblUniformBlock, m_size) == 0x10, "");
static_assert(offsetof(CGLibDblUniformBlock, m_gpuAddresses) == 0x18, "");
static_assert(offsetof(CGLibDblUniformBlock, m_memType) == 0x28, "");

} // namespace grlib
