#pragma once
#include <stddef.h>

#include "grlib/cglib_mem_handle.h"
#include "types.h"

namespace grlib {

class CGLibPixlCounter {
public:
  CGLibPixlCounter();
  void release();
  void beginCounter();
  void endCounter();
  void setUniformBlock(u32 index);

  u64 unknown00;          // Inferred role: gpu address; original member name unknown.
  CGLibMemType unknown08; // Inferred role: uniform buffer; original member name unknown.
};

static_assert(offsetof(CGLibPixlCounter, unknown08) == 0x08, "");
static_assert(sizeof(CGLibPixlCounter) == 0x18, "");

} // namespace grlib
