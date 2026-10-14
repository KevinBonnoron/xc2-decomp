#include "gf/data/gf_data_develop.h"
#include "gf/data/gf_game_flag.h"

namespace gf {

enum {
  FLAG_DEVELOP_POINT = 0x5,
  FLAG_DEVELOP_LEVEL = 0x27b,
};

constexpr u32 DEVELOP_POINT_MAX = 0xffff;
constexpr u32 DEVELOP_LEVEL_MIN = 1;
constexpr u32 DEVELOP_LEVEL_MAX = 5;
constexpr u32 NATION_COUNT = 8;

u32 GfDataDevelop::getPoint(u32 nation) { return GfGameFlag::getLocal(16, FLAG_DEVELOP_POINT + nation); }

void GfDataDevelop::setPoint(u32 nation, u32 point) {
  if (point > DEVELOP_POINT_MAX) {
    point = DEVELOP_POINT_MAX;
  }

  GfGameFlag::setLocal(16, FLAG_DEVELOP_POINT + nation, point);
}

void GfDataDevelop::resetPoint(u32 nation) { GfGameFlag::setLocal(16, FLAG_DEVELOP_POINT + nation, 0); }

u32 GfDataDevelop::getLevel(u32 nation) {
  if (nation < 1 || nation > NATION_COUNT) {
    return 0;
  }

  return GfGameFlag::getLocal(4, FLAG_DEVELOP_LEVEL + nation);
}

void GfDataDevelop::setLevel(u32 nation, u32 level) {
  if (level < DEVELOP_LEVEL_MIN) {
    level = DEVELOP_LEVEL_MIN;
  } else if (level > DEVELOP_LEVEL_MAX) {
    level = DEVELOP_LEVEL_MAX;
  }

  GfGameFlag::setLocal(4, FLAG_DEVELOP_LEVEL + nation, level);
}

} // namespace gf
