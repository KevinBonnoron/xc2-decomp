#pragma once
#include "types.h"

namespace gf {

constexpr u32 SCRIPT_SLOT_FIELD = 1;
constexpr u32 SCRIPT_SLOT_AFTER_EVENT = 3;
constexpr u32 SCRIPT_SLOT_TUTORIAL = 4;

class GfScriptManager {
public:
  static void loadScript(u32 slot, const char *filename);
  static bool isScriptLoadError(u32 slot);
  static void startScript(u32 slot);
  static bool isScriptActive(u32 slot);
  static bool isScriptFinish(u32 slot);
};

} // namespace gf
