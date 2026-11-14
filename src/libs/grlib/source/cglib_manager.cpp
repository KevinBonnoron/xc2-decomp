#include "grlib/cglib_manager.h"

#include "grlib/cglib_display.h"
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

void CGLibManager::begin() {
  unknown5028->unknown1110.updateSignaled();
  context::CGLibSystemContext *context = unknown5028;
  if (context->unknown1110.unknownfcb) {
    int index = s_nDblNowIdx;
    s_nDblNowIdx = index == 0;
    s_nStkNowIdx = index != 0;
    if (s_nTriNowIdx >= 2) {
      s_nTriNowIdx = 0;
    } else {
      s_nTriNowIdx = s_nTriNowIdx + 1;
    }
  }
  context->begin();
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

bool CGLibManager::isRelease() { return unknown5028 != nullptr && unknown5028->isRelease(); }

bool CGLibManager::isReleaseOk() { return s_nReleaseOk; }

void CGLibManager::end() { unknown5028->end(); }

void CGLibManager::swap() { swapChain(); }

void CGLibManager::tail() {}

s64 CGLibManager::getGpuTimeStamp() const { return unknown5028->unknown24d8.unknown00; }

} // namespace grlib
