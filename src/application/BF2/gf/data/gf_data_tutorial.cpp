#include "gf/data/gf_data_tutorial.h"
#include "gf/data/gf_game_flag.h"

namespace gf {

enum {
  FLAG_TUTORIAL_MENU = 0xc710,
};

bool GfDataTutorial::isMenuFlag(u32 menu) { return GfGameFlag::getLocal(1, FLAG_TUTORIAL_MENU + menu) != 0; }

void GfDataTutorial::setMenuFlag(u32 menu, bool menuFlag) { GfGameFlag::setLocal(1, FLAG_TUTORIAL_MENU + menu, menuFlag); }

} // namespace gf
