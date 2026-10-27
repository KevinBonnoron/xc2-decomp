#pragma once
#include <stddef.h>

#include "types.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace ml {
class CriticalSection;
} // namespace ml

namespace grlib {

class CGLibMemPool;
class CGLibPartsMemPool;

class CGLibMemPoolAdder {
public:
  static ml::CriticalSection &getCriticalSection();

  CGLibMemPoolAdder();
  ~CGLibMemPoolAdder();
  void release();
  void setup();
  CGLibMemPool *getMemPool(const void *address);
  void addAdder(mtl::ALLOC_HANDLE handle);
  void addAdder(void *buffer, u32 size);
  void releaseAdder(mtl::ALLOC_HANDLE handle);
  void releaseAdder(void *buffer);

  CGLibPartsMemPool *unknown00; // Inferred role: first pool; original member name unknown.
  CGLibPartsMemPool *unknown08; // Inferred role: last pool; original member name unknown.
};

static_assert(offsetof(CGLibMemPoolAdder, unknown08) == 0x08, "");
static_assert(sizeof(CGLibMemPoolAdder) == 0x10, "");

} // namespace grlib
