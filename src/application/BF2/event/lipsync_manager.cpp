#include "event/lipsync_manager.h"

namespace event {

LipsyncManager::LipsyncManager() : flags(0), mCurrentRes(nullptr), mCsv(nullptr) {}

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
