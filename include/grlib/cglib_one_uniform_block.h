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
  void beginStreamOut(u32 offset);

  void *m_mapping;
  u32 m_size;
  u64 unknown10;          // Inferred role: gpu address; original member name unknown.
  CGLibMemType unknown18; // Inferred role: mem type; original member name unknown.
};

static_assert(offsetof(CGLibOneUniformBlock, m_size) == 0x08, "");
static_assert(offsetof(CGLibOneUniformBlock, unknown10) == 0x10, "");
static_assert(offsetof(CGLibOneUniformBlock, unknown18) == 0x18, "");
static_assert(sizeof(CGLibOneUniformBlock) == 0x28, "");

} // namespace grlib
