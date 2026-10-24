#include "gf/script/gf_script_manager.h"

#include "dr/dr_man.h"
#include "framework/script/script_manager.h"
#include "gf/gf_allocator.h"
#include "mm_mtl/array.h"

namespace gf {

constexpr size_t SCRIPT_SIZE = 0x2000;
constexpr size_t LARGE_SCRIPT_SIZE = 0x100000;
constexpr size_t AI_SCRIPT_SIZE = 0x4000;
const ml::FILE_PRIO SCRIPT_FILE_PRIO = static_cast<ml::FILE_PRIO>(7);

GfScriptManager::GfScriptManager(const GfSetupParam &param) : unknown08(false) { initialize(param); }

void GfScriptManager::initialize(const GfSetupParam &) {
  fw::ScriptManager *scriptManager = fw::ScriptManager::get();
  scriptManager->createScript(SCRIPT_SLOT_FIELD_SYSTEM, getAllocator(ALLOCATOR_SCRIPT), SCRIPT_SIZE);
  scriptManager->createScript(SCRIPT_SLOT_FIELD, getAllocator(ALLOCATOR_SCRIPT), SCRIPT_SIZE);
  scriptManager->createScript(SCRIPT_SLOT_LARGE, getAllocator(ALLOCATOR_SCRIPT), LARGE_SCRIPT_SIZE);
  scriptManager->createScript(SCRIPT_SLOT_AFTER_EVENT, getAllocator(ALLOCATOR_SCRIPT), SCRIPT_SIZE);
  for (u32 slot = SCRIPT_SLOT_TUTORIAL; slot < SCRIPT_SLOT_AI; slot++) {
    scriptManager->createScript(slot, getAllocator(ALLOCATOR_SCRIPT), SCRIPT_SIZE);
  }
  for (u32 slot = SCRIPT_SLOT_AI; slot < SCRIPT_SLOT_GMK_TUTORIAL; slot++) {
    scriptManager->createScript(slot, getAllocator(ALLOCATOR_SCRIPT), AI_SCRIPT_SIZE);
  }
  scriptManager->createScript(SCRIPT_SLOT_GMK_TUTORIAL, getAllocator(ALLOCATOR_SCRIPT), SCRIPT_SIZE);
  unknown08 = true;
}

GfScriptManager::~GfScriptManager() {}

void GfScriptManager::build(const GfSetupParam &param) {
  // __LINE__ must be 59 as in the original file: its value changes the instruction order.
#line 59
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfScriptManager(param);
}

void GfScriptManager::destroy() {
  GfScriptManager *scriptManager = get();
  scriptManager->finalize();
  delete scriptManager;
}

void GfScriptManager::finalize() {
  fw::ScriptManager *scriptManager = fw::ScriptManager::get();
  scriptManager->destroyScript(SCRIPT_SLOT_GMK_TUTORIAL, true);
  for (u32 slot = SCRIPT_SLOT_AI; slot < SCRIPT_SLOT_GMK_TUTORIAL; slot++) {
    scriptManager->destroyScript(slot, true);
  }
  for (u32 slot = SCRIPT_SLOT_TUTORIAL; slot < SCRIPT_SLOT_AI; slot++) {
    scriptManager->destroyScript(slot, true);
  }
  scriptManager->destroyScript(SCRIPT_SLOT_AFTER_EVENT, true);
  scriptManager->destroyScript(SCRIPT_SLOT_LARGE, true);
  scriptManager->destroyScript(SCRIPT_SLOT_FIELD, true);
  scriptManager->destroyScript(SCRIPT_SLOT_FIELD_SYSTEM, true);
  unknown08 = false;
}

bool GfScriptManager::isInitialized() {
  GfScriptManager *scriptManager = get();
  return scriptManager != nullptr ? scriptManager->unknown08 : false;
}

void GfScriptManager::loadScript(u32 slot, const char *filename) {
  fw::ScriptManager *scriptManager = fw::ScriptManager::get();
  scriptManager->destroyScript(slot, false);
  scriptManager->loadScript(slot, filename, SCRIPT_FILE_PRIO);
}

bool GfScriptManager::isScriptLoadError(u32 slot) { return fw::ScriptManager::get()->scripts[static_cast<int>(slot)].isLoadErr(); }

void GfScriptManager::startScript(u32 slot) { fw::ScriptManager::get()->scripts[static_cast<int>(slot)].start(); }

void GfScriptManager::destroyScript(u32 slot) { fw::ScriptManager::get()->destroyScript(slot, false); }

bool GfScriptManager::isScriptWaitStart(u32 slot) {
  fw::ScriptManager *scriptManager = fw::ScriptManager::get();
  if (scriptManager->scripts[static_cast<int>(slot)].isActive()) {
    return false;
  }

  return scriptManager->isScriptLoaded(slot);
}

bool GfScriptManager::isScriptLoaded(u32 slot) { return fw::ScriptManager::get()->isScriptLoaded(slot); }

bool GfScriptManager::isScriptActive(u32 slot) { return fw::ScriptManager::get()->scripts[static_cast<int>(slot)].isActive(); }

bool GfScriptManager::isScriptFinish(u32 slot) { return fw::ScriptManager::get()->scripts[static_cast<int>(slot)].isFinish(); }

} // namespace gf
