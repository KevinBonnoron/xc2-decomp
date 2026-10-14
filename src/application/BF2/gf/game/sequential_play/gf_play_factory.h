#pragma once
#include "types.h"

namespace gf {

class GfSequentialPlaySignal;

enum MAINMENU {
  MAINMENU_TOP,
  MAINMENU_SYSTEM,
  MAINMENU_SKIP_TRAVEL,
};

class GfPlayFactory {
public:
  static void createOpenMenu2(u32 type, MAINMENU menu, GfSequentialPlaySignal *signal);
  static void createMenuQuestList();
  static void createHoodHomuraBattou();
};

} // namespace gf
