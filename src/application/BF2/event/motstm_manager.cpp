#include "event/motstm_manager.h"

#include "event/frame_manager.h"
#include "event/memory_manager.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace event {

MotstmManager::MotstmManager() : unknown10(), unknown14(0), unknown18("streaming 1(eva lgt hkt)") {}

void MotstmManager::create(mtl::ALLOC_HANDLE handle) {
  unknown18.create(mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), handle);
  unknown18.pause(true);
  unknown10.set(FLAG_CREATE);
  unknown10.set(FLAG_PAUSE);
}

void MotstmManager::loadStream(const char *name) {
  mm::mtl::FixStr<128> headerPath;
  headerPath.format("/event/stm/%s.motstm", name);
  mm::mtl::FixStr<128> dataPath;
  dataPath.format("/event/stm/%s.motstm_data", name);
  unknown18.loadStream(name, headerPath.c_str(), dataPath.c_str());
}

void MotstmManager::changeStream(const char *name) { unknown18.changeStream(name); }

void MotstmManager::clear() {
  unknown18.destroy();
  unknown10.clear();
}

void MotstmManager::start() {
  if (unknown10.test(FLAG_CREATE)) {
    unknown10.set(FLAG_START);
  }
}

void MotstmManager::stop() {
  if (unknown10.test(FLAG_CREATE)) {
    unknown18.stopStream();
  }
}

bool MotstmManager::isBusy() {
  if (unknown10.test(FLAG_CREATE)) {
    return unknown18.isBusy();
  }
  return false;
}

void MotstmManager::render() {
  if (unknown10.test(FLAG_CREATE) && isDisp()) {
    mm::mtl::Singleton<FrameManager>::getPtr();
  }
}

void MotstmManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_UPDATE:
    update();
    break;
  case MSG_TYPE_RENDER:
    render();
    break;
  case MSG_TYPE_CLEAR:
    clear();
    break;
  default:
    break;
  }
}

void *MotstmManager::adr(const char *path, size_t *size) { return unknown18.adr(path, size); }

void MotstmManager::free(void *adr) { unknown18.free(adr, 0); }

bool MotstmManager::isLoadingPrio(f32 prio) const { return unknown18.isLoadingPrio(prio); }

bool MotstmManager::isFailure() const { return unknown18.isFailure(); }

void MotstmManager::setDisp(bool isDisp) {
  if (isDisp) {
    unknown14 |= DISP_FLAG_DISP;
  } else {
    unknown14 &= ~DISP_FLAG_DISP;
  }
}

bool MotstmManager::isDisp() const { return (unknown14 & DISP_FLAG_DISP) != 0; }

} // namespace event
