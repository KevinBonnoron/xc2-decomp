#include "event/select_manager.h"

namespace event {

SelectManager::SelectManager() : flags(0), mTalkerType(0), mSelected(0), mResult(0) {}

void SelectManager::update() {
  if (isActive()) {
    mWindow.update();
  }
}

int SelectManager::getResult() const { return mResult; }

bool SelectManager::isActive() const { return (flags & FLAG_ACTIVE) != 0; }

} // namespace event
