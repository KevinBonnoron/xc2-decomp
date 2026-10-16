#include "event/stm_manager.h"

#include "event/stm_pack_memory.h"
#include "mtl/alloc_handle.h"
#include <float.h>

namespace event {

StmManager::StmManager(const char *name) : flags(0), mName(name), mMemory(nullptr) {}

StmManager::~StmManager() {
  if (mMemory != nullptr) {
    delete mMemory;
    mMemory = nullptr;
  }
}

void StmManager::create(mtl::ALLOC_HANDLE handle, mtl::ALLOC_HANDLE memoryHandle) { mMemory = new (handle) StmPackMemory(memoryHandle); }

void StmManager::destroy() {
  if (mMemory != nullptr) {
    delete mMemory;
    mMemory = nullptr;
  }
  flags = 0;
}

void StmManager::loadStream(const char *name, const char *headerPath, const char *dataPath) { mMemory->loadStream(name, headerPath, dataPath); }

void StmManager::changeStream(const char *name) { mMemory->changeStream(name); }

void StmManager::stopStream() {
  if (mMemory != nullptr) {
    mMemory->stopStream();
  }
}

bool StmManager::isBusy() {
  if (mMemory != nullptr) {
    return mMemory->isBusy();
  }
  return false;
}

void StmManager::update() {
  if (!(flags & FLAG_PAUSE) && mMemory != nullptr) {
    mMemory->update();
  }
}

void StmManager::render(int x, f32 frame) {}

void StmManager::tail() {
  if (!(flags & FLAG_PAUSE) && mMemory != nullptr) {
    mMemory->tail();
  }
}

void StmManager::pause(bool isPause) {
  if (isPause) {
    flags |= FLAG_PAUSE;
  } else {
    flags &= ~FLAG_PAUSE;
  }
}

void *StmManager::adr(const char *path, size_t *size) { return mMemory != nullptr ? mMemory->adr(path, size) : nullptr; }

void StmManager::free(void *adr, int frame) {
  if (mMemory != nullptr) {
    mMemory->free(adr, frame);
  }
}

bool StmManager::isLoadingPrio(f32 prio) const { return mMemory != nullptr ? mMemory->isLoadingPrio(prio) : false; }

bool StmManager::isLoadingAll() const { return mMemory != nullptr ? mMemory->isLoadingPrio(FLT_MAX) : false; }

bool StmManager::isFailure() const { return mMemory != nullptr ? mMemory->isFailure() : false; }

} // namespace event
