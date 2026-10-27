#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {
class DrResMdoPos;

class DrResMdoPosAddList {
public:
  static int createBuffSize();
  int setupBuff(u8 *buffer);
  void release();
  void begin();
  DrResMdoPos *createAdd();

  DrResMdoPos *unknown00; // Inferred role: positions; original member name unknown.
  s32 unknown08;          // Inferred role: used count; original member name unknown.
};

static_assert(offsetof(DrResMdoPosAddList, unknown08) == 0x08, "");

} // namespace ml
