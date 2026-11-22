#include "gf/request/gf_req_manager.h"

#include "gf/gf_allocator.h"
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

GfReqManager::GfReqManager(const GfSetupParam &param) : unknown18(reinterpret_cast<ml::MLTHG *>(-1)), unknown20(-1), m_reqSmallCom(nullptr), unknown1840(false), unknown1848(false) {
  initialize(param);
}

void GfReqManager::initialize(const GfSetupParam &) {
  unknown18 = ml::MicroThread::get()->createGroup();
  unknown20 = ml::MicroThread::get()->createThread(unknown18, fnReqUpdate, this);
#line 93
  m_reqSmallCom = new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfReqSmallCom();
  unknown1848 = true;
}

GfReqManager::~GfReqManager() {}

void GfReqManager::build(const GfSetupParam &param) {
#line 53
  new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfReqManager(param);
}

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
  if (m_reqSmallCom != nullptr) {
    delete m_reqSmallCom;
    m_reqSmallCom = nullptr;
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
  m_updateInfo = info;
  ml::MicroThread::get()->update(unknown18);
  m_reqSmallCom->update(info);
}

void GfReqManager::reqUpdate() {
  while (true) {
    if (unknown28.empty()) {
      if (GfManager::isDestroyNow()) {
        return;
      }
    } else {
      unknown001 &request = unknown28.front();
      request.unknown08(request.m_reqParam);
      if (request.m_reqParam != nullptr) {
        delete request.m_reqParam;
        request.m_reqParam = nullptr;
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
    request.m_reqParam = param;
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

fw::UpdateInfo *GfReqManager::getUpdateInfo() { return &get()->m_updateInfo; }

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
