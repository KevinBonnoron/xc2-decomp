#pragma once
#include <stddef.h>

#include "grlib/cglib_mem_handle.h"
#include "types.h"

namespace grlib {

class CGLibVtxStmOut {
public:
  CGLibVtxStmOut();
  ~CGLibVtxStmOut();
  void release();
  int getStreamOutWorkSize();
  void createWorkBuff(int size);
  int getSize();
  void *getBuff();
  void *getMapping();
  void begin(int stride);
  void end(u32 count);
  void setUniformBlock(u32 index);
  void setUniformBlock(u32 index, u32 offset, u32 size);
  void setStorageBuffer(u32 index);
  void setStorageBuffer(u32 index, u32 offset, u32 size);

  int unknown00; // Inferred role: written size; original member name unknown.
  int m_size;
  int unknown08;          // Inferred role: stride; original member name unknown.
  CGLibMemType unknown10; // Inferred role: mem type; original member name unknown.
  u64 unknown20;          // Inferred role: gpu address; original member name unknown.
};

static_assert(offsetof(CGLibVtxStmOut, unknown08) == 0x08, "");
static_assert(offsetof(CGLibVtxStmOut, unknown10) == 0x10, "");
static_assert(offsetof(CGLibVtxStmOut, unknown20) == 0x20, "");
static_assert(sizeof(CGLibVtxStmOut) == 0x28, "");

} // namespace grlib
