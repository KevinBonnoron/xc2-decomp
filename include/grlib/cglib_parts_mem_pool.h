#pragma once
#include <stddef.h>

#include "grlib/cglib_mem_pool.h"
#include "types.h"

namespace grlib {

class CGLibPartsMemPool {
public:
  ~CGLibPartsMemPool();
  void addAdder(void *buffer, u32 size);

  CGLibPartsMemPool *unknown00; // Inferred role: previous pool; original member name unknown.
  CGLibPartsMemPool *unknown08; // Inferred role: next pool; original member name unknown.
  CGLibMemPool unknown10;       // Inferred role: memory pool; original member name unknown.
};

static_assert(offsetof(CGLibPartsMemPool, unknown10) == 0x10, "");
static_assert(sizeof(CGLibPartsMemPool) == 0x30, "");

} // namespace grlib
