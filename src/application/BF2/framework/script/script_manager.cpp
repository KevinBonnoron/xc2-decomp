#include "framework/script/script_manager.h"

#include "ml/path_util.h"
#include "mm_mtl/allocator.h"
#include "mm_mtl/str_util.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

#include "plugin/plugin_regist.h"

extern "C" void vmExec();

namespace fw {

mm::mtl::FixStr<256> ScriptManager::m_rootPath;

ScriptManager::ScriptManager(mm::mtl::IAllocator *allocator, size_t count) : unknown20(allocator) { unknown20.reserve(count); }

ScriptManager::~ScriptManager() { finalize(); }

IScriptEvent::IScriptEvent() {
  if (ScriptManager::get() != nullptr) {
    ScriptManager::get()->addEvent(this);
  }
}

void ScriptManager::addEvent(IScriptEvent *event) {
  if (unknown38.find(event) == unknown38.end()) {
    unknown38.push(event);
  }
}

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

void ScriptManager::setScriptPath(const char *path) {
  m_rootPath = path;
  // The game (1.0.0: 0x710019e1c4, `ldurb w8, [x19, #-1]`) tests the byte before the buffer, not the last character; the index -1 is what
  // it computes, indexing with length() - 1 loads m_nLen first and gives 51 instructions instead of 50.
  if (m_rootPath[-1] != '/') {
    m_rootPath += "/";
  }
}

// 1.0.0: 0x710019e240. The root path followed by the file name without directory and extension, with ".sb" added when it holds no dot, lower-cased
// by mm::mtl::unknown002. getNoExtName<FixStr<256>> is the standalone instance 0x710019e430 of this unit.
void ScriptManager::makeFullPath(mm::mtl::FixStr<256> &path, const char *name) {
  mm::mtl::FixStr<256> noExt;
  mm::mtl::FixStr<256> file;
  ml::PathUtil::getNoExtName(noExt, name);
  file = ml::PathUtil::getNoPathExtName(noExt.c_str()).c_str();
  if (file.unknown004('.') == -1) {
    file += ".sb";
  }
  path.format("%s%s", m_rootPath.c_str(), file.c_str());
  mm::mtl::unknown002(path);
}

void ScriptManager::loadScript(int type, const char *name, ml::FILE_PRIO priority) {
  mm::mtl::FixStr<256> path;
  makeFullPath(path, name);
  unknown20[type].load(path, priority);
}

void ScriptManager::loadScriptFromMemory(int type, const char *name, const char *data, size_t size) {
  mm::mtl::FixStr<256> path;
  makeFullPath(path, name);
  unknown20[type].loadFromMemory(path, data, size);
}

} // namespace fw
