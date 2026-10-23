#include "event/mstxt_manager.h"

#include <stddef.h>

#include "event/memory_manager.h"
#include "event/mstxt_res.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace event {

MstxtManager::MstxtManager() : mCurrentRes(nullptr) {}

void MstxtManager::clear() {
  if (mCurrentRes != nullptr) {
    mCurrentRes->unregisterBdat();
    mCurrentRes = nullptr;
  }
  for (size_t i = 0; i < mResList.size(); i++) {
    if (mResList[i] != nullptr) {
      delete mResList[i];
      mResList[i] = nullptr;
    }
  }
  mResList.clear();
}

void MstxtManager::registerBdat(const char *path) {
  if (mCurrentRes != nullptr) {
    mCurrentRes->unregisterBdat();
    mCurrentRes = nullptr;
  }
  mCurrentRes = search(path);
  mCurrentRes->registerBdat();
}

void MstxtManager::load(const char *path) {
  if (search(path) != nullptr) {
    return;
  }
  mResList.push_back(new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle()) MstxtRes(path));
}

MstxtRes *MstxtManager::search(const char *path) {
  for (size_t i = 0; i < mResList.size(); i++) {
    if (__builtin_strcmp(path, mResList[i]->getPath()) == 0) {
      return mResList[i];
    }
  }
  return nullptr;
}

bool MstxtManager::isLoading() const {
  for (size_t i = 0; i < mResList.size(); i++) {
    if (mResList[i]->isLoading()) {
      return true;
    }
  }
  return false;
}

bool MstxtManager::isLoaded() const { return mCurrentRes != nullptr ? mCurrentRes->isLoaded() : false; }

unsigned char *MstxtManager::getFp() const { return mCurrentRes != nullptr ? mCurrentRes->getFp() : nullptr; }

int MstxtManager::getSeatID(const char *label) const {
  if (mCurrentRes == nullptr) {
    return -1;
  }
  return mCurrentRes->getSeatID(label);
}

const char *MstxtManager::getText(const char *label) const { return mCurrentRes != nullptr ? mCurrentRes->getText(label) : ""; }

int MstxtManager::getTop() const { return mCurrentRes != nullptr ? mCurrentRes->getTop() : 0; }

int MstxtManager::getCount() const { return mCurrentRes != nullptr ? mCurrentRes->getCount() : 0; }

void MstxtManager::OnEventProc(MSG_TYPE type) {
  if (type == MSG_TYPE_CLEAR) {
    clear();
  }
}

} // namespace event
