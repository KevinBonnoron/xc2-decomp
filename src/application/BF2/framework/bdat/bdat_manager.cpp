#include <stddef.h>

#include "bdat.h"
#include "framework/lang_util.h"
#include "fw/fw_bdat_manager.h"
#include "mm_mtl/fixstr.h"
#include "mtl/alloc_handle.h"

namespace fw {

bool BdatManager::Impl::isMsgFile(const char *name) { return __builtin_strstr(name, "_ms.") != nullptr; }

void BdatManager::Impl::unregistBdat(const char *name) {
  int id = find(name);
  if (id >= 0) {
    unregistBdat(id);
  }
}

bool BdatManager::Impl::isExistBdat(int id) const { return infos[id].loadingData != nullptr || infos[id].data != nullptr; }

bool BdatManager::Impl::isEnableBdat(int id) const {
  if (!isExistBdat(id)) {
    return false;
  }

  return infos[id].state == STATE_ENABLE;
}

bool BdatManager::initialize() { return true; }

bool BdatManager::finalize() {
  if (impl != nullptr) {
    delete impl;
    impl = nullptr;
  }

  return true;
}

void BdatManager::setBasePath(const char *path) { get()->impl->basePath = path; }

const char *BdatManager::getLocale() { return LangUtil::getLangFolder().c_str(); }

bool BdatManager::loadBdat(int id, mtl::ALLOC_HANDLE handle, const char *path) { return get()->impl->loadBdat(id, handle, path); }

void BdatManager::reloadBdat(int id) { get()->impl->reloadBdat(id); }

void BdatManager::loadBdatFromMemory(int id, mtl::ALLOC_HANDLE handle, void *data, size_t size, const char *name) { get()->impl->loadBdatFromMemory(id, handle, data, size, name); }

void BdatManager::loadBdatFromMemory(int id, void *data) { get()->impl->loadBdatFromMemory(id, data); }

void BdatManager::unregistBdat(int id) { get()->impl->unregistBdat(id); }

void BdatManager::unregistBdat(const char *name) { get()->impl->unregistBdat(name); }

bool BdatManager::isExistBdat(int id) { return get()->impl->isExistBdat(id); }

bool BdatManager::isEnableBdat(int id) { return get()->impl->isEnableBdat(id); }

unsigned char *BdatManager::getFp(int table, int id) { return Bdat::getFP(table, id); }

} // namespace fw
