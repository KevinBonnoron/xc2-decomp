#include "event/motstm_manager.h"

#include "event/memory_manager.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace event {

MotstmManager::MotstmManager() : flags(0), dispFlags(0), mStm("streaming 1(eva lgt hkt)") {}

void MotstmManager::create(mtl::ALLOC_HANDLE handle) {
  mStm.create(mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), handle);
  mStm.pause(true);
  flags |= FLAG_CREATE | FLAG_PAUSE;
}

void MotstmManager::loadStream(const char *name) {
  mm::mtl::FixStr<128> headerPath;
  headerPath.format("/event/stm/%s.motstm", name);
  mm::mtl::FixStr<128> dataPath;
  dataPath.format("/event/stm/%s.motstm_data", name);
  mStm.loadStream(name, headerPath.c_str(), dataPath.c_str());
}

void MotstmManager::changeStream(const char *name) { mStm.changeStream(name); }

void MotstmManager::clear() {
  mStm.destroy();
  flags = 0;
}

void MotstmManager::start() {
  if (flags & FLAG_CREATE) {
    flags |= FLAG_START;
  }
}

void MotstmManager::stop() {
  if (flags & FLAG_CREATE) {
    mStm.stopStream();
  }
}

bool MotstmManager::isBusy() {
  if (flags & FLAG_CREATE) {
    return mStm.isBusy();
  }
  return false;
}

void *MotstmManager::adr(const char *path, size_t *size) { return mStm.adr(path, size); }

void MotstmManager::free(void *adr) { mStm.free(adr, 0); }

bool MotstmManager::isLoadingPrio(f32 prio) const { return mStm.isLoadingPrio(prio); }

bool MotstmManager::isFailure() const { return mStm.isFailure(); }

void MotstmManager::setDisp(bool isDisp) {
  if (isDisp) {
    dispFlags |= DISP_FLAG_DISP;
  } else {
    dispFlags &= ~DISP_FLAG_DISP;
  }
}

bool MotstmManager::isDisp() const { return (dispFlags & DISP_FLAG_DISP) != 0; }

} // namespace event
