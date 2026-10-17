#pragma once
#include <stddef.h>

#include "grlib/cglib_mem_handle.h"
#include "types.h"

namespace grlib {

class CGLibVtxInstans {
public:
  CGLibVtxInstans();
  ~CGLibVtxInstans();
  void release();
  void createInstansBuffer(int size);
  void beginInstansBuff();
  void updateInstansBuff();
  void *getNextInstansBuff();

  u32 m_size;
  u32 m_bankSize;
  u32 m_writeOffset;
  u32 m_flushedOffset;
  u32 m_bankOffset;
  CGLibMemType m_memType;
  u64 m_gpuAddress;
};

static_assert(offsetof(CGLibVtxInstans, m_bankOffset) == 0x10, "");
static_assert(offsetof(CGLibVtxInstans, m_memType) == 0x18, "");
static_assert(offsetof(CGLibVtxInstans, m_gpuAddress) == 0x28, "");

} // namespace grlib
