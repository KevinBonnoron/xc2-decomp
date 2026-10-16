#include "event/effect_manager.h"

namespace event {

EffectManager::EffectManager() : flags(0), dispFlags(0), mCurrentRes(nullptr), mOffscrID(0), mReplaceID(0) {}

void EffectManager::setStreamMode(bool isStreamMode) { setFlag(FLAG_STREAM_MODE, isStreamMode); }

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

} // namespace event
