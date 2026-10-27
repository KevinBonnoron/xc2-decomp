#include "gf/game/mercenaries/gf_game_mercenaries.h"

#include "gf/data/gf_data_mercenaries.h"

namespace gf {

u32 GfGameMercenaries::getMissionFlag(u32 mission) { return GfDataMercenaries::getMissionFlag(mission); }

void GfGameMercenaries::setLevel(u32 level) {
  GfDataMercenaries::getLevel();
  if (level > GfDataMercenaries::getLevelMax()) {
    level = GfDataMercenaries::getLevelMax();
  }
  GfDataMercenaries::setLevel(level);
}

void GfGameMercenaries::addPoint(u32 point) {
  if (GfDataMercenaries::getLevel() != 0 && GfDataMercenaries::getLevel() < 5) {
    u32 current = GfDataMercenaries::getPoint();
    point += current;
    u32 limit = GfDataMercenaries::getPointLimit();
    if (point > limit) {
      point = limit;
    }
    if (point != current) {
      GfDataMercenaries::setPoint(point);
    }
  }
}

void GfGameMercenaries::setupNewGameParam() {}

} // namespace gf
