#pragma once
#include <stddef.h>

#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

struct GfSetupParam;

constexpr u32 SCRIPT_SLOT_FIELD_SYSTEM = 0;
constexpr u32 SCRIPT_SLOT_FIELD = 1;
constexpr u32 SCRIPT_SLOT_LARGE = 2;
constexpr u32 SCRIPT_SLOT_AFTER_EVENT = 3;
constexpr u32 SCRIPT_SLOT_TUTORIAL = 4;
constexpr u32 SCRIPT_SLOT_AI = 0x24;
constexpr u32 SCRIPT_SLOT_GMK_TUTORIAL = 0x44;

class GfScriptManager : public mm::mtl::PtrSingleton<GfScriptManager> {
public:
  GfScriptManager(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfScriptManager();
  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  static bool isInitialized();
  static void loadScript(u32 slot, const char *filename);
  static bool isScriptLoadError(u32 slot);
  static void startScript(u32 slot);
  static void destroyScript(u32 slot);
  static bool isScriptWaitStart(u32 slot);
  static bool isScriptLoaded(u32 slot);
  static bool isScriptActive(u32 slot);
  static bool isScriptFinish(u32 slot);

  bool initialized;
};

static_assert(offsetof(GfScriptManager, initialized) == 0x08, "");
static_assert(sizeof(GfScriptManager) == 0x10, "");

} // namespace gf
