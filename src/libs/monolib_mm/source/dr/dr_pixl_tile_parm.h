#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrPixlTileParm {
public:
  ~DrPixlTileParm();
  enum TileType {
    TILE_TYPE_MAIN,
  };

  void begin(TileType type);
  void end(TileType type);
  void update();

  struct unknown001 {
    bool unknown00; // Inferred role: tile type enabled; original member name unknown.
    u32 unknown04;  // Inferred role: tile cache width; original member name unknown.
    u32 unknown08;  // Inferred role: tile cache height; original member name unknown.
  };

  s16 unknown00;              // Inferred role: tile mode; original member name unknown.
  unknown001 unknown04[2][9]; // Inferred role: tile cache settings per mode and tile type; original member name unknown.
};

static_assert(offsetof(DrPixlTileParm, unknown00) == 0x00, "");
static_assert(offsetof(DrPixlTileParm, unknown04) == 0x04, "");
static_assert(sizeof(DrPixlTileParm) == 0xdc, "");

} // namespace ml
