#pragma once
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;

class GfGameParty {
public:
  static GF_OBJ_HANDLE *getHandleBlade(u32 member, int slot);
};

} // namespace gf
