#pragma once
#include <stddef.h>

#include "grlib/cglib_buff_fix_alloc.h"
#include "grlib/cglib_mem_pool.h"
#include "types.h"

namespace grlib {

class CGLibBuffMinUniform : public CGLibBuffFixAlloc {
public:
  CGLibBuffMinUniform();
  ~CGLibBuffMinUniform();
  void release();
  void createUniform(u32 size, u32 unitSize);
  u8 *allocBuffer();

  CGLibMemPool unknown28; // Inferred role: memory pool of the buffer; original member name unknown.
};

static_assert(offsetof(CGLibBuffMinUniform, unknown28) == 0x28, "");
static_assert(sizeof(CGLibBuffMinUniform) == 0x48, "");

} // namespace grlib
