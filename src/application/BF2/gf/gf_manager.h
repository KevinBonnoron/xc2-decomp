#pragma once
#include "types.h"

namespace gf {

struct GfSetupParam {
  u8 _00[0x20 - 0x00];
  f32 globalSpeed;
  u8 _24[0x28 - 0x24];
};

static_assert(sizeof(GfSetupParam) == 0x28, "");

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
