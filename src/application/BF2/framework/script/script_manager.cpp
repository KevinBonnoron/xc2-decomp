#include "framework/script/script_manager.h"

#include "mm_mtl/allocator.h"

void pluginRegist();

namespace fw {

IScriptEvent::~IScriptEvent() {
  if (ScriptManager::get() != nullptr) {
    ScriptManager::get()->removeEvent(this);
  }
}

void IScriptEvent::scriptEvent(ScriptEventParam &param) {}

void ScriptManager::removeEvent(IScriptEvent *event) { unknown38.remove(event); }

void ScriptManager::createScript(int type, mm::mtl::IAllocator *allocator, size_t size) {
  void *memory = allocator->allocate(size, 0x1000);
  unknown20[type].initialize(this, type, memory, size);
  unknown20[type].unknown230 = allocator;
}

void ScriptManager::notifyEvent(int type, ScriptEventParam::State state) {
  ScriptEventParam param;
  param.unknown00 = type;
  param.unknown04 = state;
  for (size_t i = 0; i < unknown38.size(); i++) {
    unknown38[i]->scriptEvent(param);
  }
}

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
