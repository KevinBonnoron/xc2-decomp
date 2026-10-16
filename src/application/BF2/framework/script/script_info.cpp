#include "framework/script/script_manager.h"
#include "mm_mtl/fixstr.h"
#include "types.h"
#include "vm/vm.h"

namespace fw {

void ScriptInfo::initialize(ScriptManager *manager, int type, void *vm, u32 size) {
  clear();
  this->vm = vm;
  this->size = size;
  this->manager = manager;
  this->type = type;
}

void ScriptInfo::clear() {
  path.clear();
  name.clear();
  state = STATE_EMPTY;
  flags = 0;
  fileHandle = nullptr;
}

void ScriptInfo::unlink() {
  if ((flags & FLAG_LINKED) != 0 && vm != nullptr) {
    flags &= ~FLAG_LINKED;
    vmUnlink(vm);
  }
}

void ScriptInfo::relink() {
  unlink();
  flags = (flags & ~(FLAG_LOADING | FLAG_LOADED | FLAG_STARTED | FLAG_LINKED | FLAG_LOAD_ERROR)) | FLAG_LOADED;
  state = STATE_LOADED;
}

void ScriptInfo::start() {
  if ((flags & FLAG_STARTED) != 0) {
    return;
  }

  u32 previousFlags = flags;
  flags |= FLAG_STARTED;
  if ((previousFlags & FLAG_LOADED) != 0) {
    execute();
  }
}

void ScriptInfo::update() {
  if (vmThreadIsFinish(vm) == 0) {
    return;
  }

  flags &= ~FLAG_ACTIVE;
  state = STATE_FINISH;
  if (manager != nullptr) {
    manager->notifyEvent(type, static_cast<ScriptEventParam::State>(STATE_FINISH));
  }
}

bool ScriptInfo::isLoaded() const { return (flags & FLAG_LOADED) != 0; }

bool ScriptInfo::isLoading() const { return (flags & FLAG_LOADING) != 0; }

bool ScriptInfo::isLoadErr() const { return (flags & FLAG_LOAD_ERROR) != 0; }

void ScriptInfo::sleep() {
  if ((flags & FLAG_ACTIVE) != 0 && vm != nullptr) {
    vmThreadSleepAll(vm);
  }
}

void ScriptInfo::wakeup() {
  if ((flags & FLAG_ACTIVE) != 0 && vm != nullptr) {
    vmThreadWakeupAll(vm);
  }
}

bool ScriptInfo::isFinish() const { return state == STATE_FINISH; }

bool ScriptInfo::isEmpty() const { return state == STATE_EMPTY; }

bool ScriptInfo::isActive() const { return (flags & FLAG_ACTIVE) != 0; }

} // namespace fw
