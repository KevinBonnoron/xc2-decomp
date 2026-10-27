#include "framework/script/script_manager.h"

#include "mm_mtl/allocator.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

void pluginRegist();
extern "C" void vmExec();

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

void ScriptManager::createScript(int type, mtl::ALLOC_HANDLE handle, size_t size) {
  void *memory = mtl::MemManager::allocate(handle, size, 0x1000, false, "no name", 0);
  unknown20[type].initialize(this, type, memory, size);
}

void ScriptManager::destroyScript(int type, bool isForce) {
  unknown20[type].destroy();
  if (isForce) {
    void *memory = unknown20[type].unknown08;
    if (memory != nullptr) {
      mm::mtl::IAllocator *allocator = unknown20[type].unknown230;
      if (allocator == nullptr) {
        mtl::MemManager::deallocate(memory, 0, false);
      } else {
        allocator->deallocate(memory);
      }

      unknown20[type].unknown08 = nullptr;
    }
  }
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

void ScriptManager::update(const UpdateInfo &info) {
  if (!isFinalized()) {
    vmExec();
    for (size_t i = 0; i < unknown20.size(); i++) {
      unknown20[i].execute();
    }
  }
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
