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
  u32 unknown04;          // Inferred role: write offset; original member name unknown.
  u32 unknown08;          // Inferred role: flushed offset; original member name unknown.
  u64 unknown10;          // Inferred role: gpu address; original member name unknown.
  CGLibMemType unknown18; // Inferred role: mem type; original member name unknown.
};

static_assert(offsetof(CGLibVtxOneInstans, unknown08) == 0x08, "");
static_assert(offsetof(CGLibVtxOneInstans, unknown10) == 0x10, "");
static_assert(offsetof(CGLibVtxOneInstans, unknown18) == 0x18, "");

} // namespace grlib
