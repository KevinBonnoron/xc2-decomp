#include "event/res_manager.h"

#include "event/memory_manager.h"
#include "fw/fw_render_resource.h"
#include "gf/asset/gf_asset_manager.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace event {

ResManager::Item::Item(const char *path, IResEvent *event, bool isPackOnly, RES_RESULT_TYPE result, void *adr, size_t size, bool isPackLoaded)
    : unknown00(path), unknown408(isPackOnly), unknown40c(0), unknown410(1), unknown418(nullptr), unknown420(adr), unknown428(size), unknown430(result), unknown434(isPackLoaded) {
  unknown108[0] = event;
  for (u32 i = 1; i < EVENT_COUNT; i++) {
    unknown108[i] = nullptr;
  }
}

ResManager::Item::Item() : unknown418(nullptr) {}

void ResManager::Item::addRef(IResEvent *event) { unknown108[unknown410++] = event; }

ResManager::ResManager() : unknown18(0), unknown10b8(0), unknown10bc(0) {}

void ResManager::clear() {
  for (Item **it = unknown20.begin(); it != unknown20.end(); it++) {
    Item *item = *it;
    if (item->unknown418 != nullptr) {
      if (item->unknown418->getRefCount() == 1) {
        gf::GfAssetManager::get()->releaseRefResource(item->unknown420);
      }
      if (item->unknown418 != nullptr) {
        item->unknown418->release();
        item->unknown418 = nullptr;
      }
    }
    delete item;
  }
  unknown20.clear();
  unknown1028.clear();
  unknown10b8 = 0;
  unknown10bc = 0;
}

void ResManager::update() {
  if (unknown1028.isLoading()) {
    unknown1028.update();
    return;
  }
  updateNormal();
}

void ResManager::updateNormal() {
  if (unknown20.empty()) {
    return;
  }
  for (Item **it = unknown20.begin(); it != unknown20.end(); it++) {
    Item *item = *it;
    if (item->unknown430 == RES_RESULT_TYPE_WAIT && item->unknown408) {
      item->unknown430 = RES_RESULT_TYPE_LOADED;
    }
  }
  for (Item **it = unknown20.begin(); it != unknown20.end(); it++) {
    Item *item = *it;
    if (item->unknown430 == RES_RESULT_TYPE_WAIT) {
      item->unknown418 = fw::RenderResource::request(mm::mtl::Singleton<MemoryManager>::getPtr()->getResHandle(), item->unknown00.c_str(), 0);
      item->unknown430 = RES_RESULT_TYPE_LOADING;
    }
  }
  for (Item **it = unknown20.begin(); it != unknown20.end(); it++) {
    Item *item = *it;
    if (item->unknown430 == RES_RESULT_TYPE_LOADING && item->unknown418->valid()) {
      item->unknown420 = item->unknown418->getAssetData();
      item->unknown428 = item->unknown418->getAssetSize();
      item->unknown430 = RES_RESULT_TYPE_LOADED;
    }
  }
  for (Item **it = unknown20.begin(); it != unknown20.end(); it++) {
    Item *item = *it;
    if (item->unknown430 == RES_RESULT_TYPE_LOADED) {
      item->unknown430 = item->unknown420 != nullptr ? RES_RESULT_TYPE_SUCCESS : RES_RESULT_TYPE_FAILURE;
      unknown10b8--;
      if (unknown10b8 < 0) {
        unknown10b8 = 0;
      }
      execCallback(item);
    }
  }
}

void ResManager::execCallback(Item *item) {
  IResEvent::PARAM param(item->unknown430, item->unknown00.c_str(), item->unknown420, item->unknown428);
  for (; item->unknown40c < item->unknown410; item->unknown40c++) {
    IResEvent *event = item->unknown108[item->unknown40c];
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

void ResManager::loadPack(const char *path) { unknown1028.load(mm::mtl::Singleton<MemoryManager>::getPtr()->getResHandle(), path, this); }

void ResManager::load(const char *path, IResEvent *event, bool isPackOnly) {
  Item *item = search(path);
  if (item != nullptr) {
    item->addRef(event);
    if (item->unknown430 < RES_RESULT_TYPE_SUCCESS) {
      return;
    }
    item->unknown430 = RES_RESULT_TYPE_LOADED;
  } else {
    item = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle()) Item(path, event, isPackOnly, RES_RESULT_TYPE_WAIT, nullptr, 0, false);
    unknown20.push_back(item);
  }
  unknown10b8++;
}

ResManager::Item *ResManager::search(const char *path) {
  for (Item **it = unknown20.begin(); it != unknown20.end(); it++) {
    if (__builtin_strstr((*it)->unknown00.c_str(), path) != nullptr) {
      return *it;
    }
  }
  return nullptr;
}

void *ResManager::adr(const char *path, size_t *size) {
  Item *item = search(path);
  if (item == nullptr || item->unknown420 == nullptr || item->unknown428 == 0) {
    return nullptr;
  }
  if (size != nullptr) {
    *size = item->unknown428;
  }
  return item->unknown420;
}

bool ResManager::isLoading() { return unknown10b8 > 0; }

void ResManager::OnPackEvent(const PARAM &param) {
  const char *path = param.path;
  void *adr = param.adr;
  size_t size = param.size;
  Item *item = search(path);
  if (item == nullptr) {
    item = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle()) Item(path, nullptr, false, RES_RESULT_TYPE_SUCCESS, adr, size, true);
  } else if (item->unknown420 == nullptr) {
    item->unknown430 = RES_RESULT_TYPE_LOADED;
    item->unknown420 = adr;
    item->unknown428 = size;
    item->unknown434 = true;
    return;
  } else {
    item = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle()) Item(path, nullptr, false, RES_RESULT_TYPE_SUCCESS, adr, size, true);
  }
  unknown20.push_back(item);
}

void ResManager::setDisp(bool isDisp) {
  if (isDisp) {
    unknown18 |= FLAG_DISP;
  } else {
    unknown18 &= ~FLAG_DISP;
  }
}

bool ResManager::isDisp() const { return (unknown18 & FLAG_DISP) != 0; }

} // namespace event
