#pragma once
#include <stddef.h>

#include "types.h"

// Memory allocator of the SDK. The class and function names come from the imports of the game
// (_ZN2nn3mem17StandardAllocator8AllocateEmm, _ZN2nn3mem17StandardAllocator4FreeEPv); the size is the one of open-ead
// nnheaders include/nn/mem.h (https://github.com/open-ead/nnheaders). The members are unknown.

namespace nn {
namespace mem {

class StandardAllocator {
public:
  void *Allocate(size_t size, size_t alignment);
  void Free(void *address);

  u8 _00[0x48];
};

static_assert(sizeof(StandardAllocator) == 0x48, "");

} // namespace mem
} // namespace nn
