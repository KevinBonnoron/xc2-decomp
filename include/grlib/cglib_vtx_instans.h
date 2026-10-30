#pragma once
#include <stddef.h>

#include "grlib/cglib_mem_handle.h"
#include "types.h"

namespace grlib {

class CGLibVtxInstans_plf {
public:
  u64 getGPUAdress();

  u32 m_size;
  u32 unknown04;          // Inferred role: bank size; original member name unknown.
  u32 unknown08;          // Inferred role: write offset; original member name unknown.
  u32 unknown0c;          // Inferred role: flushed offset; original member name unknown.
  u32 unknown10;          // Inferred role: bank offset; original member name unknown.
  CGLibMemType unknown18; // Inferred role: mem type; original member name unknown.
  u64 unknown28;          // Inferred role: gpu address; original member name unknown.
};

static_assert(offsetof(CGLibVtxInstans_plf, unknown10) == 0x10, "");
static_assert(offsetof(CGLibVtxInstans_plf, unknown18) == 0x18, "");
static_assert(offsetof(CGLibVtxInstans_plf, unknown28) == 0x28, "");
static_assert(sizeof(CGLibVtxInstans_plf) == 0x30, "");

class CGLibVtxInstans : public CGLibVtxInstans_plf {
public:
  CGLibVtxInstans();
  ~CGLibVtxInstans();
  void release();
  void createInstansBuffer(int size);
  void beginInstansBuff();
  void updateInstansBuff();
  void *getNextInstansBuff();
};

static_assert(sizeof(CGLibVtxInstans) == 0x30, "");

} // namespace grlib
