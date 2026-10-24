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
  void setUniformBlock(u32 index);
  void setStorageBuffer(u32 index);

  void *unknown00[2]; // Inferred role: mappings; original member name unknown.
  u32 m_size;
  u64 unknown18[2];       // Inferred role: gpu addresses; original member name unknown.
  CGLibMemType unknown28; // Inferred role: mem type; original member name unknown.
};

static_assert(offsetof(CGLibDblUniformBlock, m_size) == 0x10, "");
static_assert(offsetof(CGLibDblUniformBlock, unknown18) == 0x18, "");
static_assert(offsetof(CGLibDblUniformBlock, unknown28) == 0x28, "");

} // namespace grlib
