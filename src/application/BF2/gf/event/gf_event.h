#pragma once
#include "types.h"

namespace gf {

class GfEvent {
public:
  static void callChangeScenarioFlag(u32 scenarioFlag, u32 oldScenarioFlag);
};

} // namespace gf
