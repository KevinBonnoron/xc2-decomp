#include "gf/data/gf_data_develop.h"
#include "gf/data/gf_game_flag.h"

namespace gf {

enum {
  FLAG_DEVELOP_UNKNOWN_5 = 0x5,     // Inferred role: flag develop point; original name unknown.
  FLAG_DEVELOP_UNKNOWN_635 = 0x27b, // Inferred role: flag develop level; original name unknown.
};

constexpr u32 DEVELOP_UNKNOWN_65535 = 0xffff; // Inferred role: develop point max; original name unknown.
constexpr u32 DEVELOP_UNKNOWN_1 = 1;          // Inferred role: develop level min; original name unknown.

u32 GfDataDevelop::getPoint(u32 nation) { return GfGameFlag::getLocal(16, FLAG_DEVELOP_UNKNOWN_5 + nation); }

void GfDataDevelop::setPoint(u32 nation, u32 point) {
  if (point > DEVELOP_UNKNOWN_65535) {
    point = DEVELOP_UNKNOWN_65535;
  }

  GfGameFlag::setLocal(16, FLAG_DEVELOP_UNKNOWN_5 + nation, point);
}

void GfDataDevelop::resetPoint(u32 nation) { GfGameFlag::setLocal(16, FLAG_DEVELOP_UNKNOWN_5 + nation, 0); }

u32 GfDataDevelop::getLevel(u32 nation) {
  if (nation < 1 || nation > NATION_UNKNOWN_8) {
    return 0;
  }

  return GfGameFlag::getLocal(4, FLAG_DEVELOP_UNKNOWN_635 + nation);
}

void GfDataDevelop::setLevel(u32 nation, u32 level) {
  if (level < DEVELOP_UNKNOWN_1) {
    level = DEVELOP_UNKNOWN_1;
  } else if (level > DEVELOP_LEVEL_UNKNOWN_5) {
    level = DEVELOP_LEVEL_UNKNOWN_5;
  }

  GfGameFlag::setLocal(4, FLAG_DEVELOP_UNKNOWN_635 + nation, level);
}

} // namespace gf
