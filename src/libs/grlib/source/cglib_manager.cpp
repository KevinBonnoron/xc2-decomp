#include "grlib/cglib_manager.h"

#include "grlib/cglib_gpu_time_stamp.h"
#include "grlib/cglib_mem_handle.h"
#include "grlib/cglib_system_context.h"

namespace grlib {

CGLibManager::CGLibManager() : unknown5028(nullptr) { s_nReleaseOk = false; }

CGLibManager::~CGLibManager() {
  if (unknown5028 != nullptr) {
    delete unknown5028;
    unknown5028 = nullptr;
  }
  s_nReleaseOk = true;
}

bool CGLibManager::deviceRelease() {
  bool result = true;
  if (unknown5028 != nullptr) {
    result = unknown5028->cleanup();
    if (unknown5028 != nullptr) {
      delete unknown5028;
      unknown5028 = nullptr;
    }
    CGLibDeviceObj::release();
    CGLibMemHandle::release();
  }
  s_nReleaseOk = true;
  return result;
}

void CGLibManager::isRelease() {
  if (unknown5028 != nullptr) {
    unknown5028->isRelease();
  }
}

bool CGLibManager::isReleaseOk() { return s_nReleaseOk; }

void CGLibManager::end() { unknown5028->end(); }

void CGLibManager::swap() { swapChain(); }

void CGLibManager::tail() {}

s64 CGLibManager::getGpuTimeStamp() const { return unknown5028->unknown24d8.unknown00; }

} // namespace grlib
