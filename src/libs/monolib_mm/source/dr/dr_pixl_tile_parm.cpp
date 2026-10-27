#include "dr/dr_pixl_tile_parm.h"

#include "dr/dr_man.h"
#include "grlib/cglib_gpu_cache.h"

namespace ml {

DrPixlTileParm::~DrPixlTileParm() {}

void DrPixlTileParm::begin(TileType type) {
  if (unknown04[unknown00][TILE_TYPE_MAIN].unknown00) {
    if (type != TILE_TYPE_MAIN) {
      return;
    }
  } else if (!unknown04[unknown00][type].unknown00) {
    return;
  }
  grlib::CGLibGPUCache::setTiledCacheSize(unknown04[unknown00][type].unknown04, unknown04[unknown00][type].unknown08);
  grlib::CGLibGPUCache::setTiledCacheAction(GRL_TILED_CACHE_ACTION_UNKNOWN_1);
}

void DrPixlTileParm::end(TileType type) {
  if (unknown04[unknown00][TILE_TYPE_MAIN].unknown00) {
    if (type != TILE_TYPE_MAIN) {
      return;
    }
  } else if (!unknown04[unknown00][type].unknown00) {
    return;
  }
  grlib::CGLibGPUCache::setTiledCacheAction(GRL_TILED_CACHE_ACTION_UNKNOWN_3);
  grlib::CGLibGPUCache::setTiledCacheAction(GRL_TILED_CACHE_ACTION_UNKNOWN_2);
}

void DrPixlTileParm::update() { unknown00 = DrMan::get()->unknown1c60 == 0; }

} // namespace ml
