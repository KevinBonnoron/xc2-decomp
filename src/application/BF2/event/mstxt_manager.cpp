#include "event/mstxt_manager.h"

#include <stddef.h>

#include "event/memory_manager.h"
#include "event/mstxt_res.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace event {

MstxtManager::MstxtManager() : m_mstxtRes(nullptr) {}

void MstxtManager::clear() {
  if (m_mstxtRes != nullptr) {
    m_mstxtRes->unregisterBdat();
    m_mstxtRes = nullptr;
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
  if (m_mstxtRes != nullptr) {
    m_mstxtRes->unregisterBdat();
    m_mstxtRes = nullptr;
  }
  m_mstxtRes = search(path);
  m_mstxtRes->registerBdat();
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

bool MstxtManager::isLoaded() const { return m_mstxtRes != nullptr ? m_mstxtRes->isLoaded() : false; }

unsigned char *MstxtManager::getFp() const { return m_mstxtRes != nullptr ? m_mstxtRes->getFp() : nullptr; }

int MstxtManager::getSeatID(const char *label) const {
  if (m_mstxtRes == nullptr) {
    return -1;
  }
  return m_mstxtRes->getSeatID(label);
}

const char *MstxtManager::getText(const char *label) const { return m_mstxtRes != nullptr ? m_mstxtRes->getText(label) : ""; }

int MstxtManager::getTop() const { return m_mstxtRes != nullptr ? m_mstxtRes->getTop() : 0; }

int MstxtManager::getCount() const { return m_mstxtRes != nullptr ? m_mstxtRes->getCount() : 0; }

void MstxtManager::OnEventProc(MSG_TYPE type) {
  if (type == MSG_TYPE_UNKNOWN_12) {
    clear();
  }
}

} // namespace event
