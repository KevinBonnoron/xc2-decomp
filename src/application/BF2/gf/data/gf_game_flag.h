#pragma once
#include "mm_mtl/bitflag.h"
#include "types.h"

namespace gf {

struct GfSetupParam;

struct GameFlag {
  mm::mtl::BitFlag<65536> oneBitFlags;
};

static_assert(sizeof(GameFlag) == 0x2000, "");

class GfGameFlag {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
  static void clear();

  static u32 getLocal(u32 size, int index);
  static void setLocal(u32 size, int index, u32 value);
};

} // namespace gf
