#include "framework/script/script_manager.h"

void pluginRegist();

namespace fw {

bool ScriptManager::initialize() {
  if (!isInitialized()) {
    pluginRegist();
  }

  return true;
}

bool ScriptManager::isScriptCreated(int type) const { return scripts[type].vm != nullptr; }

bool ScriptManager::isScriptLoaded(int type) const { return scripts[type].isLoaded(); }

bool ScriptManager::isScriptFree(int type) const {
  if (!scripts[type].isEmpty()) {
    return false;
  }

  return scripts[type].isFinish();
}

u32 ScriptManager::getTypeMax() const { return scripts.size(); }

} // namespace fw
