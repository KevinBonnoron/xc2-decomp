#include "event/offscr_manager.h"

namespace event {

OffscrManager::OffscrManager() {
  for (u32 i = 0; i < SCREEN_COUNT; i++) {
    unknown10[i] = nullptr;
  }
}

bool OffscrManager::isScreenExist(u32 screenID) const { return unknown10[screenID] != nullptr; }

void OffscrManager::OnEventProc(MSG_TYPE type) {
  if (type == MSG_TYPE_CLEAR) {
    clear();
  }
}

} // namespace event
