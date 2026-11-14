#include "framework/script/script_manager.h"

#include "ml/dev_file_th.h"
#include "mm_mtl/fixstr.h"
#include "types.h"
#include "vm/vm.h"

namespace fw {

ScriptInfo::ScriptInfo() : unknown08(nullptr), unknown10(0), unknown21c(-1), unknown220(nullptr), unknown228(STATE_UNKNOWN_0), unknown22c(0), unknown230(nullptr), unknown238(nullptr) {}

ScriptInfo::~ScriptInfo() {
  if ((unknown22c & FLAG_UNKNOWN_3) != 0 && unknown08 != nullptr) {
    unlink();
  } else if (unknown220 != nullptr) {
    ml::DevFileTh::cancel(unknown220, false);
    unknown220 = nullptr;
  }

  clear();
}

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
  unknown228 = STATE_UNKNOWN_0;
  unknown22c = 0;
  unknown220 = nullptr;
}

void ScriptInfo::unlink() {
  if ((unknown22c & FLAG_UNKNOWN_3) != 0 && unknown08 != nullptr) {
    unknown22c &= ~FLAG_UNKNOWN_3;
    vmUnlink(unknown08);
  }
}

void ScriptInfo::relink() {
  unlink();
  unknown22c = (unknown22c & ~(FLAG_UNKNOWN_0 | FLAG_UNKNOWN_1 | FLAG_UNKNOWN_2 | FLAG_UNKNOWN_3 | FLAG_UNKNOWN_5)) | FLAG_UNKNOWN_1;
  unknown228 = STATE_UNKNOWN_1;
}

void ScriptInfo::execute() {
  if (unknown08 == nullptr) {
    return;
  }
  if (unknown228 == STATE_UNKNOWN_1) {
    waitLoad();
  } else if (unknown228 == STATE_UNKNOWN_2) {
    update();
  }
}

void ScriptInfo::start() {
  if ((unknown22c & FLAG_UNKNOWN_2) != 0) {
    return;
  }

  u32 previousFlags = unknown22c;
  unknown22c |= FLAG_UNKNOWN_2;
  if ((previousFlags & FLAG_UNKNOWN_1) != 0) {
    execute();
  }
}

void ScriptInfo::waitLoad() {
  if ((unknown22c & (FLAG_UNKNOWN_1 | FLAG_UNKNOWN_2)) == (FLAG_UNKNOWN_1 | FLAG_UNKNOWN_2)) {
    if ((unknown22c & FLAG_UNKNOWN_3) == 0 && vmLink(unknown08) != 0) {
      vmStart(unknown08);
      unknown22c |= FLAG_UNKNOWN_3 | FLAG_UNKNOWN_6;
      if (unknown238 != nullptr) {
        unknown238->notifyEvent(unknown21c, static_cast<ScriptEventParam::State>(2));
      }
    }

    unknown228 = STATE_UNKNOWN_2;
  }
}

void ScriptInfo::update() {
  if (vmThreadIsFinish(unknown08) == 0) {
    return;
  }

  unknown22c &= ~FLAG_UNKNOWN_6;
  unknown228 = STATE_UNKNOWN_3;
  if (unknown238 != nullptr) {
    unknown238->notifyEvent(unknown21c, static_cast<ScriptEventParam::State>(STATE_UNKNOWN_3));
  }
}

bool ScriptInfo::isLoaded() const { return (unknown22c & FLAG_UNKNOWN_1) != 0; }

bool ScriptInfo::isLoading() const { return (unknown22c & FLAG_UNKNOWN_0) != 0; }

bool ScriptInfo::isLoadErr() const { return (unknown22c & FLAG_UNKNOWN_5) != 0; }

void ScriptInfo::sleep() {
  if ((unknown22c & FLAG_UNKNOWN_6) != 0 && unknown08 != nullptr) {
    vmThreadSleepAll(unknown08);
  }
}

void ScriptInfo::wakeup() {
  if ((unknown22c & FLAG_UNKNOWN_6) != 0 && unknown08 != nullptr) {
    vmThreadWakeupAll(unknown08);
  }
}

bool ScriptInfo::isFinish() const { return unknown228 == STATE_UNKNOWN_3; }

bool ScriptInfo::isEmpty() const { return unknown228 == STATE_UNKNOWN_0; }

bool ScriptInfo::isActive() const { return (unknown22c & FLAG_UNKNOWN_6) != 0; }

} // namespace fw
