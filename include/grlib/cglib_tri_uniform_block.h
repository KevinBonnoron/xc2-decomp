#pragma once
#include <stddef.h>

#include "grlib/cglib_mem_handle.h"
#include "types.h"

namespace grlib {

class CGLibVtlMemPool;

class CGLibTriUniformBlock {
public:
  CGLibTriUniformBlock();
  ~CGLibTriUniformBlock();
  void release();
  void setup(int size);
  void setup(CGLibVtlMemPool *memPool, u32 size, u32 offset);
  int setupArray(int size, CGLibMemType &memType, u32 offset);
  void updateData();
  void updateData(u32 offset, u32 size);
  void updateOldData();
  void updateOldData(u32 offset, u32 size);
  void *getBuff();
  void *getOldBuff();
  void *getOldTriBuff();
  void *getMapping();

  void *m_mappings[3];
  u32 m_size;
  u64 m_gpuAddresses[3];
  CGLibMemType m_memType;
};

static_assert(offsetof(CGLibTriUniformBlock, m_size) == 0x18, "");
static_assert(offsetof(CGLibTriUniformBlock, m_gpuAddresses) == 0x20, "");
static_assert(offsetof(CGLibTriUniformBlock, m_memType) == 0x38, "");

} // namespace grlib
