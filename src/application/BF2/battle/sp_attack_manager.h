#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace btl {

class SpAttackManager : public mm::mtl::PtrSingleton<SpAttackManager> {
public:
  u8 _08[0x208 - 0x08];
  int procCount;
};

static_assert(offsetof(SpAttackManager, procCount) == 0x208, "");

} // namespace btl
