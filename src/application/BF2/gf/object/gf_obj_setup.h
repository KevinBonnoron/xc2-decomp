#pragma once
#include "types.h"
#include <stddef.h>

namespace gf {

class GfObjSetup {
public:
  u8 _00[0x14 - 0x00];
  int partyMember;
  u8 _18[0x54 - 0x18];
  bool hasFixedBlade;
  u8 _55[0x58 - 0x55];
  u32 fixedBlade;
};

static_assert(offsetof(GfObjSetup, partyMember) == 0x14, "");
static_assert(offsetof(GfObjSetup, hasFixedBlade) == 0x54, "");
static_assert(offsetof(GfObjSetup, fixedBlade) == 0x58, "");

} // namespace gf
