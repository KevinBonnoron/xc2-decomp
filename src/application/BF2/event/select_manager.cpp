#include "event/select_manager.h"

namespace event {

SelectManager::SelectManager() : unknown10(0), unknown14(0), unknown38(0), m_result(0) {}

void SelectManager::clear() {
  unknown18.clear();
  unknown38 = 0;
  m_result = 0;
  unknown10 = 0;
  unknown14 = 0;
}

void SelectManager::update() {
  if (isActive()) {
    unknown18.update();
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

int SelectManager::getResult() const { return m_result; }

bool SelectManager::isActive() const { return (unknown10 & FLAG_ACTIVE) != 0; }

} // namespace event
