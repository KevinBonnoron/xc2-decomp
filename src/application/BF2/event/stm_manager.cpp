#include "event/stm_manager.h"

#include "event/stm_pack_memory.h"
#include "mtl/alloc_handle.h"
#include <float.h>

namespace event {

StmManager::StmManager(const char *name) : unknown08(0), unknown0c(name), unknown50(nullptr) {}

StmManager::~StmManager() {
  if (unknown50 != nullptr) {
    delete unknown50;
    unknown50 = nullptr;
  }
}

void StmManager::create(mtl::ALLOC_HANDLE handle, mtl::ALLOC_HANDLE memoryHandle) { unknown50 = new (handle) StmPackMemory(memoryHandle); }

void StmManager::destroy() {
  if (unknown50 != nullptr) {
    delete unknown50;
    unknown50 = nullptr;
  }
  unknown08 = 0;
}

void StmManager::loadStream(const char *name, const char *headerPath, const char *dataPath) { unknown50->loadStream(name, headerPath, dataPath); }

void StmManager::changeStream(const char *name) { unknown50->changeStream(name); }

void StmManager::stopStream() {
  if (unknown50 != nullptr) {
    unknown50->stopStream();
  }
}

bool StmManager::isBusy() {
  if (unknown50 != nullptr) {
    return unknown50->isBusy();
  }
  return false;
}

void StmManager::update() {
  if (!(unknown08 & FLAG_PAUSE) && unknown50 != nullptr) {
    unknown50->update();
  }
}

void StmManager::render(int x, f32 frame) {}

void StmManager::tail() {
  if (!(unknown08 & FLAG_PAUSE) && unknown50 != nullptr) {
    unknown50->tail();
  }
}

void StmManager::pause(bool isPause) {
  if (isPause) {
    unknown08 |= FLAG_PAUSE;
  } else {
    unknown08 &= ~FLAG_PAUSE;
  }
}

void *StmManager::adr(const char *path, size_t *size) { return unknown50 != nullptr ? unknown50->adr(path, size) : nullptr; }

void StmManager::free(void *adr, int frame) {
  if (unknown50 != nullptr) {
    unknown50->free(adr, frame);
  }
}

bool StmManager::isLoadingPrio(f32 prio) const { return unknown50 != nullptr ? unknown50->isLoadingPrio(prio) : false; }

bool StmManager::isLoadingAll() const { return unknown50 != nullptr ? unknown50->isLoadingPrio(FLT_MAX) : false; }

bool StmManager::isFailure() const { return unknown50 != nullptr ? unknown50->isFailure() : false; }

} // namespace event
