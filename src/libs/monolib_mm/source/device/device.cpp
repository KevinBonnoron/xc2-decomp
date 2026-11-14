#include "ml/device.h"

#include "device/nx/dev_file_nx_th.h"
#include "device/nx/device_nx.h"
#include "ml/dev_base.h"
#include "ml/language_info.h"
#include "ml/lib_main.h"
#include "ml/reslist.h"
#include "ml/work_control.h"
#include "ml/work_cpu.h"
#include "ml/work_system.h"
#include "ml/work_util.h"

namespace ml {

Device::Device(const char *name, WorkObj *parent) : WorkObj(name, parent, 0x20), unknown1b0(-1), unknown370(nullptr) {}

void Device::initializeSDK(const InitParam &param) { DeviceNx::initializeSDK(param); }

void DeviceNx::finalizeSDK() { DevFileNxTh::finalizeSDK(); }

void Device::finalizeSDK() { DeviceNx::finalizeSDK(); }

void Device::createPort(const char *name) {
  Device *device = get();
  if (device != nullptr && !device->wkIsShutdown()) {
    device->createDevicePort(name);
  }
}

bool Device::isHotStartDestructed() {
  Device *device = get();
  if (!device->wkIsWaitException() && device->wkIsActive()) {
    bool result = true;
    for (reslist<WorkObj *>::Node *node = get()->wkGetChild()->begin(); node != get()->wkGetChild()->end(); node = node->getNext()) {
      result &= static_cast<DevBase *>(node->value)->_1a8 & 1;
    }
    return result;
  }
  return false;
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

void Device::create() { WorkUtil::createWork<DeviceNx>("DeviceNx", WorkControl::get(), false); }

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
#include "cache_draw.cpp"
#include "dev_clock.cpp"
#include "dev_file_job.cpp"
#include "dev_file_job_send_com.cpp"
#include "dev_file_parser.cpp"
#include "dev_font_layer.cpp"
#include "dev_graph.cpp"
#include "dev_graph_cb.cpp"
#include "dev_keyboard.cpp"
#include "dev_mouse.cpp"
#include "dev_pad.cpp"
#include "dev_pad_util.cpp"
#include "dev_touch.cpp"
#include "dev_perf.cpp"
#include "dev_setting.cpp"
#include "../scn/scn_deb_draw.cpp"
#include "dev_font.cpp"
#include "dev_file_job_read_dvd.cpp"
#include "wii_filer_common.cpp"
#include "nx/dev_clock_nx.cpp"
#include "nx/dev_font_nx.cpp"
#include "nx/dev_graph_nx.cpp"
#include "nx/dev_keyboard_nx.cpp"
#include "nx/dev_mouse_nx.cpp"
#include "nx/dev_pad_nx.cpp"
#include "nx/dev_perf_nx.cpp"
#include "nx/dev_touch_nx.cpp"
#include "nx/dev_setting_nx.cpp"
#include "nx/th_dev_file_nx.cpp"
#include "nx/dev_file_nx_th.cpp"
#include "nx/device_nx.cpp"
#include "rom_mount.cpp"
#include "nx/dev_file_util_nx.cpp"
#include "nx/file_loader.cpp"
#include "nx/dev_file_archive_nx.cpp"
#include "dev_file_th.cpp"
#include "file_handle_th.cpp"
#include "event_file_th.cpp"
#include "file_res_th.cpp"
#include "dev_file_archiver.cpp"
#include "dev_file_job_th.cpp"
#include "dev_file_accessor.cpp"
// clang-format on
