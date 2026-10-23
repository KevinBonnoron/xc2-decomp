#include "event/lipsync_manager.h"

#include <stddef.h>

#include "csvb/csvb_data.h"
#include "event/lipsync_res.h"
#include "event/memory_manager.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace event {

bool LipsyncManager::isActive() const { return (flags & FLAG_ACTIVE) != 0; }

f32 LipsyncManager::getVolume(f32 frame) const {
  if (!(flags & FLAG_ACTIVE))
    return 0.0f;
  int row = frame;
  if (mCsv->GetRowCount() <= row)
    row = mCsv->GetRowCount() - 1;
  return mCsv->GetFloat(row, 1);
}

LipsyncManager::LipsyncManager() : flags(0), mCurrentRes(nullptr), mCsv(nullptr) {}

void LipsyncManager::clear() {
  for (size_t i = 0; i < mResList.size(); i++) {
    if (mResList[i] != nullptr) {
      delete mResList[i];
      mResList[i] = nullptr;
    }
  }
  mResList.clear();
  mCurrentRes = nullptr;
  if (mCsv != nullptr) {
    delete mCsv;
    mCsv = nullptr;
  }
  mTarget = "";
  flags = 0;
}

void LipsyncManager::load(const char *name) {
  if (searchRes(name) != nullptr) {
    return;
  }
  mResList.push_back(new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) LipsyncRes(name));
}

LipsyncRes *LipsyncManager::searchRes(const char *name) {
  for (size_t i = 0; i < mResList.size(); i++) {
    if (__builtin_strcmp(name, mResList[i]->getName()) == 0) {
      return mResList[i];
    }
  }
  return nullptr;
}

bool LipsyncManager::isLoading() const {
  for (size_t i = 0; i < mResList.size(); i++) {
    if (mResList[i]->isLoading()) {
      return true;
    }
  }
  return false;
}

f32 LipsyncManager::getFrameMax() const {
  if (!(flags & FLAG_ACTIVE)) {
    return 0.0f;
  }
  return mCsv->GetRowCount() - 1;
}

void LipsyncManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_INIT:
    clear();
    break;
  case MSG_TYPE_CLEAR:
    clear();
    break;
  default:
    break;
  }
}

} // namespace event
