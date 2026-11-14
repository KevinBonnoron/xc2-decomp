#pragma once
#include "gf/data/gf_data_save.h"

namespace gf {

struct RealTime;

class GfDebugSave {
public:
  static bool isExist(SAVESLOT slot);
  static bool loadSavedTime(RealTime &realTime, SAVESLOT slot);
};

} // namespace gf
