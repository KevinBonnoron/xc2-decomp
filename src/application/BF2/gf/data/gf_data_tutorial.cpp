#include "gf/data/gf_data_tutorial.h"
#include "gf/data/gf_game_flag.h"

namespace gf {

enum {
  FLAG_UNKNOWN_50960 = 0xc710, // Inferred role: flag tutorial menu; original name unknown.
};

bool GfDataTutorial::isMenuFlag(u32 menu) { return GfGameFlag::getLocal(1, FLAG_UNKNOWN_50960 + menu) != 0; }

void GfDataTutorial::setMenuFlag(u32 menu, bool menuFlag) { GfGameFlag::setLocal(1, FLAG_UNKNOWN_50960 + menu, menuFlag); }

} // namespace gf
