#include "event/res_manager.h"

#include "event/memory_manager.h"
#include "fw/fw_render_resource.h"
#include "gf/asset/gf_asset_manager.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace event {

ResManager::Item::Item(const char *path, IResEvent *event, bool isPackOnly, RES_RESULT_TYPE result, void *adr, size_t size, bool isPackLoaded)
    : path(path), mIsPackOnly(isPackOnly), mCallbackIndex(0), mEventCount(1), mResource(nullptr), mAdr(adr), mSize(size), mResult(result), mIsPackLoaded(isPackLoaded) {
  mEvents[0] = event;
  for (u32 i = 1; i < EVENT_COUNT; i++) {
    mEvents[i] = nullptr;
  }
}

ResManager::Item::Item() : mResource(nullptr) {}

void ResManager::Item::addRef(IResEvent *event) { mEvents[mEventCount++] = event; }

ResManager::ResManager() : flags(0), mLoadingCount(0), mLoadedCount(0) {}

void ResManager::clear() {
  for (Item **it = mItems.begin(); it != mItems.end(); it++) {
    Item *item = *it;
    if (item->mResource != nullptr) {
      if (item->mResource->getRefCount() == 1) {
        gf::GfAssetManager::get()->releaseRefResource(item->mAdr);
      }
      if (item->mResource != nullptr) {
        item->mResource->release();
        item->mResource = nullptr;
      }
    }
    delete item;
  }
  mItems.clear();
  mPackManager.clear();
  mLoadingCount = 0;
  mLoadedCount = 0;
}

void ResManager::update() {
  if (mPackManager.isLoading()) {
    mPackManager.update();
    return;
  }
  updateNormal();
}

void ResManager::updateNormal() {
  if (mItems.empty()) {
    return;
  }
  for (Item **it = mItems.begin(); it != mItems.end(); it++) {
    Item *item = *it;
    if (item->mResult == RES_RESULT_TYPE_WAIT && item->mIsPackOnly) {
      item->mResult = RES_RESULT_TYPE_LOADED;
    }
  }
  for (Item **it = mItems.begin(); it != mItems.end(); it++) {
    Item *item = *it;
    if (item->mResult == RES_RESULT_TYPE_WAIT) {
      item->mResource = fw::RenderResource::request(mm::mtl::Singleton<MemoryManager>::getPtr()->getResHandle(), item->path.c_str(), 0);
      item->mResult = RES_RESULT_TYPE_LOADING;
    }
  }
  for (Item **it = mItems.begin(); it != mItems.end(); it++) {
    Item *item = *it;
    if (item->mResult == RES_RESULT_TYPE_LOADING && item->mResource->valid()) {
      item->mAdr = item->mResource->getAssetData();
      item->mSize = item->mResource->getAssetSize();
      item->mResult = RES_RESULT_TYPE_LOADED;
    }
  }
  for (Item **it = mItems.begin(); it != mItems.end(); it++) {
    Item *item = *it;
    if (item->mResult == RES_RESULT_TYPE_LOADED) {
      item->mResult = item->mAdr != nullptr ? RES_RESULT_TYPE_SUCCESS : RES_RESULT_TYPE_FAILURE;
      mLoadingCount--;
      if (mLoadingCount < 0) {
        mLoadingCount = 0;
      }
      execCallback(item);
    }
  }
}

void ResManager::execCallback(Item *item) {
  IResEvent::PARAM param(item->mResult, item->path.c_str(), item->mAdr, item->mSize);
  for (; item->mCallbackIndex < item->mEventCount; item->mCallbackIndex++) {
    IResEvent *event = item->mEvents[item->mCallbackIndex];
    if (event != nullptr) {
      event->OnResEvent(param);
    }
  }
}

const char *ResManager::filename(const char *path) {
  const char *separator = __builtin_strrchr(path, '\\');
  if (separator != nullptr) {
    return separator + 1;
  }
  separator = __builtin_strrchr(path, '/');
  return separator != nullptr ? separator + 1 : path;
}

void ResManager::loadPack(const char *path) { mPackManager.load(mm::mtl::Singleton<MemoryManager>::getPtr()->getResHandle(), path, this); }

void ResManager::load(const char *path, IResEvent *event, bool isPackOnly) {
  Item *item = search(path);
  if (item != nullptr) {
    item->addRef(event);
    if (item->mResult < RES_RESULT_TYPE_SUCCESS) {
      return;
    }
    item->mResult = RES_RESULT_TYPE_LOADED;
  } else {
    item = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle()) Item(path, event, isPackOnly, RES_RESULT_TYPE_WAIT, nullptr, 0, false);
    mItems.push_back(item);
  }
  mLoadingCount++;
}

ResManager::Item *ResManager::search(const char *path) {
  for (Item **it = mItems.begin(); it != mItems.end(); it++) {
    if (__builtin_strstr((*it)->path.c_str(), path) != nullptr) {
      return *it;
    }
  }
  return nullptr;
}

void *ResManager::adr(const char *path, size_t *size) {
  Item *item = search(path);
  if (item == nullptr || item->mAdr == nullptr || item->mSize == 0) {
    return nullptr;
  }
  if (size != nullptr) {
    *size = item->mSize;
  }
  return item->mAdr;
}

bool ResManager::isLoading() { return mLoadingCount > 0; }

void ResManager::OnPackEvent(const PARAM &param) {
  const char *path = param.path;
  void *adr = param.adr;
  size_t size = param.size;
  Item *item = search(path);
  if (item == nullptr) {
    item = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle()) Item(path, nullptr, false, RES_RESULT_TYPE_SUCCESS, adr, size, true);
  } else if (item->mAdr == nullptr) {
    item->mResult = RES_RESULT_TYPE_LOADED;
    item->mAdr = adr;
    item->mSize = size;
    item->mIsPackLoaded = true;
    return;
  } else {
    item = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle()) Item(path, nullptr, false, RES_RESULT_TYPE_SUCCESS, adr, size, true);
  }
  mItems.push_back(item);
}

void ResManager::setDisp(bool isDisp) {
  if (isDisp) {
    flags |= FLAG_DISP;
  } else {
    flags &= ~FLAG_DISP;
  }
}

bool ResManager::isDisp() const { return (flags & FLAG_DISP) != 0; }

} // namespace event
