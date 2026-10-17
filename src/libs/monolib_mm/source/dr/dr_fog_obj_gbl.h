#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrFogObjGbl {
public:
  u8 _00[0x44 - 0x00];
  f32 m_near;
  f32 m_far;
  f32 m_str;
  u8 _50[0x54 - 0x50];
  f32 m_pow;
};

static_assert(offsetof(DrFogObjGbl, m_near) == 0x44, "");
static_assert(offsetof(DrFogObjGbl, m_pow) == 0x54, "");

} // namespace ml
