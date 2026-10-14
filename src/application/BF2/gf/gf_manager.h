#pragma once
#include "types.h"

namespace gf {

void GfSleep(u32 frame);

class GfManager {
public:
  static bool isDestroyNow();
  static bool isExecKillPartyCreate();
  static bool isExecModeScenarioGame();
  static bool isExecModeAdvertize();
  static bool isExecModeTool();
  static bool isExecModeDebug();
  static bool isExecModeThater();
  static bool isContinueGame();
  static bool isNewGame();
};

} // namespace gf
