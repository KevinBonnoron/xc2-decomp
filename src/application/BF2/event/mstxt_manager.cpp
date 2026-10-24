#include "event/mstxt_manager.h"

#include <stddef.h>

#include "event/memory_manager.h"
#include "event/mstxt_res.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace event {

MstxtManager::MstxtManager() : unknown98(nullptr) {}

void MstxtManager::clear() {
  if (unknown98 != nullptr) {
    unknown98->unregisterBdat();
    unknown98 = nullptr;
  }
  for (size_t i = 0; i < unknown10.size(); i++) {
    if (unknown10[i] != nullptr) {
      delete unknown10[i];
      unknown10[i] = nullptr;
    }
  }
  unknown10.clear();
}

void MstxtManager::registerBdat(const char *path) {
  if (unknown98 != nullptr) {
    unknown98->unregisterBdat();
    unknown98 = nullptr;
  }
  unknown98 = search(path);
  unknown98->registerBdat();
}

void MstxtManager::load(const char *path) {
  if (search(path) != nullptr) {
    return;
  }
  unknown10.push_back(new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle()) MstxtRes(path));
}

MstxtRes *MstxtManager::search(const char *path) {
  for (size_t i = 0; i < unknown10.size(); i++) {
    if (__builtin_strcmp(path, unknown10[i]->getPath()) == 0) {
      return unknown10[i];
    }
  }
  return nullptr;
}

bool MstxtManager::isLoading() const {
  for (size_t i = 0; i < unknown10.size(); i++) {
    if (unknown10[i]->isLoading()) {
      return true;
    }
  }
  return false;
}

bool MstxtManager::isLoaded() const { return unknown98 != nullptr ? unknown98->isLoaded() : false; }

unsigned char *MstxtManager::getFp() const { return unknown98 != nullptr ? unknown98->getFp() : nullptr; }

int MstxtManager::getSeatID(const char *label) const {
  if (unknown98 == nullptr) {
    return -1;
  }
  return unknown98->getSeatID(label);
}

const char *MstxtManager::getText(const char *label) const { return unknown98 != nullptr ? unknown98->getText(label) : ""; }

int MstxtManager::getTop() const { return unknown98 != nullptr ? unknown98->getTop() : 0; }

int MstxtManager::getCount() const { return unknown98 != nullptr ? unknown98->getCount() : 0; }

void MstxtManager::OnEventProc(MSG_TYPE type) {
  if (type == MSG_TYPE_CLEAR) {
    clear();
  }
}

} // namespace event
