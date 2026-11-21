#pragma once
#include "gf/data/gf_data_save.h"
#include "mm_mtl/fixstr.h"

namespace gf {

struct RealTime;

class GfDebugSave {
public:
  static bool isExist(SAVESLOT slot);
  static bool loadSavedTime(RealTime &realTime, SAVESLOT slot);
};

// Name from the game's symbol gf::GfDebugUtil::getSaveDataPath (0x71002cf75c, between GfDebugSave::loadSavedTime and the bgmvol functions).
class GfDebugUtil {
public:
  static void getSaveDataPath(mm::mtl::FixStr<256> &path);
};

} // namespace gf
