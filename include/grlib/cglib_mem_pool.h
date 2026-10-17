#pragma once
#include "types.h"

struct NVNmemoryPool;

namespace grlib {

class CGLibMemPool {
public:
  void setupBuffer(void *buffer, u32 size, u32 flags);

  NVNmemoryPool *m_memoryPool;
};

} // namespace grlib
