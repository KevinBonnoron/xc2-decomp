#pragma once
#include <stddef.h>

#include "types.h"

// Memory allocator of the SDK. The class and function names come from the imports of the game
// (_ZN2nn3mem17StandardAllocator8AllocateEmm, _ZN2nn3mem17StandardAllocator4FreeEPv); the size, mIsInitialized and
// the destructor are the ones of open-ead nnheaders include/nn/mem.h (https://github.com/open-ead/nnheaders). The other
// members are unknown.

namespace nn {
namespace mem {

class StandardAllocator {
public:
  ~StandardAllocator() {
    if (mIsInitialized) {
      Finalize();
    }
  }

  void Initialize(void *address, size_t size);
  void Finalize();
  void *Allocate(size_t size);
  void *Allocate(size_t size, size_t alignment);
  void Free(void *address);

  bool mIsInitialized;
  u8 _01[0x48 - 0x01];
};

static_assert(sizeof(StandardAllocator) == 0x48, "");

} // namespace mem
} // namespace nn
