#pragma once
#include <stddef.h>

#include "grlib/cglib_mem_pool.h"
#include "types.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace grlib {

class CGLibMemPoolList : public CGLibMemPool {
public:
  CGLibMemPoolList();
  ~CGLibMemPoolList();
  void release();
  void setupHandle(mtl::ALLOC_HANDLE handle, u32 size, u32 flags);
  int cntOffset(u32 size, u32 alignment);

  u32 unknown20; // Inferred role: used size; original member name unknown.
};

static_assert(offsetof(CGLibMemPoolList, unknown20) == 0x20, "");

} // namespace grlib
