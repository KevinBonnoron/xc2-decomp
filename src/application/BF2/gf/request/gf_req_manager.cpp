#include "gf/request/gf_req_manager.h"

namespace gf {

bool GfReqManager::isInitialized() {
  GfReqManager *manager = get();
  if (manager != nullptr) {
    return manager->unknown1848;
  }
  return false;
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

fw::UpdateInfo *GfReqManager::getUpdateInfo() { return &get()->unknown08; }

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfReqManager>::~PtrSingleton();
