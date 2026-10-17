#pragma once
#include "types.h"

namespace ml {

class IDrDrawWorkInfo {
public:
  u8 _000[0x560 - 0x000];
  int m_loop;
  u8 _564[0x580 - 0x564];
};

static_assert(sizeof(IDrDrawWorkInfo) == 0x580, "");

} // namespace ml
