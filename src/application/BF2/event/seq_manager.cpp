#include "event/seq_manager.h"

#include "event/manager.h"

namespace event {

constexpr u32 CATEGORY_CAPTURE = 5;

bool SeqManager::checkWait3D(const SeqInfo &info) { return (Manager::get()->getPlayParam(2) | info.mLinkID) == 0; }

bool SeqManager::checkSyncBgm(const SeqInfo &info, bool isSync) {
  if (Manager::get()->isEndFadeOut() || info.mNextID == 0) {
    isSync = false;
  }
  return isSync;
}

bool SeqManager::checkCapture(const SeqInfo &info) {
  if (info.mLinkID < 1) {
    return false;
  }
  SeqInfo link(info.mLinkID);
  return link.mCategory == CATEGORY_CAPTURE;
}

void SeqManager::nextEvent(int next) { mNextEvent = next; }

void SeqManager::setDisp(bool isDisp) {
  if (isDisp) {
    dispFlags |= DISP_FLAG_DISP;
  } else {
    dispFlags &= ~DISP_FLAG_DISP;
  }
}

bool SeqManager::isDisp() const { return (dispFlags & DISP_FLAG_DISP) != 0; }

} // namespace event
