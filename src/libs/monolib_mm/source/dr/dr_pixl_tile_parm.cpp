#include "dr/dr_pixl_tile_parm.h"

#include "dr/dr_man.h"

namespace ml {

void DrPixlTileParm::update() { unknown00 = DrMan::get()->unknown1c60 == 0; }

} // namespace ml
