#pragma once
#include <stddef.h>

#include "grlib/cglib_mem_pool.h"
#include "types.h"

namespace grlib {

class CGLibPartsMemPool;

// Inferred role: link of a CGLibPartsMemPool in the list of CGLibMemPoolAdder; original type name unknown. The
// constructor (0x71007aeebc) clears both links before the CGLibMemPool member, as a base class constructor does.
struct unknown090 {
  unknown090() : unknown00(nullptr), unknown08(nullptr) {}

  CGLibPartsMemPool *unknown00; // Inferred role: previous pool; original member name unknown.
  CGLibPartsMemPool *unknown08; // Inferred role: next pool; original member name unknown.
};

class CGLibPartsMemPool : public unknown090 {
public:
  CGLibPartsMemPool();
  ~CGLibPartsMemPool();
  void addAdder(void *buffer, u32 size);

  CGLibMemPool unknown10; // Inferred role: memory pool; original member name unknown.
};

static_assert(offsetof(CGLibPartsMemPool, unknown08) == 0x08, "");
static_assert(offsetof(CGLibPartsMemPool, unknown10) == 0x10, "");
static_assert(sizeof(CGLibPartsMemPool) == 0x30, "");

} // namespace grlib
