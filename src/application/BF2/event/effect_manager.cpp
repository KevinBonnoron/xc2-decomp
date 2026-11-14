#include "event/effect_manager.h"

#include <stddef.h>

#include "event/effect_res.h"
#include "event/extend.h"
#include "event/memory_manager.h"
#include "event/res_manager.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace event {

fw::EffectPack *EffectManager::getResPack() const {
  if (unknowna0 != nullptr) {
    return unknowna0->getResPack();
  }
  return nullptr;
}

bool EffectManager::isStreamMode() const { return (unknown10 & FLAG_UNKNOWN_0) != 0; }

bool EffectManager::isOffscrMode() const { return (unknown10 & FLAG_UNKNOWN_1) != 0; }

u32 EffectManager::getOffscrID() const { return m_offscrID; }

bool EffectManager::isReplaceMode() const { return (unknown10 & FLAG_UNKNOWN_2) != 0; }

EffectManager::EffectManager() : unknown10(0), unknown14(0), unknowna0(nullptr), m_offscrID(0), unknownac(0) {}

void EffectManager::clear() {
  for (size_t i = 0; i < unknown18.size(); i++) {
    if (unknown18[i] != nullptr) {
      delete unknown18[i];
      unknown18[i] = nullptr;
    }
  }
  unknown18.clear();
  unknown10 = 0;
  unknowna0 = nullptr;
  m_offscrID = 0;
  unknownac = 0;
}

void EffectManager::load(const char *name) {
  if (searchRes(name) != nullptr) {
    return;
  }
  unknown18.push_back(new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) EffectRes(name));
}

EffectRes *EffectManager::searchRes(const char *name) {
  for (size_t i = 0; i < unknown18.size(); i++) {
    if (__builtin_strcmp(name, unknown18[i]->getName()) == 0) {
      return unknown18[i];
    }
  }
  return nullptr;
}

bool EffectManager::isLoading() const {
  for (size_t i = 0; i < unknown18.size(); i++) {
    if (unknown18[i]->isLoading()) {
      return true;
    }
  }
  return false;
}

void EffectManager::setEvent(const char *name) { unknowna0 = searchRes(name); }

void EffectManager::setStreamMode(bool isStreamMode) { setFlag(FLAG_UNKNOWN_0, isStreamMode); }

void EffectManager::loadResource(const char *name) {
  if (isStreamMode()) {
    return;
  }
  mm::mtl::Singleton<ResManager>::getPtr()->load(mm::mtl::Singleton<Extend>::getPtr()->eva(name), nullptr, false);
}

void EffectManager::setOffscrMode(bool isOffscrMode, u32 offscrID) {
  if (isOffscrMode) {
    unknown10 |= FLAG_UNKNOWN_1;
    m_offscrID = offscrID;
  } else {
    unknown10 &= ~FLAG_UNKNOWN_1;
    m_offscrID = 0;
  }
}

void EffectManager::setReplaceMode(bool isReplaceMode, u32 replaceID) {
  if (isReplaceMode) {
    unknown10 |= FLAG_UNKNOWN_2;
    unknownac = replaceID;
  } else {
    unknown10 &= ~FLAG_UNKNOWN_2;
    unknownac = 0;
  }
}

void EffectManager::setEffectDisp(bool isDisp) { setDispFlag(DISP_FLAG_UNKNOWN_0, isDisp); }

bool EffectManager::isEffectDisp() const { return (unknown14 & DISP_FLAG_UNKNOWN_0) != 0; }

void EffectManager::setEffectDisable(bool isDisable) { setDispFlag(DISP_FLAG_UNKNOWN_1, isDisable); }

bool EffectManager::isEffectDisable() const { return (unknown14 & DISP_FLAG_UNKNOWN_1) != 0; }

void EffectManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_UNKNOWN_4:
    clear();
    break;
  case MSG_TYPE_UNKNOWN_12:
    clear();
    break;
  default:
    break;
  }
}

} // namespace event
