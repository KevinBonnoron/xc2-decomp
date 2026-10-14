#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace gf {

struct GF_OBJ_HANDLE;

class GfGamePlayerFormation : public mm::mtl::PtrSingleton<GfGamePlayerFormation> {
public:
  struct Player {
    u32 followIndex;
    GF_OBJ_HANDLE *handle;
    u8 _10[0x18 - 0x10];
  };

  u8 _08[0x1a0 - 0x08];
  Player players[6];
};

static_assert(offsetof(GfGamePlayerFormation, players) == 0x1a0, "");

} // namespace gf
