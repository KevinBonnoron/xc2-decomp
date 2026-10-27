#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrPixlTileParm {
public:
  enum TileType {
    TILE_TYPE_MAIN,
  };

  void begin(TileType type);
  void end(TileType type);
  void update();

  u16 unknown00; // Inferred role: tile mode; original member name unknown.
};

static_assert(offsetof(DrPixlTileParm, unknown00) == 0x00, "");

} // namespace ml
