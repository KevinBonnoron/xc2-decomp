#pragma once
#include "grlib/cglib_buff_fix_alloc.h"
#include "types.h"

namespace grlib {

class CGLibBuffMemPoolTbl : public CGLibBuffFixAlloc {
public:
  CGLibBuffMemPoolTbl();
  ~CGLibBuffMemPoolTbl();
  void release();
  void createMemPoolTbl(u32 num);
};

static_assert(sizeof(CGLibBuffMemPoolTbl) == 0x28, "");

} // namespace grlib
