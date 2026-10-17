#pragma once
#include <stddef.h>

#include "grlib/cglib_mem_handle.h"
#include "types.h"

namespace grlib {

class CGLibVtxOneInstans {
public:
  CGLibVtxOneInstans();
  ~CGLibVtxOneInstans();
  void release();
  void createInstansBuffer(int size);
  void beginInstansBuff();
  void updateInstansBuff();
  void *getNextInstansBuff();
  void *getBuff();

  u32 m_size;
  u32 m_writeOffset;
  u32 m_flushedOffset;
  u64 m_gpuAddress;
  CGLibMemType m_memType;
};

static_assert(offsetof(CGLibVtxOneInstans, m_flushedOffset) == 0x08, "");
static_assert(offsetof(CGLibVtxOneInstans, m_gpuAddress) == 0x10, "");
static_assert(offsetof(CGLibVtxOneInstans, m_memType) == 0x18, "");

} // namespace grlib
