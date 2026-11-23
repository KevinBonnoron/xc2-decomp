#include "event/stm_manager.h"

#include "event/stm_pack_memory.h"
#include "mtl/alloc_handle.h"
#include <float.h>

namespace event {

StmManager::StmManager(const char *name) : unknown08(0), unknown0c(name), m_stmPackMemory(nullptr) {}

StmManager::~StmManager() {
  if (m_stmPackMemory != nullptr) {
    delete m_stmPackMemory;
    m_stmPackMemory = nullptr;
  }
}

void StmManager::create(mtl::ALLOC_HANDLE handle, mtl::ALLOC_HANDLE memoryHandle) { m_stmPackMemory = new (handle) StmPackMemory(memoryHandle); }

void StmManager::destroy() {
  if (m_stmPackMemory != nullptr) {
    delete m_stmPackMemory;
    m_stmPackMemory = nullptr;
  }
  unknown08 = 0;
}

void StmManager::loadStream(const char *name, const char *headerPath, const char *dataPath) { m_stmPackMemory->loadStream(name, headerPath, dataPath); }

void StmManager::changeStream(const char *name) { m_stmPackMemory->changeStream(name); }

void StmManager::stopStream() {
  if (m_stmPackMemory != nullptr) {
    m_stmPackMemory->stopStream();
  }
}

bool StmManager::isBusy() {
  if (m_stmPackMemory != nullptr) {
    return m_stmPackMemory->isBusy();
  }
  return false;
}

void StmManager::update() {
  if (!(unknown08 & FLAG_UNKNOWN_0) && m_stmPackMemory != nullptr) {
    m_stmPackMemory->update();
  }
}

void StmManager::render(int x, f32 frame) {}

void StmManager::tail() {
  if (!(unknown08 & FLAG_UNKNOWN_0) && m_stmPackMemory != nullptr) {
    m_stmPackMemory->tail();
  }
}

void StmManager::pause(bool isPause) {
  if (isPause) {
    unknown08 |= FLAG_UNKNOWN_0;
  } else {
    unknown08 &= ~FLAG_UNKNOWN_0;
  }
}

void *StmManager::adr(const char *path, size_t *size) { return m_stmPackMemory != nullptr ? m_stmPackMemory->adr(path, size) : nullptr; }

void StmManager::free(void *adr, int frame) {
  if (m_stmPackMemory != nullptr) {
    m_stmPackMemory->free(adr, frame);
  }
}

bool StmManager::isLoadingPrio(f32 prio) const { return m_stmPackMemory != nullptr ? m_stmPackMemory->isLoadingPrio(prio) : false; }

bool StmManager::isLoadingAll() const { return m_stmPackMemory != nullptr ? m_stmPackMemory->isLoadingPrio(FLT_MAX) : false; }

bool StmManager::isFailure() const { return m_stmPackMemory != nullptr ? m_stmPackMemory->isFailure() : false; }

} // namespace event
