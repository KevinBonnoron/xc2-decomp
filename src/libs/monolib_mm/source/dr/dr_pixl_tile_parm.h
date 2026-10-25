#pragma once

namespace ml {

class DrPixlTileParm {
public:
  enum TileType {
    TILE_TYPE_MAIN,
  };

  void begin(TileType type);
  void end(TileType type);
};

} // namespace ml
