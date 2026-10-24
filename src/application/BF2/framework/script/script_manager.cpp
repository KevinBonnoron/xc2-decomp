#include "framework/script/script_manager.h"

void pluginRegist();

namespace fw {

bool ScriptManager::initialize() {
  if (!isInitialized()) {
    pluginRegist();
  }

  return true;
}

bool ScriptManager::isScriptCreated(int type) const { return unknown20[type].unknown08 != nullptr; }

bool ScriptManager::isScriptLoaded(int type) const { return unknown20[type].isLoaded(); }

bool ScriptManager::isScriptFree(int type) const {
  if (!unknown20[type].isEmpty()) {
    return false;
  }

  return unknown20[type].isFinish();
}

u32 ScriptManager::getTypeMax() const { return unknown20.size(); }

} // namespace fw
