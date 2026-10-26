#include "event/lipsync_manager.h"

#include <stddef.h>

#include "csvb/csvb_data.h"
#include "event/lipsync_res.h"
#include "event/memory_manager.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace event {

bool LipsyncManager::isActive() const { return (unknown10 & FLAG_ACTIVE) != 0; }

f32 LipsyncManager::getVolume(f32 frame) const {
  if (!(unknown10 & FLAG_ACTIVE))
    return 0.0f;
  int row = frame;
  if (unknownf0->GetRowCount() <= row)
    row = unknownf0->GetRowCount() - 1;
  return unknownf0->GetFloat(row, 1);
}

LipsyncManager::LipsyncManager() : unknown10(0), unknown60(nullptr), unknownf0(nullptr) {}

void LipsyncManager::clear() {
  for (size_t i = 0; i < unknown18.size(); i++) {
    if (unknown18[i] != nullptr) {
      delete unknown18[i];
      unknown18[i] = nullptr;
    }
  }
  unknown18.clear();
  unknown60 = nullptr;
  if (unknownf0 != nullptr) {
    delete unknownf0;
    unknownf0 = nullptr;
  }
  unknown68 = "";
  unknown10 = 0;
}

void LipsyncManager::load(const char *name) {
  if (searchRes(name) != nullptr) {
    return;
  }
  unknown18.push_back(new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) LipsyncRes(name));
}

LipsyncRes *LipsyncManager::searchRes(const char *name) {
  for (size_t i = 0; i < unknown18.size(); i++) {
    if (__builtin_strcmp(name, unknown18[i]->getName()) == 0) {
      return unknown18[i];
    }
  }
  return nullptr;
}

bool LipsyncManager::isLoading() const {
  for (size_t i = 0; i < unknown18.size(); i++) {
    if (unknown18[i]->isLoading()) {
      return true;
    }
  }
  return false;
}

f32 LipsyncManager::getFrameMax() const {
  if (!(unknown10 & FLAG_ACTIVE)) {
    return 0.0f;
  }
  return unknownf0->GetRowCount() - 1;
}

void LipsyncManager::setEvent(const char *name) {
  LipsyncRes *res = nullptr;
  for (size_t i = 0; i < unknown18.size(); i++) {
    if (__builtin_strcmp(name, unknown18[i]->getName()) == 0) {
      res = unknown18[i];
      break;
    }
  }
  unknown60 = res;
  setFlag(FLAG_EVENT, unknown60 != nullptr);
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
