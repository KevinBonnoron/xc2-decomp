#pragma once
#include "gf/data/gf_data_blade.h"
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
  static void addEventCallback(IGfEvent *event);
  static void removeEventCallback(IGfEvent *event);
  static void callChangeScenarioFlag(u32 scenarioFlag, u32 oldScenarioFlag);
  static void callBladeUnselect(u32 blade, bool unselect);
  static void callDebugChangeIdea(u32 type, u32 id, u32 idea, u32 value);
  static void callBladeActivate(u32 blade, ActivateType activateType, ActivateType oldActivateType);
};

} // namespace gf
