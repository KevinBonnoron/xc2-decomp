#include "event/motstm_manager.h"

#include "event/frame_manager.h"
#include "event/memory_manager.h"
#include "event/skip_manager.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace event {

MotstmManager::MotstmManager() : unknown10(), unknown14(0), unknown18("streaming 1(eva lgt hkt)") {}

void MotstmManager::create(mtl::ALLOC_HANDLE handle) {
  unknown18.create(mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), handle);
  unknown18.pause(true);
  unknown10.set(FLAG_UNKNOWN_0);
  unknown10.set(FLAG_UNKNOWN_2);
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
  if (unknown10.test(FLAG_UNKNOWN_0)) {
    unknown10.set(FLAG_UNKNOWN_1);
  }
}

void MotstmManager::stop() {
  if (unknown10.test(FLAG_UNKNOWN_0)) {
    unknown18.stopStream();
  }
}

bool MotstmManager::isBusy() {
  if (unknown10.test(FLAG_UNKNOWN_0)) {
    return unknown18.isBusy();
  }
  return false;
}

void MotstmManager::update() {
  if (!mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast() && unknown10.test(FLAG_UNKNOWN_0)) {
    bool isPause = !unknown10.test(FLAG_UNKNOWN_1);
    if (unknown10.test(FLAG_UNKNOWN_2) != isPause) {
      unknown18.pause(isPause);
      unknown10.set(FLAG_UNKNOWN_2, isPause);
    }
    unknown18.update();
    unknown18.tail();
  }
}

void MotstmManager::render() {
  if (unknown10.test(FLAG_UNKNOWN_0) && isDisp()) {
    mm::mtl::Singleton<FrameManager>::getPtr();
  }
}

void MotstmManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_UNKNOWN_14:
    update();
    break;
  case MSG_TYPE_UNKNOWN_16:
    render();
    break;
  case MSG_TYPE_UNKNOWN_12:
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
    unknown14 |= DISP_FLAG_UNKNOWN_0;
  } else {
    unknown14 &= ~DISP_FLAG_UNKNOWN_0;
  }
}

bool MotstmManager::isDisp() const { return (unknown14 & DISP_FLAG_UNKNOWN_0) != 0; }

} // namespace event
