#include "gf/game/mercenaries/gf_game_mercenaries.h"

#include "gf/data/gf_data_mercenaries.h"

namespace gf {

u32 GfGameMercenaries::getMissionFlag(u32 mission) { return GfDataMercenaries::getMissionFlag(mission); }

void GfGameMercenaries::setupNewGameParam() {}

} // namespace gf
