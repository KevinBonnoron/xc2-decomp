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
  void setStorageBuffer(u32 index);

  int m_writtenSize;
  int m_bufferSize;
  int m_stride;
  CGLibMemType m_memType;
  u64 m_gpuAddress;
};

static_assert(offsetof(CGLibVtxStmOut, m_stride) == 0x08, "");
static_assert(offsetof(CGLibVtxStmOut, m_memType) == 0x10, "");
static_assert(offsetof(CGLibVtxStmOut, m_gpuAddress) == 0x20, "");
static_assert(sizeof(CGLibVtxStmOut) == 0x28, "");

} // namespace grlib
