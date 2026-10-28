#include "ml/device.h"

#include "ml/language_info.h"
#include "ml/lib_main.h"
#include "ml/reslist.h"
#include "ml/work_cpu.h"
#include "ml/work_system.h"

namespace ml {

Device::Device(const char *name, WorkObj *parent) : WorkObj(name, parent, 0x20), unknown1b0(-1), unknown370(nullptr) {}

void Device::createPort(const char *name) {
  Device *device = get();
  if (device != nullptr && !device->wkIsShutdown()) {
    device->createDevicePort(name);
  }
}

u32 Device::jobUpdate(void *argument, void *userData) {
  Device *device = get();
  if (device != nullptr) {
    for (mm::mtl::FixedList<SCU, 16>::iterator it = device->unknown1b8.begin(); it != device->unknown1b8.end(); ++it) {
      it->unknown00(it->unknown08);
    }
  }
  return 0;
}

bool Device::wkStandbyLogout() {
  if (unknown60.size() != 0 || WorkSystem::get() != nullptr || LibMain::get() != nullptr) {
    return false;
  }
  WorkCpu::releaseGroupHandle(unknown1b0);
  if (unknown370 != nullptr) {
    delete unknown370;
    unknown370 = nullptr;
  }
  return WorkObj::wkStandbyLogout();
}

void Device::updateSubCpu() {
  Device *device = get();
  if (device != nullptr) {
    WorkCpu::wakeup(device->unknown1b0);
  }
}

void Device::removeSubCpuUpdate(void (*update)(void *)) {
  Device *device = get();
  for (mm::mtl::FixedList<SCU, 16>::iterator it = device->unknown1b8.begin(); it != device->unknown1b8.end(); ++it) {
    if (it->unknown00 == update) {
      device->unknown1b8.erase(it);
      return;
    }
  }
}

} // namespace ml

template mm::mtl::PtrSingleton<ml::Device>::~PtrSingleton();

// Same order as in the game executable.
// clang-format off
#include "dev_keyboard.cpp"
#include "dev_mouse.cpp"
#include "dev_pad.cpp"
#include "dev_pad_util.cpp"
#include "dev_touch.cpp"
#include "dev_perf.cpp"
#include "nx/dev_keyboard_nx.cpp"
// clang-format on
