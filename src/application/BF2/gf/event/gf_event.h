#pragma once
#include "types.h"

namespace gf {

enum RELOAD_BDAT {
  RELOAD_BDAT_ALL = 1,
};

class IGfEvent {
public:
  virtual ~IGfEvent() {}
  virtual void gevReloadBdat(RELOAD_BDAT reload, u32 value);
};

class GfEvent {
public:
  static void callChangeScenarioFlag(u32 scenarioFlag, u32 oldScenarioFlag);
};

} // namespace gf
