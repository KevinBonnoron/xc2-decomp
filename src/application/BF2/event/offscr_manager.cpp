#include "event/offscr_manager.h"

namespace event {

OffscrManager::OffscrManager() {
  for (u32 i = 0; i < SCREEN_COUNT; i++) {
    mScreens[i] = nullptr;
  }
}

bool OffscrManager::isScreenExist(u32 screenID) const { return mScreens[screenID] != nullptr; }

void OffscrManager::OnEventProc(MSG_TYPE type) {
  if (type == MSG_TYPE_CLEAR) {
    clear();
  }
}

} // namespace event
