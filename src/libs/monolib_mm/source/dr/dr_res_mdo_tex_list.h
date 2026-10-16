#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {

class DrResMdoTexList {
public:
  grlib::CGLibTextureBuffer *getTexObj(u32 index);
  const char *getTexName(u32 index);

  u8 _00[0x68 - 0x00];
  s32 m_texMax;
};

static_assert(offsetof(DrResMdoTexList, m_texMax) == 0x68, "");

} // namespace ml
