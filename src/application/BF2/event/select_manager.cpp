#include "event/select_manager.h"

namespace event {

SelectManager::SelectManager() : flags(0), talkerType(0), selected(0), result(0) {}

void SelectManager::clear() {
  window.clear();
  selected = 0;
  result = 0;
  flags = 0;
  talkerType = 0;
}

void SelectManager::update() {
  if (isActive()) {
    window.update();
  }
}

void SelectManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_INIT:
    clear();
    break;
  case MSG_TYPE_CLEAR:
    clear();
    break;
  case MSG_TYPE_UPDATE:
    update();
    break;
  default:
    break;
  }
}

int SelectManager::getResult() const { return result; }

bool SelectManager::isActive() const { return (flags & FLAG_ACTIVE) != 0; }

} // namespace event
