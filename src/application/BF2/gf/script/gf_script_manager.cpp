#include "gf/script/gf_script_manager.h"

#include "dr/dr_man.h"
#include "framework/script/script_manager.h"
#include "gf/gf_allocator.h"
#include "mm_mtl/array.h"

namespace gf {

constexpr size_t SIZE_UNKNOWN_8192 = 0x2000;                             // Inferred role: script size; original name unknown.
constexpr size_t SIZE_UNKNOWN_1048576 = 0x100000;                        // Inferred role: large script size; original name unknown.
constexpr size_t SIZE_UNKNOWN_16384 = 0x4000;                            // Inferred role: ai script size; original name unknown.
const ml::FILE_PRIO FILE_PRIO_UNKNOWN_7 = static_cast<ml::FILE_PRIO>(7); // Inferred role: script file prio; original name unknown.

GfScriptManager::GfScriptManager(const GfSetupParam &param) : unknown08(false) { initialize(param); }

void GfScriptManager::initialize(const GfSetupParam &) {
  fw::ScriptManager *scriptManager = fw::ScriptManager::get();
  scriptManager->createScript(SCRIPT_SLOT_UNKNOWN_0, getAllocator(ALLOCATOR_UNKNOWN_2), SIZE_UNKNOWN_8192);
  scriptManager->createScript(SCRIPT_SLOT_UNKNOWN_1, getAllocator(ALLOCATOR_UNKNOWN_2), SIZE_UNKNOWN_8192);
  scriptManager->createScript(SCRIPT_SLOT_UNKNOWN_2, getAllocator(ALLOCATOR_UNKNOWN_2), SIZE_UNKNOWN_1048576);
  scriptManager->createScript(SCRIPT_SLOT_UNKNOWN_3, getAllocator(ALLOCATOR_UNKNOWN_2), SIZE_UNKNOWN_8192);
  for (u32 slot = SCRIPT_SLOT_UNKNOWN_4; slot < SCRIPT_SLOT_UNKNOWN_36; slot++) {
    scriptManager->createScript(slot, getAllocator(ALLOCATOR_UNKNOWN_2), SIZE_UNKNOWN_8192);
  }
  for (u32 slot = SCRIPT_SLOT_UNKNOWN_36; slot < SCRIPT_SLOT_UNKNOWN_68; slot++) {
    scriptManager->createScript(slot, getAllocator(ALLOCATOR_UNKNOWN_2), SIZE_UNKNOWN_16384);
  }
  scriptManager->createScript(SCRIPT_SLOT_UNKNOWN_68, getAllocator(ALLOCATOR_UNKNOWN_2), SIZE_UNKNOWN_8192);
  unknown08 = true;
}

GfScriptManager::~GfScriptManager() {}

void GfScriptManager::build(const GfSetupParam &param) {
  // __LINE__ must be 59 as in the original file: its value changes the instruction order.
#line 59
  new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfScriptManager(param);
}

void GfScriptManager::destroy() {
  GfScriptManager *scriptManager = get();
  scriptManager->finalize();
  delete scriptManager;
}

void GfScriptManager::finalize() {
  fw::ScriptManager *scriptManager = fw::ScriptManager::get();
  scriptManager->destroyScript(SCRIPT_SLOT_UNKNOWN_68, true);
  for (u32 slot = SCRIPT_SLOT_UNKNOWN_36; slot < SCRIPT_SLOT_UNKNOWN_68; slot++) {
    scriptManager->destroyScript(slot, true);
  }
  for (u32 slot = SCRIPT_SLOT_UNKNOWN_4; slot < SCRIPT_SLOT_UNKNOWN_36; slot++) {
    scriptManager->destroyScript(slot, true);
  }
  scriptManager->destroyScript(SCRIPT_SLOT_UNKNOWN_3, true);
  scriptManager->destroyScript(SCRIPT_SLOT_UNKNOWN_2, true);
  scriptManager->destroyScript(SCRIPT_SLOT_UNKNOWN_1, true);
  scriptManager->destroyScript(SCRIPT_SLOT_UNKNOWN_0, true);
  unknown08 = false;
}

bool GfScriptManager::isInitialized() {
  GfScriptManager *scriptManager = get();
  return scriptManager != nullptr ? scriptManager->unknown08 : false;
}

void GfScriptManager::loadScript(u32 slot, const char *filename) {
  fw::ScriptManager *scriptManager = fw::ScriptManager::get();
  scriptManager->destroyScript(slot, false);
  scriptManager->loadScript(slot, filename, FILE_PRIO_UNKNOWN_7);
}

bool GfScriptManager::isScriptLoadError(u32 slot) { return fw::ScriptManager::get()->unknown20[static_cast<int>(slot)].isLoadErr(); }

void GfScriptManager::startScript(u32 slot) { fw::ScriptManager::get()->unknown20[static_cast<int>(slot)].start(); }

void GfScriptManager::destroyScript(u32 slot) { fw::ScriptManager::get()->destroyScript(slot, false); }

bool GfScriptManager::isScriptWaitStart(u32 slot) {
  fw::ScriptManager *scriptManager = fw::ScriptManager::get();
  if (scriptManager->unknown20[static_cast<int>(slot)].isActive()) {
    return false;
  }

  return scriptManager->isScriptLoaded(slot);
}

bool GfScriptManager::isScriptLoaded(u32 slot) { return fw::ScriptManager::get()->isScriptLoaded(slot); }

bool GfScriptManager::isScriptActive(u32 slot) { return fw::ScriptManager::get()->unknown20[static_cast<int>(slot)].isActive(); }

bool GfScriptManager::isScriptFinish(u32 slot) { return fw::ScriptManager::get()->unknown20[static_cast<int>(slot)].isFinish(); }

} // namespace gf
