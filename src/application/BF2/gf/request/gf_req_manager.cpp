#include "gf/request/gf_req_manager.h"

#include "gf/gf_manager.h"
#include "gf/request/gf_req_scom.h"
#include "ml/micro_thread.h"
#include "mm_mtl/fixed_queue.h"

namespace nn {
namespace os {
struct FiberType;
} // namespace os
} // namespace nn
namespace gf {

GfReqManager::~GfReqManager() {}

void GfReqManager::destroy() {
  GfReqManager *manager = get();
  manager->finalize();
  delete manager;
}

void GfReqManager::finalize() {
  while (unknown20 != -1) {
    GfSleep(1);
  }
  if (unknown18 != reinterpret_cast<ml::MLTHG *>(-1)) {
    ml::MicroThread::get()->releaseGroup(unknown18);
    unknown18 = reinterpret_cast<ml::MLTHG *>(-1);
  }
  while (GfReqSmallCom::isExistCommand()) {
    GfSleep(1);
  }
  if (unknown1838 != nullptr) {
    delete unknown1838;
    unknown1838 = nullptr;
  }
  unknown1848 = false;
}

bool GfReqManager::isInitialized() {
  GfReqManager *manager = get();
  if (manager != nullptr) {
    return manager->unknown1848;
  }
  return false;
}

nn::os::FiberType *GfReqManager::fnReqUpdate(void *) {
  GfReqManager *manager = get();
  manager->reqUpdate();
  manager->unknown20 = -1;
  ml::MicroThread::get()->exit();
  return nullptr;
}

void GfReqManager::update(const fw::UpdateInfo &info) {
  unknown08 = info;
  ml::MicroThread::get()->update(unknown18);
  unknown1838->update(info);
}

void GfReqManager::reqUpdate() {
  while (true) {
    if (unknown28.empty()) {
      if (GfManager::isDestroyNow()) {
        return;
      }
    } else {
      unknown001 &request = unknown28.front();
      request.unknown08(request.unknown00);
      if (request.unknown00 != nullptr) {
        delete request.unknown00;
        request.unknown00 = nullptr;
      }
      unknown28.pop_front();
    }
    GfSleep(1);
  }
}

int GfReqManager::addCommand(GfReqParam *param, void (*command)(const GfReqParam *param)) {
  GfReqManager *manager = get();
  int handle;
  if (!manager->unknown1840) {
    handle = manager->getHandle();
    unknown001 request;
    request.unknown00 = param;
    request.unknown08 = command;
    request.unknown10 = handle;
    manager->unknown28.push(request);
  } else {
    if (param != nullptr) {
      delete param;
    }
    handle = -1;
  }
  return handle;
}

int GfReqManager::getHandle() {
  int handle = unknown1844 + 1;
  if (handle == -1) {
    handle = 0;
  }
  unknown1844 = handle;
  return handle;
}

void GfReqManager::terminateCommand() { get()->unknown1840 = true; }

bool GfReqManager::isExistCommand(void (*command)(const GfReqParam *param)) {
  GfReqManager *manager = get();
  if (manager == nullptr) {
    return false;
  }
  if (command == nullptr) {
    if (!manager->unknown28.empty()) {
      return true;
    }
    return GfReqSmallCom::isExistCommand();
  }
  for (mm::mtl::FixedQueue<unknown001, 256>::iterator it = manager->unknown28.begin(); it != manager->unknown28.end(); ++it) {
    if ((*it).unknown08 == command) {
      return true;
    }
  }
  return GfReqSmallCom::isExistCommand();
}

fw::UpdateInfo *GfReqManager::getUpdateInfo() { return &get()->unknown08; }

bool GfReqManager::isValid(u32 request) {
  if (request == 0xffffffff) {
    return false;
  }
  GfReqManager *manager = get();
  for (const unknown001 &queued : manager->unknown28) {
    if (queued.unknown10 == request) {
      return true;
    }
  }
  return false;
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfReqManager>::~PtrSingleton();
