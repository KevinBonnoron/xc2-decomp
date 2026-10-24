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
  void setUniformBlock(u32 index);

  void *unknown00[3]; // Inferred role: mappings; original member name unknown.
  u32 m_size;
  u64 unknown20[3];       // Inferred role: gpu addresses; original member name unknown.
  CGLibMemType unknown38; // Inferred role: mem type; original member name unknown.
};

static_assert(offsetof(CGLibTriUniformBlock, m_size) == 0x18, "");
static_assert(offsetof(CGLibTriUniformBlock, unknown20) == 0x20, "");
static_assert(offsetof(CGLibTriUniformBlock, unknown38) == 0x38, "");

} // namespace grlib
