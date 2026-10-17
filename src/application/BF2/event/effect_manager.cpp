#include "event/effect_manager.h"

#include <stddef.h>

#include "event/extend.h"
#include "event/memory_manager.h"
#include "event/res_manager.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace event {

bool EffectManager::isStreamMode() const { return (flags & FLAG_STREAM_MODE) != 0; }

bool EffectManager::isOffscrMode() const { return (flags & FLAG_OFFSCR_MODE) != 0; }

u32 EffectManager::getOffscrID() const { return mOffscrID; }

bool EffectManager::isReplaceMode() const { return (flags & FLAG_REPLACE_MODE) != 0; }

EffectManager::EffectManager() : flags(0), dispFlags(0), mCurrentRes(nullptr), mOffscrID(0), mReplaceID(0) {}

void EffectManager::clear() {
  for (size_t i = 0; i < mResList.size(); i++) {
    if (mResList[i] != nullptr) {
      delete mResList[i];
      mResList[i] = nullptr;
    }
  }
  mResList.clear();
  flags = 0;
  mCurrentRes = nullptr;
  mOffscrID = 0;
  mReplaceID = 0;
}

void EffectManager::load(const char *name) {
  if (searchRes(name) != nullptr) {
    return;
  }
  mResList.push_back(new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) EffectRes(name));
}

EffectRes *EffectManager::searchRes(const char *name) {
  for (size_t i = 0; i < mResList.size(); i++) {
    if (__builtin_strcmp(name, mResList[i]->getName()) == 0) {
      return mResList[i];
    }
  }
  return nullptr;
}

bool EffectManager::isLoading() const {
  for (size_t i = 0; i < mResList.size(); i++) {
    if (mResList[i]->isLoading()) {
      return true;
    }
  }
  return false;
}

void EffectManager::setEvent(const char *name) { mCurrentRes = searchRes(name); }

void EffectManager::setStreamMode(bool isStreamMode) { setFlag(FLAG_STREAM_MODE, isStreamMode); }

void EffectManager::loadResource(const char *name) {
  if (isStreamMode()) {
    return;
  }
  mm::mtl::Singleton<ResManager>::getPtr()->load(mm::mtl::Singleton<Extend>::getPtr()->eva(name), nullptr, false);
}

void EffectManager::setOffscrMode(bool isOffscrMode, u32 offscrID) {
  if (isOffscrMode) {
    flags |= FLAG_OFFSCR_MODE;
    mOffscrID = offscrID;
  } else {
    flags &= ~FLAG_OFFSCR_MODE;
    mOffscrID = 0;
  }
}

void EffectManager::setReplaceMode(bool isReplaceMode, u32 replaceID) {
  if (isReplaceMode) {
    flags |= FLAG_REPLACE_MODE;
    mReplaceID = replaceID;
  } else {
    flags &= ~FLAG_REPLACE_MODE;
    mReplaceID = 0;
  }
}

void EffectManager::setEffectDisp(bool isDisp) { setDispFlag(DISP_FLAG_EFFECT, isDisp); }

bool EffectManager::isEffectDisp() const { return (dispFlags & DISP_FLAG_EFFECT) != 0; }

void EffectManager::setEffectDisable(bool isDisable) { setDispFlag(DISP_FLAG_DISABLE, isDisable); }

bool EffectManager::isEffectDisable() const { return (dispFlags & DISP_FLAG_DISABLE) != 0; }

void EffectManager::OnEventProc(MSG_TYPE type) {
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
