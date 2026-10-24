#include "framework/script/script_manager.h"
#include "mm_mtl/fixstr.h"
#include "types.h"
#include "vm/vm.h"

namespace fw {

void ScriptInfo::initialize(ScriptManager *manager, int type, void *vm, u32 size) {
  clear();
  this->unknown08 = vm;
  this->unknown10 = size;
  this->unknown238 = manager;
  this->unknown21c = type;
}

void ScriptInfo::clear() {
  unknown14.clear();
  unknown118.clear();
  unknown228 = STATE_EMPTY;
  unknown22c = 0;
  unknown220 = nullptr;
}

void ScriptInfo::unlink() {
  if ((unknown22c & FLAG_LINKED) != 0 && unknown08 != nullptr) {
    unknown22c &= ~FLAG_LINKED;
    vmUnlink(unknown08);
  }
}

void ScriptInfo::relink() {
  unlink();
  unknown22c = (unknown22c & ~(FLAG_LOADING | FLAG_LOADED | FLAG_STARTED | FLAG_LINKED | FLAG_LOAD_ERROR)) | FLAG_LOADED;
  unknown228 = STATE_LOADED;
}

void ScriptInfo::start() {
  if ((unknown22c & FLAG_STARTED) != 0) {
    return;
  }

  u32 previousFlags = unknown22c;
  unknown22c |= FLAG_STARTED;
  if ((previousFlags & FLAG_LOADED) != 0) {
    execute();
  }
}

void ScriptInfo::update() {
  if (vmThreadIsFinish(unknown08) == 0) {
    return;
  }

  unknown22c &= ~FLAG_ACTIVE;
  unknown228 = STATE_FINISH;
  if (unknown238 != nullptr) {
    unknown238->notifyEvent(unknown21c, static_cast<ScriptEventParam::State>(STATE_FINISH));
  }
}

bool ScriptInfo::isLoaded() const { return (unknown22c & FLAG_LOADED) != 0; }

bool ScriptInfo::isLoading() const { return (unknown22c & FLAG_LOADING) != 0; }

bool ScriptInfo::isLoadErr() const { return (unknown22c & FLAG_LOAD_ERROR) != 0; }

void ScriptInfo::sleep() {
  if ((unknown22c & FLAG_ACTIVE) != 0 && unknown08 != nullptr) {
    vmThreadSleepAll(unknown08);
  }
}

void ScriptInfo::wakeup() {
  if ((unknown22c & FLAG_ACTIVE) != 0 && unknown08 != nullptr) {
    vmThreadWakeupAll(unknown08);
  }
}

bool ScriptInfo::isFinish() const { return unknown228 == STATE_FINISH; }

bool ScriptInfo::isEmpty() const { return unknown228 == STATE_EMPTY; }

bool ScriptInfo::isActive() const { return (unknown22c & FLAG_ACTIVE) != 0; }

} // namespace fw
