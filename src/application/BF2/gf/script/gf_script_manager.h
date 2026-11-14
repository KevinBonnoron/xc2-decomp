#pragma once
#include <stddef.h>

#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

struct GfSetupParam;

constexpr u32 SCRIPT_SLOT_UNKNOWN_0 = 0;     // Inferred role: script slot field system; original name unknown.
constexpr u32 SCRIPT_SLOT_UNKNOWN_1 = 1;     // Inferred role: script slot field; original name unknown.
constexpr u32 SCRIPT_SLOT_UNKNOWN_2 = 2;     // Inferred role: script slot large; original name unknown.
constexpr u32 SCRIPT_SLOT_UNKNOWN_3 = 3;     // Inferred role: script slot after event; original name unknown.
constexpr u32 SCRIPT_SLOT_UNKNOWN_4 = 4;     // Inferred role: script slot tutorial; original name unknown.
constexpr u32 SCRIPT_SLOT_UNKNOWN_36 = 0x24; // Inferred role: script slot ai; original name unknown.
constexpr u32 SCRIPT_SLOT_UNKNOWN_68 = 0x44; // Inferred role: script slot gmk tutorial; original name unknown.

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

  bool unknown08; // Inferred role: initialized; original member name unknown.
};

static_assert(offsetof(GfScriptManager, unknown08) == 0x08, "");
static_assert(sizeof(GfScriptManager) == 0x10, "");

} // namespace gf
