#pragma once
#include <stddef.h>

#include "mm_mtl/singleton.h"
#include "types.h"

namespace ml {

class DrPixlMemMan : public mm::mtl::PtrSingleton<DrPixlMemMan> {
public:
  u8 _008[0x434 - 0x008];
  u32 m_mem1AlphaFree;
};

static_assert(offsetof(DrPixlMemMan, m_mem1AlphaFree) == 0x434, "");

} // namespace ml
